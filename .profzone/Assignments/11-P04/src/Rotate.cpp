#include "Rotate.h"

Rotate::Rotate(int degrees) : degrees_(degrees) {}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

void Rotate::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    if (height == 0) return;
    int width  = static_cast<int>(pixels[0].size());
    (void)width;  // used in the TODO branches — remove when implementing

    if (degrees_ == 0) {
        return;  // nothing to do
    }

    if (degrees_ == 180) {
        // TODO: paste your P03 implementation here.
        // 180° — same dimensions, reverse every row then reverse all rows.
        //
        // Option A: two-pass
        //   for (auto& row : pixels) std::reverse(row.begin(), row.end());
        //   std::reverse(pixels.begin(), pixels.end());
        //
        // Option B: build a new Grid and map:
        //   result[height-1-row][width-1-col] = pixels[row][col]
    }

    if (degrees_ == 90) {
        // TODO: paste your P03 implementation here.
        // 90° clockwise — new dimensions are (width rows × height cols).
        //
        //   using Row = std::vector<Pixel>;
        //   Grid result(width, Row(height));
        //   for (int row = 0; row < height; ++row)
        //       for (int col = 0; col < width; ++col)
        //           result[col][height-1-row] = pixels[row][col];
        //   pixels = std::move(result);
    }

    if (degrees_ == 270) {
        // TODO: paste your P03 implementation here.
        // 270° clockwise — new dimensions are (width rows × height cols).
        //
        //   using Row = std::vector<Pixel>;
        //   Grid result(width, Row(height));
        //   for (int row = 0; row < height; ++row)
        //       for (int col = 0; col < width; ++col)
        //           result[width-1-col][row] = pixels[row][col];
        //   pixels = std::move(result);
    }
}
