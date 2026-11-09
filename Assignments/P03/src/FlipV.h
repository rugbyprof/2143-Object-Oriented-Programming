#pragma once
#include "Filter.h"

// Mirrors the image top-to-bottom. Dimensions don't change.
// The pixel at (row, col) moves to (height - 1 - row, col).
class FlipV : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;   // "flipV"
};
