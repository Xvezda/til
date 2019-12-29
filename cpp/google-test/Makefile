.SUFFIXES: .cpp .o

CC=g++
CXX=$(CC)
CXXFLAGS=-std=c++14
TARGET=test
OBJS=sample.o
LIBS=-lgtest_main -lgtest -pthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LIBS)

clean:
	rm -rf *.o $(TARGET)
