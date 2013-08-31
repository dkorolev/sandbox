#include <string.h>

extern void foo(const char*, long long);

int main() {
  const char* s = "Hehe! It works!\n";
  foo(s, strlen(s));
}
