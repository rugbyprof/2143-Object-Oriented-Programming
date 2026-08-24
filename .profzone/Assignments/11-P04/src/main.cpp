// main.cpp — Program 4 driver
//
// Demonstrates the P03 → P04 upgrade:
//   - Same pipeline pattern, same Pipeline/Filter classes
//   - blur is now a KernelFilter wrapping Kernel::boxBlur()
//   - New kernel effects: sharpen, edgeDetect, emboss, gaussian
//   - Color::operator[] allows per-channel access in KernelFilter
//
// You should not need to change this file.
// All filter logic belongs in the individual filter and kernel classes.

#include "Args.h"
#include "Image.h"
#include "Kernel.h"
#include "Pipeline.h"
#include "KernelFilter.h"
#include "Brighten.h"
#include "Grayscale.h"
#include "FlipH.h"
#include "FlipV.h"
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
            // P04 change: Blur class is gone. boxBlur is a named kernel.
            // The convolution code now lives in KernelFilter::apply()
            // rather than in a custom Blur class.
            pipeline.add(new KernelFilter(Kernel::boxBlur(), "blur"));
        } else if (op == "flipH") {
            pipeline.add(new FlipH());
        } else if (op == "flipV") {
            pipeline.add(new FlipV());
        } else if (op == "rotate") {
            pipeline.add(new Rotate(args.rotate));
        } else if (op == "sharpen") {
            pipeline.add(new KernelFilter(Kernel::sharpen(), "sharpen"));
        } else if (op == "edgeDetect") {
            pipeline.add(new KernelFilter(Kernel::edgeDetect(), "edgeDetect"));
        } else if (op == "emboss") {
            pipeline.add(new KernelFilter(Kernel::emboss(), "emboss"));
        } else if (op == "gaussian") {
            pipeline.add(new KernelFilter(Kernel::gaussianBlur(), "gaussian"));
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
