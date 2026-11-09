#pragma once
#include "Filter.h"

// Adds a fixed amount to every channel. Negative amounts darken.  (provided)
class Brighten : public Filter {
public:
    explicit Brighten(int amount);

    void apply(Grid& pixels) override;
    std::string name() const override;   // "brighten(N)"

private:
    int amount_;
};
