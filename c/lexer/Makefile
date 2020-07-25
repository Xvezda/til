.SUFFIXES: .c

PY = python3
CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = main


all: $(TARGET)

$(TARGET): $(TARGET).o

test:
	$(PY) scaffolding.py

clean:
	$(RM) -rf $(TARGET) *.o
