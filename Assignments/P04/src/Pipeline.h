#pragma once

#include "Filter.h"

#include <memory>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Pipeline — a sequence of filters that is ITSELF a filter.
// (header provided; YOU implement apply() and name() in Pipeline.cpp)
//
// This is the COMPOSITE pattern. A Pipeline holds Filters, and a
// Pipeline IS-A Filter, so a Pipeline can hold other Pipelines:
//
//   auto sketch = std::make_unique<Pipeline>("sketch");
//   sketch->add(std::make_unique<Grayscale>());
//   sketch->add(std::make_unique<KernelFilter>(Kernel::edgeDetect(), "edgeDetect"));
//   sketch->add(std::make_unique<Invert>());
//
//   Pipeline main;
//   main.add(std::make_unique<Brighten>(20));
//   main.add(std::move(sketch));      // a whole pipeline, added as one filter
//
//   main.printSteps();
//   // FILTERS : brighten(20) -> sketch[grayscale -> edgeDetect -> invert]
//
// Code that runs filters (main.cpp) can't tell a single filter from a
// whole group, and doesn't need to. That's the point.
//
// Changes from P03: run() is now apply() (it overrides Filter::apply),
// and there is a name() and a label.
// -----------------------------------------------------------------------
class Pipeline : public Filter {
public:
    // label is used by name() when this pipeline is nested in another.
    explicit Pipeline(std::string label = "pipeline");

    // Take ownership of f and append it. Ignores a null pointer.
    void add(std::unique_ptr<Filter> f);

    // Filter interface:
    void apply(Grid& pixels) override;    // every filter, in order
    std::string name() const override;    // label[a -> b -> c]   or   label[]

    // FILTERS : a -> b -> c    or    FILTERS : (none)
    void printSteps() const;

    int size() const;

private:
    std::string label_;
    std::vector<std::unique_ptr<Filter>> filters_;
};
