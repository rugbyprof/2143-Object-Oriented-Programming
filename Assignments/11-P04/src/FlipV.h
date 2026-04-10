#pragma once
#include "Filter.h"
#include <algorithm>  // std::swap

// Mirrors the image top-to-bottom (vertical flip).
// Image dimensions are unchanged.
class FlipV : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "flipV"
};
