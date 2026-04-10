#pragma once
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Args — parsed and validated command-line configuration for imgtool.
//
// Updated from P02: adds the `order` field, which records filter names
// in the exact sequence they appear on the command line.
//
// Why order matters here but not in P02:
//   P02 only printed the parsed args. P03 runs them as a pipeline.
//   "--grayscale --brighten 50"  is not the same as "--brighten 50 --grayscale"
//   (grayscale-then-brighten brightens a gray image; the other order
//    brightens in color first, then flattens to gray — different result).
//
// Usage:
//   Args args = Args::parse(argc, argv);
//   for (const std::string& op : args.order) {
//       if (op == "grayscale") pipeline.add(new Grayscale());
//       if (op == "brighten")  pipeline.add(new Brighten(args.brighten));
//       ...
//   }
// -----------------------------------------------------------------------
struct Args {
    // Positional (required)
    std::string input;
    std::string output;

    // Flags
    bool grayscale = false;
    bool blur      = false;
    bool flipH     = false;
    bool flipV     = false;

    // Valued options
    bool use_brighten = false;
    int  brighten     = 0;   // [-255, 255]
    bool use_rotate   = false;
    int  rotate       = 0;   // {0, 90, 180, 270}

    // Filter names in the order they appeared on the command line.
    // Each entry is one of: "grayscale" "blur" "flipH" "flipV" "brighten" "rotate"
    std::vector<std::string> order;

    static Args parse(int argc, char* argv[]);
    void print() const;

private:
    Args() = default;
};
