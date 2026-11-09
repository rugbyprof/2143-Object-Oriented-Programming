#pragma once

#include "Operation.h"

#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Args — parsed and validated command-line options.  (header provided)
//
// You implement Args::parse and Args::print in Args.cpp.
//
//   ./imgtool <input_image> <output_image> [options]
//
// The data members are public: once parsing succeeds, an Args is just a
// bundle of settings that the rest of the program reads.
//
// The CONSTRUCTOR is private: the only way to get an Args is
// Args::parse(), which validates everything first. So any Args object
// that exists anywhere in the program is guaranteed to be valid.
// That guarantee is the whole point of the static factory method.
// (See docs/factory.md.)
// -----------------------------------------------------------------------
class Args {
public:
    std::string input;    // first positional argument
    std::string output;   // second positional argument
    bool open = false;    // --open : show the result in the default viewer

    // Every image operation, in the order it was typed:
    //   ./imgtool a.png b.png -b 20 -g -r 90
    //   order = { {"brighten", 20}, {"grayscale", 0}, {"rotate", 90} }
    std::vector<Operation> order;

    // Reads argc/argv and returns a fully validated Args.
    // On any error: prints a colored error + usage line and exits(1).
    static Args parse(int argc, char* argv[]);

    // Prints what was parsed (see README for the exact format).
    void print() const;

private:
    Args() = default;
};
