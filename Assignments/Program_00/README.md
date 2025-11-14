# 🧱 `Program_00_Install_and_Compile`

#### Due: 11-07-2025 (Friday @ ClassTime)

```yaml
title: "Program_00 — Installing and Compiling SDL2"
course: "Operating Systems / Game of Life Series"
language: "C++17"
library: "SDL2"
author: "T. Griffin"
summary: >
  This starter module ensures every student can compile and run a basic SDL2 program.
  It introduces installation, linking, and the structure of a minimal SDL2 application.
objectives:
  - Install SDL2 development libraries
  - Compile and run a simple SDL2 window program
  - Understand the build command and Makefile structure
dependencies:
  - C++17 or higher
  - SDL2 development libraries
  - pkg-config or equivalent
next: "Program_01_JSON_Loader"
```

---

## 🧩 Overview

Welcome to **Program_00**, the “Hello, World” of SDL2.
The only goal here: get a working window to pop up and close cleanly.

If you can see a blank window for 3 seconds, congratulations — you’re ready for everything that follows.

---

# ⚙️ Installation Instructions

### 🐧 Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install libsdl2-dev
```

### 🍎 macOS (Homebrew)

```bash
brew install sdl2
```

### 🪟 Windows (MSYS2 / Mingw64)

```bash
pacman -S mingw-w64-x86_64-sdl2
```

Check installation:

```bash
pkg-config --cflags --libs sdl2
```

You should see something like:

```
-I/usr/include/SDL2 -D_REENTRANT -lSDL2
```

---

# 🧰 File Structure

```
Program_00_Install_and_Compile/
├── main.cpp
├── Makefile
└── README.md
```

---

# 💻 main.cpp

```cpp
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Game of Life — Program 00",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set background color (MSU maroon and gold flair 😎)
    SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000); // Keep window open for 3 seconds

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
```

---

# 💻 main_txt.cpp

```cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Text Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load font (path + size)
    TTF_Font* font = TTF_OpenFont("DejaVuSans.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Create a color (RGBA)
    SDL_Color white = {255, 255, 255, 255};

    // Create surface from text
    SDL_Surface* surface = TTF_RenderText_Blended(font, "Hello SDL2!", white);
    if (!surface) {
        std::cerr << "Text render error: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Convert surface to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Get text dimensions
    int textW = 0, textH = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);
    SDL_Rect dstRect = {320 - textW / 2, 240 - textH / 2, textW, textH};

    // Main loop
    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
```

---

# 🛠️ Makefile

```makefile
CXX := g++
CXXFLAGS := -Wall -std=c++17 $(shell pkg-config --cflags sdl2)
LDFLAGS := $(shell pkg-config --libs sdl2)

TARGET := program00
SRC := main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
```

---

# 🚀 Run It

```bash
make run
```

Expected result:
A window appears titled **“Game of Life — Program 00”** with a maroon background.
No errors, no tears, no existential crises.

---

# 🧠 Discussion

This “hello world” does three major things:

1. **Initializes** SDL (`SDL_Init`).
2. **Creates** a window and renderer.
3. **Cleans up** after itself.

Students should:

- Try changing the window size and background color.
- Deliberately break it (e.g., misspell `SDL_INIT_VIDEO`) to see error handling.
- Note that _nothing happens_ until they start using **events** — that comes later.

---

# ✅ Next Steps

You’ve officially entered the SDL multiverse.
Next: learn to load and parse a simple JSON file (`Program_01_JSON_Loader`) and start printing Game of Life patterns.
