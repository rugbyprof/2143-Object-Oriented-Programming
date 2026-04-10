// Brighten.cpp — provided as a complete example.
//
// This is your P03 implementation, unchanged. It compiles in P04 because
// Filter.h defines:  using Pixel = Color;
//
// Notice that the direct channel arithmetic (p.r += amount_) still works
// because Color stores r, g, b as public int members, just like Pixel did.
//
// For comparison, here is the same logic using Color operators:
//
//   for (auto& row : pixels)
//       for (Color& p : row)
//           p = p + Color(amount_, amount_, amount_);
//
// Which style you prefer is a matter of taste — both are correct.

#include "Brighten.h"
#include <string>

Brighten::Brighten(int amount) : amount_(amount) {}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount_) + ")";
}

void Brighten::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (Pixel& p : row) {
            p.r += amount_;
            p.g += amount_;
            p.b += amount_;
        }
    }
}
