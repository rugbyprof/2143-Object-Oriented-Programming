# MouseClicks

## 🧠 Concept Summary

When you poll for events using `SDL_PollEvent(&event)`, you can check for mouse events such as:

- `SDL_MOUSEBUTTONDOWN` — when a button is pressed.
- `SDL_MOUSEBUTTONUP` — when it’s released.
- `SDL_MOUSEMOTION` — when the mouse moves.

Each `SDL_Event` contains a sub-structure with details about the mouse event:

```cpp
event.button.x;  // X coordinate of click
event.button.y;  // Y coordinate of click
event.button.button; // which mouse button
```

---

## 🧩 Minimal Example

```cpp
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Mouse Click Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    std::cout << "Mouse Button Down at ("
                              << event.button.x << ", "
                              << event.button.y << ") ";
                    if (event.button.button == SDL_BUTTON_LEFT)
                        std::cout << "[LEFT]";
                    else if (event.button.button == SDL_BUTTON_RIGHT)
                        std::cout << "[RIGHT]";
                    else if (event.button.button == SDL_BUTTON_MIDDLE)
                        std::cout << "[MIDDLE]";
                    std::cout << std::endl;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
```

---

## 🧭 Explanation

- `SDL_MOUSEBUTTONDOWN`: Fired when a mouse button is pressed.
- `event.button.x` / `event.button.y`: Mouse coordinates **relative to the window**.
- `event.button.button`: Which button (`SDL_BUTTON_LEFT`, etc.).
- You can also use:

  ```cpp
  SDL_MOUSEBUTTONUP
  SDL_MOUSEMOTION
  SDL_MOUSEWHEEL
  ```

  depending on what you need.

---

## ⚙️ Quick Extension

If you want to capture **clicks inside a specific region** (like a button):

```cpp
if (event.type == SDL_MOUSEBUTTONDOWN) {
    int mx = event.button.x;
    int my = event.button.y;
    SDL_Rect buttonRect = {100, 100, 200, 50};  // x, y, w, h

    if (mx >= buttonRect.x && mx <= buttonRect.x + buttonRect.w &&
        my >= buttonRect.y && my <= buttonRect.y + buttonRect.h) {
        std::cout << "Button clicked!" << std::endl;
    }
}
```

---

## 🧩 Click to Change Color

```cpp
#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Click to Change Color",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    bool isRed = true; // toggles color
    SDL_Event event;

    // Our clickable rectangle
    SDL_Rect box = {220, 190, 200, 100};  // x, y, width, height

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN: {
                    int mx = event.button.x;
                    int my = event.button.y;

                    // check if inside box
                    if (mx >= box.x && mx <= box.x + box.w &&
                        my >= box.y && my <= box.y + box.h) {
                        isRed = !isRed;  // toggle color
                        std::cout << "Clicked box at (" << mx << "," << my << ")\n";
                    }
                    break;
                }
            }
        }

        // clear background
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);

        // draw box
        if (isRed)
            SDL_SetRenderDrawColor(renderer, 255, 60, 60, 255);
        else
            SDL_SetRenderDrawColor(renderer, 60, 180, 255, 255);

        SDL_RenderFillRect(renderer, &box);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
```

---

## 🧠 Key Takeaways for Students

| Concept                | What’s Happening                               |
| ---------------------- | ---------------------------------------------- |
| **Event polling**      | The loop checks for all SDL events every frame |
| **Mouse region check** | Rectangle hit-test via coordinate bounds       |
| **State toggle**       | A simple boolean flips between colors          |
| **Repainting**         | Renderer is redrawn every frame with new color |

---

## 🧰 Try This (Mini Extensions)

- Make multiple rectangles and detect _which_ was clicked.
- Change shape color based on **left vs right click**.
- Add **hover highlighting** with `SDL_MOUSEMOTION`.
- Print click coordinates on the screen using `SDL_ttf`.
