CC = gcc
TARGET = main


all: $(TARGET) plugin.so

$(TARGET): $(TARGET).c

plugin.so: plugin.c
	$(CC) -shared -fPIC -o $@ $<

clean:
	$(RM) $(TARGET) *.so *.o
