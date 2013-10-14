all: gen apply solve

gen: gen.cc common.h
	g++ -o $@ $<

apply: apply.cc common.h
	g++ -o $@ $<

solve: solve.cc common.h
	g++ -o $@ $<

test: all
	./test.sh

clean:
	rm -f gen apply solve
