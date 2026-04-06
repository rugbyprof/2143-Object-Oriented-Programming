#pragma once
#include "Color.h"
#include "Kernel.h"
#include <iostream>
#include <string>
#include <vector>

class PPM {
public:
    // Construct a width x height black image (all pixels are Color())
    PPM(int width, int height);

    // Load a PPM P3 file — throws std::runtime_error if the file can't be opened
    // or the format is not "P3"
    static PPM load(const std::string& filename);

    // Save to a PPM P3 file
    void save(const std::string& filename) const;

    int width()  const;
    int height() const;

    // Pixel access by row — returns a reference to the row vector
    // Use as: img[row][col]
    std::vector<Color>&       operator[](int row);
    const std::vector<Color>& operator[](int row) const;

    // Apply a convolution kernel and return a NEW PPM.
    // The original is never modified.
    // Border pixels (within kernel.size()/2 of any edge) are copied unchanged.
    PPM apply(const Kernel& k) const;

    // Prints a compact summary: PPM(640 x 480, 307200 pixels)
    friend std::ostream& operator<<(std::ostream& os, const PPM& img);

private:
    int width_;
    int height_;
    std::vector<std::vector<Color>> pixels_;  // pixels_[row][col]
};
