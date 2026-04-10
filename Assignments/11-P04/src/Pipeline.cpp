#include "Pipeline.h"
#include <iostream>

Pipeline::~Pipeline() {
    // Pipeline owns every Filter* added via add().
    // Delete them all to avoid memory leaks.
    for (Filter* f : filters_)
        delete f;
}

void Pipeline::add(Filter* f) {
    filters_.push_back(f);
}

void Pipeline::run(Grid& pixels) {
    for (Filter* f : filters_)
        f->apply(pixels);
}

void Pipeline::printSteps() const {
    if (filters_.empty()) {
        std::cout << "FILTERS : (empty)\n";
        return;
    }

    std::cout << "FILTERS :";
    for (size_t i = 0; i < filters_.size(); ++i) {
        std::cout << " " << filters_[i]->name();
        if (i + 1 < filters_.size())
            std::cout << " ->";
    }
    std::cout << "\n";
}
