#include "Rotate.h"

Rotate::Rotate(int degrees) : degrees_(degrees) {}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

void Rotate::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    if (height == 0) return;
    int width  = static_cast<int>(pixels[0].size());
    (void)width;  // used in the TODO branches — remove this line when implementing

    if (degrees_ == 0) {
        return;  // nothing to do
    }

    if (degrees_ == 180) {
        // TODO: 180° — same dimensions, reverse every row then reverse all rows.
        // This is equivalent to applying FlipH then FlipV (or vice versa).
        //
        // Option A: two-pass (FlipH then FlipV)
        // Option B: build a new Grid(height, Row(width)) and map:
        //           result[height-1-row][width-1-col] = pixels[row][col]
    }

    if (degrees_ == 90) {
        // TODO: 90° clockwise — new dimensions are (width × height).
        // Build a new Grid(width, Row(height)), then:
        //   result[col][height-1-row] = pixels[row][col]
        // Replace pixels with result at the end.
    }

    if (degrees_ == 270) {
        // TODO: 270° clockwise (= 90° counter-clockwise) — new dimensions (width × height).
        // Build a new Grid(width, Row(height)), then:
        //   result[width-1-col][row] = pixels[row][col]
        // Replace pixels with result at the end.
    }
}
