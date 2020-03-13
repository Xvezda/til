CC = gcc
# CCFLAGS = -O0 -g
CCFLAGS = -O3 -g
TARGET = sum
OBJ_FILES = $(patsubst %, %.o, $(TARGET))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CCFLAGS) $< -o $@


%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
