#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

/**
 * Class Tile: Used to represent one cell in our MineSweeper Game.
 * Extends: sf::Sprite
 * 
 * Data Members:
 *    All the stuff from Sprite +
 * 
 *    origWidth     {int}         : width in pixels of original image
 *    origHeight    {int}         : height in pixels of original image
 *    xScale        {float}       : value to scale image. starts at 1.
 *    yScale        {float}       : value to scale image. starts at 1.
 *    tileTexture   {sf::Texture}  : Texture for the tile
 * 
 * Methods:
 *     Tile();  
 *     Tile(int , int , string );
 *     void scaleImage(int , int , int , int );
 *     void setOriginalSize(int , int );
 *     void setSize(int , int );
 *     void setTexture(string);
 */
class Tile : public sf::Sprite {
private:
    int origWidth;
    int origHeight;
    int scaledWidth;
    int scaledHeight;
    float xScale;
    float yScale;
    sf::Texture tileTexture;
public:
    Tile();
    Tile(int , int , string );
    void scaleImage(int , int , int , int );
    void resetTile(int , int ,string);
    void setSize(int , int );
    void setTileTexture(string);
    bool intersectsWith(int,int);
};



/**
 * Constructor
 * Purpose:
 *      Sets tile to have square image and sets size of image to 0,0.
 * Params:
 *      None
 */
Tile::Tile()
{
    origWidth = 0;
    origHeight = 0;
    scaledWidth = 0;
    scaledHeight = 0;
    xScale = 1.0;
    yScale = 1.0;
    if (!tileTexture.loadFromFile("images/square.png")) {
        //std::cout << "Could not load images/square.png ... " << std::endl;
    }else{
        this->setTexture(tileTexture);
    }
}

/**
 * Constructor
 * Purpose:
 *      Initialize our tile sprite with a width, height and a texture (image file)
 * Params:
 *      width {int}          : original image width
 *      height {int}         : original image height
 *      texture_name {string}: path/to/image for texture
 */
Tile::Tile(int width, int height, string texture_name)
{
    origWidth = width;
    origHeight = height;
    scaledWidth = width;
    scaledHeight = height;
    xScale = 1.0;
    yScale = 1.0;
    if (!tileTexture.loadFromFile(texture_name)) {
        std::cout << "Could not load " + texture_name + " ... " << std::endl;
    }
    this->setTexture(tileTexture);
}

/**
 * Method: scaleImage
 * Purpose:
 *      Takes the images original width and height along with a new width and height
 *      and uses that data to calculate a scale value (< 1 = shrink image, > 1 grow image)
 * Params: 
 *      origwidth {int}  : original image width
 *      origheight {int} : original image height
 *      newWidth {int}   : target image height
 *      newHeight {int}  : target image height
 */
void Tile::scaleImage(int origWidth, int origHeight, int newWidth, int newHeight)
{
    xScale = float(newWidth) / float(origWidth);
    yScale = float(newHeight) / float(origHeight);

    scaledWidth = newWidth;
    scaledHeight = newHeight;

    //this = the sprite we inherited from
    //so we are scaling the sprite
    this->setScale(xScale, yScale);
}

/**
 * Method: resetTile
 * Purpose:
 *      Sets the orignal width and height of the image and the image texture. 
 *      We can use this method if we called the default constructor that doesn't 
 *      init anything!
 * Params: 
 *      width           {int}      : set width of sprite
 *      height          {int}      : set height of sprite
 *      texture_path    {string}   : path to image file 
 */
void Tile::resetTile(int width, int height, string texture_name)
{
    origWidth = width;
    origHeight = height;
    scaledWidth = width;
    scaledHeight = height;
    xScale = 1.0;
    yScale = 1.0;
    if (!tileTexture.loadFromFile(texture_name)) {
        std::cout << "Could not load " + texture_name + " ... " << std::endl;
    }
    this->setTexture(tileTexture);
}

/**
 * Method: setSize
 * Purpose:
 *      Changes the sprite size by calculating a new scale factor and applying it.
 *      With a sprite you can't just set a new size, it can only be scaled. So if we
 *      pass in a new width/height we must use the new size values to calculate scaling
 *      factors.
 * Params: 
 *      new_width {int}  : new width of sprite
 *      new_height {int}  : new height of sprite
 */
void Tile::setSize(int new_width, int new_height)
{
    if (origWidth == 0 || origHeight == 0) {
        std::cout << "Error: Cannot set new image size without original image size...." << std::endl;
        return;
    }
    float xScale = float(new_width) / float(origWidth);
    float yScale = float(new_height) / float(origHeight);

    scaledWidth = new_width;
    scaledHeight = new_height;
    this->setScale(xScale, yScale);
}

/**
 * Method: setTexture
 * Purpose:
 *      Changes the texture used by our tile sprite
 * Params: 
 *      texture_path {string}  : path / filename of texture image
 */
void Tile::setTileTexture(string texture_path){
    if (!tileTexture.loadFromFile(texture_path)) {
        std::cout << "Could not load " + texture_path + " ... " << std::endl;
    }
    this->setTexture(tileTexture);
}

bool Tile::intersectsWith(int x, int y){
    // get the bounding box of the entity
    sf::FloatRect boundingBox = this->getGlobalBounds();

    std::cout<<boundingBox.left<<":"<<boundingBox.top<<" "<<x<<","<<y<<std::endl;



    if (boundingBox.contains(x,y))
    {
        return true;
    }
    return false;
}
