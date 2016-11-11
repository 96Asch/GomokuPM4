# eenvoudige makefile
all: hoofd.o gobord.o
	g++ -Wall -o GomokuGame gobord.o hoofd.o
gobord.o: gobord.cc gobord.h
	g++ -Wall -c gobord.cc
hoofd.o: hoofd.cc gobord.h
	g++ -Wall -c hoofd.cc
