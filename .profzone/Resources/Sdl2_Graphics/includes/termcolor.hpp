#pragma once
#include <string>

namespace Termcolor {
    const std::string reset = "\033[0m";
    const std::string boldYellow = "\033[1;33m";  // bold yellow
    const std::string green = "\033[0;32m";       // green
    const std::string cyan = "\033[1;36m";        // cyan
    const std::string magenta = "\033[1;35m";     // magenta
    const std::string gray = "\033[90m";          // gray
    const std::string white = "\033[1;37m";       // white
}  // namespace Termcolor