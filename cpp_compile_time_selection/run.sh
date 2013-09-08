#!/bin/bash

# OK, one.
g++ -DIMPL="one" example.cc && ./a.out
# OK, two.
g++ -DIMPL="two" example.cc && ./a.out
# Compilation error.
g++ -DIMPL="foo" example.cc && ./a.out

# OK, one.
clang++ -DIMPL="one" example.cc && ./a.out
# OK, two.
clang++ -DIMPL="two" example.cc && ./a.out
# Compilation error.
clang++ -DIMPL="foo" example.cc && ./a.out

rm -f a.out
