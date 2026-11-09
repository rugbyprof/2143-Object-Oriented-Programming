// Image.cpp — YOU implement every Image member function.
//
// The README walks through each one. Do them in this order:
//   width/height -> constructor -> pixels -> at -> operator<< ->
//   load -> save -> toGrayscale

#include "Image.h"

#include "stb_image.h"         // declarations only; bodies are in stb_impl.cpp
#include "stb_image_write.h"

#include <algorithm>   // std::clamp, std::transform
#include <memory>      // std::unique_ptr
#include <stdexcept>   // std::invalid_argument, std::out_of_range, std::runtime_error

Image::Image(int width, int height) {
    // TODO: throw std::invalid_argument if width or height < 1
    // TODO: make pixels_ a grid of 'height' rows, each 'width' black Pixels
    (void)width;   // remove these two lines when you implement this
    (void)height;
}

Image Image::load(const std::string& filename) {
    // TODO: see "Image::load and RAII" in the README.
    //   - stbi_load(filename.c_str(), &w, &h, &channelsInFile, 3)
    //   - wrap the result in a std::unique_ptr with stbi_image_free as its deleter
    //   - throw std::runtime_error if it is null
    //   - copy the bytes into a new Image, 3 bytes (r, g, b) per pixel
    (void)filename;
    return Image(1, 1);   // placeholder
}

void Image::save(const std::string& filename, int jpegQuality) const {
    // TODO: see "Image::save" in the README.
    //   - flatten pixels_ into a vector<unsigned char>, clamping to [0, 255]
    //   - choose stbi_write_jpg / stbi_write_bmp / stbi_write_png by extension
    //   - throw std::runtime_error if the write fails
    (void)filename;
    (void)jpegQuality;
}

int Image::width() const {
    return 0;   // TODO: number of columns (careful: the grid may be empty)
}

int Image::height() const {
    return 0;   // TODO: number of rows
}

Pixel& Image::at(int row, int col) {
    // TODO: throw std::out_of_range if (row, col) is outside the image
    return pixels_[row][col];
}

const Pixel& Image::at(int row, int col) const {
    // TODO: same check as above
    return pixels_[row][col];
}

Grid& Image::pixels() { return pixels_; }
const Grid& Image::pixels() const { return pixels_; }

void Image::toGrayscale() {
    // TODO: gray = 0.299*r + 0.587*g + 0.114*b, then r = g = b = gray
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    // TODO: print  Image(<width> x <height>)
    (void)img;
    return os;
}
