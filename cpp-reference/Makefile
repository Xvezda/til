CXX=g++
CPPFLAGS=-std=c++14 -O2 -Wall -Wextra -pedantic
TARGET=test


all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CXX) $(CPPFLAGS) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CPPFLAGS) -c $(TARGET).cpp -o $(TARGET).o

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o
