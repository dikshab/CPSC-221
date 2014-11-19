CXX:=g++
CXXFLAGS:=-O2 -o
PROGS:=hash

.PHONY: all clean

all: $(PROGS)

$(PROGS): $(PROGS).cc
	$(CXX) $(CXXFLAGS) $@ $@.cc

clean:
	rm $(PROGS)
