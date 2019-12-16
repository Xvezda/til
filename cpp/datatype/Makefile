CXX=g++
CPPFLAGS=-std=c++14 -Wall -Wextra -pedantic
TARGETS=$(patsubst %.cpp,%,$(wildcard *.cpp))


all: $(TARGETS)

debug: CPPFLAGS+=-O0 -g -DDEBUG
debug: $(TARGETS)

clean:
	rm -rf $(TARGETS) *.o *.dSYM
