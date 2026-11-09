#pragma once

#include "Image.h"   // Grid, Pixel

#include <string>

// -----------------------------------------------------------------------
// Filter — the interface every image operation implements.  (provided)
//
// This is the STRATEGY pattern: each filter class wraps one algorithm
// behind the same two-function interface. The Pipeline holds a list of
// Filters and calls apply() on each one without knowing (or caring)
// which concrete filter it is. The virtual call picks the right apply()
// at run time.
//
// To add a filter:
//   1. class MyFilter : public Filter { ... }  in MyFilter.h
//   2. implement apply() and name() in MyFilter.cpp
//   3. register it in FilterFactory.cpp (one line)
//   4. teach Args the new flag
// Nothing else in the program changes. That's the Open/Closed Principle:
// open for extension (new classes), closed for modification (old code).
// -----------------------------------------------------------------------
class Filter {
public:
    // Change the grid in place. pixels[row][col], top-left is [0][0].
    virtual void apply(Grid& pixels) = 0;

    // Short label for Pipeline::printSteps(), e.g. "grayscale", "brighten(50)".
    virtual std::string name() const = 0;

    // Virtual destructor: the Pipeline deletes filters through a Filter
    // pointer. Without 'virtual', deleting a Rotate through a Filter*
    // would run only ~Filter() — undefined behavior.
    virtual ~Filter() = default;
};
