CC=gcc -ansi -pedantic

all: binary lib.h

binary: main.c hola_str_lib.h
	${CC} -o $@ $<

lib.h: hola_str_lib.h
	cpp hola_str_lib.h | grep -v "^#" | grep -v "^$$" >$@

clean:
	rm -f binary lib.h
