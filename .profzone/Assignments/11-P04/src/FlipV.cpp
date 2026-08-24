#include "FlipV.h"
#include <algorithm>    // std::swap

std::string FlipV::name() const {
    return "flipV";
}

void FlipV::apply(Grid& pixels) {
    (void)pixels;  // remove this line when implementing
    // TODO: paste your P03 implementation here.
    //
    //   int height = pixels.size();
    //   for (int row = 0; row < height / 2; ++row) {
    //       std::swap(pixels[row], pixels[height - 1 - row]);
    //   }
}
