#include "PPM.h"
#include <fstream>
#include <stdexcept>

// -------------------------------------------------------
// Constructors
// -------------------------------------------------------

PPM::PPM(int width, int height)
    : width_(width), height_(height),
      pixels_(height, std::vector<Color>(width)) {}

// -------------------------------------------------------
// Static factory: load
// -------------------------------------------------------

PPM PPM::load(const std::string& filename) {
    // TODO: open the file — throw std::runtime_error if it won't open
    // TODO: read the magic number — throw if it's not "P3"
    // TODO: read width, height, and maxval
    // TODO: construct a PPM(width, height), then fill pixels_ by reading
    //       triplets and assigning Color(r, g, b) to each pixels_[row][col]
    // TODO: return the filled PPM
    //
    // Hint: std::ifstream, f >> width_ >> height_ >> maxval
    // Hint: row-major order — pixels[0][0] is top-left, pixels[0][1] is one right, etc.
    return PPM(0, 0);  // placeholder
}

// -------------------------------------------------------
// save
// -------------------------------------------------------

void PPM::save(const std::string& filename) const {
    // TODO: open an ofstream — throw std::runtime_error if it won't open
    // TODO: write the PPM P3 header:
    //   P3
    //   <width> <height>
    //   255
    // TODO: write each pixel's r g b values separated by spaces, one row per line
    //   Hint: use operator[] on Color to get r, g, b channels:
    //         pixels_[row][col][0]  pixels_[row][col][1]  pixels_[row][col][2]
}

// -------------------------------------------------------
// Accessors
// -------------------------------------------------------

int PPM::width()  const { return width_;  }
int PPM::height() const { return height_; }

std::vector<Color>& PPM::operator[](int row) {
    // TODO: throw std::out_of_range if row is not in [0, height_)
    return pixels_[row];  // placeholder — no bounds check yet
}

const std::vector<Color>& PPM::operator[](int row) const {
    // TODO: throw std::out_of_range if row is not in [0, height_)
    return pixels_[row];  // placeholder
}

// -------------------------------------------------------
// apply — kernel convolution
// -------------------------------------------------------

PPM PPM::apply(const Kernel& k) const {
    // Start with a copy of *this so border pixels are already filled in.
    PPM result = *this;

    int half = k.size() / 2;

    // Only process pixels that have a full kernel neighborhood.
    // Rows: [half, height_ - half)
    // Cols: [half, width_  - half)
    for (int row = half; row < height_ - half; ++row) {
        for (int col = half; col < width_ - half; ++col) {

            // Accumulate a separate sum for each channel.
            double sumR = 0.0, sumG = 0.0, sumB = 0.0;

            // TODO: iterate over the kernel window:
            //   for int kr in [-half .. half]:
            //     for int kc in [-half .. half]:
            //       Color neighbor = pixels_[row + kr][col + kc];
            //       double weight  = k.at(kr + half, kc + half);
            //       sumR += neighbor[0] * weight;
            //       sumG += neighbor[1] * weight;
            //       sumB += neighbor[2] * weight;

            // TODO: assign the clamped result to result[row][col]
            //   result[row][col] = Color(
            //       static_cast<int>(sumR),
            //       static_cast<int>(sumG),
            //       static_cast<int>(sumB)
            //   );
            //   Color's constructor already clamps, so no extra work needed.
        }
    }

    return result;
}

// -------------------------------------------------------
// I/O
// -------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const PPM& img) {
    // TODO: print: PPM(<width> x <height>, <total pixels> pixels)
    //   e.g.:  PPM(640 x 480, 307200 pixels)
    return os;  // placeholder
}
