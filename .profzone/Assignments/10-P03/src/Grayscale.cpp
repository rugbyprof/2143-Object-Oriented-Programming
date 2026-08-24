#include "Grayscale.h"

std::string Grayscale::name() const {
    return "grayscale";
}

void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for ([[maybe_unused]] Pixel& p : row) {
            // TODO: compute a single gray value from p.r, p.g, p.b
            //   Simple average:  int gray = (p.r + p.g + p.b) / 3;
            //   Luminance:       int gray = static_cast<int>(0.299*p.r + 0.587*p.g + 0.114*p.b);

            // TODO: set all three channels to gray
            //   p.r = gray;
            //   p.g = gray;
            //   p.b = gray;
        }
    }
}
