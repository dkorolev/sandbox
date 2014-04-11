// Different syntaxes of declaring and using lambdas in C++11.

#include <iostream>
#include <functional>

using std::function;

// A quick way to indicate that a composite call has terminated
// is to `throw done();`.
struct done {};

// A global definition of the function that is later
// assigned to a local variable.
void global_take_definition(
    int n,
    function<void(function<void(int)>)> generator,
    function<void(int)> next) {
  generator([&n, next](int x) {
    if (n > 0) {
      --n;
      next(x);
    } else {
      throw done();
    }
  });
}

// A slightly more tricky function with multiple functional inputs
// and funcional return value.
function<void(function<void(int)>)> filter(
    function<void(function<void(int)>)> generator,
    function<bool(int)> predicate) {
  return [generator, predicate](function<void(int)> next) {
    generator([predicate, next](int x) {
      if (predicate(x)) {
        next(x);
      }
    });
  };
}

int main() {
  // Assign a lambda to an auto variable.
  auto print = [](int x) {
    std::cout << x << ' ';
  };

  // Assign a pre-defined function to an auto variable.
  auto take = global_take_definition;

  // Assign a lambda to a typed variable.
  function<void(function<void(int)>)> generator = [](function<void(int)> f) {
    int a = 0;
    while (true) {
      f(++a);
    }
  };

  // Print "1 2 3 4 5 6 7 8 9 10 ".
  try {
    take(10, generator, print);
  } catch (done&) {
    std::cout << std::endl;
  }

  // Print "1 3 5 7 9 11 13 15 17 19 ".
  try {
    // Predicate `odd` is defined inline.
    take(10, filter(generator, [](int x) { return x & 1; }), print);
  } catch (done&) {
    std::cout << std::endl;
  }

  // Print "1 9 25 49 81 121 169 225 289 361 ".
  function<function<void(int)>(function<int(int)>, function<void(int)>)> chain =
    [](function<int(int)> a, function<void(int)> b) {
      return [a, b](int x) {
        b(a(x));
      };
    };
  function<int(int)> square = [](int x) {
    return x * x;
  };
  try {
    take(10, filter(generator, [](int x) { return x & 1; }), chain(square, print));
  } catch (done&) {
    std::cout << std::endl;
  }

  // Print "1 9 5 9 1 1 9 5 9 1 ".
  try {
    take(
        10,
        filter(generator, [](int x) { return x & 1; }),
        chain(square, chain([](int x) { return x % 10; }, print)));
  } catch (done&) {
    std::cout << std::endl;
  }
}
