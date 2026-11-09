#pragma once
#include <string>

struct Args {
    // ----------------------------------------------------------------
    // Positional arguments (required — must appear in this order)
    // ----------------------------------------------------------------
    std::string input;   // argv[1]
    std::string output;  // argv[2]

    // ----------------------------------------------------------------
    // Flags — true if the flag was present on the command line
    // ----------------------------------------------------------------
    bool grayscale = false;  // --grayscale  / -g
    bool blur      = false;  // --blur       / -l
    bool flipH     = false;  // --flipH      / -h
    bool flipV     = false;  // --flipV      / -v

    // ----------------------------------------------------------------
    // Valued options — track the value AND whether it was given.
    //
    // Why two fields per option instead of a sentinel like -1?
    // Because -1 is a valid brighten value. Keeping "was it set?" and
    // "what is the value?" separate avoids that ambiguity.
    // ----------------------------------------------------------------
    bool use_brighten = false;
    int  brighten     = 0;   // must be in [-255, 255]

    bool use_rotate   = false;
    int  rotate       = 0;   // must be one of {0, 90, 180, 270}

    // ----------------------------------------------------------------
    // Static factory method — the only way to construct a valid Args.
    //
    // Reads argc/argv, validates everything, and returns a filled-in
    // Args object. On any error it prints a message and calls exit(1).
    //
    // Why a static factory instead of Args(argc, argv)?
    // See docs/factory.md for the full discussion.
    // ----------------------------------------------------------------
    static Args parse(int argc, char* argv[]);

    // Print a formatted summary of what was parsed.
    void print() const;

private:
    Args() = default;  // prevent construction outside of parse()
};
