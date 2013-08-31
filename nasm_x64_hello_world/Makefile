all: p

p: p.nasm
	nasm -g -f elf64 -o p.o p.nasm
	ld -o p p.o

clean:
	rm -f p p.o
