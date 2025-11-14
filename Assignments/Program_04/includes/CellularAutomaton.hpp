#pragma once
#include <iostream>
#include <vector>

// --------------------------------------------------------------
// Base class for 2D Cellular Automata.
// This provides the grid structure and general utilities,
// while 'step()' and 'display()' must be implemented by derived classes.
//
// Example Uses:
//  - Conway's Game of Life
//  - Elementary automata
//  - Forest fire simulations
//  - Langton's Ant, Wireworld, etc.
//
// The goal is to give students a reusable polymorphic foundation.
// --------------------------------------------------------------
class CellularAutomaton {
   protected:
    int rows, cols;  // Dimensions of the grid (rows x columns)

    // 2D grid storing integer states.
    // Many automata use 0 = dead, 1 = alive, but derived classes may extend this.
    std::vector<std::vector<int>> grid;

   public:
    // ----------------------------------------------------------
    // Constructor initializes grid size and sets all cells to 0.
    // ----------------------------------------------------------
    CellularAutomaton(int r, int c) : rows(r), cols(c), grid(r, std::vector<int>(c, 0)) {
    }

    // Virtual destructor for safe polymorphic deletion.
    virtual ~CellularAutomaton() = default;

    // ----------------------------------------------------------
    // step(): Perform one update of the automaton rules.
    // Pure virtual → derived classes MUST implement this.
    // ----------------------------------------------------------
    virtual void step() = 0;

    // ----------------------------------------------------------
    // display(): Print or visualize the automaton.
    // Pure virtual → derived classes MUST implement this.
    // ----------------------------------------------------------
    virtual void display() const = 0;

    // ----------------------------------------------------------
    // countNeighbors:
    // Counts all orthogonal + diagonal neighbors around (r, c)
    // that are equal to 1 (typical for Game of Life).
    //
    // NOTE: Does NOT wrap around by default
    //       (students can override or extend this).
    // ----------------------------------------------------------
    int countNeighbors(int r, int c) const {
        int count = 0;

        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0)
                    continue;  // skip the cell itself

                int nr = r + dr;
                int nc = c + dc;

                // Boundary check (no wrapping)
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
                    if (grid[nr][nc] == 1)
                        count++;
            }
        }

        return count;
    }

    // ----------------------------------------------------------
    // randomize(density):
    // Fills the grid randomly with 1s based on probability.
    //
    // Example: density = 0.20 → 20% chance of being alive.
    // ----------------------------------------------------------
    void randomize(double density) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                double x   = (double)rand() / RAND_MAX;
                grid[r][c] = (x < density) ? 1 : 0;
            }
        }
    }

    // ----------------------------------------------------------
    // Accessor for grid (read-only).
    // Lets tests or models inspect output state.
    // ----------------------------------------------------------
    const std::vector<std::vector<int>>& getGrid() const {
        return grid;
    }
};