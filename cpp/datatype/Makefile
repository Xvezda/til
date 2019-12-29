CC=g++
CXX=$(CC)
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic
OBJECTS=$(patsubst %.cpp,%.o,$(filter-out *_test.cpp,$(wildcard *.cpp)))
TARGETS=$(patsubst %.cpp,%,$(wildcard *_test.cpp))


all: $(TARGETS)

$(TARGETS): $(OBJECTS)

debug: CXXFLAGS+=-O0 -g -DDEBUG
debug: $(TARGETS)

clean:
	rm -rf $(TARGETS) *.o *.dSYM
