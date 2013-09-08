CC=g++  # Works with clang++ as well.

all: main

main: main.cc lib.so
	${CC} -o $@ $< -ldl

lib.o: module.nasm
	nasm -shared -f elf64 -o $@ $<

lib.so: lib.o
	ld -shared -o $@ $< -lm

clean:
	rm -f main lib.o lib.so
