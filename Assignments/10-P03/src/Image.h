#pragma once

#include <iostream>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Pixel — one RGB pixel, three integer channels in [0, 255].
//
// Storing channels as int (not unsigned char) keeps filter arithmetic
// clean: you can add, subtract, and multiply without casting and without
// risk of silent unsigned overflow.
//
// Image::save() clamps each channel back to [0, 255] before writing.
// -----------------------------------------------------------------------
struct Pixel {
    int r = 0;
    int g = 0;
    int b = 0;

    Pixel() = default;
    Pixel(int r, int g, int b) : r(r), g(g), b(b) {}
};

// Stream operator so you can: std::cout << img[row][col] << "\n";
// Prints: (255,128,0)
inline std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    return os << '(' << p.r << ',' << p.g << ',' << p.b << ')';
}


// -----------------------------------------------------------------------
// Image — a 2D grid of pixels backed by stb_image.
//
// Loading and saving support PNG, JPG, BMP, TGA, and more.
// The format on save is chosen automatically from the file extension:
//   .jpg / .jpeg  ->  lossy JPEG (default quality 90)
//   anything else ->  lossless PNG
//
// Interface is intentionally identical to PPM so you can swap the two
// classes without touching any of the image-processing loops.
//
// Usage:
//
//   Image img = Image::load("photo.jpg");
//
//   for (int row = 0; row < img.height(); ++row) {
//       for (int col = 0; col < img.width(); ++col) {
//           int gray = 0.299 * img[row][col].r
//                    + 0.587 * img[row][col].g
//                    + 0.114 * img[row][col].b;
//           img[row][col] = Pixel(gray, gray, gray);
//       }
//   }
//
//   img.save("gray.png");    // saves as PNG
//   img.save("gray.jpg");    // saves as JPEG (quality 90)
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
    std::vector<Pixel>&       operator[](int row);
    const std::vector<Pixel>& operator[](int row) const;

    // Direct access to the underlying pixel grid.
    // Used by Pipeline to pass the grid to each Filter::apply().
    std::vector<std::vector<Pixel>>&       pixels();
    const std::vector<std::vector<Pixel>>& pixels() const;

    // Prints a compact summary, e.g.: Image(640 x 480, 307200 pixels)
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

private:
    int _width;
    int _height;

    // Row-major storage: _pixels[row][col].
    // This mirrors the layout of the raw stb_image byte buffer,
    // which also stores pixels left-to-right, top-to-bottom.
    std::vector<std::vector<Pixel>> _pixels;
};
