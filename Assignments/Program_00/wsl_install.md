```yaml
title: "Installing and Verifying SDL2 + SDL2_ttf on WSL"
author: "T. Griffin"
course: "Operating Systems / 2D Game Programming"
tags: ["SDL2", "WSL", "C++", "Linux", "Graphics"]
```

---

# 🧩 Installing SDL2 and SDL2_ttf on WSL

This guide walks through installing **SDL2** and **SDL2_ttf** on a Windows Subsystem for Linux (WSL) environment, verifying their locations, and running a minimal text-rendering example.
Perfect for verifying your development setup before diving into SDL2 projects.

---

## 🪄 1️⃣ Install SDL2 and SDL2_ttf

Update your package list and install SDL2 development libraries:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-ttf-dev build-essential pkg-config
```

To confirm successful installs:

```bash
pkg-config --list-all | grep -i sdl
```

You should see something like:

```
sdl2             SDL - Simple DirectMedia Layer
SDL2_ttf         SDL_ttf - TrueType font rendering for SDL
```

---

## 🎨 2️⃣ Minimal Example — Displaying Text in the Middle of a Window

Here’s a small **C++** program (`main.cpp`) that opens a window, renders text using SDL_ttf, and displays it in the center:

```cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF could not initialize! " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Text Example",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          400, 200,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! " << SDL_GetError() << std::endl;
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 28);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, SDL2_ttf!", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0, texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {200 - texW / 2, 100 - texH / 2, texW, texH};

    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);  // Display window for 3 seconds

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
```

> ⚠️ Make sure you have a TTF font on your system —
> `DejaVuSans.ttf` is a safe default on Ubuntu/WSL.

---

## ⚙️ 3️⃣ One-Liner Compile + Run Command

```bash
g++ -std=c++17 -Wall -O2 main.cpp -o main $(pkg-config --cflags --libs sdl2 SDL2_ttf libzmq)
```

Compile and run using a single command:

```bash
g++ -std=c++17 -Wall -O2 main.cpp -o sdl_text \
    $(pkg-config --cflags --libs sdl2 SDL2_ttf) && ./sdl_text
```

If everything is installed correctly, you’ll see a small window displaying:

> **Hello, SDL2_ttf!**

---

## 🧠 4️⃣ Verify Installation: `check_sdl2.sh`

You can use this script to confirm your SDL2 setup:

```bash
#!/usr/bin/env bash
# check_sdl2.sh — verify SDL2 + SDL2_ttf installation paths on WSL/Linux

echo "🔍 Checking SDL2 installation paths..."

# 1️⃣ Check pkg-config results (best method)
if command -v pkg-config &> /dev/null; then
    echo "✅ pkg-config found. Checking libraries..."
    echo "---- SDL2 ----"
    pkg-config --cflags --libs sdl2 2>/dev/null || echo "⚠️ SDL2 not found via pkg-config."
    echo "---- SDL2_ttf ----"
    pkg-config --cflags --libs SDL2_ttf 2>/dev/null || echo "⚠️ SDL2_ttf not found via pkg-config."
else
    echo "❌ pkg-config not installed. Run: sudo apt install pkg-config"
fi

# 2️⃣ Look manually for headers and libs
echo
echo "🔎 Searching for SDL2 headers..."
find /usr/include /usr/local/include /opt -type d -name "SDL2" 2>/dev/null | head -n 5 || echo "No SDL2 include dirs found."

echo
echo "🔎 Searching for SDL2 libraries..."
find /usr/lib /usr/local/lib /lib -type f \( -name "libSDL2*.so*" -o -name "libSDL2*.a" \) 2>/dev/null | head -n 5 || echo "No SDL2 libs found."

echo
echo "✅ Done."
```

Make it executable and run it:

```bash
chmod +x check_sdl2.sh
./check_sdl2.sh
```

---

### ✅ Example Output

```
🔍 Checking SDL2 installation paths...
✅ pkg-config found. Checking libraries...
---- SDL2 ----
-I/usr/include/SDL2 -D_REENTRANT  -lSDL2
---- SDL2_ttf ----
-I/usr/include/SDL2 -D_REENTRANT  -lSDL2_ttf

🔎 Searching for SDL2 headers...
/usr/include/SDL2

🔎 Searching for SDL2 libraries...
/usr/lib/x86_64-linux-gnu/libSDL2.so
/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so

✅ Done.
```

---

💡 **Pro Tip:**
If you get a blank or invisible window under WSL, make sure an **X server** (like [VcXsrv](https://sourceforge.net/projects/vcxsrv/) or [X410](https://x410.dev/)) is running on Windows, and your `$DISPLAY` variable is set:

```bash
export DISPLAY=$(grep nameserver /etc/resolv.conf | awk '{print $2}'):0
```
