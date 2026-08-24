// =============================================================
// 01_window.cpp - Minimal SDL2 Window
// =============================================================
// To compile (macOS example):
// g++ 01_window.cpp -o window -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// =============================================================

#include <SDL.h>  // Include the SDL2 library header

int main() {
    SDL_Init(SDL_INIT_VIDEO);  // 1️⃣ Initialize the SDL video subsystem

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window",           // 2️⃣ Title text for the window
        SDL_WINDOWPOS_CENTERED,  // 3️⃣ X position on the screen
        SDL_WINDOWPOS_CENTERED,  // 4️⃣ Y position on the screen
        800,                     // 5️⃣ Width of the window in pixels
        600,                     // 6️⃣ Height of the window in pixels
        0                        // 7️⃣ No flags (basic window)
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Delay(10000);  // 8️⃣ Keep window open for 2 seconds
    SDL_Quit();        // 9️⃣ Shut down SDL
    return 0;
}