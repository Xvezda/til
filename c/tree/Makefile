.SUFFIXES: .c


CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c, %, $(SRCS))


all: $(BINS)

debug: CC = clang
debug: CFLAGS += -g -O0 -fsanitize=address,alignment,undefined -DDEBUG
debug: all

clean:
	$(RM) $(BINS)

