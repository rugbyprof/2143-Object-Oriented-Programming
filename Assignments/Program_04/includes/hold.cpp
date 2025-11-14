#pragma once
#include "CellularAutomaton.h"
#include "Screen.h"
#include <chrono>
#include <memory>
#include <thread>
#include <vector>

// --------------------------------------------------------------
// Base Class: Screen
// --------------------------------------------------------------
// Purpose:
//   This class defines a generic rendering interface for anything
//   that displays a 2D cellular automaton (or any grid of ints).
//
// Why this is useful:
//   - Allows multiple display backends (text, SDL2, ncurses, GUI)
//   - Code that runs the automaton does NOT depend on how it is drawn
//   - Encourages clean separation of "model" vs "view"
//
// The grid is represented as a vector of vector<int>, where
// each element is the state of a cell (0, 1, or other integers).
// --------------------------------------------------------------
class Screen {
   public:
    // ----------------------------------------------------------
    // render():
    //   Pure virtual function that must be implemented by any
    //   subclass. Responsible for drawing the given 2D grid.
    //
    //   The 'const' means the method does not modify the Screen.
    // ----------------------------------------------------------
    virtual void render(const std::vector<std::vector<int>>& grid) const = 0;

    // ----------------------------------------------------------
    // pause():
    //   Pure virtual. Allows a screen to control timing, frame rate,
    //   or animation pacing by sleeping for 'ms' milliseconds.
    // ----------------------------------------------------------
    virtual void pause(int ms) const = 0;

    // ----------------------------------------------------------
    // Virtual destructor:
    //   Ensures safe cleanup when deleting derived classes through
    //   a base pointer — required for polymorphic classes.
    // ----------------------------------------------------------
    virtual ~Screen() = default;
};

// --------------------------------------------------------------
// TextScreen:
// --------------------------------------------------------------
// A concrete implementation of Screen that renders a grid directly
// to the terminal using ASCII or Unicode characters.
//
// Useful for:
//   - quick demos
//   - debugging visual behavior quietly
//   - environments where no graphics library is available
//
// Implementations of render() and pause() live in TextScreen.cpp
// --------------------------------------------------------------
class TextScreen : public Screen {
   public:
    void render(const std::vector<std::vector<int>>& grid) const override;
    void pause(int ms) const override;
};

// --------------------------------------------------------------
// TextScreen::render()
// --------------------------------------------------------------
// Purpose:
//   Render a 2D grid of integers as simple text/emoji graphics.
//   - 1 = live cell  → shown as "⬜"
//   - 0 = dead cell  → shown as two spaces
//
// Behavior:
//   - Clears the terminal each frame (Linux: "clear", Windows: "cls")
//   - Prints each row, then flushes stdout so animation is smooth
//
// Notes for students:
//   - This is not performance-optimized; it's meant for clarity.
//   - Rendering via the terminal is simple but slow, which they
//     will notice once grids get large.
// --------------------------------------------------------------
void TextScreen::render(const std::vector<std::vector<int>>& grid) const {
#if defined(_WIN32)
    system("cls");  // Windows terminal clear
#else
    system("clear");  // Linux/macOS terminal clear
#endif

    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell ? "⬜" : "  ");
        }
        std::cout << "\n";
    }

    std::cout.flush();  // Force immediate screen output
}

// --------------------------------------------------------------
// TextScreen::pause()
// --------------------------------------------------------------
// Purpose:
//   Pause the simulation for a given number of milliseconds.
//   Useful for animation pacing.
//
// Uses C++ chrono + thread sleep.
// --------------------------------------------------------------
void TextScreen::pause(int ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}