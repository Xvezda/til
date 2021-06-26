.SUFFIXES: .c


CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra
SRCS = $(wildcard *.c)
BINS = $(patsubst %.c, %, $(SRCS))


all: $(BINS)

debug: CC = clang
debug: CFLAGS += -fsanitize=address,alignment,undefined -DDEBUG
debug: all

profile: CFLAGS += -g
profile: all

clean:
	$(RM) $(BINS)

