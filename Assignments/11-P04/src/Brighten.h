#pragma once
#include "Filter.h"

// Adds a fixed integer amount to every channel of every pixel.
// Positive amount = brighter; negative amount = darker.
//
// Values outside [0, 255] are left as-is here — Image::save() clamps
// them when writing to disk. This means chaining multiple Brighten
// filters doesn't lose precision mid-pipeline.
//
// P04 note: 'Pixel' in the apply signature is an alias for 'Color'
// (defined in Filter.h). The implementation below uses direct channel
// arithmetic (p.r, p.g, p.b), but you could also write it as:
//
//   p = p + Color(amount_, amount_, amount_);
//
// Both are correct. The operator form is more expressive once Color
// is implemented.
class Brighten : public Filter {
public:
    explicit Brighten(int amount);

    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "brighten(N)"

private:
    int amount_;
};
