# a simple makefile
all: main.o goboard.o
	g++ -Wall -o GomokuGame goboard.o main.o
gobord.o: goboard.cc goboard.h
	g++ -Wall -c goboard.cc
main.o: main.cc goboard.h
	g++ -Wall -c main.cc
