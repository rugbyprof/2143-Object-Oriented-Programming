#include "Kernel.h"
#include <iomanip>
#include <sstream>

// -------------------------------------------------------
// Constructors
// -------------------------------------------------------

Kernel::Kernel(int size)
    : size_(size), data_(size, std::vector<double>(size, 0.0)) {
    if (size < 3 || size % 2 == 0) {
        throw std::invalid_argument("kernel size must be an odd number >= 3");
    }
}

Kernel::Kernel(int size, const std::vector<double>& values)
    : size_(size), data_(size, std::vector<double>(size, 0.0)) {
    if (size < 3 || size % 2 == 0) {
        throw std::invalid_argument("kernel size must be an odd number >= 3");
    }
    if (static_cast<int>(values.size()) != size * size) {
        throw std::invalid_argument("values.size() must equal size * size");
    }
    // TODO: unpack the flat row-major vector into data_[row][col]
    //   Hint: data_[r][c] = values[r * size_ + c]
}

// -------------------------------------------------------
// Element access
// -------------------------------------------------------

double& Kernel::at(int row, int col) {
    // TODO: throw std::out_of_range if row or col is not in [0, size_)
    // TODO: return data_[row][col]
    return data_[row][col];  // placeholder — no bounds check yet
}

const double& Kernel::at(int row, int col) const {
    // TODO: same as above, const version
    return data_[row][col];  // placeholder
}

int Kernel::size() const { return size_; }

// -------------------------------------------------------
// Named kernel factories
// -------------------------------------------------------

Kernel Kernel::identity() {
    // A kernel that does nothing: every pixel maps to itself.
    // The only nonzero value is 1.0 in the exact center.
    //
    //   0  0  0
    //   0  1  0
    //   0  0  0
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

Kernel Kernel::boxBlur() {
    // Every value is 1/9 — the output pixel is the simple average of its
    // 3x3 neighborhood including itself. The kernel sum is exactly 1.0,
    // so overall brightness is preserved.
    //
    //   1/9  1/9  1/9
    //   1/9  1/9  1/9
    //   1/9  1/9  1/9
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

Kernel Kernel::sharpen() {
    // Boosts the center pixel and subtracts the direct (non-diagonal) neighbors.
    // The kernel sum is 1.0, so a flat region passes through unchanged.
    // At an edge, where neighbors differ, the difference is amplified.
    //
    //    0  -1   0
    //   -1   5  -1
    //    0  -1   0
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

Kernel Kernel::edgeDetect() {
    // Laplacian edge detector. The kernel sum is 0, so flat (uniform) regions
    // produce 0 output (black). Where neighboring pixels differ — an edge —
    // the sum is nonzero and the output is bright.
    //
    //   -1  -1  -1
    //   -1   8  -1
    //   -1  -1  -1
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

Kernel Kernel::emboss() {
    // Creates the illusion of a raised surface by replacing each pixel with
    // a shadow/highlight based on the NW-to-SE luminance gradient.
    // The kernel sums to 1.0 so mid-gray areas stay mid-gray.
    //
    //   -2  -1   0
    //   -1   1   1
    //    0   1   2
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

Kernel Kernel::gaussianBlur() {
    // 3x3 approximation of a 2-D Gaussian distribution.
    // Center weight is highest; diagonals are lowest.
    // The kernel sums to 1.0 (divide each entry by 16).
    //
    //   1  2  1       1/16  2/16  1/16
    //   2  4  2  -->  2/16  4/16  2/16
    //   1  2  1       1/16  2/16  1/16
    //
    // TODO: build and return this kernel
    return Kernel(3);  // placeholder
}

// -------------------------------------------------------
// I/O
// -------------------------------------------------------

std::ostream& operator<<(std::ostream& os, [[maybe_unused]] const Kernel& k) {
    // TODO: print the kernel as a grid, one row per line.
    //   Format each value with a fixed width so columns align.
    //   Example for boxBlur:
    //     [ 0.111  0.111  0.111 ]
    //     [ 0.111  0.111  0.111 ]
    //     [ 0.111  0.111  0.111 ]
    //   Hint: std::setw and std::fixed from <iomanip> will help.
    return os;  // placeholder
}
