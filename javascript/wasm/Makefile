CC = emcc
CFLAGS = --shell-file=shell.html \
		 -s ENVIRONMENT=web \
		 -s EXPORTED_FUNCTIONS=_base64_encode,_free \
		 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap
TARGET = base64.html


all: $(TARGET)

%.html: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET) *.js

