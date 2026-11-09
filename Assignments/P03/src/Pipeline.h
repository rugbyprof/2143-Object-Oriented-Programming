#pragma once

#include "Filter.h"

#include <memory>
#include <vector>

// -----------------------------------------------------------------------
// Pipeline — owns a sequence of filters and runs them in order.
// (header provided; YOU implement Pipeline.cpp)
//
//   Pipeline pipeline;
//   pipeline.add(std::make_unique<Grayscale>());
//   pipeline.add(std::make_unique<Brighten>(50));
//   pipeline.printSteps();         // FILTERS : grayscale -> brighten(50)
//   pipeline.run(img.pixels());
//
// Ownership (W08): the Pipeline OWNS its filters, through unique_ptr.
//   * They are deleted automatically when the Pipeline is destroyed,
//     so Pipeline has no destructor at all.
//   * unique_ptr can't be copied, so neither can Pipeline. With raw
//     Filter* pointers, a copied Pipeline would delete the same filters
//     twice. The compiler now rules that out.
//
// Why pointers at all? The vector holds DIFFERENT filter types. A
// vector<Filter> can't: Filter is abstract, and storing a Rotate in a
// Filter-sized slot would "slice" off the Rotate part.
// -----------------------------------------------------------------------
class Pipeline {
public:
    // Take ownership of f and append it. Ignores a null pointer.
    void add(std::unique_ptr<Filter> f);

    // Apply every filter to the grid, in the order they were added.
    void run(Grid& pixels) const;

    // Prints  FILTERS : grayscale -> brighten(50)   or   FILTERS : (none)
    void printSteps() const;

    // How many filters are in the pipeline.
    int size() const;

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
