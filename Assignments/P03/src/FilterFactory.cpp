// FilterFactory.cpp — YOU finish the registry.

#include "FilterFactory.h"

#include "Blur.h"
#include "Brighten.h"
// TODO: include the headers for the filters you register

#include <stdexcept>

const std::map<std::string, FilterFactory::Creator>& FilterFactory::registry() {
    // A function-local static is built the first time this line runs, then
    // reused on every later call. Each entry maps a name to a lambda.
    static const std::map<std::string, Creator> table = {
        {"blur",     [](const Operation&) { return std::make_unique<Blur>(); }},
        {"brighten", [](const Operation& op) { return std::make_unique<Brighten>(op.value); }},

        // TODO: grayscale, flipH, flipV, rotate (uses op.value), invert
    };
    return table;
}

std::unique_ptr<Filter> FilterFactory::create(const Operation& op) {
    // TODO: look op.name up in registry(). If it isn't there, throw
    //   std::invalid_argument("no filter named '" + op.name + "'").
    //   If it is, call the Creator:  return it->second(op);
    (void)op;
    return nullptr;
}

std::vector<std::string> FilterFactory::names() {
    std::vector<std::string> result;
    for (const auto& entry : registry())
        result.push_back(entry.first);
    return result;
}
