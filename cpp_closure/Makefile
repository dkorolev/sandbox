all: binary

binary: closure.cc
	g++ --std=c++11 -o $@ $<
	./$@

clean:
	rm -f binary
