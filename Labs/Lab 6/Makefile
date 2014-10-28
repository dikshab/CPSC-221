CXX:=g++
CXXFLAGS:=-g -o
PROGS:=avl

.PHONY: all clean

all: $(PROGS)

$(PROGS): $(PROGS).cc
	$(CXX) $(CXXFLAGS) $@ $@.cc

clean:
	rm $(PROGS)