#pragma once
#include "Filter.h"

// Rotates the image clockwise by 0°, 90°, 180°, or 270°.
//
// IMPORTANT: 90° and 270° rotations change the image dimensions.
// A 200×100 image becomes 100×200 after a 90° rotation.
// You must build a new Grid with the swapped dimensions.
//
// Coordinate mappings (clockwise):
//
//   90°:  new[col][height-1-row]       = old[row][col]
//         → new grid is (width × height)
//
//   180°: new[height-1-row][width-1-col] = old[row][col]
//         → same dimensions
//
//   270°: new[width-1-col][row]        = old[row][col]
//         → new grid is (width × height)
//
//   0°:   no change
class Rotate : public Filter {
public:
    explicit Rotate(int degrees);

    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "rotate(N)"

private:
    int degrees_;
};
