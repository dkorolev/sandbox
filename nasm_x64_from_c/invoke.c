#include <stdio.h>
#include <string.h>

extern void foo(const char*, long long);
extern double bar(const double*);

int main() {
  const char* s = "Hehe! It works!\n";
  const double x[2] = { 17, 42.042 };
  printf("Begin.\n");
  foo(s, strlen(s));
  printf("%lf\n", bar(x));  // Prints x[1] == 42.042.
  printf("End.\n");
}
