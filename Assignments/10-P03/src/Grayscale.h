#pragma once
#include "Filter.h"

// Converts every pixel to grayscale.
//
// Grayscale means setting r = g = b = some single luminance value.
// Two formulas — pick one:
//
//   Simple average:   gray = (r + g + b) / 3
//
//   Luminance (perceptual): gray = 0.299*r + 0.587*g + 0.114*b
//     Weights more green because the human eye is more sensitive to green.
//     This formula was used in P01's starter code.
class Grayscale : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "grayscale"
};
