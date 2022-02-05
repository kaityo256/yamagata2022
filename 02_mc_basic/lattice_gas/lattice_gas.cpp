#include <array>
#include <cmath>
#include <cstdio>
#include <random>
#include <vector>

int LX, LY;        // System Size
int N;             // Number of sites
double e_table[5]; // Energy Table

std::vector<int> lattice;
std::vector<std::array<int, 4>> neighbor;

int pos2index(int ix, int iy) {
  ix = (ix + LX) % LX;
  iy = (iy + LY) % LY;
  return ix + iy * LX;
}

void init(int size_x, int size_y) {
  LX = size_x;
  LY = size_y;
  N = LX * LY;
  lattice.resize(N, 0);
  neighbor.resize(N);
  for (int i = 0; i < N; i++) {
    int ix = i % LX;
    int iy = i / LX;
    neighbor[i][0] = pos2index(ix + 1, iy);
    neighbor[i][1] = pos2index(ix - 1, iy);
    neighbor[i][2] = pos2index(ix, iy + 1);
    neighbor[i][3] = pos2index(ix, iy - 1);
  }
  for (int j = 0; j < LY; j++) {
    for (int i = 0; i < LX / 2; i++) {
      int index = pos2index(i, j);
      lattice[index] = 1;
    }
  }
}

void exchange_particle(std::mt19937 &mt) {
  std::uniform_int_distribution<> uid(0, N - 1);
  std::uniform_real_distribution<> ud(0.0, 1.0);
  int p1 = uid(mt);
  int p2 = uid(mt);
  if (lattice[p1] == lattice[p2]) return;
  if (lattice[p2] == 1) {
    std::swap(p1, p2);
  }
  int n1 = 0;
  n1 += lattice[neighbor[p1][0]];
  n1 += lattice[neighbor[p1][1]];
  n1 += lattice[neighbor[p1][2]];
  n1 += lattice[neighbor[p1][3]];
  int n2 = 0;
  n2 += lattice[neighbor[p2][0]];
  n2 += lattice[neighbor[p2][1]];
  n2 += lattice[neighbor[p2][2]];
  n2 += lattice[neighbor[p2][3]];
  int nd = n1 - n2;
  if (nd < 0 || e_table[nd] > ud(mt)) {
    std::swap(lattice[p1], lattice[p2]);
  }
}

void show_lattice() {
  for (int j = 0; j < LY; j++) {
    for (int i = 0; i < LX; i++) {
      if (lattice[i + j * LX] == 1) {
        printf("*");
      } else {
        printf("-");
      }
    }
    printf("\n");
  }
}

void make_table(double beta) {
  for (int i = 0; i < 5; i++) {
    e_table[i] = exp(-i * beta);
  }
}

int main() {
  init(10, 5);
  show_lattice();
  std::mt19937 mt;
  make_table(10.0);
  for (int i = 0; i < 1000; i++) {
    exchange_particle(mt);
  }
  show_lattice();
}