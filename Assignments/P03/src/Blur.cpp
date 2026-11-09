// Blur.cpp — provided as a complete example of a NEIGHBORHOOD filter.
//
// Key idea: read from the original grid, write into a copy. If you read
// and write the same grid, pixels you already blurred would feed into
// their neighbors' averages, and the blur would smear in one direction.

#include "Blur.h"

#include <utility>   // std::move

std::string Blur::name() const {
    return "blur";
}

void Blur::apply(Grid& pixels) {
    const int height = static_cast<int>(pixels.size());
    if (height < 3)
        return;
    const int width = static_cast<int>(pixels[0].size());

    Grid result = pixels;   // copy: border pixels stay as they were

    for (int row = 1; row < height - 1; ++row) {
        for (int col = 1; col < width - 1; ++col) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    const Pixel& n = pixels[row + dr][col + dc];
                    sumR += n.r;
                    sumG += n.g;
                    sumB += n.b;
                }
            }
            result[row][col] = Pixel{sumR / 9, sumG / 9, sumB / 9};
        }
    }

    pixels = std::move(result);
}
