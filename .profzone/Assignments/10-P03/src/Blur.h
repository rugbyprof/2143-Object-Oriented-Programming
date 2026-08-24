#pragma once
#include "Filter.h"

// 3×3 box blur: replaces each pixel with the average of itself and its
// eight neighbors. Border pixels (within 1 of any edge) are left unchanged.
//
// Because we need the original neighbor values — not the already-blurred ones
// — apply() works on a copy of the grid and writes results back at the end.
class Blur : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "blur"
};
