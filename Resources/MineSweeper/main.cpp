/**
 * An eclectic collection of Minesweeper helper functions / classes / structs / etc.
 * All so you can create a nice class hierarchy to implement your game.
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <functional>

using namespace std;

#define WIDTH 800
#define HEIGHT 800
#define CELLWIDTH 50.0
#define CELLHEIGHT 50.0
#define HEADER 60

/**
 * struct MineSquare: Used to represent one cell in our Minecraft Game.
 * Data Members:
 *    sprite {sf::Sprite} : this represents the image we want our cell to display
 *    bombNeighbors {int} : this would be how many bombs neighbor the cell
 *    covered {bool}      : True = cell is covered, False = cell has been uncovered
 */ 
struct MineSquare
{
    sf::Sprite sprite;
    int bombNeighbors;
    bool covered;
};

/**
 * struct CellPosition: Used to return a coord pair (row,col)
 * Data Members:
 *    r {int} : Row of mouse click (or similar)
 *    c {int} : Col of mouse click (or similar)
 */ 
struct CellPosition
{
    int r;
    int c;
};

/**
 * function getMineCell: turns a mouse click (x,y) into a cell position (row,col)
 * @Params:
 *    x {int} : Row of mouse click (or similar)
 *    y {int} : Col of mouse click (or similar)
 * @Returns:
 *    p {CellPosition} : a struct holding an integer pair reprenting a row/col
 */ 
CellPosition getMineCell(int x, int y)
{
    CellPosition p;
    p.c = x / CELLWIDTH;
    p.r = (y - HEADER) / CELLHEIGHT;

    return p;
}

/**
 * class Group: inherits from sf::Drawable
 * https://github.com/SFML/SFML/wiki/Tutorial:-Drawable-Group
 * Purpose:
 *      This class inherits from sf::Drawable so it can print multiple sprites with a 
 *      single call to window.draw. It makes it possible by using a vector to hold 
 *      multiple sprites, then overloads the draw method and applies it to all items
 *      within the vector.
 * @Methods:
 * public:
 *    Group() : m_drawables {}  // initialization list to create the data type at the bottom of the class
 *    virtual ~Group() = default; // = default is a c++11 way of saying use the compiler-generated version of that function
 *    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const    // const means we are not changing anything
 *          sf::RenderTarget is the base class for all drawables
 *          sf::RenderStates is define the state for the target being drawn (blend, transform, texture, shader)
 *    const sf::Drawable &operator[](std::size_t index) // overload the square brackets to access our vector and get a drawable
 *    std::size_t push_back(const sf::Drawable &drawable) // overload the push_back method to place a drawable on our vector
 *    const sf::Drawable &pop_back() // overload pop_back to remove a drawable from the vector
 * private:
 *    std::vector<std::reference_wrapper<const sf::Drawable>> m_drawables;  // a vector of Drawables 
 */ 
class Group : public sf::Drawable
{
  public:
    /**
     * Constructor
     *     https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
     * @Params: none
     */
    Group()
        : m_drawables{}
    {
    }

    /**
     * Destructor
     *     https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration
     * @Params: none
     */
    virtual ~Group() = default;

    /**
     * virtual = A virtual function a member function which is declared within base class and is re-defined (Overriden) by derived class.
     * function draw:
     *     draw an SFML object to some window
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (const auto &drawable : m_drawables)
        {
            target.draw(drawable, states);
        }
    }

    /**
     * overloaded operator "[]"
     * @Params:
     *    index {std::size_t} : index of a drawable
     * @Returns:
     *     a drawable from prescribed index
     */
    const sf::Drawable &operator[](std::size_t index)
    {
        return m_drawables[index];
    }

    /**
     * push_back
     * @Params:
     *    drawable {const sf::Drawable} : what we are pushing
     * @Returns:
     *     The new size of the vector
     */
    std::size_t push_back(const sf::Drawable &drawable)
    {
        m_drawables.push_back(drawable);
        return m_drawables.size() - 1;
    }

    /**
     * pop_back
     * @Params:
     *    drawable {const sf::Drawable} : what we are pushing
     * @Returns:
     *     drawable {const sf::Drawable}
     */
    const sf::Drawable &pop_back()
    {
        const auto &drawable = m_drawables.back();
        m_drawables.pop_back();
        return drawable;
    }

  private:
    /**
     * templated vector type
     * This defines a:
     *     - vector that holds drawables
     *     - The std::reference_wrapper is "type" that holds references since vectors cant really handle reference types.
     */
    std::vector<std::reference_wrapper<const sf::Drawable>> m_drawables;
};



/**
 * Class GameClock:
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
class GameClock : public Group
{
  private:
    sf::Font font;                     // clocks font
    int fontSize;                      // size of font in pixels
    string position;                   // N,NE,E,SE,S,SW,W,NW, C [N = top center, NE = top right, E = far right vertically centered, ..., C = centered ]
    sf::Text text;                     // var to hold clock digits
    sf::Clock gameClock;                // SFML clock type
    sf::Time startTime;
    sf::Time elapsedTime;              // SFML time type 
    sf::Color textColor;               // Color of clock text
    sf::Color backgroundColor;         // Color behind clock
    sf::Vector2f clockCoord;           // Locations to print clock
    sf::RectangleShape clockRectangle; // Rectangle representing clock back.
    int clockBuffer;                   // Padding around clock digits (size of rectangle)
    int gameBuffer;                    // Padding around game border (if any);
    int gameWidth;                     // Actual width of game window
    int gameHeight;                    // Actual height of game window

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

        if (!font.loadFromFile("arial.ttf"))
        {
            cout << "Error loading font 'arial.ttf'...";
            exit(0);
        }

        textColor = sf::Color(0, 255, 0);     // green
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

        if (!font.loadFromFile(font_name))
        {
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
        if (p == "")
        {
            p = position;
        }

        // Top Center
        if (p == "N")
        {

            coord.x = gameWidth / 2;
            coord.y = 0;
        }
        // Top Right
        else if (p == "NE")
        {

            coord.x = gameWidth;
            coord.y = 0;
        }
        // Right Middle
        else if (p == "E")
        {

            coord.x = gameWidth;
            coord.y = gameHeight / 2;
        }
        // Bottom Right
        else if (p == "SE")
        {

            coord.x = gameWidth;
            coord.y = gameHeight;
        }
        // Bottom Center
        else if (p == "S")
        {

            coord.x = gameWidth / 2;
            coord.y = gameHeight;
        }
        // Bottom Left
        else if (p == "SW")
        {

            coord.x = 0;
            coord.y = gameHeight;
        }
        // Left Middle
        else if (p == "W")
        {

            coord.x = 0;
            coord.y = gameHeight / 2;
        }
        // Top Left
        else if (p == "NW")
        {

            coord.x = 0;
            coord.y = 0;
        }
        // Center Middle
        else
        {

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


    void startClock(){
        gameClock.restart();
            // sf::Time elapsed = clock.restart();
            // updateGame(elapsed);
    }

    sf::Time getEllapsedTime(){
         return gameClock.getElapsedTime();
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

int main(int argc, char **argv)
{

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span;

    int clock = 0;

    bool gameStart = false;

    int originalImageWidth = 240;
    int originalImageHeight = 240;

    int rows = int(HEIGHT / CELLHEIGHT);
    int cols = int(WIDTH / CELLWIDTH);

    float xScaleFactor = 0.0;
    float yScaleFactor = 0.0;

    if (CELLHEIGHT < originalImageHeight)
    {
        yScaleFactor = CELLHEIGHT / originalImageHeight;
    }
    else
    {
        yScaleFactor = originalImageHeight / CELLHEIGHT;
    }

    if (CELLWIDTH < originalImageWidth)
    {
        xScaleFactor = CELLWIDTH / originalImageWidth;
    }
    else
    {
        xScaleFactor = originalImageWidth / CELLWIDTH;
    }

    std::cout << rows << "," << cols << std::endl;
    std::cout << yScaleFactor << "," << xScaleFactor << std::endl;

    // GameClock gClock(WIDTH,HEIGHT,0);
    GameClock gClock(WIDTH, HEIGHT, 15, "Segment7Standard.otf", sf::Color(255, 0, 0), sf::Color(0, 0, 0), 48, "N", 30);

    sf::Texture squareTexture;
    if (!squareTexture.loadFromFile("minesweeper/square.png"))
    {
        std::cout << "Could not load square" << std::endl;
    }

    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile("minesweeper/flag.png"))
    {
        std::cout << "Could not load flag" << std::endl;
    }

    MineSquare **MineWorld;

    MineWorld = new MineSquare *[rows];

    for (int i = 0; i < rows; i++)
    {
        MineWorld[i] = new MineSquare[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            MineWorld[i][j].sprite.setTexture(squareTexture);
            MineWorld[i][j].sprite.setScale(xScaleFactor, yScaleFactor);
            MineWorld[i][j].sprite.setPosition(sf::Vector2f((i * CELLWIDTH), (j * CELLHEIGHT) + HEADER));
        }
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT + HEADER), "My window");

    //sf::Sprite sprite;
    //sprite.setTexture(squareTexture);
    //sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    //sprite.setPosition(sf::Vector2f(10, 50));

    sf::Vector2i localPosition;

    bool mouseWasPressed = false;

    window.setKeyRepeatEnabled(false);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color(192, 192, 192));

        // draw everything here...
        // window.draw(...);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // left mouse button is pressed: shoot
            localPosition = sf::Mouse::getPosition(window);
            gameStart = true;
            if (!mouseWasPressed)
            {
                t1 = std::chrono::high_resolution_clock::now();
                std::cout << localPosition.x << "," << localPosition.y << std::endl;
                if(localPosition.x >=0 && localPosition.y >=0){
                    CellPosition p = getMineCell(localPosition.x, localPosition.y);
                    std::cout << p.c << "," << p.r << std::endl;
                    MineWorld[p.c][p.r].sprite.setTexture(flagTexture);
                }
                mouseWasPressed = true;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                window.draw(MineWorld[i][j].sprite);
            }
        }

        std::cout<<"clock: "<<gClock.getEllapsedTime().asMilliseconds()<<std::endl;

        //text.setString(std::to_string(clock));
        window.draw(gClock);

        t2 = std::chrono::high_resolution_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        if (time_span.count() > 0.5)
        {
            mouseWasPressed = false;
        }

        if (gameStart)
        {
            clock = time_span.count();
        }

        // end the current frame
        window.display();
    }

    return 1;
}