#pragma once
#include "Filter.h"

// Converts every pixel to grayscale by setting all three channels to
// the same computed gray value.
//
// P04: paste your P03 implementation here, then optionally refactor it
// to use Color operators. For example, the P04 version could read:
//
//   double avg = (p[0] + p[1] + p[2]) / 3.0;
//   p = Color(static_cast<int>(avg), static_cast<int>(avg), static_cast<int>(avg));
//
// Or, using the luminance formula with Color arithmetic, if you want.
class Grayscale : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "grayscale"
};
