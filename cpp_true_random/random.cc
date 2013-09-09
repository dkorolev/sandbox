#include <iostream>
#include <string>
#include <random>

int main() {
  std::random_device rd;
  std::uniform_int_distribution<int> dist(1, 9);
  std::cout << dist(rd) << std::endl;
}
