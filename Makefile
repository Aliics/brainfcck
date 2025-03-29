CC = cc
OUT = out
FLAGS = -Wall -I .

BIN = brainfcck

.PHONY: all clean build run

all: clean build run

clean:
	rm -rf $(OUT)

build: $(wildcard *.c)
	mkdir $(OUT)
	$(CC) -o $(OUT)/$(BIN) $^ $(FLAGS)

run:
	$(OUT)/$(BIN)
