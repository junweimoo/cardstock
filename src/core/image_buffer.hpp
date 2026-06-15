#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace imgengine {

// RGBA8 image buffer. M0 scope: allocate, fill solid, write PNG.
class ImageBuffer {
 public:
  ImageBuffer(int width, int height);

  void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void save_png(const std::string& path) const;

  int width() const { return width_; }
  int height() const { return height_; }

 private:
  int width_;
  int height_;
  std::vector<uint8_t> pixels_;  // width*height*4, RGBA, row-major
};

}  // namespace imgengine
