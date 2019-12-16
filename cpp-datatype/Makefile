CXX=g++
CPPFLAGS=-std=c++14 -Wall -Wextra -pedantic -O0 -g -DDEBUG
# CPPFLAGS=-std=c++14 -Wall -Wextra -pedantic -O2
TARGETS=$(patsubst %.cpp,%,$(wildcard *.cpp))


all: $(TARGETS)

clean:
	rm -rf $(TARGETS) *.o *.dSYM
