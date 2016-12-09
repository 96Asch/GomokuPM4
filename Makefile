# a simple makefile
all: huangdejong4.o huangdejonggoboard4.o huangdejongstack4.o
	g++ -Wall -o GomokuGame huangdejonggoboard4.o huangdejong4.o huangdejongstack4.o
huangdejonggoboard4.o: huangdejonggoboard4.cc huangdejonggoboard4.h
	g++ -Wall -c huangdejonggoboard4.cc
huangdejong4.o: huangdejong4.cc huangdejonggoboard4.h huangdejongstack4.h
	g++ -Wall -c huangdejong4.cc
huangdejongstack4.o: huangdejongstack4.cc huangdejongstack4.h
	g++ -Wall -c huangdejongstack4.cc
