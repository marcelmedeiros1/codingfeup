#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
  //Class Atributes, all of type int
    int width_;
    int height_;
    Color color_;
  public:
  //Constructors of the class
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
  //Member functions of the class
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}

#endif
