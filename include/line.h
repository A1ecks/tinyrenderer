#ifndef LINE_H

#include "../include/olcPixelGameEngine.h"

class Line {

public:
  Line();
  Line(int x, int y, int x1, int y1, olc::Pixel p);
  void lineS(int x, int y); // Starting (x, y) of the line
  void lineE(int x, int y); // Ending (x, y) of the line
  void lineC(olc::Pixel p);
  void lineD(olc::PixelGameEngine *pge);

private:
  int a{0};
  int b{0};
  int c{0};
  int d{0};
  olc::Pixel e{olc::WHITE};
  bool bHam(int x, int y);
};

#endif
