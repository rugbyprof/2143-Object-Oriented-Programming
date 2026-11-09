// FlipV.cpp — YOU implement this.

#include "FlipV.h"

#include <utility>   // std::swap

std::string FlipV::name() const {
    return "flipV";
}

void FlipV::apply(Grid& pixels) {
    // TODO: swap whole rows: row with height-1-row, stopping at the middle.
    //   std::swap on two rows (vectors) is one cheap call.
    (void)pixels;
}
