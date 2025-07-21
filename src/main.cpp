#define OLC_PGE_APPLICATION
#include "../include/olcPixelGameEngine.h"
// #include "../include/tgaimage.h"
#include <cmath>

// Original code provided by tinyrenderer repository
//
// constexpr TGAColor white = {255, 255, 255, 255}; // attention, BGRA order
// constexpr TGAColor green = {0, 255, 0, 255};
// constexpr TGAColor red = {0, 0, 255, 255};
// constexpr TGAColor blue = {255, 128, 64, 255};
// constexpr TGAColor yellow = {0, 200, 255, 255};
//
// void line(int ax, int ay, int bx, int by, TGAImage &framebuffer,
//           TGAColor color) {
//   for (float t = 0.; t < 1.; t += .02) {
//     int x = std::round(ax + (bx - ax) * t);
//     int y = std::round(ay + (by - ay) * t);
//     framebuffer.set(x, y, color);
//   }
// }
//
// int main(int argc, char **argv) {
//   constexpr int width = 64;
//   constexpr int height = 64;
//   TGAImage framebuffer(width, height, TGAImage::RGB);
//
//   int ax = 7, ay = 3;
//   int bx = 12, by = 37;
//   int cx = 62, cy = 53;
// framebuffer.set(ax, ay, white); framebuffer.set(bx, by, white);
//   framebuffer.set(cx, cy, white);
//   line(ax, ay, bx, by, framebuffer, blue);
//   line(cx, cy, bx, by, framebuffer, green);
//   line(cx, cy, ax, ay, framebuffer, yellow);
//   line(ax, ay, cx, cy, framebuffer, red);
//
//   framebuffer.write_tga_file("framebuffer.tga");
//   return 0;
// }
//

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

  // Simple implementation with floating point numbers
  //
  //  void line(int x0, int y0, int x1, int y1, olc::Pixel p) {
  //    for (float m{0.0}; m < 1.0; m += 0.02) {
  //      int x = std::round(x0 + (x1 - x0) * m);
  //      int y = std::round(y0 + (y1 - y0) * m);
  //      Draw(x, y, p);
  //    }
  //  }

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
