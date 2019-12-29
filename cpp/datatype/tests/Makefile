.SUFFIXES: .cpp

CC = g++
CXX = $(CC)
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = run_test
LDLIBS = -lgtest_main -lgtest -pthread


all: $(TARGET)

$(TARGET): $(OBJS)

clean:
	rm -rf *.o $(TARGET)
