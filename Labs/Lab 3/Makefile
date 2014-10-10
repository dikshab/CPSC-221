CC=g++
CFLAGS=-g -Wall -O3
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
PROGS=CDate linked_list

all: $(PROGS)
	
$@:
	$(CC) $(CFLAGS) $@ $@.cpp

.PHONY: clean
clean:
	rm $(PROGS)
	