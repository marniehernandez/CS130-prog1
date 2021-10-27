# CC=gcc
# CFLAGS=-I.
CXX=clang++

prog1: prog1.o
	${CXX} prog1.o -o prog1

prog1.o: prog1.cpp
	${CXX} -c prog1.cpp -o prog1.o
