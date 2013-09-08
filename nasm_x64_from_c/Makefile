CC=gcc  # Works with clang as well.

all: invoke

module.o: module.nasm
	nasm -f elf64 -o $@ $<

invoke.o: invoke.c
	$(CC) -c $< -o $@

invoke: invoke.o module.o
	$(CC) -o $@ invoke.o module.o -lm

clean:
	rm -f module.o invoke.o invoke
