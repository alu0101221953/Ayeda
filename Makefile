CC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra

all: main.cc
	$(CC) $(CFLAGS) main.cc -o practica1

.PHONY:  clean
	rm -f practica1 *.o