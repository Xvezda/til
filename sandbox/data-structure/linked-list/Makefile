CC=gcc
# CFLAGS=-Wall -Wextra -pedantic -DDEBUG -g
CFLAGS=-Wall -Wextra -pedantic
TARGET=linked_list

all: $(TARGET)

$(TARGET): main.o $(TARGET).o

$(TARGET).o: main.c $(TARGET).c $(TARGET).h

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o
