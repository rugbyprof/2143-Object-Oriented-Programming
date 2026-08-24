#include "Args.h"
#include <iostream>
#include <string>
#include <vector>

// -----------------------------------------------------------------------
// TODO: add any helper functions here.
//
// Suggestions to get you started:
//
//   bool isImageFile(const std::string& filename)
//       — return true if the filename ends with .png, .jpg, .jpeg, etc.
//
//   std::pair<std::string, std::string> splitEq(const std::string& token)
//       — split "--brighten=20" into ("--brighten", "20")
//       — return ("token", "") if there is no '='
//
//   bool startsWith(const std::string& s, const std::string& prefix)
//       — return true if s begins with prefix
//
//   void error(const std::string& type, const std::string& msg)
//       — print a colored error + usage line, then exit(1)
// -----------------------------------------------------------------------


// -----------------------------------------------------------------------
// Args::parse
//
// Strategy:
//   1. Copy argv[1..argc-1] into a vector<string> (token queue).
//   2. Consume the two required positional args (input, output).
//   3. Loop over remaining tokens, matching flags and valued options.
//   4. On any error: print a helpful message + usage line, then exit(1).
//
// Token queue pattern:
//   tokens.front()           — peek at the next token (does not remove it)
//   tokens.erase(tokens.begin()) — consume (remove) the front token
// -----------------------------------------------------------------------
Args Args::parse(int argc, char* argv[]) {
    Args args;

    // Step 1 — load tokens into a vector so we can process them one by one
    std::vector<std::string> tokens;
    for (int i = 1; i < argc; ++i)
        tokens.push_back(argv[i]);

    // Helpful while building: print all tokens to see what arrived
    // for (const auto& t : tokens)
    //     std::cout << "token: " << t << "\n";

    // TODO: check that tokens is not empty (missing both positional args)

    // TODO: read and validate args.input (first positional arg)

    // TODO: check that at least one more token remains (missing output)

    // TODO: read and validate args.output (second positional arg)

    // TODO: loop over remaining tokens and match flags / valued options
    //
    //   while (!tokens.empty()) {
    //       auto [flag, inline_val] = splitEq(tokens.front());
    //       tokens.erase(tokens.begin());
    //
    //       if (flag == "--grayscale" || flag == "-g") {
    //           args.grayscale = true;
    //       } else if ...
    //   }

    return args;
}


// -----------------------------------------------------------------------
// Args::print
//
// Expected output on success:
//   INPUT  : in.png
//   OUTPUT : out.png
//   FLAGS  : grayscale blur
//   PARAMS : brighten=20 rotate=90
//
// Only print flags/params that were actually set.
// -----------------------------------------------------------------------
void Args::print() const {
    std::cout << "INPUT  : " << input  << "\n";
    std::cout << "OUTPUT : " << output << "\n";

    std::cout << "FLAGS  :";
    // TODO: append each enabled flag name (separated by spaces)
    std::cout << "\n";

    std::cout << "PARAMS :";
    // TODO: append each set param as name=value (separated by spaces)
    std::cout << "\n";
}
