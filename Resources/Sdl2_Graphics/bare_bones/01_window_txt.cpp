// =============================================================
// 01_window.cpp - Minimal SDL2 Window
// =============================================================
// To compile (macOS example):
// g++ 01_window_txt.cpp -o window_txt -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
// =============================================================

#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // 🧠 Initialize SDL_ttf

    SDL_Window* window = SDL_CreateWindow("SDL2 Text Example",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool      running = true;
    SDL_Event event;

    // 1️⃣ Load a font (adjust the path to your .ttf file)
    TTF_Font* font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 48);

    // 2️⃣ Create a color (white)
    SDL_Color color = {255, 255, 255, 255};

    while (running) {
        // 1️⃣ Poll for events (keyboard, mouse, quit)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

   
        // 3️⃣ Render text to a *surface*
        SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, Graylian!", color);

        // 4️⃣ Convert surface to a *texture* for rendering
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // 5️⃣ Query texture size for placement
        int textW = 0, textH = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);

        SDL_Rect dst = {100, 100, textW, textH};

        // 6️⃣ Draw it
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, &dst);
        SDL_RenderPresent(renderer);
    }

    // 7️⃣ Cleanup
    // SDL_DestroyTexture(texture);
    // SDL_FreeSurface(surface);
    // TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}