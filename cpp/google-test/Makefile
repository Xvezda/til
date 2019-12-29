.SUFFIXES: .cpp

CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic -O2
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
TARGETS=$(patsubst %.o,%,$(OBJS))

all: $(TARGETS) test

test:
	cd tests && $(MAKE)

clean:
	rm -rf *.o $(TARGETS)
	cd tests && $(MAKE) clean

