#define OLC_PGE_APPLICATION
#include "../include/olcPixelGameEngine.h"
#include <cmath>

class TinyRenderer : public olc::PixelGameEngine {
public:
  TinyRenderer() { sAppName = "Tiny Renderer"; }

public:
  bool OnUserCreate() override {
    // Called once at the start, so create things here
    void line(int x0, int y0, int x1, int y1, olc::Pixel p);
    int fixY(int y);
    return true;
  }

  static const int WIDTH{64}, HEIGHT{64};

  // Adjust Y coordinate to match tinyrenderer guide
  int fixY(int y) { return std::abs(HEIGHT - y); }

  void line(int x0, int y0, int x1, int y1, olc::Pixel p) {
    bool v{std::abs(x1 - x0) < std::abs(y1 - y0)};
    if (v) {
      std::swap(x0, y0);
      std::swap(x1, y1);
    }
    if (x0 > x1) {
      std::swap(x0, x1);
      std::swap(y0, y1);
    }
    int dx{x1 - x0}, dy{y1 - y0}, err;
    if (dy < 0) {
      err = -1;
    } else {
      err = 1;
    }
    dy *= err;
    if (dx != 0) {
      int y{y0}, m{2 * dy - dx};
      for (int x{x0 + 1}; x < x1; x++) {
        if (v) {
          Draw(y, x, p);
        } else {
          Draw(x, y, p);
        }
        if (m >= 0) {
          y += err;
          m -= 2 * dx;
        }
        m += 2 * dy;
      }
    }
  }

  bool OnUserUpdate(float fElapsedTime) override {
    // called once per frame
    int ax = 7, ay = fixY(3);
    int bx = 12, by = fixY(37);
    int cx = 62, cy = fixY(53);

    Draw(ax, ay, olc::WHITE);
    Draw(bx, by, olc::WHITE);
    Draw(cx, cy, olc::WHITE);

    line(ax, ay, bx, by, olc::BLUE);
    line(bx, by, cx, cy, olc::GREEN);
    line(ax, ay, cx, cy, olc::YELLOW);
    line(ax, ay, cx, cy, olc::RED);

    if (GetKey(olc::Key::ESCAPE).bPressed) {
      return false;
    }
    return true;
  }
};

int main() {
  TinyRenderer test;
  if (test.Construct(test.WIDTH, test.HEIGHT, 4, 4))
    test.Start();
  return 0;
}
