.SUFFIXES: .c

PY = python3
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = interpreter


all: $(TARGET)

debug: CFLAGS = -Wall -Wextra -pedantic -DDEBUG -DVERBOSE -g -O0
debug: all

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

test:
	$(PY) scaffolding.py

clean:
	$(RM) -rf $(TARGET) *.o
