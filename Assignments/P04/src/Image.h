#pragma once

#include "Color.h"
#include "Matrix.h"

#include <ostream>
#include <string>

// The pixel grid is now a Matrix of Colors: pixels(row, col).
using Grid = Matrix<Color>;

// -----------------------------------------------------------------------
// Image — an RGB image you can load, change, and save.  (provided)
//
// Same interface as P03. What changed inside:
//   * pixels are a Matrix<Color> instead of vector<vector<Pixel>>
//   * at() just forwards to Matrix::at(), which does the bounds check
//   * save() no longer clamps: a Color can't be out of range
// -----------------------------------------------------------------------
class Image {
public:
    // A width x height image, all black. Throws std::invalid_argument if
    // either dimension is less than 1.
    Image(int width, int height);

    // Throws std::runtime_error if the file can't be read.
    static Image load(const std::string& filename);

    // .jpg/.jpeg -> JPEG, .bmp -> BMP, anything else -> PNG.
    // Throws std::runtime_error if the file can't be written.
    void save(const std::string& filename, int jpegQuality = 90) const;

    int width() const;    // columns
    int height() const;   // rows

    // Bounds-checked. Throws std::out_of_range.
    Color&       at(int row, int col);
    const Color& at(int row, int col) const;

    Grid&       pixels();
    const Grid& pixels() const;

    // Image(546 x 640)
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    Grid pixels_;
};
