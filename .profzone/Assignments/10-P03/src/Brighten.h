#pragma once
#include "Filter.h"

// Adds a fixed integer amount to every channel of every pixel.
// Positive amount = brighter; negative amount = darker.
//
// Values outside [0, 255] are left as-is here — Image::save() clamps
// them when writing to disk. This means chaining multiple Brighten
// filters doesn't lose precision mid-pipeline.
class Brighten : public Filter {
public:
    explicit Brighten(int amount);

    void apply(Grid& pixels) override;
    std::string name() const override;  // returns "brighten(N)"

private:
    int amount_;
};
