/**
 * An eclectic collection of Minesweeper helper functions / classes / structs / etc.
 * All so you can create a nice class hierarchy to implement your game.
 */

#include "DirectoryListing.h"
#include "GameClock.h"
#include "Group.h"
#include "TextureManager.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define WIDTH 800
#define HEIGHT 800
#define CELLWIDTH 50.0
#define CELLHEIGHT 50.0
#define HEADER 60

struct GameBoard {
    Tile** MineWorld;
    int rows;
    int cols;
    sf::Texture squareTexture;
    sf::Texture flagTexture;

    GameBoard(int r, int c)
    {
        rows = r;
        cols = c;
        MineWorld = new Tile*[rows];

        for (int i = 0; i < rows; i++) {
            MineWorld[i] = new Tile[cols];
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                //MineWorld[i][j].setTexture(squareTexture);
                MineWorld[i][j].scaleImage(240, 240, CELLWIDTH, CELLHEIGHT);
                MineWorld[i][j].setPosition(sf::Vector2f((i * CELLWIDTH), (j * CELLHEIGHT) + HEADER));
            }
        }

        if (!squareTexture.loadFromFile("images/square.png")) {
            std::cout << "Could not load square" << std::endl;
        }

        if (!flagTexture.loadFromFile("images/flag.png")) {
            std::cout << "Could not load flag" << std::endl;
        }
    }

    void drawWorld(sf::RenderWindow& window)
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                window.draw(MineWorld[i][j]);
            }
        }
    }

    void setTexture(int x, int y)
    {
        if (x >= 0 && y >= 0) {
            sf::Vector2i p = getMineCell(x, y);
            MineWorld[p.x][p.y].setTexture(flagTexture);
        }
    }

    /**
     * function getMineCell: turns a mouse click (x,y) into a cell position (row,col)
     * @Params:
     *    x {int} : Row of mouse click (or similar)
     *    y {int} : Col of mouse click (or similar)
     * @Returns:
     *    p {CellPosition} : a struct holding an integer pair reprenting a row/col
     */
    sf::Vector2i getMineCell(int x, int y)
    {
        sf::Vector2i p;
        p.x = x / CELLWIDTH;
        p.y = (y - HEADER) / CELLHEIGHT;

        return p;
    }
};

int main(int argc, char** argv)
{

    TextureManager tex;
    vector<string> files;

    files = tex.scanDir("./playing_cards/");
    tex.stdPrintDir();
    tex.LoadTextures();

    sf::Texture t;
    t = tex.getTextureByName("3_of_hearts");
    std::cout << t.getSize().x << std::endl;

    bool mouseWasPressed = false;
    bool gameStart = false;
    float clickTime = 0.0;

    int rows = int(HEIGHT / CELLHEIGHT);
    int cols = int(WIDTH / CELLWIDTH);

    GameBoard gBoard(rows, cols);

    // GameClock gClock(WIDTH,HEIGHT,0);
    GameClock gClock(WIDTH, HEIGHT, 15, "Segment7Standard.otf", sf::Color(255, 0, 0), sf::Color(0, 0, 0), 48, "N", 30);

    gClock.startClock();

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT + HEADER), "My window");

    sf::Vector2i localPosition;

    window.setKeyRepeatEnabled(false);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color(192, 192, 192));

        // draw everything here...
        
        gBoard.drawWorld(window);
        window.draw(gClock);
        gClock.updateClock();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // left mouse button is pressed
            localPosition = sf::Mouse::getPosition(window);
            gameStart = true;
            if (!mouseWasPressed) {
                gBoard.setTexture(localPosition.x, localPosition.y);
            }
            mouseWasPressed = true;
            clickTime = gClock.getFloatRunningTime();
        }

        std::cout<<gClock.getFloatRunningTime()<<std::endl;
    
        if(gClock.getFloatRunningTime() - clickTime > .5){
            mouseWasPressed = false;
        }
        window.display();
    }

    return 1;
}