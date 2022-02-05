#include <array>
#include <cstdio>
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

int main() {
  init(6, 3);
  show_lattice();
}