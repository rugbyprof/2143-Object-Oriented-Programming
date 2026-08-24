#pragma once

#include "Filter.h"
#include <vector>
#include <string>

// -----------------------------------------------------------------------
// Pipeline — owns and executes a sequence of Filters.
//
// Usage:
//   Pipeline pipeline;
//   pipeline.add(new Grayscale());
//   pipeline.add(new Brighten(50));
//   pipeline.add(new Blur());
//
//   pipeline.printSteps();        // grayscale -> brighten(50) -> blur
//   pipeline.run(img.pixels());   // applies each filter in order
//
// Pipeline takes ownership of every Filter* passed to add().
// The destructor deletes them all.
// -----------------------------------------------------------------------
class Pipeline {
public:
    Pipeline() = default;
    ~Pipeline();

    // Take ownership of f and append it to the sequence.
    void add(Filter* f);

    // Apply all filters to the grid in the order they were added.
    // Order matters: grayscale-then-brighten != brighten-then-grayscale.
    void run(Grid& pixels);

    // Print the pipeline as a chain:
    //   grayscale -> brighten(50) -> blur
    // Prints "(empty)" if no filters were added.
    void printSteps() const;

private:
    std::vector<Filter*> filters_;
};
