#include <array>
#include <cmath>
#include <cstdio>
#include <random>
#include <vector>

int LX, LY;        // System Size
int N;             // Number of sites
double e_table[5]; // Energy Table
enum { LEFT,
       RIGHT,
       UP,
       DOWN };

std::vector<int> lattice;
std::vector<std::array<int, 4>> neighbor;

int pos2index(int ix, int iy) {
  ix = (ix + LX) % LX;
  iy = (iy + LY) % LY;
  return ix + iy * LX;
}

void init(int size_x, int size_y, int number_of_particles) {
  LX = size_x;
  LY = size_y;
  N = LX * LY;
  lattice.resize(N, 0);
  neighbor.resize(N);
  for (int i = 0; i < N; i++) {
    int ix = i % LX;
    int iy = i / LX;
    neighbor[i][LEFT] = pos2index(ix - 1, iy);
    neighbor[i][RIGHT] = pos2index(ix + 1, iy);
    neighbor[i][DOWN] = pos2index(ix, iy - 1);
    neighbor[i][UP] = pos2index(ix, iy + 1);
  }
  for (int i = 0; i < number_of_particles; i++) {
    lattice[i] = 1;
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
  n1 += lattice[neighbor[p1][RIGHT]];
  n1 += lattice[neighbor[p1][LEFT]];
  n1 += lattice[neighbor[p1][UP]];
  n1 += lattice[neighbor[p1][DOWN]];
  std::swap(lattice[p1], lattice[p2]);
  int n2 = 0;
  n2 += lattice[neighbor[p2][RIGHT]];
  n2 += lattice[neighbor[p2][LEFT]];
  n2 += lattice[neighbor[p2][UP]];
  n2 += lattice[neighbor[p2][DOWN]];
  int nd = n1 - n2;
  if (nd < 0 || e_table[nd] > ud(mt)) {
    // Accept
  } else {
    // Reject
    std::swap(lattice[p1], lattice[p2]);
  }
}

void show_lattice() {
  for (int i = 0; i < LX; i++) {
    for (int j = 0; j < LY; j++) {
      if (lattice[i + j * LX] == 1) {
        printf("*");
      } else {
        printf("-");
      }
    }
    printf("\n");
  }
}

double calc_energy() {
  double e = 0;
  for (int i = 0; i < N; i++) {
    if (lattice[i] == 0) continue;
    e += lattice[neighbor[i][RIGHT]];
    e += lattice[neighbor[i][DOWN]];
  }
  return e;
}

void make_table(double beta) {
  for (int i = 0; i < 5; i++) {
    e_table[i] = exp(-i * beta);
  }
}

void mc(double beta) {
  make_table(beta);
  std::mt19937 mt;
  const int n_mc = 1000000;
  double e = 0.0;
  for (int i = 0; i < n_mc; i++) {
    exchange_particle(mt);
    e += calc_energy();
  }
  e /= n_mc;
  printf("%f %f\n", beta, e);
}

void domc(int lx, int ly, int n) {
  init(lx, ly, n);
  double b_start = 0.0;
  double b_end = 10.0;
  const int nd = 10;
  for (int i = 0; i < nd; i++) {
    double beta = (b_end - b_start) * i / nd + b_start;
    mc(beta);
  }
}

void test() {
  init(5, 10, 25);
  show_lattice();
  std::mt19937 mt;
  make_table(10.0);
  for (int i = 0; i < 100; i++) {
    exchange_particle(mt);
  }
  show_lattice();
}

int main() {
  domc(20, 20, 2);
  //test2();
}