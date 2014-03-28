#include <cstdio>
#include <functional>

int f0() { return 42; }

int main() {
  std::function<int()> f = f0;
  printf("f() = %d\n", f());
}
