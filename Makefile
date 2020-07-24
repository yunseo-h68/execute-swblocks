CC = gcc
CFLAGS =  -W -Wall
TARGET = bin/app
OBJECTS = src/main.o src/convert_to_string.o src/sw_log.o src/sw_read_info.o src/sw_start.o
SWBLOCK_TARGET = bin/SwBlock
SWBLOCK_OBJECTS = SwBlocks/main.o

all: $(TARGET) $(SWBLOCK_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(SWBLOCK_TARGET): $(SWBLOCK_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm src/*.o SwBlocks/*.o bin/*
