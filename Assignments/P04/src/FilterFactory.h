#pragma once

#include "Filter.h"
#include "Operation.h"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// FilterFactory — turns a filter name into a filter object.
// (header provided; YOU fill in the registry in FilterFactory.cpp)
//
// This is the FACTORY pattern, built as a REGISTRY: a map from a name to
// a small function (a lambda) that knows how to build that filter.
//
//   "grayscale" -> [](const Operation&)    { return make_unique<Grayscale>(); }
//   "brighten"  -> [](const Operation& op) { return make_unique<Brighten>(op.value); }
//
// main.cpp no longer needs an if/else chain that names every filter
// class. It asks the factory, and gets back "some Filter":
//
//   for (const Operation& op : args.order)
//       pipeline.add(FilterFactory::create(op));
//
// Adding a filter later = one new line in the registry. main.cpp never
// changes again.
// -----------------------------------------------------------------------
class FilterFactory {
public:
    // A Creator is any callable that takes an Operation and returns a new Filter.
    using Creator = std::function<std::unique_ptr<Filter>(const Operation&)>;

    // Builds the filter registered under op.name, passing op.value along.
    // Throws std::invalid_argument if no filter has that name.
    //
    // Note: the factory depends on Operation, not on all of Args. It
    // doesn't need file names or --open, so it shouldn't see them.
    static std::unique_ptr<Filter> create(const Operation& op);

    // Every registered name, in alphabetical order (the map keeps them sorted).
    static std::vector<std::string> names();

private:
    // The name -> Creator table. Built once, the first time it's needed.
    static const std::map<std::string, Creator>& registry();
};
