#pragma once
#include "Filter.h"

// Mirrors the image left-to-right. Dimensions don't change.
// pixels(row, col) moves to (row, width - 1 - col).
class FlipH : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;   // "flipH"
};
