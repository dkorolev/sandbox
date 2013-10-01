#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

#include "common.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Synopsis: ./solve <lights filename>\n");
    return -1;
  } else {
    std::vector<std::vector<int> > lights = parse(argv[1]);
    
    // The equation has the form A*X=B, where all arithmetics is done modulo 2.
    // Cell [i][j] translates to variable (i*N+j).
    const size_t N = lights.size();
    const size_t D = N*N;
    std::vector<std::vector<int> > A(D, std::vector<int>(D, 0));
    std::vector<int> B(D, 0);

    // Construct the system of equations.
    const int di[5] = { 0, +1, -1,  0,  0 };
    const int dj[5] = { 0,  0,  0, -1, +1 };
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < N; ++j) {
        for (size_t t = 0; t < 5; ++t) {
          const size_t i2 = i + di[t];
          const size_t j2 = j + dj[t];
          if (i2 < N && j2 < N) {
            // Make use of size_t being unsigned.
            // Switch { i2, j2 } affects light { i, j }.
            A[i2*N+j2][i*N+j] = 1;
          }
        }
        B[i*N+j] = lights[i][j];
      }
    }

    std::vector<std::vector<int> > A0 = A;
    std::vector<int> B0 = B;

    // Solve the system of equations using Gaussian elimination.
    for (size_t x = 0; x < D; ++x) {
      // Isolate variable x.
      // First, find the equation where the coefficient before x is one,
      // if it can't be found then the system has no solution.
      // Start from row x since rows above x are already fixed
      // to become part of the diagonal matrx.
      size_t y = D;
      for (size_t j = x; j < D && y == D; ++j) {
        if (A[j][x]) {
          y = j;
        }
      }

      if (y == D) {
        break;
      }

      // Move row y into the position of row x if necessary.
      if (y != x) {
        std::swap(A[y], A[x]);
        std::swap(B[y], B[x]);
      }

      // Now eliminate x from all other equations.
      for (size_t i = 0; i < D; ++i) {
        if (i != x && A[i][x]) {
          for (size_t j = 0; j < D; ++j) {
            A[i][j] ^= A[x][j];
          }
          B[i] ^= B[x];
        }
      }
    }

    // Construct the solution.
    // The matrix A is either diagonal, or has some "slack" at the right.
    // If the matrix is diagonal, the solution is trivial.
    // If the matrix is not just a diagonal matrix, determine the values
    // of the variables that can be determined, and assume the rest to be 0.
    std::vector<int> solution(D, 0);
    for (size_t i = 0; i < D; ++i) {
      if (A[i][i]) {
        solution[i] = B[i];
      }
    }

    // Now test the solution for correctness.
    // For full rank matrices it would always be correct.
    // For non-full rank matrices it is either correct, or a contradiction
    // has been found, in which case the right solution is "no solution".
    bool ok = true;
    for (size_t i = 0; i < D && ok; ++i) {
      int rhs = 0;
      for (size_t j = 0; j < D; ++j) {
        if (A0[i][j] && solution[j]) {
          rhs ^= 1;
        }
      }
      if (rhs != B0[i]) {
        ok = false;
      }
    }

    // Print the solution.
    if (ok) {
      std::vector<std::vector<int> > switches(N, std::vector<int>(N));
      for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
          switches[i][j] = solution[i*N+j];
        }
      }
      print(switches);
      return 0;
    } else {
      std::cout << "IMPOSSIBLE" << std::endl;
      return 1;
    }
  }
}
