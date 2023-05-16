#include "Color.hpp"

namespace prog {

    //Default construtctor, all atributes are initialiazed as value 0.
    Color::Color() {
        this->blue_ = 0;
        this->green_ = 0;
        this->red_ = 0;
    }
    //Copy constructor. Receives as argument a constant object of type Color, defines as atributes of the current object a copy of the respective attributes.
    Color::Color(const Color& other) {
        this->red_ = other.red_;
        this->green_ = other.green_;
        this->blue_ = other.blue_;
    }
    //Another constructor. Receives as arguments rgb_value variables red, green and blue, those which will be passed as atributes of the object of the class.
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        this->red_ = red;
        this->green_ = green;
        this->blue_ = blue;
    }
    //A member function that, once called, returns the red_ attribute.
    rgb_value Color::red() const {
        return this->red_;
    }
    //A member function that, once called, returns the green_ attribute.
    rgb_value Color::green() const {
        return this->green_;
    }
    //A member function that, once called, returns the blue_ attribute.
    rgb_value Color::blue() const {
        return this->blue_;
    }
    //A member function that, once called, returns a mutable reference of the red_ attribute
    rgb_value& Color::red()  {
        return this->red_;
    }
    //A member function that, once called, returns a mutable reference of the green_ attribute
    rgb_value& Color::green()  {
      return this->green_;
    }
    //A member function that, once called, returns a mutable reference of the blue_ attribute
    rgb_value& Color::blue()  {
      return this->blue_;
    }
}