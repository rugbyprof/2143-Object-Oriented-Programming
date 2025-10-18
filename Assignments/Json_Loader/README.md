## 🧩 Assignment 01 – JSON Loader

### 🎯 Overview

You will write a small C++ program that loads and parses a JSON file containing **cellular automata patterns** such as “glider,” “blinker,” or “glider gun” or many others.

|                            Gosper Glider Gun                            |
| :---------------------------------------------------------------------: |
| <img src="https://images2.imgbox.com/1d/29/kSbvkMtf_o.gif" width="400"> |


---

### 🧠 Learning Objectives

- Work with **external data** in structured format (`json.hpp` or similar).
- Use **maps** and **vectors** to represent hierarchical data.
- Practice **file I/O** and **error handling** in C++.
- Understand **pattern-based data models** before introducing graphics.
- Understand and use **command line params**. 

---

### 🧰 Requirements

1. Load a `patterns.json` file (structure below).
2. Parse its data using a C++ JSON library (suggested: [nlohmann/json](https://github.com/nlohmann/json)).
3. Iterate through all patterns and print:
   - Pattern name
   - Grid size (width × height)
   - List of cell coordinates

---

### 📦 Example `patterns.json`

```json
{
  "blinker": {
    "size": { "w": 1, "h": 3 },
    "cells": [
      { "x": 0, "y": -1 },
      { "x": 0, "y": 0 },
      { "x": 0, "y": 1 }
    ]
  },
  "glider": {
    "size": { "w": 3, "h": 3 },
    "cells": [
      { "x": 0, "y": -1 },
      { "x": 1, "y": 0 },
      { "x": -1, "y": 1 },
      { "x": 0, "y": 1 },
      { "x": 1, "y": 1 }
    ]
  }
}
```

---

### 🧮 Example Output

```
Pattern: blinker
  Size: 1 x 3
  Cells:
    (0,-1),
    (0,0),
    (0,1)

Pattern: glider
  Size: 3 x 3
  Cells:
    (0,-1),
    (1,0),
    (-1,1),
    (0,1),
    (1,1)
```

---

### 💡 Suggested Starter Code

```cpp
#include <iostream>
#include <fstream>
#include "json.hpp"  // nlohmann/json
#include <string>

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

    std::ifstream file(a); // open the file

    if (!file.is_open()) {
        std::cerr << "Could not open JSON file! "<<file_name<<"\n";
        return 1;
    }

    json patterns;
    file >> patterns;

    colorPrint(patterns;)

    return 0;
}
```

---

### 🧮 Rubric

| Criterion                             | Description                      | Points  |
| ------------------------------------- | -------------------------------- | ------- |
| JSON successfully loaded              | Program loads file and parses it | 25      |
| Data structures correctly represented | Uses maps/vectors appropriately  | 20      |
| Console output formatted and correct  | Properly lists patterns          | 20      |
| Error handling and file checking      | Handles missing or invalid file  | 15      |
| Code clarity and comments             | Clean, readable, well-commented  | 20      |
| **Total**                             |                                  | **100** |
