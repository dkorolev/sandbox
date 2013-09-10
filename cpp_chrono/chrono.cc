#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>

#include <sys/time.h>

double get_wall_time_seconds(){
  // Single-threaded implementation.
  // #include <chrono> not friendly with clang++.
  // clock() and boost::time measure CPU time, not wall time.
  // More advanced Boost timer seems to be not present in my Ubuntu 12.04 as of 2013-09-10.
  static struct timeval time;
  gettimeofday(&time, NULL);
  return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int fib(int a) {
  return a <= 2 ? 1 : fib(a-1) + fib(a-2);
}

int main() {
  double begin = get_wall_time_seconds();
  std::cout << fib(40) << std::endl;
  system("sleep 3");
  double end = get_wall_time_seconds();
  double diff = end - begin;
  std::cout << std::fixed << std::setprecision(2) << diff << "s." << std::endl;
}
