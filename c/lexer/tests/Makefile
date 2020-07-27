.SUFFIXES: .c

CC = gcc
CFLAGS = -I../
LDFLAGS = -L../libs -lcommon
SRCS = $(wildcard test_*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
TARGETS = $(patsubst %.o, %, $(OBJS))


all: clean libs $(TARGETS)

libs:
	cd ../ && $(MAKE) clean && $(MAKE) && $(MAKE) libs

%: %.o

clean:
	$(RM) $(TARGETS)
	cd ../ && $(MAKE) clean
