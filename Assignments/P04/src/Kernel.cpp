// Kernel.cpp — YOU implement the functions marked TODO.

#include "Kernel.h"

#include <stdexcept>
#include <utility>

Kernel::Kernel(Matrix<double> weights) : weights_(std::move(weights)) {
    // TODO: throw std::invalid_argument unless weights_ is square, with an
    //   odd size of at least 3
}

int Kernel::size() const { return weights_.rows(); }

double Kernel::operator()(int r, int c) const { return weights_(r, c); }

double Kernel::sum() const {
    return 0.0;   // TODO: add up every weight (a range-for over weights_ works)
}

// ---- Named kernels. Values are in the README's kernel table. ----
//
// The initializer-list constructor makes these short:
//   return Kernel(Matrix<double>(3, 3, {0, 0, 0,
//                                       0, 1, 0,
//                                       0, 0, 0}));

Kernel Kernel::identity() {
    return Kernel(Matrix<double>(3, 3, {0, 0, 0,
                                        0, 1, 0,
                                        0, 0, 0}));   // provided as the example
}

Kernel Kernel::boxBlur() {
    return identity();   // TODO
}

Kernel Kernel::gaussianBlur() {
    return identity();   // TODO (hint: build the 1 2 1 grid, then forEach to divide by 16)
}

Kernel Kernel::sharpen() {
    return identity();   // TODO
}

Kernel Kernel::edgeDetect() {
    return identity();   // TODO
}

Kernel Kernel::emboss() {
    return identity();   // TODO
}

std::ostream& operator<<(std::ostream& os, const Kernel& k) {
    (void)k;
    return os;   // TODO: one line, using Matrix's operator<<
}
