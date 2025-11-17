#include <SDL.h>

#include <iostream>
#include <stdexcept>

#include "../includes/argsToJson.hpp"
#include "../includes/json.hpp"
using nlohmann::json;

using namespace std;

int main(int argc, char* argv[]) {
    json params = ArgsToJson(argc, argv);
    cout << "Starting SDL2 GOL with parameters:\n"
         << params.dump(4) << endl;
    int    cellSize = params.value("cell_size", 20);
    int    width = params.value("width", 800);
    int    height = params.value("height", 600);
    string title = params.value("title", "GOL");
    json   bgColor = params.value("bg_color", json::array({30, 30, 40, 255}));
    // json   lineColor = params.value("line_color", json::array({30, 30, 30}));
    // json gridColor = params.value("grid_color", json::array({80, 80, 100, 255}));
    json gridColor = params.value("grid_color", json::array({0, 100, 0, 0}));

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

        SDL_SetRenderDrawColor(renderer, bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        SDL_RenderClear(renderer);
        // set line color
        SDL_SetRenderDrawColor(renderer, gridColor[0], gridColor[1], gridColor[2], gridColor[3]);

        // draw vertical and horizontal grid lines
        for (int x = 0; x <= width; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, height);
        for (int y = 0; y <= height; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, width, y);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}