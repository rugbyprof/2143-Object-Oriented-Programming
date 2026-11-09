#pragma once

#include "Pixel.h"

#include <ostream>
#include <string>
#include <vector>

// A 2D grid of pixels, row-major: grid[row][col], top-left is [0][0].
using Grid = std::vector<std::vector<Pixel>>;

// -----------------------------------------------------------------------
// Image — an RGB image you can load, change, and save.  (header provided)
//
// You implement every member function in Image.cpp.
//
// Design notes:
//   * The pixels are private. The only ways in are at() (bounds-checked)
//     and pixels() (whole-grid access, used by the filter pipeline in P03).
//   * width() and height() are COMPUTED from the grid, not stored in
//     separate member variables. If a later filter rotates the grid,
//     the width and height can never be stale. One source of truth.
//   * Errors are reported by throwing exceptions, not by printing.
//     Image doesn't know whether it's running in a terminal, a test, or
//     a GUI, so it lets the caller decide what to do (see main.cpp).
// -----------------------------------------------------------------------
class Image {
public:
    // A width x height image, all black. Throws std::invalid_argument if
    // either dimension is less than 1.
    Image(int width, int height);

    // Static factory: reads any format stb_image supports (PNG, JPG, BMP...)
    // and converts it to 3-channel RGB.
    // Throws std::runtime_error if the file can't be read.
    static Image load(const std::string& filename);

    // Writes the image. The format comes from the extension:
    //   .jpg / .jpeg -> JPEG (jpegQuality 1-100)
    //   .bmp         -> BMP
    //   anything else -> PNG
    // Every channel is clamped to [0, 255] first.
    // Throws std::runtime_error if the file can't be written.
    void save(const std::string& filename, int jpegQuality = 90) const;

    int width() const;    // number of columns
    int height() const;   // number of rows

    // Bounds-checked pixel access. Throws std::out_of_range.
    Pixel&       at(int row, int col);
    const Pixel& at(int row, int col) const;

    // Direct access to the whole grid (used by filters in P03).
    Grid&       pixels();
    const Grid& pixels() const;

    // Converts every pixel to gray using the luminance formula:
    //   gray = 0.299*r + 0.587*g + 0.114*b
    void toGrayscale();

    // Prints a short summary: Image(546 x 640)
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    Grid pixels_;
};
