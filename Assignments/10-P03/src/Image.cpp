// Image.cpp — implementation of Image and the stb_image libraries.
//
// IMPORTANT: the two macros below must be defined in EXACTLY ONE .cpp file
// across the whole project. Defining them here tells the compiler to emit
// the actual function bodies from the stb headers. Every other .cpp that
// includes the stb headers must do so WITHOUT these macros.

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include <algorithm>    // std::transform, std::clamp
#include <cctype>       // ::tolower
#include <stdexcept>    // std::runtime_error, std::out_of_range

// -----------------------------------------------------------------------
// Internal helper: lowercase a string (used for extension detection).
// -----------------------------------------------------------------------
static std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


// -----------------------------------------------------------------------
// Constructor: blank image
// -----------------------------------------------------------------------

Image::Image(int width, int height)
    : _width(width), _height(height),
      _pixels(height, std::vector<Pixel>(width)) {
    // _pixels is initialized to height rows, each with width default Pixels.
    // Default Pixel is (0, 0, 0) — pure black.
}


// -----------------------------------------------------------------------
// Image::load
//
// stbi_load() returns a flat byte array arranged as:
//
//   [ R G B | R G B | R G B | ... ]
//     pixel 0  pixel 1  pixel 2   ...
//
// Pixels are stored left-to-right, top-to-bottom (row-major).
// The pixel at (row, col) starts at byte index (row * width + col) * 3.
//
// We copy each triplet into our 2D _pixels grid and then free the stb buffer.
// After this function returns, the Image owns its data and stb is done.
// -----------------------------------------------------------------------

Image Image::load(const std::string& filename) {
    int width = 0, height = 0, channels = 0;

    // The third argument receives the number of channels in the file.
    // The fourth argument (3) forces stb to give us exactly 3 channels (RGB)
    // regardless of what the file contains:
    //   - RGBA images: alpha channel is dropped
    //   - Grayscale images: single channel is copied into all three
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if (!data) {
        throw std::runtime_error("Image::load — cannot read file: " + filename);
    }

    Image img(width, height);

    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            // Index into the flat buffer for pixel (row, col).
            // Multiply by 3 because each pixel occupies 3 bytes (R, G, B).
            int idx = (row * width + col) * 3;

            // stb gives us unsigned char [0,255]; Pixel stores int — safe conversion.
            img._pixels[row][col] = Pixel(data[idx + 0],   // R
                                          data[idx + 1],   // G
                                          data[idx + 2]);  // B
        }
    }

    stbi_image_free(data);  // stb allocated this buffer — stb must free it
    return img;
}


// -----------------------------------------------------------------------
// Image::save
//
// We do the reverse of load: flatten our 2D _pixels grid back into a
// flat unsigned char array, clamping each int channel to [0, 255].
//
// stbi_write_png and stbi_write_jpg both want:
//   [ R G B | R G B | ... ]  left-to-right, top-to-bottom
//
// The "stride" argument to stbi_write_png is bytes per row = width * 3.
// -----------------------------------------------------------------------

void Image::save(const std::string& filename, int jpegQuality) const {
    std::vector<unsigned char> buf(_width * _height * 3);

    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            int idx = (row * _width + col) * 3;

            // Clamp each int channel back to [0, 255] before packing into bytes.
            // This means filters can write values outside the range freely and
            // save() will handle it — no need to clamp in every filter.
            buf[idx + 0] = static_cast<unsigned char>(std::clamp(_pixels[row][col].r, 0, 255));
            buf[idx + 1] = static_cast<unsigned char>(std::clamp(_pixels[row][col].g, 0, 255));
            buf[idx + 2] = static_cast<unsigned char>(std::clamp(_pixels[row][col].b, 0, 255));
        }
    }

    // Detect output format from file extension.
    size_t dot = filename.rfind('.');
    std::string ext = (dot != std::string::npos)
                      ? toLower(filename.substr(dot))
                      : "";

    int ok = 0;
    if (ext == ".jpg" || ext == ".jpeg") {
        // Quality 0 = worst / smallest, 100 = best / largest.
        // 90 is a good default — visually lossless for most images.
        ok = stbi_write_jpg(filename.c_str(), _width, _height, 3,
                            buf.data(), jpegQuality);
    } else {
        ok = stbi_write_png(filename.c_str(), _width, _height, 3,
                            buf.data(), _width * 3);
    }

    if (!ok) {
        throw std::runtime_error("Image::save — cannot write file: " + filename);
    }
}


// -----------------------------------------------------------------------
// Accessors
// -----------------------------------------------------------------------

int Image::width()  const { return _width;  }
int Image::height() const { return _height; }

std::vector<Pixel>& Image::operator[](int row) {
    if (row < 0 || row >= _height)
        throw std::out_of_range("Image: row " + std::to_string(row) +
                                " out of range [0, " + std::to_string(_height) + ")");
    return _pixels[row];
}

const std::vector<Pixel>& Image::operator[](int row) const {
    if (row < 0 || row >= _height)
        throw std::out_of_range("Image: row " + std::to_string(row) +
                                " out of range [0, " + std::to_string(_height) + ")");
    return _pixels[row];
}

std::vector<std::vector<Pixel>>& Image::pixels() {
    return _pixels;
}

const std::vector<std::vector<Pixel>>& Image::pixels() const {
    return _pixels;
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    return os << "Image(" << img._width << " x " << img._height
              << ", " << (img._width * img._height) << " pixels)";
}
