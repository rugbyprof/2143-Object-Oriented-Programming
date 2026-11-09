// FilterFactory.cpp — P03 filters and kernel filters are registered for
// you. YOU write preset() and register the presets (README Part 5).

#include "FilterFactory.h"

#include "Brighten.h"
#include "FlipH.h"
#include "FlipV.h"
#include "Grayscale.h"
#include "Invert.h"
#include "Kernel.h"
#include "KernelFilter.h"
#include "Pipeline.h"
#include "Rotate.h"

#include <stdexcept>

namespace {

// Builds a Creator for a kernel filter.
FilterFactory::Creator kernel(Kernel (*makeKernel)(), const std::string& label) {
    return [makeKernel, label](const Operation&) {
        return std::make_unique<KernelFilter>(makeKernel(), label);
    };
}

// Builds a Creator for a preset: a Pipeline (Composite) made of other
// registered filters. The steps are created through the factory itself
// when the preset is used, so a preset can contain any filter, even
// another preset.
// [[maybe_unused]] silences "unused function" until you register a preset.
// Remove it once you do.
[[maybe_unused]] FilterFactory::Creator preset(const std::string& label,
                                              std::vector<Operation> steps) {
    // TODO: return a lambda that captures label and steps (by value) and,
    //   when called, builds a Pipeline named 'label', adds
    //   FilterFactory::create(step) for each step, and returns it.
    //   A unique_ptr<Pipeline> converts to unique_ptr<Filter> on return.
    (void)label;
    (void)steps;
    return [](const Operation&) { return std::unique_ptr<Filter>(); };
}

}  // namespace

const std::map<std::string, FilterFactory::Creator>& FilterFactory::registry() {
    static const std::map<std::string, Creator> table = {
        // P03 filters
        {"brighten",  [](const Operation& op) { return std::make_unique<Brighten>(op.value); }},
        {"flipH",     [](const Operation&) { return std::make_unique<FlipH>(); }},
        {"flipV",     [](const Operation&) { return std::make_unique<FlipV>(); }},
        {"grayscale", [](const Operation&) { return std::make_unique<Grayscale>(); }},
        {"invert",    [](const Operation&) { return std::make_unique<Invert>(); }},
        {"rotate",    [](const Operation& op) { return std::make_unique<Rotate>(op.value); }},

        // Kernel filters (Adapter)
        {"blur",       kernel(&Kernel::boxBlur, "blur")},
        {"gaussian",   kernel(&Kernel::gaussianBlur, "gaussian")},
        {"sharpen",    kernel(&Kernel::sharpen, "sharpen")},
        {"edgeDetect", kernel(&Kernel::edgeDetect, "edgeDetect")},
        {"emboss",     kernel(&Kernel::emboss, "emboss")},

        // Presets (Composite)
        // TODO: "sketch", "soft", and one of your own design. Example:
        //   {"sketch", preset("sketch", {{"grayscale", 0}, {"edgeDetect", 0}, {"invert", 0}})},
    };
    return table;
}

std::unique_ptr<Filter> FilterFactory::create(const Operation& op) {
    const auto& table = registry();
    auto it = table.find(op.name);
    if (it == table.end())
        throw std::invalid_argument("no filter named '" + op.name + "'");
    return it->second(op);
}

std::vector<std::string> FilterFactory::names() {
    std::vector<std::string> result;
    for (const auto& entry : registry())
        result.push_back(entry.first);
    return result;
}
