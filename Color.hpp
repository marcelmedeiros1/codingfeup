#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
    //Class attributes, all of type rgb_value
        rgb_value red_;
        rgb_value green_;
        rgb_value blue_;
    public:
    //Constructors of the class
      Color();
      Color(const Color& c);
      Color(rgb_value r, rgb_value g, rgb_value b);
    //Member functions of the class
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
  };
}
#endif