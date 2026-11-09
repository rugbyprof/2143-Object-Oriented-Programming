// main.cpp — P04 driver.  (provided, do not modify)
//
//   ./imgtool --test                         run the unit tests
//   ./imgtool in.png out.png [options]       process an image
//
// Identical to P03 except for --test and pipeline.apply() (was run()).
// Kernel filters and presets needed NO changes here: they arrive through
// the factory as plain Filters.

#include "Args.h"
#include "Console.h"
#include "FilterFactory.h"
#include "Image.h"
#include "Pipeline.h"
#include "Platform.h"
#include "Tests.h"

#include <exception>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
    if (args.runTests)
        return runAllTests() ? 0 : 1;

    args.print();
    std::cout << "\n";

    try {
        Image img = Image::load(args.input);

        std::ostringstream summary;
        summary << img;
        printStatus("Loaded:", summary.str());

        Pipeline pipeline;
        for (const Operation& op : args.order)
            pipeline.add(FilterFactory::create(op));

        pipeline.printSteps();
        pipeline.apply(img.pixels());

        summary.str("");
        summary << img;   // dimensions may have changed (rotate)
        printStatus("Result:", summary.str());

        img.save(args.output);
        printStatus("Saved:", args.output);

        if (args.open && !openInDefaultViewer(args.output))
            printWarning("could not open an image viewer (no display?)");

    } catch (const std::exception& e) {
        printError(e.what());
        return 1;
    }

    return 0;
}
