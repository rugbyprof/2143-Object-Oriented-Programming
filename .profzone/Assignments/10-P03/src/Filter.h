#pragma once

#include "Image.h"
#include <string>
#include <vector>

// Convenience alias — Grid is a 2D vector of Pixels (row-major).
// Filters receive a Grid& and modify it in place.
// Image::pixels() returns Grid& so the two work together directly.
using Grid = std::vector<std::vector<Pixel>>;

// -----------------------------------------------------------------------
// Filter — abstract base class for all image operations.
//
// This is the Strategy pattern: each filter is a class that encapsulates
// one operation. The Pipeline owns a sequence of Filters and calls them
// in order, so the caller doesn't care which filters are in the list.
//
// To create a new filter:
//   1. Derive from Filter in a new header (e.g. MyFilter.h)
//   2. Implement apply() to modify the pixel grid in place
//   3. Implement name() to return a short label for Pipeline::printSteps()
//   4. Add it to Pipeline via pipeline.add(new MyFilter(...))
//
// Example:
//   class Grayscale : public Filter {
//   public:
//       void apply(Grid& pixels) override;
//       std::string name() const override;
//   };
// -----------------------------------------------------------------------
class Filter {
public:
    // Apply the filter to the pixel grid in place.
    // Row/col indexing: pixels[row][col], top-left is (0,0).
    virtual void apply(Grid& pixels) = 0;

    // Short human-readable label used by Pipeline::printSteps().
    // Examples: "grayscale", "brighten(50)", "blur"
    virtual std::string name() const = 0;

    virtual ~Filter() = default;
};
