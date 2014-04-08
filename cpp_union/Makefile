all: binary

binary: pod_field_accessors.cc
	g++ --std=c++11 -o $@ $<

clean:
	rm -f binary
