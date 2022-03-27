#include "sdouble.hpp"
#include <iostream>
#include <random>
#include <vector>

const int L = 10;
const int V = L * L;
const int SAMPLE = 1000000;

void mc(const double beta, std::mt19937 &mt) {
  std::uniform_int_distribution<> ud(0, V - 1);
  std::vector<double> vu, vz;
  const double w = exp(beta);
  for (int i = 0; i < SAMPLE; i++) {
    const int p1 = ud(mt);
    const int p2 = ud(mt);
    if (p1 == p2) continue;
    const int x1 = p1 % L;
    const int y1 = p1 / L;
    const int x2 = p2 % L;
    const int y2 = p2 / L;
    int dx = x1 - x2;
    int dy = y1 - y2;
    if (dx > L / 2) dx -= L;
    if (dx < -L / 2) dx += L;
    if (dy > L / 2) dy -= L;
    if (dy < -L / 2) dy += L;

    double ui = 0.0;
    double wi = 1.0;
    if (dx == 0 && std::abs(dy) == 1) {
      ui = -w;
      wi = w;
    } else if (dy == 0 && std::abs(dx) == 1) {
      ui = -w;
      wi = w;
    }
    vu.push_back(ui);
    vz.push_back(wi);
  }
  stat::sdouble su(vu);
  stat::sdouble sz(vz);
  std::cout << beta << " " << su / sz << std::endl;
}

void domc() {
  std::mt19937 mt;
  double b_start = 0.0;
  double b_end = 10.0;
  const int nd = 10;
  for (int i = 0; i < nd; i++) {
    double beta = (b_end - b_start) * i / nd + b_start;
    mc(beta, mt);
  }
}

int main() {
  domc();
}
