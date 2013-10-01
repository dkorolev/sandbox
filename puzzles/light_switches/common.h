#ifndef PARSE_H
#define PARSE_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::vector<int> >& X, std::ostream& out = std::cout) {
  const size_t N = X.size();
  std::vector<char> S(N * (N + 1) + 1, '\n');
  S.back() = '\0';
  for (size_t i = 0; i < N; ++i) {
    assert(X[i].size() == N);
    for (size_t j = 0; j < N; ++j) {
      S[i * (N + 1) + j] = (X[i][j] ? '+' : '.');
    }
  }
  out << &S[0];
}

std::vector<std::vector<int> > parse(const std::string& fn) {
  std::ifstream fi(fn.c_str());
  std::vector<std::string> raw;
  std::string row;
  while (fi >> row) {
    raw.push_back(row);
  }
  const size_t N = raw.size();
  assert(N && N <= 1000);
  std::vector<std::vector<int> > result(N, std::vector<int>(N));
  for (size_t i = 0; i < N; ++i) {
    assert(raw[i].length() == N);
    for (size_t j = 0; j < N; ++j) {
      const char c = raw[i][j];
      assert(c == '.' || c == '+');
      result[i][j] = (c == '+');
    }
  }
  return result;
}

#endif
