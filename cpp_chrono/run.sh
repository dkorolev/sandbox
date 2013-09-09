#!/bin/bash

# Should be 102334155.

g++ --std=c++0x -O3 chrono.cc
./a.out

clang++ --std=c++0x -O3 chrono.cc
./a.out

rm -f a.out
