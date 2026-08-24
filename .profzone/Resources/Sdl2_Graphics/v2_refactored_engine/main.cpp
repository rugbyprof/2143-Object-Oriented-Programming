#include "sdl2_engine.hpp"

int main() {
    Sdl2Start     sdl("SDL2 Grid Example", 800, 600);
    RenderContext context = sdl.init_window();

    GameEngine game(context, 10);
    game.run();

    return 0;
}