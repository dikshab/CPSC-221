CC=g++
CFLAGS=-g -Wall -Wextra
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
PROGS=modexp

all: $(PROGS)

$@:
	$(CC) $(CFLAGS) $@ $@.cpp

.PHONY: clean
clean:
	rm $(PROGS)
