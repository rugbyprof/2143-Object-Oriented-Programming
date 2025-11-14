#pragma once
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

class Screen {
   public:
    virtual void render(const std::vector<std::vector<int>>& grid) const = 0;
    virtual void pause(int ms) const                                     = 0;
    virtual ~Screen()                                                    = default;
};

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