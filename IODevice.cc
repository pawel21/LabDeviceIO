#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <errno.h>
#include <typeinfo>
#include <stdlib.h>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>


class IODevice
{
public:

		void connect(const char* port);
		void send_command(const char* command);
		void read_buffor();
		std::string get_name_device();

private:
	int file_descriptor=0;
};


void IODevice::connect(const char * port) {
	this->file_descriptor = open(port, O_RDWR | O_NOCTTY);
	if (this->file_descriptor<0)
	{
		std::cout<<"No find port"<< std::endl;
	}
}

void IODevice::send_command(const char* command)
{
	write(this->file_descriptor, (char*)command, 128);
}

void IODevice::read_buffor()
{
	char buffor[128];
	read(this->file_descriptor, buffor, 128);
	std::cout<<buffor<<std::endl;
}

std::string IODevice::get_name_device()
{
    char buffor[128];
    write(this->file_descriptor, "*IDN?", 128);
	read(this->file_descriptor, buffor, 128);
	std::string name_device = std::string(buffor);
	return name_device;
}


int main()
{
    std::map<char*, std::string> available_device;
    std::vector<char*> device_port {"/dev/usbtmc0", "/dev/usbtmc1"};

    for (std::vector<char*>::iterator it = device_port.begin(); it!=device_port.end(); ++it)
        if ( boost::filesystem::exists( *it ))
        {
             std::cout << "find device port: " << *it <<  std::endl;
             IODevice *dev = new IODevice();
             dev->connect(*it);
             available_device[*it] = dev->get_name_device();
             delete dev;
        }

    for (std::map<char*, std::string>::iterator it=available_device.begin(); it!=available_device.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}