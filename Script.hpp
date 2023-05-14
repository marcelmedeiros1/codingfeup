#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename); //Constructor
    ~Script(); //Destructor
    void run(); //A function to call the member functions defined below
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    //Private functions added
    void invert();
    void to_gray_scale();
    void replace();
    void fill();
    void h_mirror();
    void v_mirror();
    void add();
    void crop();
    void rotate_left();
    void rotate_right();
  };
}
#endif
