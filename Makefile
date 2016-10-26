target: run
	./run
run: IODevice.cc
	g++ -std=c++11 -Os -Wall -pedantic IODevice.cc -lboost_system -lboost_filesystem -lboost_iostreams -o run