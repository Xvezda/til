CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O2
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))
TARGETS=$(patsubst %.o,%,$(OBJECTS))


all: $(TARGETS)

clean:
	rm -rf $(TARGETS) $(OBJECTS)
