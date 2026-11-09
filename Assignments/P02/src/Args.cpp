// Args.cpp — YOU implement Args::parse and Args::print.
//
// The full spec (every option, every error message, the print format)
// is in the README. Read it first.

#include "Args.h"
#include "Console.h"   // printError, printUsage

#include <cstdlib>     // std::exit
#include <iostream>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// Helper functions. Put them in this unnamed namespace so they are
// private to this file (no other .cpp can see or collide with them).
//
// Suggested helpers (signatures are in the README's hints section):
//   isImageFile, fail, splitEq, looksLikeOption, takeValue, toInt
// -----------------------------------------------------------------------
namespace {

// Prints a colored error and the usage line, then exits.
// [[noreturn]] tells the compiler this function never returns.
[[noreturn]] void fail(const std::string& msg) {
    printError(msg);
    printUsage();
    std::exit(1);
}

}  // namespace

// -----------------------------------------------------------------------
// Args::parse
//
// Strategy:
//   1. Copy argv[1..argc-1] into a vector<string> (a queue of tokens).
//   2. Take the two required positional args off the front; validate them.
//   3. Loop over what's left, matching flags and valued options.
//      Append an Operation for each one to args.order as you go:
//        args.order.push_back({"grayscale", 0});
//        args.order.push_back({"brighten", n});
//   4. On any error, call fail(...) with a specific message.
// -----------------------------------------------------------------------
Args Args::parse(int argc, char* argv[]) {
    Args args;

    // Step 1 — this vector constructor copies a range of char* into strings
    std::vector<std::string> tokens(argv + 1, argv + argc);

    if (tokens.empty())
        fail("input and output files are required");

    // TODO: steps 2-4

    return args;
}

// -----------------------------------------------------------------------
// Args::print — see the README for the exact format.
// -----------------------------------------------------------------------
void Args::print() const {
    std::cout << "INPUT   : " << input << "\n";
    std::cout << "OUTPUT  : " << output << "\n";

    // TODO: the ORDER line. Operation::label() gives "grayscale" or "brighten(20)".
}
