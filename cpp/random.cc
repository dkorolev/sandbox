#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  std::vector<int> a(9);
  int i = 0;
  for (auto& x : a) {
    x = ++i;
  }
  std::mt19937 rnd(43);
  std::random_shuffle(a.begin(), a.end(), [&rnd](int n) { return rnd() % n; });
  for (auto x : a) {
    printf("%d ", x);
  }
  printf("\n");
}
