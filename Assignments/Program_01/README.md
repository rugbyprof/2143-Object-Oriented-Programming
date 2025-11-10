# 🧩 `Program_01_JSON_Loader`

#### Due: 11-12-2025 (Wednesday @ ClassTime)

```yaml
title: "Program_01 — JSON Loader Assignment"
course: "Operating Systems / Game of Life Series"
language: "C++17"
library: ["nlohmann::json"]
author: "T. Griffin"
summary: >
  A starter program to load and display Game of Life shape data from a JSON file.
  This introduces structured data parsing, iteration, and simple console output.
objectives:
  - Confirm you can compile and run a program that uses nlohmann::json
  - Understand how structured data (objects and arrays) represent GOL shapes
  - Visualize shapes as simple ASCII grids
  - Explore the JSON hierarchy and metadata
dependencies:
  - Program_00 successfully compiled and run
  - nlohmann/json.hpp placed inside ./includes/
```

---

## 🧩 Overview

Welcome to **Program_01 – JSON Loader**.
This short exercise builds your first _data-driven_ component for the Game of Life series.

You’ll load a JSON file containing named shape definitions (like “glider” or “blinker”), and then print one in ASCII form.
This will form the foundation for later programs that visualize these same shapes using **SDL2**.

---

# 🧠 Learning Goals

By completing this assignment, you’ll:

- Successfully compile and run a program that includes **nlohmann/json**.
- Load structured shape data from a file.
- Print a shape to the terminal using characters.
- Explore and optionally modify shape data to see how structure changes behavior.

---

# 🪜 Steps

## ✅ Required Tasks

1. **Setup Folder**

   - Copy or clone the `Program_01_JSON_Loader` folder.
   - Ensure the file `includes/json.hpp` exists.
   - Confirm that `shapes.json` is present in the same folder as `main.cpp`.

2. **Compile and Run**

   - In the terminal:

     ```bash
     make run
     ```

   - You should see a list of available shapes:

     ```
     Available shapes:
      - block
      - beehive
      - glider
      ...
     ```

   - Enter one shape name (e.g., `glider`) and verify that an ASCII pattern appears.

3. **Confirm Output**

   - The program should print a small text grid of `X` characters.
   - If it runs without errors, you’re ready for Program_02.

---

# 💻 `main.cpp`

```cpp
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using json = nlohmann::json;

struct Cell {
    int x;
    int y;
};

struct Shape {
    std::string name;
    int width;
    int height;
    std::vector<Cell> cells;
};

// Function to print a shape to console using ASCII characters
void print_shape(const Shape& shape) {
    // Determine min/max bounds in case there are negative coordinates
    int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
    for (const auto& c : shape.cells) {
        min_x = std::min(min_x, c.x);
        max_x = std::max(max_x, c.x);
        min_y = std::min(min_y, c.y);
        max_y = std::max(max_y, c.y);
    }

    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;

    std::vector<std::string> grid(height, std::string(width, '.'));

    // Plot live cells, adjusted for offset
    for (const auto& c : shape.cells) {
        int gx = c.x - min_x;
        int gy = c.y - min_y;
        if (gy >= 0 && gy < height && gx >= 0 && gx < width) {
            grid[gy][gx] = 'X';
        }
    }

    std::cout << "\n" << shape.name << " (" << shape.width << "x" << shape.height << ")\n";
    for (const auto& row : grid)
        std::cout << row << '\n';
}

int main() {
    std::ifstream file("shapes.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open shapes.json\n";
        return 1;
    }

    json data;
    try {
        file >> data;
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return 1;
    }

    if (!data.contains("shapes")) {
        std::cerr << "Error: JSON missing 'shapes' key\n";
        return 1;
    }

    auto shapes_data = data["shapes"];
    std::cout << "Available shapes:\n";
    for (auto it = shapes_data.begin(); it != shapes_data.end(); ++it)
        std::cout << " - " << it.key() << '\n';

    std::string choice;
    std::cout << "\nEnter shape name: ";
    std::cin >> choice;

    if (!shapes_data.contains(choice)) {
        std::cerr << "Shape not found.\n";
        return 1;
    }

    auto shape_json = shapes_data[choice];

    Shape shape;
    shape.name = choice;
    shape.width = shape_json["size"]["w"];
    shape.height = shape_json["size"]["h"];

    for (auto& cell : shape_json["cells"]) {
        shape.cells.push_back({cell["x"], cell["y"]});
    }

    print_shape(shape);
    return 0;
}
```

---

# 🧰 `Makefile` (auto-naming version)

```makefile
CXX := g++
CXXFLAGS := -Wall -std=c++17
TARGET := $(notdir $(CURDIR))
SRC := main.cpp
INCLUDES := -I./includes

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
```

---

# 🧠 Differences from Array-Based Version

| Feature             | Old Format                          | New Format                                |
| ------------------- | ----------------------------------- | ----------------------------------------- |
| Coordinates         | `[x, y]` arrays                     | `{ "x": n, "y": n }` objects              |
| Top-level structure | `shapes → name → [cells]`           | `shapes → name → {size, cells}`           |
| Parsing style       | Indexed access `cell[0]`, `cell[1]` | Named access `cell["x"]`, `cell["y"]`     |
| Metadata            | None                                | Added `size` for scaling & bounding boxes |

---

# 🧪 Example Run

```
Available shapes:
 - block
 - beehive
 - loaf
 - blinker
 - toad
 - beacon
 - glider
 - lwss
 - r_pentomino
 - diehard
 - acorn
 - gosper_glider_gun
 - lightweight_spaceship
 - small_exploder

Enter shape name: beacon

beacon (4x4)
XX..
XX..
..XX
..XX
```

---

### 🧩 1. Add Your Own Shape

Open `shapes.json` and add a simple one-cell pattern:

```json
"dot": {
  "size": { "w": 1, "h": 1 },
  "cells": [{ "x": 0, "y": 0 }]
}
```

Re-run the program and confirm it appears in the list and prints correctly.

---

### 🧩 2. Change the Display Character

In `main.cpp`, find:

```cpp
grid[gy][gx] = 'X';
```

Change it to `'█'`, `'#'`, or anything you like.
Re-run and see the difference in visualization.

---

### 🧩 3. Print Shape Count

Add this line before asking for input:

```cpp
std::cout << "\nTotal shapes loaded: " << shapes_data.size() << "\n";
```

---

# 🎯 Deliverables:

Upload your `Program_01` folder into your `Assignments` folder for grading.
