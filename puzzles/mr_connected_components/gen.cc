#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

double rnd() {
  return (1.0 / 32767) * (rand() & 32767);
}

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Synopsis: ./gen N density randseed\n");
    return -1;
  } else {
    const int N = atoi(argv[1]);
    const double Q = atof(argv[2]);
    const int RS = atoi(argv[3]);
    assert(N >= 1 && N <= 10000);
    assert(Q >= 0.0 && Q <= 1.0);
    srand(RS);
    // Generate the edges. Loops are allowed.
    std::vector<std::pair<int, int> > E;
    for (size_t i = 1; i <= N; ++i) {
      for (size_t j = i; j <= N; ++j) {
        E.push_back(std::make_pair(i, j));
      }
    }
    std::random_shuffle(E.begin(), E.end());
    int M = std::max(1, static_cast<int>(M, E.size() * Q));
    for (size_t i = 0; i < M; ++i) {
      if (rand() & 1) {
        printf("%d %d\n", E[i].first, E[i].second);
      } else {
        printf("%d %d\n", E[i].second, E[i].first);
      }
    }
  }
}
