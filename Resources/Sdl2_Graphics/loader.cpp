#include <fstream>   // For reading from files (ifstream)
#include <iomanip>   // For stream formatting (not used much here, but good to have)
#include <iostream>  // For console input/output
#include <string>    // For std::string
#include <vector>    // For std::vector container

#include "json.hpp"  // External library: nlohmann::json (header-only JSON parser)

// Create an alias for convenience, so we can write "json" instead of "nlohmann::json"
using json = nlohmann::json;

// --------------------------------------------------------------
// Struct representing a single "cell" coordinate in a shape
// --------------------------------------------------------------
struct Cell {
    int x;  // X-coordinate (horizontal position)
    int y;  // Y-coordinate (vertical position)
};

// --------------------------------------------------------------
// Struct representing a named shape made up of multiple cells
// --------------------------------------------------------------
struct Shape {
    std::string         name;    // Shape name (e.g., "glider", "beehive", etc.)
    int                 width;   // Width of the bounding box (from JSON)
    int                 height;  // Height of the bounding box (from JSON)
    std::vector< Cell > cells;   // List of active cell coordinates that form the shape
};

// --------------------------------------------------------------
// Function: print_shape()
// Purpose : Render a Shape object as ASCII art to the console.
// --------------------------------------------------------------
void print_shape(const Shape& shape) {
    // The JSON coordinates may include negative values,
    // so we need to find the minimum/maximum extents
    // to determine the actual size of the printable grid.
    int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
    for (const auto& c : shape.cells) {
        // Track the bounding box of all coordinates
        min_x = std::min(min_x, c.x);
        max_x = std::max(max_x, c.x);
        min_y = std::min(min_y, c.y);
        max_y = std::max(max_y, c.y);
    }

    // Debugging info: display the range of x-coordinates
    std::cout << "min_x = " << min_x << ", max_x = " << max_x << "\n";

    // Compute grid dimensions based on bounding box
    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;

    // Create a 2D grid of '.' (dead/empty cells)
    // Each row is a string, forming a rectangular ASCII grid
    std::vector< std::string > grid(height, std::string(width, '.'));

    // Example JSON format this function expects:
    // "cells" : [
    //     {"x" : 0, "y" : -1},
    //     {"x" : 1, "y" : -2},
    //     {"x" : 2, "y" : -2},
    //     {"x" : 3, "y" : -1},
    //     {"x" : 1, "y" : 0},
    //     {"x" : 2, "y" : 1},
    //     {"x" : 3, "y" : 0}
    // ]

    // Convert each coordinate into a position on the ASCII grid
    // Adjust for offset so negative coordinates are handled correctly
    for (const auto& c : shape.cells) {
        int gx = c.x - min_x;  // Normalize X relative to min_x
        int gy = c.y - min_y;  // Normalize Y relative to min_y

        // Safety check: ensure coordinate lies inside grid bounds
        if (gy >= 0 && gy < height && gx >= 0 && gx < width) {
            grid[gy][gx] = 'X';  // Mark a live/active cell
        }
    }

    // Display the shape name and size, then print the grid
    std::cout << "\n"
              << shape.name << " (" << shape.width << "x" << shape.height << ")\n";

    // Output each row in order (top to bottom)
    for (const auto& row : grid)
        std::cout << row << '\n';
}

// --------------------------------------------------------------
// main()
// Purpose: Load shape data from a JSON file, let user pick a shape,
//          and render it as ASCII art.
// --------------------------------------------------------------
int main() {
    std::ifstream file("shapes.json");  // Open JSON file for reading
    if (!file.is_open()) {
        std::cerr << "Error: Could not open shapes.json\n";
        return 1;  // Exit early if file missing
    }

    json data;
    try {
        file >> data;  // Parse entire JSON file into a json object
    } catch (const std::exception& e) {
        // Handle any malformed JSON parsing errors
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return 1;
    }

    // Ensure the file contains the expected top-level "shapes" object
    if (!data.contains("shapes")) {
        std::cerr << "Error: JSON missing 'shapes' key\n";
        return 1;
    }

    // Extract the dictionary of shapes
    auto shapes_data = data["shapes"];

    // Print available shape names
    std::cout << "Available shapes:\n";
    for (auto it = shapes_data.begin(); it != shapes_data.end(); ++it)
        std::cout << " - " << it.key() << '\n';

    // Ask user which shape to display
    std::string choice;
    std::cout << "\nEnter shape name: ";
    std::cin >> choice;

    // Validate user input
    if (!shapes_data.contains(choice)) {
        std::cerr << "Shape not found.\n";
        return 1;
    }

    // Extract the chosen shape’s JSON data
    auto shape_json = shapes_data[choice];

    // Expected JSON structure:
    // "size": { "w": 4, "h": 3 },
    // "cells": [ { "x": 0, "y": -1 }, ... ]

    // Build a Shape object from JSON
    Shape shape;
    shape.name = choice;
    shape.width = shape_json["size"]["w"];
    shape.height = shape_json["size"]["h"];

    // Loop through JSON array of cell coordinates and push into shape.cells
    for (auto& cell : shape_json["cells"]) {
        shape.cells.push_back({cell["x"], cell["y"]});
    }

    // Finally, print the selected shape in ASCII form
    print_shape(shape);

    return 0;  // Program success
}