// main.cpp — Program 3 driver
//
// Parses command-line arguments, builds a filter pipeline in the order
// the flags were given, applies the pipeline to the input image, and
// saves the result.
//
// You should not need to change this file.
// All filter logic belongs in the individual filter classes.

#include "Args.h"
#include "Image.h"
#include "Pipeline.h"
#include "Grayscale.h"
#include "Brighten.h"
#include "FlipH.h"
#include "FlipV.h"
#include "Blur.h"
#include "Rotate.h"

#include <iostream>

int main(int argc, char* argv[]) {
    // --- parse and validate command-line arguments ---
    Args args = Args::parse(argc, argv);
    args.print();
    std::cout << "\n";

    // --- load image ---
    Image img = Image::load(args.input);
    std::cout << "Loaded: " << img << "\n";

    // --- build pipeline in the order flags were given ---
    Pipeline pipeline;

    for (const std::string& op : args.order) {
        if (op == "grayscale") {
            pipeline.add(new Grayscale());
        } else if (op == "brighten") {
            pipeline.add(new Brighten(args.brighten));
        } else if (op == "blur") {
            pipeline.add(new Blur());
        } else if (op == "flipH") {
            pipeline.add(new FlipH());
        } else if (op == "flipV") {
            pipeline.add(new FlipV());
        } else if (op == "rotate") {
            pipeline.add(new Rotate(args.rotate));
        }
    }

    // --- print and run ---
    pipeline.printSteps();
    pipeline.run(img.pixels());  // img.pixels() returns Grid& — passed to each filter

    // --- save result ---
    img.save(args.output);
    std::cout << "Saved: " << args.output << "\n";

    return 0;
}
