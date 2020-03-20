CC = gcc
CFLAGS = $(shell pkg-config --cflags python3)
LDFLAGS = $(shell pkg-config --libs python3)
SRC_FILES = $(filter-out main.c, $(wildcard *.c))
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
TARGET = main


all: $(TARGET)

$(TARGET): $(OBJ_FILES)

clean:
	$(RM) -f $(OBJ_FILES) $(TARGET)
