CC=gcc
FLAGS=-Wall -Wextra -pedantic -O2
TARGET=main


all: $(TARGET)

$(TARGET): $(TARGET).o

$(TARGET).o: $(TARGET).c

run:
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
