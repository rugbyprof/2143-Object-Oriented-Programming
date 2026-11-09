#pragma once

#include "Matrix.h"

#include <ostream>

// -----------------------------------------------------------------------
// Kernel — a square grid of weights for convolution.
// (header provided; YOU implement the marked parts of Kernel.cpp)
//
// Convolution replaces each pixel with a weighted sum of its neighbors.
// The weights are the kernel. Change the numbers and the same loop
// blurs, sharpens, finds edges, or embosses.
//
// Kernel HAS-A Matrix<double> (composition): the same class template
// that stores the image's Colors stores these weights.
//
//   Kernel k = Kernel::sharpen();
//   std::cout << k;           // [0, -1, 0]
//                             // [-1, 5, -1]
//                             // [0, -1, 0]
// -----------------------------------------------------------------------
class Kernel {
public:
    // Throws std::invalid_argument unless weights is square with an odd
    // side of at least 3 (3x3, 5x5, ...). A kernel needs a center cell.
    explicit Kernel(Matrix<double> weights);

    int size() const;                          // side length: 3 for 3x3
    double operator()(int r, int c) const;     // weight at (r, c)

    // Sum of all weights. 1.0 keeps overall brightness the same.
    // 0.0 turns flat areas black (only edges stay bright).
    double sum() const;

    // Named kernels (static factory methods). All 3x3. Values in README.
    static Kernel identity();
    static Kernel boxBlur();
    static Kernel gaussianBlur();
    static Kernel sharpen();
    static Kernel edgeDetect();
    static Kernel emboss();

    // Prints the weights with Matrix's operator<<.
    friend std::ostream& operator<<(std::ostream& os, const Kernel& k);

private:
    Matrix<double> weights_;
};
