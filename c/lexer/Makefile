.SUFFIXES: .c

PY = python3
CC = gcc
# CFLAGS = -Wall -Wextra -pedantic -O2
CFLAGS = -Wall -Wextra -pedantic -DDEBUG -DVERBOSE -g -O0
TARGET = main


all: $(TARGET)

# debug: CFLAGS = -Wall -Wextra -pedantic -DDEBUG -g -O0
# debug: all

$(TARGET): $(TARGET).o

test:
	$(PY) scaffolding.py

clean:
	$(RM) -rf $(TARGET) *.o
