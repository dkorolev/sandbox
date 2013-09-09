// #include <chrono> -- seems to not work well in clang as of 2013-09-09.

#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

int fib(int a) {
  return a <= 2 ? 1 : fib(a-1) + fib(a-2);
}

int main() {
  //std::chrono::high_resolution_clock timer;
  clock_t begin = clock();
//  auto begin = timer.now();
  std::cout << fib(40) << std::endl;
//  double duration = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(timer.now() - begin).count() * 0.001;
  clock_t end = clock();
  double diff = double(end - begin) / CLOCKS_PER_SEC;
  std::cout << std::fixed << std::setprecision(2) << diff << "s." << std::endl;
}
