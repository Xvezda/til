CC = gcc
SOURCE = obfuscated.c
TARGET = result.i


all: deobfuscate

build: $(patsubst %.c, %, $(SOURCE))

deobfuscate: $(TARGET)
	sed -n '/^#.*$(SOURCE)/,/^#.*$(SOURCE)/p' $< | grep -v '^#'

$(TARGET):
	$(CC) -E $(SOURCE) -o $@

clean:
	rm -rf $(TARGET)
