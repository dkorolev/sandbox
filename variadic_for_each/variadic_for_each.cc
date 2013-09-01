#include <iostream>

#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/vector.hpp>

struct a {
  static void f() {
    std::cout << "a::f();" << std::endl;\
  }
};

struct b {
  static void f() {
    std::cout << "b::f();" << std::endl;\
  }
};

struct c {
  static void f() {
    std::cout << "c::f();" << std::endl;\
  }
};

struct run_f {
  template <typename T> void operator()(T) const {
    T::f();
  };
};

int main() {
  boost::fusion::vector<a, b, c> typelist;
  boost::fusion::for_each(typelist, run_f());
}
