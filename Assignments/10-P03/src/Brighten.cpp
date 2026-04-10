// Brighten.cpp — provided as a complete example.
//
// Study this implementation before writing the other filters.
// The nested loop pattern (iterate rows, then cols, then modify Pixel)
// is the same for every filter that operates on individual pixels.

#include "Brighten.h"
#include <string>

Brighten::Brighten(int amount) : amount_(amount) {}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount_) + ")";
}

void Brighten::apply(Grid& pixels) {
    // Outer loop: one pass per row (top to bottom)
    for (auto& row : pixels) {
        // Inner loop: one pixel per column (left to right)
        for (Pixel& p : row) {
            // Pixel channels are int, so this arithmetic is safe.
            // No clamping needed here — Image::save() clamps on write.
            p.r += amount_;
            p.g += amount_;
            p.b += amount_;
        }
    }
}
