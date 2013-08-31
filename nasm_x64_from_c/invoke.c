#include <stdio.h>
#include <string.h>

extern void foo(const char*, long long);
extern double add(const double*);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[2] = { 1.0, 10.0 };
  printf("Begin.\n");
  foo(s, strlen(s));
  printf("%lf\n", add(x));  // Prints x[0] + x[1] == 11.0.
  printf("End.\n");
}
