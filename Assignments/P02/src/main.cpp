// main.cpp — P02 driver.  (provided, do not modify)
//
// Parse -> load -> apply what P02 supports -> save -> optionally open.

#include "Args.h"
#include "Console.h"
#include "Image.h"
#include "Platform.h"

#include <exception>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    // Bad command line? parse() prints an error + usage and exits.
    Args args = Args::parse(argc, argv);
    args.print();
    std::cout << "\n";

    try {
        Image img = Image::load(args.input);

        std::ostringstream summary;
        summary << img;               // your Image operator<<
        printStatus("Loaded:", summary.str());

        // P02 applies grayscale only. Everything else is parsed and
        // validated now, and gets applied by the filter pipeline in P03.
        for (const Operation& op : args.order) {
            if (op.name == "grayscale") {
                img.toGrayscale();
                printStatus("Applied:", op.label());
            } else {
                printWarning("'" + op.label() + "' is parsed but not applied yet (that's P03)");
            }
        }

        img.save(args.output);
        printStatus("Saved:", args.output);

        if (args.open && !openInDefaultViewer(args.output)) {
            printWarning("could not open an image viewer (no display?)");
        }

    } catch (const std::exception& e) {
        // Image::load / save throw on missing files, bad paths, etc.
        printError(e.what());
        return 1;
    }

    return 0;
}
