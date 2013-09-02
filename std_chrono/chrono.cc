// http://stackoverflow.com/questions/13595062/inaccuracy-in-stdchronohigh-resolution-clock

#include <iostream>
#include <chrono>
#include <vector>

void long_function() {
  std::vector<long> x;
  x.push_back(1);
  x.push_back(1);
  for(int i = 2; i < 10000000; i++) {
    x.push_back(x[i-2] + x[i-1]);
  }
}

int main() {
  std::chrono::high_resolution_clock timer;

  auto start_time = timer.now();
  long_function();
  auto end_time = timer.now();

  std::cout << "It took " <<
  std::chrono::duration_cast<std::chrono::duration<int, std::milli>>(end_time - start_time).count() << "ms " << std::endl;
  return 0;
}
