#!/bin/bash

g++ --std=c++0x random.cc
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
echo

clang++ --std=c++0x random.cc
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
./a.out
echo

rm -f a.out
