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
TEST_FILE = scaffolding.py


all: $(TARGET)

debug: CFLAGS = -Wall -Wextra -pedantic -DDEBUG -DVERBOSE -g -O0
debug: all

libs: $(LIBS)

$(LIBS): $(filter-out main.o, $(OBJS))
	$(AR) rcs $@ $+

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $+ -o $@

test:
	$(PY) $(TEST_FILE)

clean:
	$(RM) $(TARGET) $(LIBS) $(OBJS)
