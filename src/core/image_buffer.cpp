#include "core/image_buffer.hpp"

#include <png.h>

#include <cstdio>
#include <stdexcept>

namespace imgengine {

ImageBuffer::ImageBuffer(int width, int height)
    : width_(width),
      height_(height),
      pixels_(static_cast<size_t>(width) * height * 4, 0) {
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("ImageBuffer dimensions must be positive");
  }
}

void ImageBuffer::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  for (size_t i = 0; i < pixels_.size(); i += 4) {
    pixels_[i + 0] = r;
    pixels_[i + 1] = g;
    pixels_[i + 2] = b;
    pixels_[i + 3] = a;
  }
}

void ImageBuffer::save_png(const std::string& path) const {
  FILE* fp = std::fopen(path.c_str(), "wb");
  if (!fp) throw std::runtime_error("cannot open file for writing: " + path);

  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  png_infop info = png_create_info_struct(png);
  if (!png || !info) {
    std::fclose(fp);
    throw std::runtime_error("libpng init failed");
  }
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_write_struct(&png, &info);
    std::fclose(fp);
    throw std::runtime_error("libpng error during write");
  }

  png_init_io(png, fp);
  png_set_IHDR(png, info, width_, height_, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  std::vector<png_bytep> rows(height_);
  for (int y = 0; y < height_; ++y) {
    rows[y] = const_cast<png_bytep>(&pixels_[static_cast<size_t>(y) * width_ * 4]);
  }
  png_write_image(png, rows.data());
  png_write_end(png, nullptr);

  png_destroy_write_struct(&png, &info);
  std::fclose(fp);
}

}  // namespace imgengine
