#pragma once
#include "Filter.h"
#include <algorithm>  // std::swap

// Mirrors the image left-to-right (horizontal flip).
// Image dimensions are unchanged.
class FlipH : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "flipH"
};
