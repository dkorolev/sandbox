all: variadic_for_each.cc
	g++ --std=c++0x variadic_for_each.cc -o test_g++
	./test_g++
	clang++ --std=c++0x variadic_for_each.cc -o test_clang++
	./test_clang++
	rm -f test_g++ test_clang++

clean:
	rm -f test_g++ test_clang++
