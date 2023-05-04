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
            if (command == "replace"){
                replace();
                continue;
            }
            if(command == "fill"){
                fill();
                continue;
            }
            if(command == "h_mirror"){
                h_mirror();
                continue;
            }
            if(command == "v_mirror"){
                v_mirror();
                continue;
            }
            if(command == "add"){
                add();
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
    void Script::replace(){
        
        
        Color c1,c2;
        input >> c1 >> c2;
        for (int i = 0; i < image->width(); i++) {
            for(int j=0; j<image->height(); j++){
                if((image->at(i,j).red() == c1.red())&&(image->at(i,j).green() == c1.green())&&(image->at(i,j).blue() == c1.blue())){
                    image->at(i,j).red() = c2.red();
                    image->at(i,j).blue() = c2.blue();
                    image->at(i,j).green() = c2.green();
                }
            }
        }
    }
    void Script::fill(){
        int x,y,w,h;
        Color c1;
        input >> x >> y >> w >> h >> c1;
        for (int i = x; i < x + w; i++) {
            for(int j=y; j< y + h; j++){
                image->at(i,j).red() = c1.red();
                image->at(i,j).green() = c1.green();
                image->at(i,j).blue() = c1.blue();
            }
        }
    }
    void Script::h_mirror(){
        Color aux;
        for (int i = 0; i < image->width()/2; i++){
            for(int j=0; j < image->height(); j++){
                aux = image->at(i, j);
                image->at(i, j) = image->at(image->width()-1 - i, j);
                image->at(image->width()-1 - i, j) = aux;
            }
        }
    }
    void Script::v_mirror(){
        Color aux;
        for (int i = 0; i < image->width(); i++){
            for(int j=0; j < image->height()/2; j++){
                aux = image->at(i, j);
                image->at(i, j) = image->at(i, image->height()-1-j);
                image->at(i,image->height()-1-j) = aux;
            }
        }
    }
    void Script::add(){
        Color c1;
        string filename;
        int x,y;
        input >> filename >> c1 >> x >> y;
        Image* aux = loadFromPNG(filename);
        for(int i = x;i < image->width() + x;i++){
            for(int j = y; y < image->height() + y;j++){
                if((aux->at(i,j).red() == c1.red())&&(aux->at(i,j).green() == c1.green())&&(aux->at(i,j).blue() == c1.blue())){
                    continue;
                }else{
                    image->at(i-x,j-y) = aux->at(i,j);
                }
            }
        }

    }
}
   

