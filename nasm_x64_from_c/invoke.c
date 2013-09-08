#include <stdio.h>
#include <string.h>
#include <math.h>

extern int dim();
extern double eval(const double* x, double* a);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[5] = { 1, 12, 3, 10, 3 };
  double a[100];
  printf("Dim: %d\n", dim());
  printf("Result: %lf\n", eval(x, a));
}
