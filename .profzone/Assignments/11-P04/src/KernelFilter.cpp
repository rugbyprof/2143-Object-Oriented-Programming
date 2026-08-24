// KernelFilter.cpp — provided as a complete example.
//
// Study this implementation before writing Image::apply().
// The convolution algorithm is identical; the only difference is that
// Image::apply() is non-destructive (returns a new Image) while this
// modifies the Grid in place.

#include "KernelFilter.h"
#include <algorithm>    // std::clamp
#include <cmath>        // std::round

KernelFilter::KernelFilter(Kernel k, std::string label)
    : kernel_(std::move(k)), label_(std::move(label)) {}

std::string KernelFilter::name() const {
    return label_;
}

void KernelFilter::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    if (height == 0) return;
    int width = static_cast<int>(pixels[0].size());

    int half = kernel_.size() / 2;

    // We must read from the original pixel values, not the ones we're
    // writing — otherwise early writes corrupt later reads.
    // Solution: work from a copy and write into the original grid.
    Grid original = pixels;

    for (int row = half; row < height - half; ++row) {
        for (int col = half; col < width - half; ++col) {
            // Convolve independently for each channel: 0=r, 1=g, 2=b
            for (int ch = 0; ch < 3; ++ch) {
                double sum = 0.0;

                // Slide the kernel window over the neighborhood.
                // kr and kc are kernel-relative indices (0 .. size-1).
                // The corresponding image pixel is at (row + kr - half, col + kc - half).
                for (int kr = 0; kr < kernel_.size(); ++kr) {
                    for (int kc = 0; kc < kernel_.size(); ++kc) {
                        int sr = row + kr - half;
                        int sc = col + kc - half;
                        sum += kernel_.at(kr, kc) * original[sr][sc][ch];
                    }
                }

                // Clamp to [0, 255] and round to nearest integer.
                // Color[ch] lets us write directly to r, g, or b by index.
                pixels[row][col][ch] = std::clamp(
                    static_cast<int>(std::round(sum)), 0, 255);
            }
        }
    }
}
