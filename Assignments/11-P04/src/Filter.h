#pragma once

#include "Color.h"
#include <string>
#include <vector>

// Convenience alias — Grid is a 2D vector of Colors (row-major).
// Filters receive a Grid& and modify it in place.
// Image::pixels() returns Grid& so the two work together directly.
using Grid = std::vector<std::vector<Color>>;

// Backward-compatibility alias: P03 filters use 'Pixel' throughout.
// Since Pixel == Color, they compile unchanged in P04.
// New P04 code can use Color directly for clarity.
using Pixel = Color;

// -----------------------------------------------------------------------
// Filter — abstract base class for all image operations.
//
// Same Strategy pattern as P03, now operating on Color pixels.
// A Pipeline owns a sequence of Filters and calls them in order.
//
// New in P04: KernelFilter implements this interface by wrapping a Kernel.
// This means boxBlur, sharpen, edgeDetect, etc. all run through the same
// pipeline mechanism without requiring separate filter classes for each.
//
// To create a new filter:
//   1. Derive from Filter in a new header (e.g. MyFilter.h)
//   2. Implement apply() to modify the pixel grid in place
//   3. Implement name() to return a short label for Pipeline::printSteps()
//   4. Add it to Pipeline via pipeline.add(new MyFilter(...))
// -----------------------------------------------------------------------
class Filter {
public:
    // Apply the filter to the pixel grid in place.
    // Row/col indexing: pixels[row][col], top-left is (0,0).
    virtual void apply(Grid& pixels) = 0;

    // Short human-readable label used by Pipeline::printSteps().
    // Examples: "grayscale", "brighten(50)", "blur", "sharpen"
    virtual std::string name() const = 0;

    virtual ~Filter() = default;
};
