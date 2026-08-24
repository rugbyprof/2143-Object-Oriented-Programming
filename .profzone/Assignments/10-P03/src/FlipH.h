#pragma once
#include "Filter.h"

// Flips the image horizontally (mirror left-right).
//
// After FlipH, the pixel that was at (row, col) ends up at
// (row, width - 1 - col).
//
// Hint: for each row, swap col 0 with col width-1,
//       col 1 with col width-2, and so on up to the midpoint.
//       std::swap works on Pixels directly.
class FlipH : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "flipH"
};
