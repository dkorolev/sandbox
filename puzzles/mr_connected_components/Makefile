all: gen baseline mapreduce

gen: gen.cc
	g++ -o $@ $<

baseline: baseline.cc
	g++ -o $@ $<

# FIXME: Actually test the MapReduce solution.
mapreduce: baseline.cc
	g++ -o $@ $<

test: all
	./test.sh

clean:
	rm -f gen baseline mapreduce
