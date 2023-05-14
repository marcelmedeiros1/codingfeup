#include "Image.hpp"

namespace prog
{
  //A constructor to fill all pixels of the image with the color "fill"
  Image::Image(int w, int h, const Color& fill)
  {
    this->width_ = w;
    this->height_ = h;
    this->pixels_ = new Color*[w];
    for (int i = 0; i < w; i++) {
        pixels_[i] = new Color[h];
        for(int j=0; j<h; j++){
          pixels_[i][j] = fill;
        }
      }
        
  }
  Image::~Image()
  {
   // Free rows
        for (int i = 0; i < width_; i++) {
            delete[] pixels_[i];
        }
        // Free columns
        delete[] pixels_;
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

  //A member function that, once called, gets the mutable reference to the value of pixel (x, y).
  Color& Image::at(int x, int y)
  {
  if(x<0 || x>=width_ || y < 0 || y >= height_) throw std::invalid_argument("Coordenadas de pixel inválidas.");

  return pixels_[x][y];

  }
//A member function that, once called, gets read-only reference to the value of pixel (x, y).
  const Color& Image::at(int x, int y) const
  {
    if(x<0 || x>=width_ || y < 0 || y >= height_) throw std::invalid_argument("Coordenadas de pixel inválidas.");
    return pixels_[x][y];
  }
}
