CC=g++
CFLAGS=-g -O2
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
PROGS=queuestack factorial

all: $(PROGS)
	
$@:
	$(CC) $(CFLAGS) $@ $@.cpp

.PHONY: clean
clean:
	rm $(PROGS)
	