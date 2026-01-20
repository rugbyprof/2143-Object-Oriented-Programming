#pragma once
#include <SDL.h>

#include <iostream>

#include "grid.hpp"

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
private:
    RenderContext ctx;
    Grid          grid;
    bool          running = true;

public:
    GameEngine(RenderContext c, int cellSize)
        : ctx(std::move(c)), grid(ctx.width, ctx.height, cellSize) {}

    void handle_event(SDL_Event& e) {
        if (e.type == SDL_QUIT)
            running = false;
        else if (e.type == SDL_MOUSEBUTTONDOWN)
            grid.toggleCell(e.button.x, e.button.y);
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            running = false;
    }

    void run() {
        SDL_Event e;
        while (running) {
            while (SDL_PollEvent(&e)) handle_event(e);
            grid.draw(ctx.renderer);
            SDL_RenderPresent(ctx.renderer);
            SDL_Delay(16);
        }
        SDL_DestroyRenderer(ctx.renderer);
        SDL_DestroyWindow(ctx.window);
    }
};