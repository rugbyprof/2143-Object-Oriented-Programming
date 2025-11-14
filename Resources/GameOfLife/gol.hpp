#include <unistd.h>  // For usleep() – used to pause between generations

#include "colors.h"    // Custom header for terminal color escape codes (e.g., ON_CYAN)
#include "helper.hpp"  // Contains helper functions like allocate()
#include <iostream>

using namespace std;

#define LIZARD u8"\U0001F438"  // Optional: Unicode emoji for a "living cell"

// --------------------------------------------------------------
// Class: GOL (Game of Life)
// Purpose: Implements Conway’s Game of Life using a simple
//          2D grid and terminal-based visualization.
// --------------------------------------------------------------
class GOL {
    int** board;  // Current generation grid
    int** next;   // Next generation grid (used during rule application)
    int width;    // Number of columns
    int height;   // Number of rows

    // ----------------------------------------------------------
    // Function: Clear
    // Purpose : Reset all cells in a 2D array to 0 (dead)
    // ----------------------------------------------------------
    void Clear(int**& array) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                array[i][j] = 0;
            }
        }
    }

    // ----------------------------------------------------------
    // Function: init
    // Purpose : Allocate both grids (board and next) and clear them.
    // ----------------------------------------------------------
    void init() {
        board = allocate(width, height);  // allocate() defined externally
        next  = allocate(width, height);

        Clear(board);
        Clear(next);
    }

   public:
    // ----------------------------------------------------------
    // Default Constructor
    // Creates a 30x20 Game of Life grid
    // ----------------------------------------------------------
    GOL() {
        width  = 30;
        height = 20;
        init();
    }

    // ----------------------------------------------------------
    // Parameterized Constructor
    // Creates a grid of user-specified dimensions
    // ----------------------------------------------------------
    GOL(int w, int h) {
        width  = w;
        height = h;
        init();
    }

    // ----------------------------------------------------------
    // Function: rando
    // Purpose : Randomly populate the grid with live (1) or dead (0) cells.
    //            Roughly 20% of cells start alive.
    // ----------------------------------------------------------
    void rando() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (rand() % 5 == 0)  // ~1 in 5 chance
                    board[i][j] = 1;
                else
                    board[i][j] = 0;
            }
        }
    }

    // ----------------------------------------------------------
    // Function: Print
    // Purpose : Draw the grid to the terminal using color blocks
    // ----------------------------------------------------------
    void Print() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (board[i][j] == 1) {
                    // Live cell → bright yellow block
                    cout << ON_IYELLOW << " ";
                    // Other options for fun:
                    // cout << "▆";  // Unicode block
                    // cout << LIZARD;  // Frog emoji for humor
                } else {
                    // Dead cell → cyan background
                    cout << ON_CYAN << " ";
                }
            }
            cout << endl << OFF;  // OFF resets color at end of each row
        }
        cout << endl << OFF;  // Reset again after the whole grid
    }

    // ----------------------------------------------------------
    // Function: OnWorld
    // Purpose : Check if a cell coordinate is inside the grid bounds
    // ----------------------------------------------------------
    bool OnWorld(int row, int col) {
        return row >= 0 && col >= 0 && row < height && col < width;
    }

    // ----------------------------------------------------------
    // Function: CountNeighbors
    // Purpose : Count live neighbors around a given cell
    // Notes   : Checks all 8 surrounding positions.
    // Description:
    //  Loops through all 3×3 surrounding positions.
    //  Skips (0, 0) so you don’t count the center cell.
    //  Still uses OnWorld() for safe bounds checking.
    // ----------------------------------------------------------
    int CountNeighbors(int row, int col) {
        int sum = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                // Skip the cell itself
                if (dy == 0 && dx == 0)
                    continue;

                int ny = row + dy;
                int nx = col + dx;

                if (OnWorld(ny, nx) && board[ny][nx] == 1)
                    sum++;
            }
        }
        return sum;
    }

    // Counts neighbors with "donut" wrapping behavior
    int CountNeighborsDonut(int row, int col) {
        int sum = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dy == 0 && dx == 0)
                    continue;

                int ny = (row + dy + height) % height;
                int nx = (col + dx + width) % width;

                if (board[ny][nx] == 1)
                    sum++;
            }
        }
        return sum;
    }

    // ----------------------------------------------------------
    // Function: ApplyRules
    // Purpose : Apply Conway’s Game of Life rules to each cell
    // ----------------------------------------------------------
    /*
        Rules Recap:
        1. Any live cell with two or three live neighbors survives.
        2. Any dead cell with exactly three live neighbors becomes a live cell.
        3. All other live cells die in the next generation.
           Similarly, all other dead cells stay dead.
    */
    void ApplyRules() {
        int n;  // neighbor count
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                n = CountNeighbors(i, j);

                if (board[i][j] && (n == 2 || n == 3)) {
                    // Rule 1: Survival
                    next[i][j] = 1;
                } else if (!board[i][j] && n == 3) {
                    // Rule 2: Birth
                    next[i][j] = 1;
                } else {
                    // Rule 3: Death or remains dead
                    next[i][j] = 0;
                }
            }
        }
    }

    // ----------------------------------------------------------
    // Function: Swap
    // Purpose : Swap "next" into "board" after each generation.
    //            Avoids copying arrays element-by-element.
    // ----------------------------------------------------------
    void Swap() {
        int** temp = board;
        board      = next;
        next       = temp;
    }

    // ----------------------------------------------------------
    // Function: Run
    // Purpose : Run the simulation for a given number of generations.
    // ----------------------------------------------------------
    void Run(int generations) {
        for (int g = 0; g < generations; g++) {
            ApplyRules();  // Apply Game of Life logic
            Swap();        // Make "next" the new "board"
            Clear(next);   // Clear out next for reuse

            Print();          // Display the grid
            usleep(500000);   // Pause (500ms)
            system("clear");  // Clear terminal for next frame
        }
    }
};