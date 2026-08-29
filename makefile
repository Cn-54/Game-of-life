CC = gcc

CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags sdl3)
LIBS = $(shell pkg-config --libs sdl3)

TARGET = bin/main

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

bin/%.o: src/%.c
	mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin