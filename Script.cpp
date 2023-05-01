#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            }
            //Added the conditional branches to access the private functions.
            if (command == "invert"){
                invert();
                continue;
            }
            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            // TODO ...

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    //Transforms each individual pixel (r,g,b) to (255-r,255-g,255-b).
    void Script::invert(){
        /*The code runs the width and height of the current image
        getting each individual pixel and inverting its atribute*/
        for (int i = 0; i < image->width(); i++) {
            for(int j=0; j<image->height(); j++){
                image->at(i,j).red() = 255 - image->at(i,j).red();
                image->at(i,j).green() = 255 - image->at(i,j).green();
                image->at(i,j).blue() = 255 - image->at(i,j).blue();
            }
      }
    }
    //Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3. You should use integer division without rounding to compute v.
    void Script::to_gray_scale(){
        /*The code runs the width and height of the current image
        getting each individual pixel and setting its atribute to
        a uniform value equal to the medium of the colors of the current pixel*/
        for (int i = 0; i < image->width(); i++) {
            for(int j=0; j<image->height(); j++){
                int v = ( image->at(i,j).red() + image->at(i,j).green() +image->at(i,j).blue() ) / 3;
                image->at(i,j).red() = v;
                image->at(i,j).green() = v;
                image->at(i,j).blue() = v;
            }
        }
    }
}
