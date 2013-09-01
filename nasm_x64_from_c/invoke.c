#include <stdio.h>
#include <string.h>
#include <math.h>

extern void foo(const char*, long long);
extern int do_dim();
extern double do_math(const double* x, double* a);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[5] = { 1, 12, 3, 10, 3 };
  double a[100];
  printf("Begin.\n");
  foo(s, strlen(s));
  printf("Dim: %d\n", do_dim());
  printf("Expected: %lf\n", exp(x[0]) + log(x[1]) + sin(x[2]));
  printf("Actual: %lf\n", do_math(x, a));
  printf("Actual: %lf\n", do_math(x, a));
  printf("XXX: %lf %lf %lf %lf %lf %lf %lf %lf\n", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
  printf("End.\n");
}
