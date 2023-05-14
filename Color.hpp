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
      Color(); //Default Constructor
      Color(const Color& c); //Copy Constructor
      Color(rgb_value r, rgb_value g, rgb_value b); //Another Constructor
    //Member functions of the class
      rgb_value red() const; //Get
      rgb_value& red(); //Set
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
  };
}
#endif
