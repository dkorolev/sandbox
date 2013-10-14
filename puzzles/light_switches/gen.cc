#include <cstdio>
#include <cstdlib>
#include <cassert>

#include "common.h"

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
    assert(N >= 1 && N <= 100);
    assert(Q >= 0.0 && Q <= 1.0);
    srand(RS);
    std::vector<std::vector<int> > X(N, std::vector<int>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        X[i][j] = (rnd() <= Q);
      }
    }
    print(X);
    return 0;
  }
}
