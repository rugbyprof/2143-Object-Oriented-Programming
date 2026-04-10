#pragma once
#include "Filter.h"
#include "Kernel.h"
#include <string>

// -----------------------------------------------------------------------
// KernelFilter — adapts a Kernel to the Filter interface.
//
// This is the bridge from P03 to P04: any Kernel can now plug into the
// existing Pipeline without touching Pipeline or main.cpp.
//
// P03 had a hand-written Blur class that manually computed a 3x3 average.
// In P04, that same operation is:
//
//   pipeline.add(new KernelFilter(Kernel::boxBlur(), "blur"));
//
// All kernel effects (sharpen, edge detect, emboss, gaussian blur) follow
// the same convolution algorithm — only the Kernel values differ.
//
// Provided as a complete example so you can study it before implementing
// Image::apply(), which uses the same algorithm non-destructively.
// -----------------------------------------------------------------------
class KernelFilter : public Filter {
public:
    // k     — the convolution kernel to apply (e.g. Kernel::sharpen())
    // label — display name used by Pipeline::printSteps()
    KernelFilter(Kernel k, std::string label);

    void apply(Grid& pixels) override;
    std::string name() const override;

private:
    Kernel      kernel_;
    std::string label_;
};
