// Args.cpp — provided (P03 parser + P04 options: kernel flags, --preset, --test).
// You may use your own instead, if it supports the same options.

#include "Args.h"
#include "Console.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace {

// Everything in an unnamed namespace is private to this .cpp file.

bool isImageFile(const std::string& filename) {
    std::string lower = filename;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    for (const std::string ext : {".png", ".jpg", ".jpeg", ".bmp"}) {
        if (lower.size() > ext.size() &&
            lower.compare(lower.size() - ext.size(), ext.size(), ext) == 0)
            return true;
    }
    return false;
}

[[noreturn]] void fail(const std::string& msg) {
    printError(msg);
    printUsage();
    std::exit(1);
}

// "--brighten=20" -> ("--brighten", "20");  "--blur" -> ("--blur", "")
std::pair<std::string, std::string> splitEq(const std::string& token) {
    size_t eq = token.find('=');
    if (eq == std::string::npos)
        return {token, ""};
    return {token.substr(0, eq), token.substr(eq + 1)};
}

// "--blur" and "-g" look like options. "-20" is a negative number.
bool looksLikeOption(const std::string& s) {
    return s.size() > 1 && s[0] == '-' &&
           !std::isdigit(static_cast<unsigned char>(s[1]));
}

// The value for a valued option: the part after '=', or the next token.
std::string takeValue(const std::string& flag, const std::string& inlineVal,
                      std::vector<std::string>& tokens, const std::string& what = "an integer") {
    if (!inlineVal.empty())
        return inlineVal;
    if (tokens.empty())
        fail("'" + flag + "' requires " + what + " value");
    if (looksLikeOption(tokens.front()))
        fail("'" + flag + "' expected a value but got option '" + tokens.front() + "'");

    std::string val = tokens.front();
    tokens.erase(tokens.begin());
    return val;
}

// std::stoi, but the whole token must be a number ("20abc" is rejected).
int toInt(const std::string& flag, const std::string& val) {
    try {
        size_t used = 0;
        int n = std::stoi(val, &used);
        if (used != val.size())
            throw std::invalid_argument(val);
        return n;
    } catch (const std::exception&) {
        fail("invalid integer for '" + flag + "': '" + val + "'");
    }
}

}  // namespace

Args Args::parse(int argc, char* argv[]) {
    Args args;

    std::vector<std::string> tokens(argv + 1, argv + argc);

    // --test runs the unit tests; no image files are involved.
    if (tokens.size() == 1 && tokens.front() == "--test") {
        args.runTests = true;
        return args;
    }

    // ---- positional ----
    if (tokens.empty())
        fail("input and output files are required");
    args.input = tokens.front();
    tokens.erase(tokens.begin());
    if (!isImageFile(args.input))
        fail("input must be an image file (.png, .jpg, .jpeg, .bmp): '" + args.input + "'");

    if (tokens.empty())
        fail("output file is required");
    args.output = tokens.front();
    tokens.erase(tokens.begin());
    if (!isImageFile(args.output))
        fail("output must be an image file (.png, .jpg, .jpeg, .bmp): '" + args.output + "'");

    // ---- options ----
    while (!tokens.empty()) {
        auto [flag, inlineVal] = splitEq(tokens.front());
        tokens.erase(tokens.begin());

        if (flag == "--grayscale" || flag == "-g") {
            args.order.push_back({"grayscale", 0});
        } else if (flag == "--blur" || flag == "-l") {
            args.order.push_back({"blur", 0});
        } else if (flag == "--flipH" || flag == "-h") {
            args.order.push_back({"flipH", 0});
        } else if (flag == "--flipV" || flag == "-v") {
            args.order.push_back({"flipV", 0});
        } else if (flag == "--invert" || flag == "-i") {
            args.order.push_back({"invert", 0});
        } else if (flag == "--sharpen" || flag == "-s") {
            args.order.push_back({"sharpen", 0});
        } else if (flag == "--edgeDetect" || flag == "-e") {
            args.order.push_back({"edgeDetect", 0});
        } else if (flag == "--emboss" || flag == "-m") {
            args.order.push_back({"emboss", 0});
        } else if (flag == "--gaussian" || flag == "-n") {
            args.order.push_back({"gaussian", 0});
        } else if (flag == "--preset" || flag == "-p") {
            // Which preset names exist is the factory's business, not
            // Args'. An unknown name is reported when the pipeline is built.
            args.order.push_back({takeValue(flag, inlineVal, tokens, "a preset name"), 0});
        } else if (flag == "--open") {
            args.open = true;
        } else if (flag == "--brighten" || flag == "-b") {
            int n = toInt(flag, takeValue(flag, inlineVal, tokens));
            if (n < -255 || n > 255)
                fail("'" + flag + "' must be in [-255, 255]");
            args.order.push_back({"brighten", n});
        } else if (flag == "--rotate" || flag == "-r") {
            int n = toInt(flag, takeValue(flag, inlineVal, tokens));
            if (n != 0 && n != 90 && n != 180 && n != 270)
                fail("'" + flag + "' must be one of {0, 90, 180, 270}");
            args.order.push_back({"rotate", n});
        } else {
            fail("unknown option '" + flag + "'");
        }
    }

    return args;
}

void Args::print() const {
    std::cout << "INPUT   : " << input << "\n";
    std::cout << "OUTPUT  : " << output << "\n";

    std::cout << "ORDER   :";
    for (const Operation& op : order)
        std::cout << " " << op.label();
    std::cout << "\n";
}
