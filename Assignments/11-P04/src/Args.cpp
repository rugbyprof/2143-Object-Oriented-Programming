#include "Args.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

// -----------------------------------------------------------------------
// Utilities
// -----------------------------------------------------------------------

static bool isImageFile(const std::string& filename) {
    std::string lower = filename;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    for (const auto& ext : {".jpg", ".jpeg", ".png", ".bmp", ".gif", ".ppm"}) {
        if (lower.size() >= std::string(ext).size() &&
            lower.compare(lower.size() - std::string(ext).size(),
                          std::string(ext).size(), ext) == 0)
            return true;
    }
    return false;
}

static void error(const std::string& type, const std::string& msg) {
    std::cerr << "\033[31mError\033[0m \033[33m" << type << "\033[0m: " << msg << "\n";
    std::cerr << "Usage: ./imgtool <input> <output> [options]\n";
}

// Split "--brighten=20" -> ("--brighten", "20")
// Returns ("token", "") when there is no '='.
static std::pair<std::string, std::string> splitEq(const std::string& token) {
    size_t eq = token.find('=');
    if (eq == std::string::npos)
        return {token, ""};
    return {token.substr(0, eq), token.substr(eq + 1)};
}

static bool startsWith(const std::string& s, const std::string& prefix) {
    return s.rfind(prefix, 0) == 0;
}

// -----------------------------------------------------------------------
// Args::parse
// -----------------------------------------------------------------------

Args Args::parse(int argc, char* argv[]) {
    Args args;

    std::vector<std::string> tokens;
    for (int i = 1; i < argc; ++i)
        tokens.push_back(argv[i]);

    // ---- positional args ----

    if (tokens.empty()) {
        error("missing args", "input and output files are required");
        exit(1);
    }

    args.input = tokens.front();
    if (!isImageFile(args.input)) {
        error("wrong filetype", "input must be an image file (.png, .jpg, ...)");
        exit(1);
    }
    tokens.erase(tokens.begin());

    if (tokens.empty()) {
        error("missing args", "output file is required");
        exit(1);
    }

    args.output = tokens.front();
    tokens.erase(tokens.begin());

    if (!isImageFile(args.output)) {
        error("wrong filetype", "output must be an image file (.png, .jpg, ...)");
        exit(1);
    }

    // ---- optional flags and valued options ----

    while (!tokens.empty()) {
        auto [flag, inline_val] = splitEq(tokens.front());
        tokens.erase(tokens.begin());

        // ---- P03 flags ----

        if (flag == "--grayscale" || flag == "-g") {
            args.grayscale = true;
            args.order.push_back("grayscale");

        } else if (flag == "--blur" || flag == "-l") {
            args.blur = true;
            args.order.push_back("blur");

        } else if (flag == "--flipH" || flag == "-h") {
            args.flipH = true;
            args.order.push_back("flipH");

        } else if (flag == "--flipV" || flag == "-v") {
            args.flipV = true;
            args.order.push_back("flipV");

        } else if (flag == "--brighten" || flag == "-b") {
            std::string val = inline_val;
            if (val.empty()) {
                if (tokens.empty()) {
                    error("missing value", flag + " requires an integer");
                    exit(1);
                }
                if (startsWith(tokens.front(), "-")) {
                    error("missing value", flag + " expected a value but got " + tokens.front());
                    exit(1);
                }
                val = tokens.front();
                tokens.erase(tokens.begin());
            }
            try {
                args.brighten = std::stoi(val);
            } catch (...) {
                error("invalid value", flag + " expects an integer, got \"" + val + "\"");
                exit(1);
            }
            if (args.brighten < -255 || args.brighten > 255) {
                error("out of range", flag + " must be in [-255, 255], got " + val);
                exit(1);
            }
            args.use_brighten = true;
            args.order.push_back("brighten");

        } else if (flag == "--rotate" || flag == "-r") {
            std::string val = inline_val;
            if (val.empty()) {
                if (tokens.empty()) {
                    error("missing value", flag + " requires an integer");
                    exit(1);
                }
                if (startsWith(tokens.front(), "-")) {
                    error("missing value", flag + " expected a value but got " + tokens.front());
                    exit(1);
                }
                val = tokens.front();
                tokens.erase(tokens.begin());
            }
            int deg;
            try {
                deg = std::stoi(val);
            } catch (...) {
                error("invalid value", flag + " expects an integer, got \"" + val + "\"");
                exit(1);
            }
            if (deg != 0 && deg != 90 && deg != 180 && deg != 270) {
                error("invalid value", flag + " must be one of {0,90,180,270}, got " + val);
                exit(1);
            }
            args.rotate     = deg;
            args.use_rotate = true;
            args.order.push_back("rotate");

        // ---- P04 kernel flags ----

        } else if (flag == "--sharpen" || flag == "-s") {
            args.sharpen = true;
            args.order.push_back("sharpen");

        } else if (flag == "--edgeDetect" || flag == "-e") {
            args.edgeDetect = true;
            args.order.push_back("edgeDetect");

        } else if (flag == "--emboss" || flag == "-m") {
            args.emboss = true;
            args.order.push_back("emboss");

        } else if (flag == "--gaussian" || flag == "-n") {
            args.gaussian = true;
            args.order.push_back("gaussian");

        } else {
            error("unknown option", flag);
            exit(1);
        }
    }

    return args;
}

// -----------------------------------------------------------------------
// Args::print
// -----------------------------------------------------------------------

void Args::print() const {
    std::cout << "INPUT   : " << input  << "\n";
    std::cout << "OUTPUT  : " << output << "\n";

    std::cout << "ORDER   :";
    for (const auto& op : order) std::cout << " " << op;
    std::cout << "\n";

    if (use_brighten)
        std::cout << "BRIGHTEN: " << brighten << "\n";
    if (use_rotate)
        std::cout << "ROTATE  : " << rotate << "\n";
}
