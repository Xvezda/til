.SUFFIXES: .c


CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = main
OBJS = $(TARGET).o


all: $(TARGET)

$(TARGET): $(OBJS)

$(OBJS): $(TARGET).c

clean:
	$(RM) -rf $(TARGET) $(OBJS)

