#include <stdio.h>
#include <string.h>

extern void foo(const char*, long long);
extern double add(const double*);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[5] = { 1, 12, 3, 10, 3 };
  printf("Begin.\n");
  foo(s, strlen(s));
  printf("%lf\n", add(x));  // ((((1 + 12) - 3) * 10) / 3) == 33.(3)
  printf("End.\n");
}
