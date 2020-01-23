#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Group.h"

using namespace std;

/**
 * Class: GameClock:
 * Extends: Group
 * Public:
 *    // Default constructor needs window width/height. 
 *    GameClock(int game_width, int game_height, int game_buffer = 0);
 * 
 *    // Overloaded constructor needs a lot!
 *    GameClock(int game_width, int game_height, int game_buffer, string font_name, 
 *              sf::Color clock_color, sf::Color clock_rect_color, int font_size, string pos, int clock_buffer);
 * 
 *    // Tells class where to print clock, expects a cardinal direction.
 *    void setClockPosition(string p = ""); 
 * 
 *    // Tells class where to print clock, expects a coordinate
 *    void setClockPosition(sf::Vector2f coord); 
 * Private:
 *    // Initializes a lot of things. Each constructor calls init for the common lines of code to run.
 *    void _init(); 
 * 
 *    // Public setClockPositionsd turn around and call this one. The string version calculates a coord based
 *    // cardinal directions, then calls this one. 
 *    void _setClockPosition(sf::Vector2f coord);
 */
class GameClock : public Group {
private:
    sf::Font font; // clocks font
    int fontSize; // size of font in pixels
    string position; // N,NE,E,SE,S,SW,W,NW, C [N = top center, NE = top right, E = far right vertically centered, ..., C = centered ]
    sf::Text text; // var to hold clock digits
    sf::Clock gameClock; // SFML clock type
    sf::Time startTime;
    sf::Time elapsedTime; // SFML time type
    sf::Color textColor; // Color of clock text
    sf::Color backgroundColor; // Color behind clock
    sf::Vector2f clockCoord; // Locations to print clock
    sf::RectangleShape clockRectangle; // Rectangle representing clock back.
    int clockBuffer; // Padding around clock digits (size of rectangle)
    int gameBuffer; // Padding around game border (if any);
    int gameWidth; // Actual width of game window
    int gameHeight; // Actual height of game window

public:
    /**
   * Public: GameClock constructor - 
   * @Params:
   *    game_width {int}: width of actual game
   *    game_height {int}: height of actual game
   *    game_buffer {int}: buffer around outside of game to keep away from edge of window
   * @Returns:
   *    void
   */
    GameClock(int game_width, int game_height, int game_buffer = 0)
    {
        gameWidth = game_width;
        gameHeight = game_height;
        gameBuffer = game_buffer;

        if (!font.loadFromFile("arial.ttf")) {
            cout << "Error loading font 'arial.ttf'...";
            exit(0);
        }

        textColor = sf::Color(0, 255, 0); // green
        backgroundColor = sf::Color(0, 0, 0); // black
        clockRectangle.setFillColor(sf::Color(0, 0, 0));
        fontSize = 24;
        position = "C";
        clockBuffer = 10;
        _init();

        // Push shapes onto our "Group" vector so we can print them together.
    }

    /**
     * Public: GameClock constructor - 
     * @Params:
     *    game_width         {int}: width of actual game
     *    game_height        {int}: height of actual game
     *    game_buffer        {int}: buffer around outside of game to keep away from edge of window
     *    font_name          {string}: name of font (or path and name)
     *    clock_color        {sf::Color}: color of clock digits
     *    clock_rect_color   {sf::Color}: color of clock background
     *    font_size          {int}: size of clock font
     *    pos                {string}: location of clock (N,NE,S,....,etc.)
     *    clock_buffer       {int} : padding between digits and background rectangle edges
     * @Returns:
     *    void
     */
    GameClock(int game_width, int game_height, int game_buffer, string font_name, sf::Color clock_color, sf::Color clock_rect_color, int font_size, string pos, int clock_buffer)
    {

        gameWidth = game_width;
        gameHeight = game_height;
        gameBuffer = game_buffer;

        if (!font.loadFromFile(font_name)) {
            cout << "Error loading font 'arial.ttf'...";
            exit(0);
        }

        textColor = clock_color;
        backgroundColor = clock_rect_color;
        clockRectangle.setFillColor(backgroundColor);
        fontSize = font_size;
        position = pos;
        clockBuffer = clock_buffer;
        _init();
    }

    /**
     * Public: setClockPosition
     *    An easy way to position your game clock. 
     * @Params: 
     *   p {string} : position where N,NE,E,SE,S,SW,W,NW, C [N = top center, NE = top right, E = far right vertically centered, ..., C = centered ]
     * @returns:
     *   void
     */
    void setClockPosition(string p = "")
    {
        sf::Vector2f coord; // var to hold calculated position

        // if p is empty, set p = to default value from class data member
        if (p == "") {
            p = position;
        }

        // Top Center
        if (p == "N") {

            coord.x = gameWidth / 2;
            coord.y = 0;
        }
        // Top Right
        else if (p == "NE") {

            coord.x = gameWidth;
            coord.y = 0;
        }
        // Right Middle
        else if (p == "E") {

            coord.x = gameWidth;
            coord.y = gameHeight / 2;
        }
        // Bottom Right
        else if (p == "SE") {

            coord.x = gameWidth;
            coord.y = gameHeight;
        }
        // Bottom Center
        else if (p == "S") {

            coord.x = gameWidth / 2;
            coord.y = gameHeight;
        }
        // Bottom Left
        else if (p == "SW") {

            coord.x = 0;
            coord.y = gameHeight;
        }
        // Left Middle
        else if (p == "W") {

            coord.x = 0;
            coord.y = gameHeight / 2;
        }
        // Top Left
        else if (p == "NW") {

            coord.x = 0;
            coord.y = 0;
        }
        // Center Middle
        else {

            coord.x = gameWidth / 2;
            coord.y = gameHeight / 2;
        }

        _setClockPosition(coord);
    }

    /**
     * Public: setClockPosition:
     * @Params:
     *   coord {sf::Vector2f} : x,y position
     * @returns:
     *   void
     */
    void setClockPosition(sf::Vector2f coord)
    {
        _setClockPosition(coord);
    }

    void startClock()
    {
        gameClock.restart();
        // sf::Time elapsed = clock.restart();
        // updateGame(elapsed);
    }

    int getIntRunningTime()
    {
        return gameClock.getElapsedTime().asSeconds();
        
    }

    float getFloatRunningTime()
    {
        return gameClock.getElapsedTime().asSeconds();
        
    }

    void updateClock(){
        int time = gameClock.getElapsedTime().asSeconds();
        string ptime = "";
        if(time < 10){
            ptime = "0" + to_string(time);
        }else{
            ptime = to_string(time);
        }
        text.setString(ptime);
    }

private:
    /**
     * Private: init
     *    Called from the constructors to reduce repeat code.
     * @Params: 
     *   p {string} : position where N,NE,E,SE,S,SW,W,NW, C [N = top center, NE = top right, E = far right vertically centered, ..., C = centered ]
     * @returns:
     *   void
     */
    void _init()
    {
        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("0");

        // set the character size
        text.setCharacterSize(fontSize); // in pixels, not points!

        // set the color
        text.setFillColor(textColor);

        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        text.setStyle(sf::Text::Bold);
        //text.setPosition(sf::Vector2f(WIDTH / 2.0f, HEIGHT / 2.0f));

        setClockPosition();

        elapsedTime = sf::Time::Zero;

        push_back(clockRectangle);
        push_back(text);
    }

    /**
     * Private: _setClockPosition
     *    After x,y is found for clock position, this method will make adjustments based on the "game buffer" and "clock buffer"
     * @Params:
     *    coord {sf::Vector2f} : x,y position
     * @returns:
     *    void
     */
    void _setClockPosition(sf::Vector2f coord)
    {
        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;

        coord.x += gameBuffer;
        coord.y += gameBuffer;

        sf::Vector2f origin(textWidth / 2.0f, textHeight / 2.0f);

        text.setOrigin(origin);
        text.setPosition(coord);

        // sf::FloatRect textRect = text.getLocalBounds();

        clockRectangle.setSize(sf::Vector2f(textWidth + clockBuffer, textHeight + clockBuffer));
        clockRectangle.setOrigin(origin);
        clockRectangle.setPosition(coord);
    }
};
