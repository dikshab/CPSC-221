CC=g++
CFLAGS=-g -Wall -O2
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
PROGS=1a 1b 2 3 4

all: $(PROGS)
	
$@:
	$(CC) $(CFLAGS) $@ $@.cpp

clean:
	rm -rf *o
