#include "../include/olcPixelGameEngine.h"

class TinyRenderer : public olc::PixelGameEngine {
public:
  TinyRenderer() { sAppName = "Tiny Renderer"; }

public:
  bool OnUserCreate() override {
    // Called once at the start, so create things here
    void line(int x0, int y0, int x1, int y1, olc::Pixel p);
    return true;
  }

  // Bresenham's Line Algorithm
  void line(int x0, int y0, int x1, int y1, olc::Pixel p) {
    int dx{x1 - x0};
    int dy{y1 - y0};
    int d{2 * dy - dx};
    for (int x{x0}, y{y0}; x <= x1; x++) {
      if (d > 0) {
        Draw(x, y++, p);
        // d = d - 2 * dx;
        d = 2 * dy - 2 * dx;
      } else {
        Draw(x, y, p);
        // d = d + 2 * dy;
        d = 2 * dy;
      }
    }
  }

  bool OnUserUpdate(float fElapsedTime) override {
    // called once per frame
    line(13, 20, 80, 40, olc::WHITE);
    line(20, 13, 40, 80, olc::RED);
    line(80, 40, 13, 20, olc::RED);
    if (GetKey(olc::Key::ESCAPE).bPressed) {
      return false;
    }
    return true;
  }
};

int main() {
  TinyRenderer test;
  if (test.Construct(100, 100, 1, 1))
    test.Start();

  return 0;
}
