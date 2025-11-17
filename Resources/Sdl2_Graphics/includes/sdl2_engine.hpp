#pragma once
#include <SDL.h>

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

#include "json.hpp"
using nlohmann::json;

struct RenderContext {
    SDL_Window*   window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int           width = 0;
    int           height = 0;
};

// =============================================================
//  SDL2 Initialization Helper
// =============================================================
class Sdl2Start {
private:
    std::string     title;
    int             windowWidth;
    int             windowHeight;
    SDL_DisplayMode displayMode;
    RenderContext   context;

    std::pair< int, int > screen_size() {
        if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
            std::cerr << "SDL_GetCurrentDisplayMode Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return {800, 600};
        }
        return {displayMode.w, displayMode.h};
    }

    RenderContext create_render_context(const std::string& title, int width, int height, Uint32 flags) {
        SDL_Window* window = SDL_CreateWindow(title.c_str(),
                                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              width, height, flags);
        if (!window)
            throw std::runtime_error(std::string("Window Error: ") + SDL_GetError());

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_DestroyWindow(window);
            throw std::runtime_error(std::string("Renderer Error: ") + SDL_GetError());
        }

        return {window, renderer, width, height};
    }

public:
    Sdl2Start(std::string title, int width, int height)
        : title(std::move(title)), windowWidth(width), windowHeight(height) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            throw std::runtime_error(std::string("SDL Init Error: ") + SDL_GetError());
        screen_size();
    }

    RenderContext init_window() {
        context = create_render_context(title, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        return context;
    }

    ~Sdl2Start() {
        SDL_Quit();
    }
};

// =============================================================
//  Game Engine Wrapper
// =============================================================
class GameEngine {
private:
    RenderContext ctx;
    bool          running = true;
    int           cellSize = 10;

public:
    GameEngine(RenderContext context, int cellSize = 10)
        : ctx(std::move(context)), cellSize(cellSize) {}

    void handle_event(SDL_Event& event) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << "Mouse click at (" << event.button.x
                          << ", " << event.button.y << ")\n";
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
                break;
        }
    }

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

    void add_pattern(const json& j, int offsetX, int offsetY) {
        // Placeholder for adding pattern logic
        if (j.is_object()) {
            auto it = j.begin();
            while (it != j.end()) {
                const auto& cell = it.value();
                int         x = cell[0].get< int >() + offsetX;
                int         y = cell[1].get< int >() + offsetY;
                std::cout << "Adding cell at (" << x << ", " << y << ")\n";
                ++it;
            }
        }
    }

    void run() {
        SDL_Event event;
        while (running) {
            while (SDL_PollEvent(&event)) {
                handle_event(event);
            }
            draw_grid();
            SDL_Delay(16);
        }
        SDL_DestroyRenderer(ctx.renderer);
        SDL_DestroyWindow(ctx.window);
    }
};
//         // FRAME RATE CONTROL
//         // --------------------------------------------------------
//         // Delay to cap frame rate (approx. 60 FPS here).
//         SDL_Delay(16);  // Roughly 16 milliseconds per frame
//     }

//     // Cleanup resources before exiting.
//     SDL_DestroyRenderer(context.renderer);
//     SDL_DestroyWindow(context.window);
//     SDL_Quit();

//     return 0;
// }