.SUFFIXES: .cpp

CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
TARGETS=$(patsubst %.o,%,$(OBJS))
LDLIBS=-lgtest_main -lgtest -pthread


all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)
