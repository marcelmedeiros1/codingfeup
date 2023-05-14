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
            if(command == "crop"){
                crop();
                continue;
            }
            if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            if(command == "rotate_right"){
                rotate_right();
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
        
         /*The code replaces all pixels with c1 color to c2 color*/
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
        /*The code replaces to color c1 a sector in the image limited by x,y (top-left corner) and w,h*/
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
        /*The code mirrors the image horizontally*/
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
        /*The code mirrors the image vertically*/
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
        /*The code copies to the current image, in a sector which the top left corner is x,y, all pixels from image stored in PNG filename, except pixels with the Color c1*/
        Color c1;
        string filename;
        int x,y;
        input >> filename >> c1 >> x >> y;
        Image* aux = loadFromPNG(filename); //New Image
        for(int i = x;i < aux->width()+x;i++){
            for(int j = y; j < aux->height()+y;j++){
                if((aux->at(i-x,j-y).red() == c1.red())&&(aux->at(i-x,j-y).green() == c1.green())&&(aux->at(i-x,j-y).blue() == c1.blue())){
                    continue;
                }else{
                   image->at(i,j) = {aux->at(i-x,j-y).red(), aux->at(i-x,j-y).green(), aux->at(i-x,j-y).blue()};
                }
            }
        }
        delete aux;
    }
    void Script::crop(){
        /*Crop the image*/
        int x,y,w,h;
        input >> x >> y >> w >> h;
        Image* aux = new Image(w,h); //Cropped image
        for(int i = x; i < w+x; i++){
            for(int j = y; j < h+y; j++){
                aux->at(i-x, j-y) = {image->at(i,j).red(), image->at(i,j).green(), image->at(i,j).blue()};
            }
        }
        clear_image_if_any(); //Clear the old image
        image = new Image(aux->width(), aux->height());
        for(int i = 0; i < aux->width(); i++){
            for(int j = 0; j < aux->height(); j++){
                image->at(i, j) = {aux->at(i,j).red(), aux->at(i,j).green(), aux->at(i,j).blue()};
            }
        }
        delete aux;
    } 
    void Script::rotate_left(){
        /*Rotate 90 degrees to the left*/
        Image* aux = new Image(image->height(), image->width());

        for (int i = 0; i < image->width(); i++) {
             for (int j = 0; j < image->height(); j++) {
                aux->at(j, image->width() - i - 1) = image->at(i, j);
         }
    }
    clear_image_if_any();
        image = new Image(aux->width(), aux->height());
        for(int i = 0; i < image->width(); i++){
            for(int j = 0; j < image->height(); j++){
                image->at(i, j) = {aux->at(i,j).red(), aux->at(i,j).green(), aux->at(i,j).blue()};
            }
        }
        delete aux;
    }

    void Script::rotate_right(){
        /*Rotate 90 degrees to the left*/
        Image* aux = new Image(image->height(), image->width());
        int h = image->height();
        int w = image->width();
        for (int i = 0; i < h; i++) {
             for (int j = 0; j < w; j++) {
                aux->at(i,j) = image->at(j, h - i -1);
         }
    }
    clear_image_if_any();
        image = new Image(aux->width(), aux->height());
        for(int i = 0; i < h; i++){
            for(int j = 0; j < w; j++){
                image->at(i, j) = {aux->at(i,j).red(), aux->at(i,j).green(), aux->at(i,j).blue()};
            }
        }
        delete aux;
    }
    
}

   


   

