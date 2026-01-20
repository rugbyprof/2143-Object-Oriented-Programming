#include <fstream>
#include <iostream>

#include "includes/argsToJson.hpp"
#include "includes/json.hpp"
#include "includes/sdl2_engine.hpp"
#include "includes/termcolor.hpp"

using namespace std;

using nlohmann::json;

json getParams(int argc, char* argv[]) {
    try {
        return ArgsToJson(argc, argv);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    ifstream f("patterns.json");
    json     data = json::parse(f);

    json params = getParams(argc, argv);
    int  cellSize = params.value("cell_size", 10);
    int  width = params.value("window_width", 800);
    int  height = params.value("window_height", 600);

    std::cout << params.dump(2) << "\n";

    std::cout << data["glider"].dump(4) << std::endl;

    Sdl2Start     sdl("SDL2 Grid Example", width, height);
    RenderContext context = sdl.init_window();

    GameEngine game(context, cellSize);
    game.add_pattern(data["glider"], 5, 5);
    game.run();

    return 0;
}