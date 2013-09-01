#include <iostream>
#include <tuple>

struct a {
  static void f() {
    std::cout << "a::f();" << std::endl;\
  }
};

struct b {
  static void f() {
    std::cout << "a::f();" << std::endl;\
  }
};

struct c {
  static void f() {
    std::cout << "a::f();" << std::endl;\
  }
};

int main() {
  typedef std::tuple<a, b, c> typelist;
  a::f();
  b::f();
  c::f();
}
