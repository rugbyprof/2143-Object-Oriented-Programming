/**
 * GRID CLASS:
 *  This file contains a grid class that gives you the start of displaying score values
 *  within the proper grid columns. There is another version in lesson_05b.cpp that may
 *  implement things a little different.
 *
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// 11:00

class Grid {
    int rows;
    int cols;
    float cellSize;     // Width and height of each cell
    float gridStartX;   // Starting X position of the grid
    float gridStartY;   // Starting Y position of the grid
    float cellSpacing;  // Spacing between cells
    float lineThickness;
    std::vector<sf::RectangleShape> grid;

    void createGrid() {
        // Create the grid cells
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setFillColor(sf::Color::White);  // Default cell color
                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(lineThickness);

                // Calculate cell position
                float x = gridStartX + col * (cellSize + cellSpacing);
                float y = gridStartY + row * (cellSize + cellSpacing);
                cell.setPosition(x, y);

                // Add the cell to the grid
                grid.push_back(cell);
            }
        }
    }

   public:
    Grid(int r, int c, int cs, int gsx, int gsy, int space, int thick)
        : rows(r), cols(c), cellSize(cs), gridStartX(gsx), gridStartY(gsy), cellSpacing(space), lineThickness(thick) {
        createGrid();
    }
    Grid() {
        // Grid configuration
        rows          = 3;
        cols          = 3;
        cellSize      = 100.f;
        gridStartX    = 200.f;  // Starting X position of the grid
        gridStartY    = 100.f;  // Starting Y position of the grid
        cellSpacing   = 10.f;   // Spacing between cells
        lineThickness = 2.f;
        createGrid();
    }
    int getRows() { return rows; }
    int getCols() { return cols; }

    sf::RectangleShape getCell(int row, int col) { return grid[row * cols + col]; }

    sf::Vector2i cellClicked(int x, int y) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i * cols + j].getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
                    std::cout << "Cell clicked at: " << i << ", " << j << std::endl;
                    return sf::Vector2i(i, j);
                }
            }
        }
        return sf::Vector2i(-1, -1);
    }
};

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 5: Drawing the Game Grid");

    Grid grid(3, 3, 50, 400, 100, 0, 4);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Get mouse position relative to the window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;
                grid.cellClicked(mousePos.x, mousePos.y);
            }
        }

        // Render
        window.clear(sf::Color::White);
        // for (const auto& cell : grid) {
        //     window.draw(cell);
        // }
        for (int i = 0; i < grid.getRows(); i++) {
            for (int j = 0; j < grid.getCols(); j++) {
                window.draw(grid.getCell(i, j));
            }
        }
        window.display();
    }

    return 0;
}