CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
TARGET=abstract_item


all: $(TARGET)

$(TARGET): main.o $(TARGET).o

main.o: main.c $(TARGET).h

$(TARGET).o: $(TARGET).c $(TARGET).h

run:
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)
