CXX=g++
CPPFLAGS=-std=c++14 -O2 -Wall -Wextra -pedantic
# CPPFLAGS=-std=c++14 -g -DDEBUG -O0 -Wall -Wextra -pedantic
TARGETS=$(patsubst %.cpp,%,$(wildcard *.cpp))


all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)
