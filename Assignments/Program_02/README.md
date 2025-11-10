## 🎨 Assignment 02 – SDL2 Shape Renderer

#### Due: 11-19-2025 (Wednesday @ ClassTime)

### 🎯 Overview

Now that you can parse patterns from JSON, use **SDL2** to render those shapes visually on screen.

You’ll create an SDL2 window and draw each cell as a filled rectangle (no grid lines or animation yet).
This sets the foundation for your upcoming **Game of Life** grid engine.

---

### 🧠 Learning Objectives

- Set up an SDL2 window and renderer.
- Draw rectangles to represent live cells.
- Load pattern data from JSON and render at correct coordinates.
- Understand the difference between **logical** vs **pixel** space.

---

### 🧰 Requirements

1. Load the same `patterns.json` file.
2. Select one pattern (e.g., `glider`) to draw.
3. Each cell is a filled rectangle of a fixed size (e.g., 10×10 px).
4. The pattern should be centered in the window.
5. The pattern should have a random color.
6. BONUS: Load pattern choice from command line argument.
7. Press **ESC** to quit.

---

### 🪄 Example Output

A 500×500 window showing small white squares arranged in your chosen pattern.

---

### 🧩 Suggested Starter Code

```cpp
/**
 * ============================================================
 *  SDL2 Grid Example
 * ============================================================
 *  This program creates a simple window using SDL2 and
 *  renders a visible grid based on a given cell size.
 *
 *  Concepts introduced:
 *   - Converting grid coordinates to pixel coordinates
 *   - Drawing vertical & horizontal grid lines
 *   - Handling the basic SDL event loop
 *   - Using variables to control cell size, grid width, and height
 *
 */
#include <SDL.h>
#include <fstream>
#include <iostream>  // For error logging to std::cerr

#include "json.hpp"

using json = nlohmann::json;

using namespace std;

int main() {
    // ------------------------------------------------------------
    // CONFIGURATION SECTION
    // ------------------------------------------------------------
    // Each "cell" will be a square this many pixels wide/tall
    const int cellSize = 20;

    // Number of cells horizontally and vertically
    const int gridWidth = 30;   // 30 cells across
    const int gridHeight = 20;  // 20 cells tall

    // Total pixel dimensions of the SDL window
    const int windowWidth = cellSize * gridWidth;
    const int windowHeight = cellSize * gridHeight;

    // ------------------------------------------------------------
    // INITIALIZE SDL
    // ------------------------------------------------------------
    // SDL_Init starts the requested SDL subsystems.
    // SDL_INIT_VIDEO allows us to create a window and draw graphics.
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << "\n";
        return 1;  // Return non-zero to indicate an error
    }

    // ------------------------------------------------------------
    // CREATE THE WINDOW
    // ------------------------------------------------------------
    // SDL_CreateWindow opens a visible OS-level window.
    // Parameters:
    //   - Title text
    //   - x, y screen position (SDL_WINDOWPOS_CENTERED lets SDL decide)
    //   - Width and height in pixels
    //   - Flags (SDL_WINDOW_SHOWN = visible on creation)
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Grid Example",     // title
        SDL_WINDOWPOS_CENTERED,  // x position
        SDL_WINDOWPOS_CENTERED,  // y position
        windowWidth,             // window width (pixels)
        windowHeight,            // window height (pixels)
        SDL_WINDOW_SHOWN         // flags
    );

    // Verify the window was successfully created
    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << "\n";
        SDL_Quit();  // Clean up SDL before exiting
        return 1;
    }

    // ------------------------------------------------------------
    // CREATE A RENDERER
    // ------------------------------------------------------------
    // The renderer handles drawing operations on the window.
    // SDL_RENDERER_ACCELERATED tells SDL to use GPU acceleration.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // ------------------------------------------------------------
    // MAIN LOOP
    // ------------------------------------------------------------
    // "running" flag controls the lifetime of the program.
    bool      running = true;
    SDL_Event event;  // Struct that holds event information (keyboard, mouse, quit, etc.)

    ifstream f("patterns.json");
    json     data = json::parse(f);

    while (running) {
        // --------------------------------------------------------
        // EVENT HANDLING
        // --------------------------------------------------------
        // SDL_PollEvent() pulls events from the event queue.
        // This loop checks for any pending events, e.g. user clicking "X" to close.
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)  // Window close event
                running = false;         // Exit the main loop
        }

        // --------------------------------------------------------
        // CLEAR SCREEN
        // --------------------------------------------------------
        // Set the background color first (dark blue-gray here).
        // The format is RGBA, each component 0–255.
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // --------------------------------------------------------
        // DRAW GRID LINES
        // --------------------------------------------------------
        // Set the color for the grid lines (lighter gray).
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);

        // Draw vertical lines.
        // Start at x = 0 and go to windowWidth, stepping by cellSize each time.
        for (int x = 0; x <= windowWidth; x += cellSize) {
            SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
        }

        // Draw horizontal lines.
        // Start at y = 0 and go to windowHeight, stepping by cellSize each time.
        for (int y = 0; y <= windowHeight; y += cellSize) {
            SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
        }

        // --------------------------------------------------------
        // SHOW THE RESULT
        // --------------------------------------------------------
        // Swap the off-screen buffer with the on-screen buffer.
        // Everything drawn since the last call to SDL_RenderPresent()
        // now becomes visible.
        SDL_RenderPresent(renderer);

        // --------------------------------------------------------
        // FRAME RATE LIMIT
        // --------------------------------------------------------
        // Delay ~16 ms to target roughly 60 frames per second.
        // (1000 ms / 60 ≈ 16.6 ms)
        SDL_Delay(16);
    }

    // ------------------------------------------------------------
    // CLEANUP
    // ------------------------------------------------------------
    // Free SDL resources before exiting to avoid memory leaks.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;  // 0 = successful program termination
}

```

### 🧮 Rubric

Upload your `Program_02` folder into your `Assignments` folder for grading.

| Criterion                          | Description                             | Points  |
| ---------------------------------- | --------------------------------------- | ------- |
| SDL2 window setup                  | Properly initializes and shuts down SDL | 20      |
| JSON data correctly rendered       | Pattern visible as expected             | 25      |
| Centered and scaled correctly      | Pattern placement logical               | 15      |
| Code organization and clarity      | Readable, modular, comments             | 20      |
| Responsiveness (ESC to quit, etc.) | Handles input cleanly                   | 20      |
| **Total**                          |                                         | **100** |
