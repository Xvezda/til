CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
TARGET=main


all: $(TARGET)

$(TARGET): $(OBJECTS)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o

