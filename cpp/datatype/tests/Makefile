.SUFFIXES: .cpp

CC = g++
CXX = $(CC)
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
INC = -I../include
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = run_test
LDLIBS = -lgtest_main -lgtest -pthread -L../libs/static -lxvzd
# LDLIBS = -lgtest_main -lgtest -pthread -L../libs/shared -lxvzd


all: $(TARGET) ../libs/static/libxvzd.a

$(TARGET): $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
