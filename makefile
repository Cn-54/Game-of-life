CC = gcc

CFLAGS = -Wall -Wextra -std=c11 $(shell pkg-config --cflags sdl3)
LIBS = $(shell pkg-config --libs sdl3)

TARGET = bin/main

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin obj