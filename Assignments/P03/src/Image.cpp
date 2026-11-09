// Image.cpp — provided (the P02 solution, minus toGrayscale).

#include "Image.h"

#include "stb_image.h"         // declarations only; bodies are in stb_impl.cpp
#include "stb_image_write.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <stdexcept>

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

unsigned char toByte(int channel) {
    return static_cast<unsigned char>(std::clamp(channel, 0, 255));
}

}  // namespace

Image::Image(int width, int height) {
    if (width < 1 || height < 1)
        throw std::invalid_argument("Image size must be at least 1 x 1");
    pixels_ = Grid(height, std::vector<Pixel>(width));
}

Image Image::load(const std::string& filename) {
    int w = 0, h = 0, channelsInFile = 0;

    // RAII: the unique_ptr owns the buffer stb_image allocates. Its custom
    // deleter (stbi_image_free) runs when 'data' goes out of scope, on
    // every path out of this function, including when we throw.
    std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
        stbi_load(filename.c_str(), &w, &h, &channelsInFile, 3),
        &stbi_image_free);

    if (!data)
        throw std::runtime_error("cannot read image '" + filename + "'");

    Image img(w, h);
    const unsigned char* bytes = data.get();
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            int i = (row * w + col) * 3;
            img.pixels_[row][col] = Pixel{bytes[i], bytes[i + 1], bytes[i + 2]};
        }
    }
    return img;
}

void Image::save(const std::string& filename, int jpegQuality) const {
    const int w = width();
    const int h = height();

    std::vector<unsigned char> buf(static_cast<size_t>(w) * h * 3);
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            size_t i = (static_cast<size_t>(row) * w + col) * 3;
            const Pixel& p = pixels_[row][col];
            buf[i + 0] = toByte(p.r);
            buf[i + 1] = toByte(p.g);
            buf[i + 2] = toByte(p.b);
        }
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

int Image::width() const {
    return pixels_.empty() ? 0 : static_cast<int>(pixels_[0].size());
}

int Image::height() const {
    return static_cast<int>(pixels_.size());
}

Pixel& Image::at(int row, int col) {
    if (row < 0 || row >= height() || col < 0 || col >= width())
        throw std::out_of_range("Image::at(" + std::to_string(row) + ", " +
                                std::to_string(col) + ") is outside the image");
    return pixels_[row][col];
}

const Pixel& Image::at(int row, int col) const {
    // Reuse the non-const version instead of copying its bounds check.
    return const_cast<Image*>(this)->at(row, col);
}

Grid& Image::pixels() { return pixels_; }
const Grid& Image::pixels() const { return pixels_; }

std::ostream& operator<<(std::ostream& os, const Image& img) {
    return os << "Image(" << img.width() << " x " << img.height() << ")";
}
