#pragma once
#include "Filter.h"

// Flips the image vertically (mirror top-bottom).
//
// After FlipV, the pixel that was at (row, col) ends up at
// (height - 1 - row, col).
//
// Hint: swap row 0 with row height-1, row 1 with row height-2,
//       and so on up to the midpoint.
//       std::swap works on entire rows (std::vector<Pixel>) at once.
class FlipV : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "flipV"
};
