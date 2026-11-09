#pragma once
#include "Filter.h"

// Rotates clockwise by 0, 90, 180, or 270 degrees.
// 90 and 270 swap the width and height.
class Rotate : public Filter {
public:
    // Throws std::invalid_argument unless degrees is 0, 90, 180, or 270.
    // Args already checks this, but a class should protect its own rules:
    // Rotate might be created somewhere other than the command line later.
    explicit Rotate(int degrees);

    void apply(Grid& pixels) override;
    std::string name() const override;   // "rotate(N)"

private:
    int degrees_;
};
