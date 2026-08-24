// Blur.cpp — provided as a complete example.
//
// This is more complex than Brighten because we need neighbor pixels.
// The key insight: always read from the ORIGINAL grid, write to a copy,
// then replace the original at the end. If you read from the same grid
// you're modifying, early pixels will influence later ones and the blur
// will be uneven.

#include "Blur.h"

std::string Blur::name() const {
    return "blur";
}

void Blur::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    if (height == 0) return;
    int width  = static_cast<int>(pixels[0].size());

    // Work on a full copy so every read uses the unmodified original.
    Grid result = pixels;

    // Skip the one-pixel border (rows 0 and height-1, cols 0 and width-1).
    // Those pixels don't have a full 3x3 neighborhood, so we leave them as-is.
    for (int row = 1; row < height - 1; ++row) {
        for (int col = 1; col < width - 1; ++col) {

            int sumR = 0, sumG = 0, sumB = 0;

            // Accumulate all 9 pixels in the 3x3 window centered on (row, col).
            for (int kr = -1; kr <= 1; ++kr) {
                for (int kc = -1; kc <= 1; ++kc) {
                    const Pixel& neighbor = pixels[row + kr][col + kc];
                    sumR += neighbor.r;
                    sumG += neighbor.g;
                    sumB += neighbor.b;
                }
            }

            // Integer division by 9 — slight truncation is fine for a blur.
            result[row][col] = Pixel(sumR / 9, sumG / 9, sumB / 9);
        }
    }

    pixels = result;
}
