CC = cc
OUT = out
FLAGS = -Wall -I .

BIN = brainfcck

.PHONY: all clean build

all: clean build

clean:
	rm -rf $(OUT)

build: $(wildcard *.c)
	mkdir $(OUT)
	$(CC) -o $(OUT)/$(BIN) $^ $(FLAGS)
