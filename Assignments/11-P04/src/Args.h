#pragma once
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Args — parsed and validated command-line configuration for imgtool.
//
// Updated from P03: adds kernel filter flags (sharpen, edgeDetect, emboss,
// gaussian). The `order` vector still records every filter name in CLI order
// so the Pipeline runs them in the correct sequence.
//
// P04 also replaces the hand-written Blur with a KernelFilter wrapper:
//   --blur / -l  now produces KernelFilter(Kernel::boxBlur(), "blur")
//   --sharpen / -s  produces KernelFilter(Kernel::sharpen(), "sharpen")
//   etc.
//
// The pipeline-building logic in main.cpp is the only place that changes.
// -----------------------------------------------------------------------
struct Args {
    // Positional (required)
    std::string input;
    std::string output;

    // P03 flags (unchanged)
    bool grayscale = false;
    bool blur      = false;
    bool flipH     = false;
    bool flipV     = false;

    // P03 valued options
    bool use_brighten = false;
    int  brighten     = 0;   // [-255, 255]
    bool use_rotate   = false;
    int  rotate       = 0;   // {0, 90, 180, 270}

    // P04 kernel filter flags
    bool sharpen    = false;
    bool edgeDetect = false;
    bool emboss     = false;
    bool gaussian   = false;

    // Filter names in the order they appeared on the command line.
    // Each entry is one of:
    //   "grayscale" "blur" "flipH" "flipV" "brighten" "rotate"
    //   "sharpen" "edgeDetect" "emboss" "gaussian"
    std::vector<std::string> order;

    static Args parse(int argc, char* argv[]);
    void print() const;

private:
    Args() = default;
};
