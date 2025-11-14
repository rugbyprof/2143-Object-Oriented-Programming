#pragma once

#include "CellularAutomaton.hpp"
#include <iostream>
#include <vector>

class ConwayLife : public CellularAutomaton {
   public:
    ConwayLife(int r, int c);
    void step() override;           // Conway's rules
    void display() const override;  // ASCII visualization
};

// --------------------------------------------------------------
// Constructor:
// Calls the base CellularAutomaton(r, c) to set up grid size,
// then initializes the grid with a random pattern.
// --------------------------------------------------------------
ConwayLife::ConwayLife(int r, int c)
    : CellularAutomaton(r, c)  // delegate grid creation to base class
{
    randomize(0.25);  // 25% initial density
}

// --------------------------------------------------------------
// step()
// Applies Conway's Game of Life rules to update the grid by ONE generation.
//
// Rules Recap:
//   1. A live cell with 2 or 3 neighbors survives.
//   2. A dead cell becomes alive if it has exactly 3 neighbors.
//   3. All other live cells die; all other dead cells stay dead.
//
// Implementation:
//   - Create a separate "next" grid so updates do not interfere.
//   - Use countNeighbors() inherited from CellularAutomaton.
// --------------------------------------------------------------
void ConwayLife::step() {
    // Copy current grid so we can compute next generation safely
    std::vector<std::vector<int>> next = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int n = countNeighbors(i, j);  // # of live neighbors

            if (grid[i][j]) {
                // Live cell: survives only with 2 or 3 neighbors
                next[i][j] = (n == 2 || n == 3);
            } else {
                // Dead cell: birth occurs only with exactly 3 neighbors
                next[i][j] = (n == 3);
            }
        }
    }

    grid = next;  // Commit new generation
}

// --------------------------------------------------------------
// display()
// Prints '#' for live cells and '.' for dead cells.
// Simple text-based visualization for terminal.
// --------------------------------------------------------------
void ConwayLife::display() const {
    for (const auto& row : grid) {
        for (int cell : row) std::cout << (cell ? "⬜" : "  ");
        std::cout << "\n";
    }
}