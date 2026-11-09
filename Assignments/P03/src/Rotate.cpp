// Rotate.cpp — YOU implement this.

#include "Rotate.h"

#include <stdexcept>

Rotate::Rotate(int degrees) : degrees_(degrees) {
    // TODO: throw std::invalid_argument if degrees_ is not 0, 90, 180, or 270
}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

void Rotate::apply(Grid& pixels) {
    // TODO: see the mapping table in the README.
    //   Build a new Grid of the right shape, copy pixels into it with the
    //   mapping, then  pixels = std::move(result);
    (void)pixels;
}
