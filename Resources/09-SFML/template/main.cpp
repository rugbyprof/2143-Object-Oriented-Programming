#include "Game.hpp"

/**
 * @brief Main driver for our game program
 * 
 * @param argc  - number of args passed in
 * @param argv  - char* array of arguments on command line
 * @return int  - success code
 */
int main(int argc, char **argv) {
    sf::RenderWindow *gameWindow;  // ref to game window
    Game *            game;        // ref to instance of game

    // default values if none are passed in by command line params
    int         width = 800;
    int         height = 600;
    std::string title = "Default Game Title";

    if (argc > 1) {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
        title = argv[3];
    }

    gameWindow = new sf::RenderWindow(sf::VideoMode(width, height), title);

    game = new Game(gameWindow);

    game->run();

    return 0;
}