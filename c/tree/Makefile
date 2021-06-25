.SUFFIXES: .c

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c, %, $(SRCS))


all: $(BINS)

%: %.c

clean:
	$(RM) $(BINS)

