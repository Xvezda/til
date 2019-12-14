CXX=g++
CPPFLAGS=-std=c++14 -O2 -Wall -Wextra -pedantic
TARGETS=$(patsubst %.cpp,%,$(wildcard *.cpp))


all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)
