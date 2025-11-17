#pragma once
#include <SDL.h>

#include <iostream>
#include <stdexcept>

struct RenderContext {
    SDL_Window*   window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int           width = 0, height = 0;
};

class Sdl2Start {
public:
    Sdl2Start(const std::string& title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error(std::string("SDL Init Error: ") + SDL_GetError());
        window = SDL_CreateWindow(title.c_str(),
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  width, height, SDL_WINDOW_SHOWN);
        if (!window)
            throw std::runtime_error(std::string("Window Error: ") + SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
            throw std::runtime_error(std::string("Renderer Error: ") + SDL_GetError());
        context = {window, renderer, width, height};
    }

    RenderContext init_window() { return context; }

    ~Sdl2Start() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window*   window = nullptr;
    SDL_Renderer* renderer = nullptr;
    RenderContext context;
};

class GameEngine {
public:
    GameEngine(RenderContext ctx, int cellSize) : ctx(ctx), cellSize(cellSize) {}
    void run() {
        SDL_Event e;
        bool      running = true;
        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    running = false;
            }
            draw_grid();
            SDL_Delay(16);
        }
    }

private:
    RenderContext ctx;
    int           cellSize;

    void draw_grid() {
        SDL_SetRenderDrawColor(ctx.renderer, 30, 30, 40, 255);
        SDL_RenderClear(ctx.renderer);
        SDL_SetRenderDrawColor(ctx.renderer, 80, 80, 100, 255);
        for (int x = 0; x <= ctx.width; x += cellSize)
            SDL_RenderDrawLine(ctx.renderer, x, 0, x, ctx.height);
        for (int y = 0; y <= ctx.height; y += cellSize)
            SDL_RenderDrawLine(ctx.renderer, 0, y, ctx.width, y);
        SDL_RenderPresent(ctx.renderer);
    }
};