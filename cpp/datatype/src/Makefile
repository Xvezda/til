CC = g++
CXX = $(CC)
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
INC = -I../include/xvzd
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))


all: build

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

build: $(OBJS)
	$(CXX) -shared -o ../lib/libxvzd.so $(OBJS)

debug: CXXFLAGS+=-O0 -g -DDEBUG
debug: $(OBJS)

clean:
	rm -rf *.o *.dSYM
