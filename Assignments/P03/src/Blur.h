#pragma once
#include "Filter.h"

// 3x3 box blur: each pixel becomes the average of itself and its eight
// neighbors. The one-pixel border is left unchanged.  (provided)
class Blur : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;   // "blur"
};
