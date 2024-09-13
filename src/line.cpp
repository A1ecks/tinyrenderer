#include "../include/line.h"
#include <winerror.h>

bool Line::bHam(int x, int y) {
  int dx{x - a};
  int dy(y - b);
  int d{((2 * dy) - dx)};
  if (d == 0 || abs(d) + d) {
    return 1;
  }
  return 0;
}

Line::Line() { this->e = olc::WHITE; };

Line::Line(int x, int y, int x1, int y1, olc::Pixel p) {
  this->a = x;
  this->b = y;
  this->c = x1;
  this->b = y1;
  this->e = p;
}

void Line::lineS(int x, int y) {
  this->a = x;
  this->b = y;
}

void Line::lineE(int x, int y) {
  this->c = x;
  this->d = y;
}

void Line::lineC(olc::Pixel p) { this->e = p; }

// Bresenham's Line Algorithm
void Line::lineD(olc::PixelGameEngine *pge) {
  for (int x{a}, y{b}; x <= c; x++) {
    if (bHam(x, y)) {
      pge->Draw(x, y, e);
    } else {
      pge->Draw(x, y++, e);
    }
  }
}
