CC = gcc
SOURCE = obfuscated.c
TARGET = result.i


all: deobfuscate

deobfuscate: $(TARGET)

$(TARGET):
	$(CC) -E $(SOURCE) -o $@

clean:
	rm -rf $(TARGET)
