#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Tile.h"
#include "Group.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png

class DrawMe : public Group{
private:
    Tile smiley;
    sf::RectangleShape rectangle;
    float angle;
    int justFlippedX;
    float xDirection;
    float yDirection;
public:
    DrawMe(){
        xDirection = 1.0;
        yDirection = 1.0;

        smiley.resetTile(128,128,"./smiley.png");
        smiley.setPosition(sf::Vector2f(100.0, 100.0));
        smiley.setSize(64,64);
        smiley.setOrigin(64.0,64.0);

        rectangle.setSize(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setOrigin(50,50);
        rectangle.setPosition(100, 100);

        angle = .01;
        
        this->push_back(rectangle);
        this->push_back(smiley);    

    }

    void moveSmiley(float dx,float dy){
        sf::Vector2f pos = smiley.getPosition();

        cout<<pos.x<<","<<pos.y<<endl;
            
        if(pos.x > 300){
            xDirection = -1.0;
        }
        if(pos.y > 400){
            yDirection = -1.0;
        }
    
        if(pos.x < 0){
            xDirection = 1.0;
        }
        if(pos.y < 0){
            yDirection = 1.0;
        }
            
        cout<<(float)dx*(float)xDirection<<","<<(float)dy*(float)yDirection<<endl;

        smiley.move(dx * xDirection , dy * yDirection);
    }

    void changeSmiley(string image){
        smiley.setTileTexture(image);
    }

    void update(){
        rectangle.rotate(angle);

        angle += .0001;
    }
};

class GameClock : public Group{
private:
    sf::Text text;          // var to hold clock digits
    sf::Clock gameClock;    // SFML clock type
    sf::Time startTime;
    sf::Font font;
    sf::Color textColor;
    sf::RectangleShape rectangle;
    int fontSize;
public:
    GameClock(){
        gameClock.restart();
        if (!font.loadFromFile("Segment7Standard.otf")) {
            cout << "Error loading font 'Segment7Standard.otf'...";
            exit(0);
        }

        fontSize = 48;

        textColor = sf::Color(0, 255, 0); // green

        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("0");

        text.setCharacterSize(fontSize); // in pixels, not points!

        text.setFillColor(textColor);

        text.setStyle(sf::Text::Bold);

        rectangle.setSize(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setOrigin(50,50);
        rectangle.setPosition(100, 100);
        this->push_back(text);
        this->push_back(rectangle);

    }

    void printClock(int gameWidth, int gameHeight){

        int itime = gameClock.getElapsedTime().asSeconds();

        
        string stime = to_string(itime);

        text.setString(stime);

        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;

        sf::Vector2f coord(gameWidth / 2,gameHeight / 2);
        sf::Vector2f origin(textWidth / 2.0f, textHeight / 2.0f);

        text.setOrigin(origin);
        text.setPosition(coord);

    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(300, 400), "SFML Smiley!");

    DrawMe D;
    GameClock G;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            D.changeSmiley("./surprised.png");
        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            D.changeSmiley("./smiley.png");
        }


        D.moveSmiley(.55,.55);
        
        window.clear();
        
        G.printClock(300,400);
        window.draw(G);
        D.update();
        window.draw(D);
        window.display();


    }

    return 0;
}