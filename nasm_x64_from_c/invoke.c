#include <stdio.h>
#include <string.h>
#include <math.h>

extern void foo(const char*, long long);
extern double do_math(const double* x, double* a);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[5] = { 1, 12, 3, 10, 3 };
  double a[100];
  printf("Begin.\n");
  foo(s, strlen(s));
  printf("Expected: %lf\n", exp(x[0]) + log(x[1]));
  printf("Actual: %lf\n", do_math(x, a));
  printf("Actual: %lf\n", do_math(x, a));
  printf("XXX: %lf %lf %lf %lf %lf\n", a[0], a[1], a[2], a[3], a[4]);
  printf("End.\n");
}
