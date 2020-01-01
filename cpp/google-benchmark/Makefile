.SUFFIXES: .cpp

CC = g++
CXX = $(CC)
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
LDLIBS = -lbenchmark -pthread
SRCS = $(wildcard *_test.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGETS = $(patsubst %.o,%,$(OBJS))


all: $(TARGETS)

clean:
	rm -rf $(TARGETS) $(OBJS)
