// Pipeline.cpp — P03's Pipeline is provided; YOU implement apply() and name().

#include "Pipeline.h"

#include <iostream>
#include <utility>

Pipeline::Pipeline(std::string label) : label_(std::move(label)) {}

void Pipeline::add(std::unique_ptr<Filter> f) {
    if (f)
        filters_.push_back(std::move(f));
}

void Pipeline::apply(Grid& pixels) {
    // TODO: P03's run(), renamed. Each child may itself be a Pipeline;
    //   the virtual call handles that, so this stays a simple loop.
    (void)pixels;
}

std::string Pipeline::name() const {
    // TODO: label_ + "[" + child names joined by " -> " + "]"
    //   e.g.  sketch[grayscale -> edgeDetect -> invert]     or   empty[]
    return label_ + "[]";
}

void Pipeline::printSteps() const {
    std::cout << "FILTERS :";
    if (filters_.empty()) {
        std::cout << " (none)\n";
        return;
    }
    for (size_t i = 0; i < filters_.size(); ++i)
        std::cout << (i == 0 ? " " : " -> ") << filters_[i]->name();
    std::cout << "\n";
}

int Pipeline::size() const {
    return static_cast<int>(filters_.size());
}
