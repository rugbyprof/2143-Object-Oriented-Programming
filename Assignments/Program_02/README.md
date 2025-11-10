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
#include <SDL2/SDL.h>
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main() {
    // Load JSON patterns
    std::ifstream file("patterns.json");
    json patterns;
    file >> patterns;
    auto shape = patterns["glider"];

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL2 Shape Renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event e;
    const int CELL_SIZE = 10;
    int cx = 250, cy = 250; // Center of window

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (auto& c : shape["cells"]) {
            int x = cx + c["x"].get<int>() * CELL_SIZE;
            int y = cy + c["y"].get<int>() * CELL_SIZE;
            SDL_Rect rect = { x, y, CELL_SIZE-1, CELL_SIZE-1 };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
