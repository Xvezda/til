.SUFFIXES: .cpp .o

CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -pedantic -O0 -g -DDEBUG
SRCS=$(filter-out *_test.cpp,$(wildcard *.cpp))
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
TARGETS=$(patsubst %.o,%,$(OBJS))
LIBS=-lgtest_main -lgtest -pthread

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean:
	rm -rf *.o $(TARGETS)
