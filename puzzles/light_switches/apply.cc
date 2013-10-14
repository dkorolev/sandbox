#include <cstdio>
#include <vector>

#include "common.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Synopsis: ./apply <lights filename> <switches filename>\n");
    return -1;
  } else {
    std::vector<std::vector<int> > lights = parse(argv[1]);
    std::vector<std::vector<int> > switches = parse(argv[2]);
    const size_t N = lights.size();
    assert(switches.size() == N);
    const int di[5] = { 0, +1, -1,  0,  0 };
    const int dj[5] = { 0,  0,  0, -1, +1 };
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        if (switches[i][j]) {
          for (size_t t = 0; t < 5; ++t) {
            const size_t i2 = i + di[t];
            const size_t j2 = j + dj[t];
            if (i2 < N && j2 < N) {
              // Make use of size_t being unsigned.
              lights[i2][j2] ^= 1;
            }
          }
        }
      }
    }
    // For the purposes of this test, just return 0 is the test has passed,
    // otherwise print the output matrix and return a nonzero code.
    if (lights == std::vector<std::vector<int> >(N, std::vector<int>(N, 0))) {
      return 0;
    } else {
      print(lights);
      return 1;
    }
  }
}
