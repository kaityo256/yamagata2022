#include <array>
#include <iostream>
#include <numeric>

int main() {
  const int N = 10;
  std::array<int, N> v;
  std::iota(v.begin(), v.end(), 0);
  for (auto i : v) {
    std::cout << i << std::endl;
  }
}
