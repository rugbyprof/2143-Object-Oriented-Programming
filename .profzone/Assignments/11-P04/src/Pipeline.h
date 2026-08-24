#pragma once

#include "Filter.h"
#include <vector>
#include <string>

// -----------------------------------------------------------------------
// Pipeline — owns and executes a sequence of Filters.
//
// Unchanged from P03 — the pipeline mechanism is generic enough that
// adding KernelFilter required zero modifications here.
//
// Usage:
//   Pipeline pipeline;
//   pipeline.add(new Grayscale());
//   pipeline.add(new KernelFilter(Kernel::sharpen(), "sharpen"));
//   pipeline.add(new Brighten(30));
//
//   pipeline.printSteps();        // grayscale -> sharpen -> brighten(30)
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
    // Order matters: grayscale-then-sharpen != sharpen-then-grayscale.
    void run(Grid& pixels);

    // Print the pipeline as a chain:
    //   grayscale -> sharpen -> brighten(30)
    // Prints "(empty)" if no filters were added.
    void printSteps() const;

private:
    std::vector<Filter*> filters_;
};
