CC=gcc
CPP=g++

# Works fine with CC=clang, CPP=clang++

all: main

main: main.cc lib.so
	${CPP} -o main main.cc -ldl

lib.so: lib.c
	${CC} -fPIC -shared -nostartfiles lib.c -o lib.so

clean:  
	rm -f main lib.so
