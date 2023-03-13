CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
SRC = main.c
EXECUTABLE = brainfuck

.PHONY: all clean build run

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE)

build: clean $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
