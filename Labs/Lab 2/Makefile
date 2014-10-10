CC=g++
CFLAGS=-g -Wall -O3
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
PROGS=insertion pointers bonus

all: $(PROGS)
	
$@:
	$(CC) $(CFLAGS) $@ $@.cpp

.PHONY: clean
clean:
	rm $(PROGS)
	