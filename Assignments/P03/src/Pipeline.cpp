// Pipeline.cpp — YOU implement these four functions.

#include "Pipeline.h"

#include <iostream>
#include <utility>   // std::move

void Pipeline::add(std::unique_ptr<Filter> f) {
    // TODO: if f is not null, move it onto the end of filters_.
    //   A unique_ptr can't be copied, only moved: push_back(std::move(f))
    (void)f;
}

void Pipeline::run(Grid& pixels) const {
    // TODO: call apply(pixels) on every filter, in order.
    //   Loop with  for (const auto& f : filters_)  — a reference, because
    //   copying a unique_ptr won't compile.
    (void)pixels;
}

void Pipeline::printSteps() const {
    // TODO: print  FILTERS : a -> b -> c   or   FILTERS : (none)
    std::cout << "FILTERS :\n";
}

int Pipeline::size() const {
    return 0;   // TODO
}
