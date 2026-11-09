#pragma once
#include "Filter.h"

// Converts every pixel to gray with the luminance formula from P02:
//   gray = 0.299*r + 0.587*g + 0.114*b
class Grayscale : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;   // "grayscale"
};
