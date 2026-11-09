// KernelFilter.cpp — provided. Study apply(): it's the whole idea of
// convolution in about fifteen lines.

#include "KernelFilter.h"

#include <cmath>
#include <utility>

KernelFilter::KernelFilter(Kernel kernel, std::string label)
    : kernel_(std::move(kernel)), label_(std::move(label)) {}

std::string KernelFilter::name() const {
    return label_;
}

void KernelFilter::apply(Grid& pixels) {
    const int size = kernel_.size();
    const int half = size / 2;
    const int rows = pixels.rows();
    const int cols = pixels.cols();

    // Read from an untouched copy; write into 'pixels'. (Same reason as
    // P03's Blur: don't let already-changed pixels feed their neighbors.)
    const Grid source = pixels;

    // The 'half'-wide border has no full neighborhood, so it's left as is.
    for (int row = half; row < rows - half; ++row) {
        for (int col = half; col < cols - half; ++col) {
            double sum[3] = {0.0, 0.0, 0.0};

            for (int kr = 0; kr < size; ++kr) {
                for (int kc = 0; kc < size; ++kc) {
                    const Color& neighbor = source(row + kr - half, col + kc - half);
                    const double weight = kernel_(kr, kc);
                    for (int ch = 0; ch < 3; ++ch)
                        sum[ch] += weight * neighbor[ch];   // Color::operator[]
                }
            }

            // Sums can be negative or above 255 (sharpen, edgeDetect).
            // Accumulate in double, then let Color's constructor clamp once.
            pixels(row, col) = Color(static_cast<int>(std::lround(sum[0])),
                                     static_cast<int>(std::lround(sum[1])),
                                     static_cast<int>(std::lround(sum[2])));
        }
    }
}
