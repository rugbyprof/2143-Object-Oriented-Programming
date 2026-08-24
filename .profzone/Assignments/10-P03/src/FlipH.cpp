#include "FlipH.h"
#include <algorithm>    // std::swap

std::string FlipH::name() const {
    return "flipH";
}

void FlipH::apply(Grid& pixels) {
    (void)pixels;  // remove this line when implementing
    // TODO: iterate over every row and reverse it left-to-right.
    //
    // Hint: for each row, swap pixels at mirror positions:
    //   for (auto& row : pixels) {
    //       int width = row.size();
    //       for (int col = 0; col < width / 2; ++col) {
    //           std::swap(row[col], row[width - 1 - col]);
    //       }
    //   }
}
