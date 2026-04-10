#include "Grayscale.h"

std::string Grayscale::name() const {
    return "grayscale";
}

void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for ([[maybe_unused]] Pixel& p : row) {
            // TODO: paste your P03 implementation here.
            //
            // Simple average:
            //   int gray = (p.r + p.g + p.b) / 3;
            //   p.r = p.g = p.b = gray;
            //
            // Luminance formula (perceptual):
            //   int gray = static_cast<int>(0.299*p.r + 0.587*p.g + 0.114*p.b);
            //   p.r = p.g = p.b = gray;
            //
            // P04 refactor (uses Color::operator[]):
            //   int gray = (p[0] + p[1] + p[2]) / 3;
            //   p = Color(gray, gray, gray);
        }
    }
}
