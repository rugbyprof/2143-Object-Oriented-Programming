#include <SDL.h>

#include <iostream>
#include <stdexcept>

#include "../includes/json.hpp"
using nlohmann::json;

using namespace std;

int main(int argc, char* argv[]) {
    int    cellSize = 10;
    int    width = 800;
    int    height = 600;
    string title = "GOL";

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        cerr << "Window Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Renderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool      running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);

        for (int x = 0; x <= 800; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y <= 600; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}