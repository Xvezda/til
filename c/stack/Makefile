.SUFFIXES: .c .s

CC = gcc
# CFLAGS = -g -DDEBUG -O0 -w
SRC_FILES = $(wildcard *.c)
ASM_FILES = $(patsubst %.c, %.s, $(SRC_FILES))
TARGETS = $(patsubst %.c, %, $(SRC_FILES))


all: $(TARGETS)

asm: $(ASM_FILES)

%.s: %.c
	$(CC) -S -o $@ $<

clean:
	$(RM) $(TARGETS) $(ASM_FILES)
	$(RM) -r *.dSYM
