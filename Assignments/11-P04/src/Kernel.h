#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

class Kernel {
public:
    // Construct a size x size zero-filled kernel.
    // size must be odd and >= 3, or the constructor throws std::invalid_argument.
    explicit Kernel(int size);

    // Construct from flat row-major values.
    // values.size() must equal size*size, or throws std::invalid_argument.
    Kernel(int size, const std::vector<double>& values);

    // Element access — throws std::out_of_range if row or col is out of bounds
    double&       at(int row, int col);
    const double& at(int row, int col) const;

    int size() const;  // side length: 3 for a 3x3 kernel, 5 for a 5x5, etc.

    // Named kernel factories — each returns a 3x3 Kernel
    static Kernel identity();      // passes the image through unchanged
    static Kernel boxBlur();       // uniform 3x3 average (all 1/9)
    static Kernel sharpen();       // amplifies center, subtracts neighbors
    static Kernel edgeDetect();    // Laplacian: bright at edges, black in flat areas
    static Kernel emboss();        // directional depth illusion (NW to SE)
    static Kernel gaussianBlur();  // weighted average, smoother than boxBlur

    // Prints the kernel as a grid of values
    friend std::ostream& operator<<(std::ostream& os, const Kernel& k);

private:
    int size_;
    std::vector<std::vector<double>> data_;  // data_[row][col]
};
