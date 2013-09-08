#include <cstdio>

struct master {
  struct one {
    static const char* f() { return "one"; }
  };
  struct two {
    static const char* f() { return "two"; }
  };
  typedef IMPL active;
};

int main() {
  printf("%s\n", master::active::f());
}
