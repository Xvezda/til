CC=g++
CXX=$(CC)
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic
OBJECTS=$(patsubst %.cpp,%.o,$(filter-out *_test.cpp,$(wildcard *.cpp)))
TARGETS=$(patsubst %.cpp,%,$(wildcard *_test.cpp))


all: $(TARGETS) test

$(TARGETS): $(OBJECTS)

test:
	cd tests && $(MAKE)

debug: CXXFLAGS+=-O0 -g -DDEBUG
debug: $(TARGETS)

clean:
	rm -rf $(TARGETS) *.o *.dSYM
	cd tests && $(MAKE) clean
