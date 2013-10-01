all: gen baseline mapreduce

gen: gen.cc
	g++ -o $@ $<

baseline: baseline.cc
	g++ -o $@ $<

mapreduce: mapreduce.cc
	g++ --std=c++0x -o $@ $<

test: all
	./test.sh

clean:
	rm -f gen baseline mapreduce
