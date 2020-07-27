.PHONY: libs
.SUFFIXES: .c

PY = python3
AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGET = interpreter
LIBS = libs/libcommon.a


all: $(TARGET)

debug: CFLAGS = -Wall -Wextra -pedantic -DDEBUG -DVERBOSE -g -O0
debug: all

libs: $(LIBS)

$(LIBS):
	$(AR) rcs $@ $(filter-out main.o, $(OBJS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

test:
	$(PY) scaffolding.py

clean:
	$(RM) $(TARGET) $(LIBS) $(OBJS)
