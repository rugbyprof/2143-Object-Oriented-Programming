// Image.cpp — provided (P03's Image, moved onto Matrix<Color>).

#include "Image.h"

#include "stb_image.h"
#include "stb_image_write.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <vector>

namespace {

std::string lowerExtension(const std::string& filename) {
    size_t dot = filename.rfind('.');
    if (dot == std::string::npos)
        return "";
    std::string ext = filename.substr(dot);
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return ext;
}

}  // namespace

Image::Image(int width, int height) {
    if (width < 1 || height < 1)
        throw std::invalid_argument("Image size must be at least 1 x 1");
    pixels_ = Grid(height, width);   // rows, cols — every element Color() (black)
}

Image Image::load(const std::string& filename) {
    int w = 0, h = 0, channelsInFile = 0;

    // RAII: unique_ptr frees stb's buffer on every path out of this function.
    std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
        stbi_load(filename.c_str(), &w, &h, &channelsInFile, 3),
        &stbi_image_free);

    if (!data)
        throw std::runtime_error("cannot read image '" + filename + "'");

    Image img(w, h);
    const unsigned char* bytes = data.get();
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            size_t i = (static_cast<size_t>(row) * w + col) * 3;
            img.pixels_(row, col) = Color(bytes[i], bytes[i + 1], bytes[i + 2]);
        }
    }
    return img;
}

void Image::save(const std::string& filename, int jpegQuality) const {
    const int w = width();
    const int h = height();

    std::vector<unsigned char> buf(static_cast<size_t>(w) * h * 3);
    size_t i = 0;
    for (const Color& c : pixels_) {          // Matrix begin()/end(), row-major
        buf[i++] = static_cast<unsigned char>(c.r());
        buf[i++] = static_cast<unsigned char>(c.g());
        buf[i++] = static_cast<unsigned char>(c.b());
    }

    const std::string ext = lowerExtension(filename);
    int ok = 0;
    if (ext == ".jpg" || ext == ".jpeg")
        ok = stbi_write_jpg(filename.c_str(), w, h, 3, buf.data(), jpegQuality);
    else if (ext == ".bmp")
        ok = stbi_write_bmp(filename.c_str(), w, h, 3, buf.data());
    else
        ok = stbi_write_png(filename.c_str(), w, h, 3, buf.data(), w * 3);

    if (!ok)
        throw std::runtime_error("cannot write image '" + filename + "'");
}

int Image::width() const { return pixels_.cols(); }
int Image::height() const { return pixels_.rows(); }

Color& Image::at(int row, int col) { return pixels_.at(row, col); }
const Color& Image::at(int row, int col) const { return pixels_.at(row, col); }

Grid& Image::pixels() { return pixels_; }
const Grid& Image::pixels() const { return pixels_; }

std::ostream& operator<<(std::ostream& os, const Image& img) {
    return os << "Image(" << img.width() << " x " << img.height() << ")";
}
