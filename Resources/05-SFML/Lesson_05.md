## Lesson 5: Drawing the Game Grid

### Objective:

Learn how to draw a game grid using SFML’s sf::RectangleShape and manage grid cell positioning. This lesson is essential for creating the Knucklebones game board.

### Key Concepts

1. Grid Structure:
   - A game grid consists of rows and columns, where each cell can hold game elements (e.g., dice values).
   - Use sf::RectangleShape for the grid’s visual structure.
2. Dynamic Positioning:
   - Calculate positions for grid cells dynamically based on screen size.
3. Visual Customization:
   - Add colors, outlines, and other effects for visual clarity.

##Code Example

This example draws a 3x3 grid for one player, dynamically positioning cells within the window.
e

```cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 5: Drawing the Game Grid");

    // Grid configuration
    const int rows = 3;
    const int cols = 3;
    const float cellSize = 100.f; // Width and height of each cell
    const float gridStartX = 200.f; // Starting X position of the grid
    const float gridStartY = 100.f; // Starting Y position of the grid
    const float cellSpacing = 10.f; // Spacing between cells

    // Vector to hold grid cells
    std::vector<sf::RectangleShape> grid;

    // Create the grid cells
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setFillColor(sf::Color::White); // Default cell color
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(2.f);

            // Calculate cell position
            float x = gridStartX + col * (cellSize + cellSpacing);
            float y = gridStartY + row * (cellSize + cellSpacing);
            cell.setPosition(x, y);

            // Add the cell to the grid
            grid.push_back(cell);
        }
    }

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Render
        window.clear(sf::Color::White);
        for (const auto& cell : grid) {
            window.draw(cell);
        }
        window.display();
    }

    return 0;
}
```

## Explanation

### Grid Basics

1. Rows and Columns:
   - The grid is defined by a specific number of rows and columns (rows = 3, cols = 3).
2. Cell Positioning:
   - Each cell’s position is calculated dynamically:

```cpp
float x = gridStartX + col * (cellSize + cellSpacing);
float y = gridStartY + row * (cellSize + cellSpacing);
```

• gridStartX and gridStartY determine the grid’s starting position on the screen.

3. Cell Customization:
   - setFillColor: Sets the cell’s background color.
   - setOutlineColor and setOutlineThickness: Add a border for better visibility.

Activity

1. Expand the Grid:
   - Change the grid size to 5x5. Ensure the cells still fit within the window.
2. Add Labels:
   - Use sf::Text to label each cell with its row and column index.
3. Highlight Cells:
   - Change a cell’s color when the mouse hovers over it. Use:

```cpp
sf::Vector2i mousePos = sf::Mouse::getPosition(window);
```

### Discussion Questions

1. How would you center the grid within the window regardless of its size?
2. How could you store and render the values (e.g., dice rolls) within the grid cells?
3. What would you change to draw grids for two players on the same screen?

### Expected Output

1. A 3x3 grid is displayed starting at (200, 100).
2. Cells have white backgrounds, black outlines, and a small gap between them.

This lesson establishes the visual foundation for the Knucklebones game board.
