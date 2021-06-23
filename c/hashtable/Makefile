CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c, %, $(SRCS))


all: $(BINS)

%: %.c

clean:
	$(RM) $(BINS)

