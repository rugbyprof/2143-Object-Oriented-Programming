#pragma once

#include "Filter.h"
#include "Kernel.h"

#include <string>

// -----------------------------------------------------------------------
// KernelFilter — makes any Kernel usable as a Filter.  (provided)
//
// This is the ADAPTER pattern. A Kernel is just numbers; it knows
// nothing about Filter, Grid, or pipelines. KernelFilter wraps one and
// presents the Filter interface (apply + name), so every kernel plugs
// into the existing Pipeline without changing Kernel or Pipeline:
//
//   pipeline.add(std::make_unique<KernelFilter>(Kernel::sharpen(), "sharpen"));
//
// P03's hand-written Blur class is gone: it's now
//   KernelFilter(Kernel::boxBlur(), "blur")
// -----------------------------------------------------------------------
class KernelFilter : public Filter {
public:
    KernelFilter(Kernel kernel, std::string label);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    Kernel kernel_;
    std::string label_;
};
