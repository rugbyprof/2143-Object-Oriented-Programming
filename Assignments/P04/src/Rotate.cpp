// Rotate.cpp — YOU port your P03 version to Matrix<Color>.
//
// The constructor carries over unchanged. In apply(), build the result as
//   Grid result(newRows, newCols);
// and index with result(r, c) instead of result[r][c].

#include "Rotate.h"

#include <stdexcept>
#include <utility>

Rotate::Rotate(int degrees) : degrees_(degrees) {
    if (degrees_ != 0 && degrees_ != 90 && degrees_ != 180 && degrees_ != 270)
        throw std::invalid_argument("Rotate: degrees must be 0, 90, 180, or 270");
}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

void Rotate::apply(Grid& pixels) {
    // TODO
    (void)pixels;
}
