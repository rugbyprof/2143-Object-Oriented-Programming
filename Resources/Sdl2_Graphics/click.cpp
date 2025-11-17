
#include <SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Click to Change Color",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool      running = true;
    bool      isRed = true;  // toggles color
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