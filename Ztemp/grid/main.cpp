#include <SFML/Graphics.hpp>

#define WINDOWSIZE 800
#define CELLSIZE 20

using namespace sf;

/**
 * Class Line : Extends Drawable
 */
class Line : public Drawable
{
  private:
    /**
     * void draw:
     *     overloaded sf draw method lets us draw a "line" which in the mind of sfml
     *     is really an array of two points.
     */
    virtual void draw(RenderTarget &target, RenderStates states) const
    {
        Vertex line[2];
        line[0] = Vertex(P1, lineColor);
        line[1] = Vertex(P2, lineColor);
        target.draw(line, 2, Lines, states);
    }

  public:
    Vector2f P1, P2; // 2 floating point vector types
    Color lineColor; // sfml color type

    /**
     * Default Constructor
     *  Sets both points to 0,0 with a color black
     */
    Line()
    {
        P1 = Vector2f(0, 0);
        P2 = Vector2f(0, 0);
        lineColor = Color::Black;
    }

    /**
     * Overloaded Constructor
     * @Params:
     *      Vector2f p1 : start of the line
     *      Vector2f p2 : end of the line
     *      Color c : sfml color
     */
    Line(Vector2f p1, Vector2f p2, Color c)
    {
        setLine(p1, p2, c);
    }

    /**
     * Method to setup the line (same as overloaded constructor)
     * @Params:
     *      Vector2f p1 : start of the line
     *      Vector2f p2 : end of the line
     *      Color c : sfml color
     */
    void setLine(Vector2f p1, Vector2f p2, Color c)
    {
        P1 = p1;
        P2 = p2;
        lineColor = c;
    }

    /**
     * Additional methods could be:
     * setColor
     * getColor
     * setP1
     * setP2
     * setP (sets two new points)
     * getP1
     * getP2
     */
};

/**
 * Class Grid : Extends Line
 * This class simply draws a bunch of lines so it looks like a grid.
 */
class Grid
{
  private:
    int WindowSize;       // Main window size in pixels (e.g. 500)
    int CellSize;         // Size of a cell in pixels (e.g. 10)
    int NumCells;         // Number of cells (e.g. 500 / 10 or 50)
    Line *vLines;         // Line pointer for our array of vertical lines
    Line *hLines;         // Line pointer for our array of horizontal lines
    RenderWindow &Window; // Window reference so we can draw to the sfml window
    Texture texture;
    Sprite *sprite;
  public:
    /**
     * Constructor:
     * @params:
     *    int window_size : size in pixels of main window (I expect a square window I guess)
     *    int cell_sized : size in pixels of a cell
     *    RenderWindow &window : reference to main sfml window
     */
    Grid(int window_size, int cell_size, RenderWindow &window) : Window(window)
    {
        WindowSize = window_size;
        CellSize = cell_size;

        NumCells = WindowSize / CellSize; // calculate how many cells we need for our arrays

        vLines = new Line[NumCells]; // allocate array to hold lines
        for (int i = 0; i < NumCells; i++)
        {
            //set up our lines p1,p2 and color
            vLines[i].setLine(Vector2f(i * CELLSIZE, 0), Vector2f(i * CELLSIZE, WINDOWSIZE), Color::Green);
        }

        // Same as above but horizontal
        hLines = new Line[NumCells];
        for (int i = 0; i < NumCells; i++)
        {
            hLines[i].setLine(Vector2f(0, i * CELLSIZE), Vector2f(WINDOWSIZE, i * CELLSIZE), Color::Green);
        }
    }

    /**
     * drawGrid: ummm draws the grid :) 
     */
    void drawGrid()
    {
        for (int i = 0; i < NumCells; i++)
        {
            //Draw directly to our window reference
            Window.draw(vLines[i]);
        }

        for (int i = 0; i < NumCells; i++)
        {
            //Draw directly to our window reference
            Window.draw(hLines[i]);
        }
    }

    void drawBackground(){
        
        if (!texture.loadFromFile("grid.png"))
        {
            // error...
        }

        sprite = new Sprite[CellSize*CellSize];
        
        for(int i=0;i<CellSize*CellSize;i++){
            sprite[i].setTexture(texture);
            sprite[i].setScale(sf::Vector2f(0.2f, 0.2f)); // absolute scale factor
            sprite[i].setColor(sf::Color(0, 255, 0));
            Window.draw(sprite[i]);
        }


        

    }
};

int main()
{
    // create the window
    RenderWindow window(VideoMode(WINDOWSIZE, WINDOWSIZE), "My window");

    // Create an instance of a Grid class
    Grid G(WINDOWSIZE, CELLSIZE, window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);

        G.drawGrid();
        //G.drawBackground();
        

        // end the current frame
        window.display();
    }

    return 0;
}