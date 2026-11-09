// Brighten.cpp — provided as a complete example. Read it first.
//
// Every per-pixel filter has this same shape: loop over rows, loop over
// the pixels in each row (by reference, so the change sticks), change it.

#include "Brighten.h"

Brighten::Brighten(int amount) : amount_(amount) {}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount_) + ")";
}

void Brighten::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for (Pixel& p : row) {
            // No clamping here: channels are int, and Image::save() clamps.
            p.r += amount_;
            p.g += amount_;
            p.b += amount_;
        }
    }
}
