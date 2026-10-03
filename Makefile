CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

.PHONY: all clean test bookindex

all: $(OBJ)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/bookindex: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

bookindex: build/bookindex

build/extract_test: tests/extract_test.c build/extract.o build/status.o
	$(CC) $(CFLAGS) -o $@ tests/extract_test.c build/extract.o build/status.o

test: build/extract_test
	./build/extract_test

clean:
	rm -rf build
