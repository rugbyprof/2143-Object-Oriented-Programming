#pragma once
#include "Filter.h"

// Photographic negative: every channel c becomes 255 - c.
// Color(255, 255, 255) - c does it in one expression.
class Invert : public Filter {
public:
    void apply(Grid& pixels) override;
    std::string name() const override;   // "invert"
};
