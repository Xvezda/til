CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
TARGET = main


all: $(TARGET)

$(TARGET): $(TARGET).c

debug: CFLAGS += -DDEBUG
debug: $(TARGET)

clean:
	$(RM) $(TARGET) *.o
