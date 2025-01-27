all: Prog.exe

Prog.exe: expression.o main.o
	g++ -g expression.o main.o -o Prog.exe

expression.o: expression.cpp expression.h
	g++ -g -c expression.cpp

main.o: main.cpp
	g++ -g -c main.cpp

