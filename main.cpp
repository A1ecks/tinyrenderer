#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class TinyRenderer : public olc::PixelGameEngine {
public:
  TinyRenderer() { sAppName = "TinyRenderer"; }

public:
  bool OnUserCreate() override {
    // Called once at the start, so create things here
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {
    // called once per frame
    Draw(50, 50, olc::Pixel(255, 0, 0));
    return true;
  }
};

int main() {
  TinyRenderer test;
  if (test.Construct(100, 100, 4, 4))
    test.Start();

  return 0;
}
