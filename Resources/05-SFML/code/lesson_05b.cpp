
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// 12:00

class Grid {
    // Grid configuration
    int rows;
    int cols;
    float cellSize;     // Width and height of each cell
    float gridStartX;   // Starting X position of the grid
    float gridStartY;   // Starting Y position of the grid
    float cellSpacing;  // Spacing between cells
    float lineThickness;
    std::vector<sf::RectangleShape> grid;  // Vector to hold grid cells

    void init() {
        // Create the grid cells
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setFillColor(sf::Color::White);  // Default cell color
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
    }

   public:
    Grid() {
        rows          = 3;
        cols          = 3;
        cellSize      = 100.f;  // Width and height of each cell
        gridStartX    = 200.f;  // Starting X position of the grid
        gridStartY    = 100.f;  // Starting Y position of the grid
        cellSpacing   = 0.f;    // Spacing between cells
        lineThickness = 1.f;
        init();
    }

    Grid(int rows, int cols) : rows(rows), cols(cols) {
        cellSize      = 100.f;  // Width and height of each cell
        gridStartX    = 200.f;  // Starting X position of the grid
        gridStartY    = 100.f;  // Starting Y position of the grid
        cellSpacing   = 0.f;    // Spacing between cells
        lineThickness = 1.f;
        init();
    }

    void setLineThickness(float thickness) {
        lineThickness = thickness;
        for (auto& cell : grid) {
            cell.setOutlineThickness(thickness);
        }
    }

    sf::Vector2i cellClicked(int x, int y) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row * cols + col].getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y))) {
                    // std::cout << "Cell clicked: " << row << ", " << col << std::endl;
                    return sf::Vector2i(row, col);
                }
            }
        }
        return sf::Vector2i(-1, -1);
    }

    std::vector<sf::RectangleShape> getGrid() { return grid; }
};

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 5: Drawing the Game Grid");
    sf::Vector2i clicked;
    Grid grid(3, 3);

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

                clicked = grid.cellClicked(mousePos.x, mousePos.y);
                std::cout << "clicked: " << clicked.x << ", " << clicked.y << std::endl;
            }
        }
        // Render
        window.clear(sf::Color::White);
        for (const auto& cell : grid.getGrid()) {
            window.draw(cell);
        }
        window.display();
    }

    return 0;
}