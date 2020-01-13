CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -Wno-unused-function
SOURCE = hooks_test.c
TARGET = $(patsubst %.c, %, $(SOURCE))

all: $(TARGET)


# TODO: Is there any elegant way to do this?
hooks: CCFLAGS += -DPREHOOK
hooks: CCFLAGS += -DPOSTHOOK
hooks: all

prehook: CCFLAGS += -DPREHOOK
prehook: all

posthook: CCFLAGS += -DPOSTHOOK
posthook: all

%: %.c
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	rm -rf $(TARGET)

