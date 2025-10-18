
#include <fstream>
#include <iostream>
#include <string>

#include "json.hpp"  // nlohmann/json

using json = nlohmann::json;

using namespace std;

namespace termcolor {
    const std::string reset = "\033[0m";
    const std::string key = "\033[1;33m";      // bold yellow
    const std::string stringv = "\033[0;32m";  // green
    const std::string number = "\033[1;36m";   // cyan
    const std::string boolean = "\033[1;35m";  // magenta
    const std::string nullv = "\033[90m";      // gray
    const std::string brace = "\033[1;37m";    // white
}  // namespace termcolor

void colorPrint(const json& j, int indent = 0) {
    std::string pad(indent, ' ');

    if (j.is_object()) {
        std::cout << termcolor::brace << "{\n"
                  << termcolor::reset;
        auto it = j.begin();
        while (it != j.end()) {
            std::cout << pad << "  " << termcolor::key << "\"" << it.key() << "\""
                      << termcolor::reset << ": ";
            colorPrint(it.value(), indent + 2);
            if (++it != j.end()) std::cout << ",";
            std::cout << "\n";
        }
        std::cout << pad << termcolor::brace << "}" << termcolor::reset;
    } else if (j.is_array()) {
        std::cout << termcolor::brace << "[\n"
                  << termcolor::reset;
        for (size_t i = 0; i < j.size(); ++i) {
            std::cout << pad << "  ";
            colorPrint(j[i], indent + 2);
            if (i != j.size() - 1) std::cout << ",";
            std::cout << "\n";
        }
        std::cout << pad << termcolor::brace << "]" << termcolor::reset;
    } else if (j.is_string()) {
        std::cout << termcolor::stringv << "\"" << j.get< std::string >() << "\"" << termcolor::reset;
    } else if (j.is_number()) {
        std::cout << termcolor::number << j << termcolor::reset;
    } else if (j.is_boolean()) {
        std::cout << termcolor::boolean << (j.get< bool >() ? "true" : "false") << termcolor::reset;
    } else if (j.is_null()) {
        std::cout << termcolor::nullv << "null" << termcolor::reset;
    }
}

void prettyPrint(const json& j) {
    std::cout << j.dump(4) << std::endl;
}

void usage(const char* progName) {
    std::cerr << "Usage: " << progName << " <input_file> <pattern_name>\n";
    std::cerr << "  <input_file>   : Name of the file to read (e.g ./data/patterns.json)\n";
    std::cerr << "  <pattern_name>  : Name of the pattern to print (e.g. beehive or glider etc.) \n";
    std::cerr << "Example: " << progName << " ./data/patterns.json glider\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    string pattern_name = argv[2];
    string file_name = argv[1];

    std::ifstream file(file_name);  // open the file

    if (!file.is_open()) {
        std::cerr << "Could not open JSON file! " << file_name << "\n";
        return 1;
    }

    json patterns;
    file >> patterns;

    colorPrint(patterns);

    return 0;
}