CC=clang++  # Works with clang++ as well.

all: main

main: main.cc lib.so
	${CC} --std=c++0x -o $@ $< -lm -ldl

lib.o: module.nasm
	nasm -f elf64 -o $@ $<

lib.so: lib.o
	ld -lm -shared -o $@ $<

clean:
	rm -f main lib.o lib.so
