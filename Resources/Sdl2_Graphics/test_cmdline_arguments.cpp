
#include <fstream>
#include <iostream>
#include <string>

#include "includes/json.hpp"  // nlohmann/json
#include "includes/termcolor.hpp"

using json = nlohmann::json;

using namespace std;

json parse_args_to_json(int argc, char* argv[]) {
    json params = json::object();

    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        auto             separator = arg.find('=');
        if (separator == std::string_view::npos || separator == 0 || separator == arg.size() - 1) {
            throw std::invalid_argument("Arguments must be formatted as key=value with non-empty key and value");
        }

        std::string key{arg.substr(0, separator)};
        std::string value{arg.substr(separator + 1)};
        params[key] = value;  // later keys overwrite earlier ones with the same name
    }

    return params;
}

int main(int argc, char* argv[]) {
    json params;
    try {
        params = parse_args_to_json(argc, argv);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    std::cout << params.dump(2) << '\n';
    for (auto& [key, value] : params.items()) {
        std::cout << Termcolor::boldYellow << key << Termcolor::reset << ", " << Termcolor::cyan << value << Termcolor::reset << '\n';
    }
    return 0;
}