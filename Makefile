# a simple makefile
all: main.o goboard.o stack.o
	g++ -Wall -o GomokuGame goboard.o main.o stack.o
gobord.o: goboard.cc goboard.h
	g++ -Wall -c goboard.cc
main.o: main.cc goboard.h stack.h
	g++ -Wall -c main.cc
stack.o: stack.cc stack.h
	g++ -Wall -c stack.cc
