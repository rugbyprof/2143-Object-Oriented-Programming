#pragma once

#include "Color.h"
#include <iostream>
#include <string>
#include <vector>

// Forward declaration — full definition in Kernel.h.
// Using a forward declaration here keeps Image.h from pulling in Kernel.h
// everywhere Image.h is included.
class Kernel;

// -----------------------------------------------------------------------
// Image — a 2D grid of Color pixels backed by stb_image.
//
// P04 update: Pixel is gone. Every cell is a Color, which carries the
// arithmetic operators (+, *, []) students implement in Part 1.
// Filters from P03 continue to compile unchanged because Filter.h
// defines:  using Pixel = Color;
//
// Loading and saving support PNG, JPG, BMP, TGA, and more.
// The format on save is chosen automatically from the file extension:
//   .jpg / .jpeg  ->  lossy JPEG (default quality 90)
//   anything else ->  lossless PNG
//
// Usage:
//
//   Image img = Image::load("photo.jpg");
//
//   for (int row = 0; row < img.height(); ++row) {
//       for (int col = 0; col < img.width(); ++col) {
//           // Color operators make filter math cleaner than raw r/g/b:
//           img[row][col] = img[row][col] * 0.5;   // darken
//       }
//   }
//
//   img.save("dark.png");     // PNG
//   img.save("dark.jpg");     // JPEG (quality 90)
//
//   // Non-destructive kernel convolution (returns a new Image):
//   Image blurred = img.apply(Kernel::boxBlur());
//   img.save("original.png");   // img is unchanged
//   blurred.save("blurred.png");
// -----------------------------------------------------------------------
class Image {
public:
    // Create a blank (all-black) image of the given dimensions.
    Image(int width, int height);

    // Load from any format stb_image supports: PNG, JPG, BMP, TGA, ...
    // Always converts to 3-channel RGB (alpha is dropped; grayscale is expanded).
    // Throws std::runtime_error if the file cannot be read.
    static Image load(const std::string& filename);

    // Save to disk.  Format is inferred from the extension:
    //   .jpg / .jpeg  ->  stbi_write_jpg (lossy, jpegQuality 0–100)
    //   anything else ->  stbi_write_png (lossless)
    // Channels are clamped to [0, 255] before writing.
    // Throws std::runtime_error if the file cannot be written.
    void save(const std::string& filename, int jpegQuality = 90) const;

    int width()  const;
    int height() const;

    // 2D access: img[row][col]
    //   row 0   = top edge      row height()-1  = bottom edge
    //   col 0   = left edge     col width()-1   = right edge
    //
    // Throws std::out_of_range if the index is out of bounds.
    std::vector<Color>&       operator[](int row);
    const std::vector<Color>& operator[](int row) const;

    // Direct access to the underlying pixel grid.
    // Used by Pipeline to pass the grid to each Filter::apply().
    std::vector<std::vector<Color>>&       pixels();
    const std::vector<std::vector<Color>>& pixels() const;

    // Apply a convolution kernel and return a NEW image (non-destructive).
    // The original image is unchanged — this is the correct design for
    // chaining multiple kernel passes without destroying intermediate results:
    //
    //   Image pass1 = img.apply(Kernel::gaussianBlur());
    //   Image pass2 = pass1.apply(Kernel::edgeDetect());
    //
    // Border pixels (within half of any edge) are copied unchanged.
    // See Kernel.h for boundary strategy details.
    Image apply(const Kernel& k) const;

    // Prints a compact summary, e.g.: Image(640 x 480, 307200 pixels)
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    int _width;
    int _height;

    // Row-major storage: _pixels[row][col].
    // This mirrors the layout of the raw stb_image byte buffer,
    // which also stores pixels left-to-right, top-to-bottom.
    std::vector<std::vector<Color>> _pixels;
};
