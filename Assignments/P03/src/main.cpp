// main.cpp — P03 driver.  (provided, do not modify)
//
// Parse -> load -> build the pipeline with the factory -> run -> save.
//
// Compare with P02's main: there is no if/else naming filter classes.
// main only knows about Filter (through Pipeline) and FilterFactory.

#include "Args.h"
#include "Console.h"
#include "FilterFactory.h"
#include "Image.h"
#include "Pipeline.h"
#include "Platform.h"

#include <exception>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
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
        pipeline.run(img.pixels());

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
