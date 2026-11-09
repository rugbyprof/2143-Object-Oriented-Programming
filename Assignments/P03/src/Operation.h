#pragma once

#include <string>

// -----------------------------------------------------------------------
// Operation — one image operation from the command line.  (provided)
//
//   --grayscale      ->  Operation{"grayscale", 0}
//   --brighten 20    ->  Operation{"brighten", 20}
//   --rotate=90      ->  Operation{"rotate", 90}
//
// Why store the value WITH the name? So the same option can appear more
// than once with different values:
//
//   ./imgtool a.png b.png --rotate 90 --grayscale --rotate 180
//
// A single 'int rotate' member could only hold the last value (180), and
// both rotations would silently use it. Each Operation keeps its own.
// -----------------------------------------------------------------------
struct Operation {
    std::string name;
    int value = 0;     // only meaningful for brighten and rotate

    // "grayscale", or "brighten(20)" for operations that take a value.
    std::string label() const {
        if (name == "brighten" || name == "rotate")
            return name + "(" + std::to_string(value) + ")";
        return name;
    }
};
