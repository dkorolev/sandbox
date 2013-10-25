// http://stackoverflow.com/questions/13595062/inaccuracy-in-stdchronohigh-resolution-clock

#include <iostream>
#include <chrono>
#include <vector>

void test1() {
  std::chrono::high_resolution_clock timer;
  std::vector<long> x;

  auto start_time = timer.now();

  x.push_back(42);
  x.push_back(43);
  for(int i = 2; i < 10000000; i++) {
    x.push_back(x[i-2] + x[i-1]);
  }

  auto end_time = timer.now();

  std::cout << "It took " << std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end_time - start_time).count() << "ms " << std::endl;
}

void test2() {
  std::chrono::high_resolution_clock timer;
  std::vector<long> x;

  auto start_time = timer.now();

  x.push_back(1);
  x.push_back(1);

  double duration;
  do {
    size_t i = x.size();
    x.push_back(x[i-2] + x[i-1]);
    duration = std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(timer.now() - start_time).count();
  } while (duration < 875);

  std::cout << duration << "ms, " << x.size() << " numbers." << std::endl;
}

int main() {
  test1();
  test2();
}
