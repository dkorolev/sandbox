// The code I wrote during the phone interview, fixed a few typos to compile.

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#ifndef MAX_N
#define MAX_N 10000
#endif

#define DEBUG_ASSERT assert

std::vector<size_t> outgoing[MAX_N];
bool seen[MAX_N];
bool visited[MAX_N];
std::vector<std::vector<size_t> > component;

void dfs(int i) {
  if (!visited[i]) {
    visited[i] = true;
    component.back().push_back(i);
    for (size_t j = 0; j < outgoing[i].size(); ++j) {
      dfs(outgoing[i][j]);
    }
  }
}

int main() {
  //std::ifstream fi("input.txt");
  std::istream& fi = std::cin;
  int a, b;
  while (fi >> a >> b) {
    DEBUG_ASSERT(a > 0 && a <= MAX_N);
    DEBUG_ASSERT(b > 0 && b <= MAX_N);
    // assume no duplicate edges; no big deal if we have some, the code would still work.
    --a;
    --b;
    seen[a] = true;
    seen[b] = true;
    outgoing[a].push_back(b);
    outgoing[b].push_back(a);
  }
  for (size_t i = 0; i < MAX_N; ++i) {
    if (seen[i] && !visited[i]) {
      component.push_back(std::vector<size_t>());
      dfs(i);
    }
  }
  for (size_t i = 0; i < component.size(); ++i) {
    std::sort(component[i].begin(), component[i].end());
    for (size_t j = 0; j < component[i].size(); ++j) {
      std::cout << component[i][j] + 1 << ((j+1) == component[i].size() ? '\n' : ' ');
    }
  }
}
