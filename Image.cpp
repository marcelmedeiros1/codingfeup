#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    this->width_ = w;
    this->height_ = h;

  }
  Image::~Image()
  {
  }
  //A member function that, once called, returns the width_ attribute.
  int Image::width() const
  {
    return this->width_;
  }
  //A member function that, once called, returns the height_ attribute.
  int Image::height() const
  {
    return this->height_;
  }

  // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
  Color DUMMY_color;

  Color& Image::at(int x, int y)
  {
    return DUMMY_color;
  }

  const Color& Image::at(int x, int y) const
  {
    return DUMMY_color;
  }
}
