#pragma once
#include "json.hpp"
#include <iostream>  // For error logging to std::cerr
#include <string>

using nlohmann::json;

json ArgsToJson(int argc, char* argv[]) {
    json params = json::object();

    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        auto separator = arg.find('=');
        if (separator == std::string_view::npos || separator == 0 || separator == arg.size() - 1) {
            throw std::invalid_argument("Arguments must be formatted as key=value with non-empty key and value");
        }

        std::string key{arg.substr(0, separator)};
        std::string value{arg.substr(separator + 1)};
        params[key] = json::parse(value);
    }

    return params;
}