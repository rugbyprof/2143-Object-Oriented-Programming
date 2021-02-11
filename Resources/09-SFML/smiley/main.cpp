#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "Group.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png


class DrawMe : public Group{
private:
    Tile smiley;
    sf::RectangleShape rectangle;
    float angle;
    float x;
    float y;
    int dx;
    int dy;
public:
    DrawMe(){
        x = 100;
        y = 100;
        dx = 1;
        dy = 1;
        smiley.resetTile(128,128,"./smiley.png");
        smiley.setPosition(sf::Vector2f(x,y));
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

    void changeSmiley(string image){
        smiley.setTileTexture(image);
    }

    void update(){
        //rectangle.rotate(angle);
        x = x + (.2 * dx);
        y = y + (.25 * dy);
        if(x >= 600 || x <= 0){
            dx = dx * -1;
        }
        if(y >= 600 || y <= 0){
            dy = dy * -1;
        }
        smiley.setPosition(sf::Vector2f(x, y));

        angle += .0001;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Smiley!");//, sf::Style::Fullscreen


    DrawMe D;

    
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
        }else{
            D.changeSmiley("./smiley.png");
        }

        // if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //     D.changeSmiley("./smiley.png");
        // }

        window.clear();
        window.draw(D);
        D.update();

        window.display();
    }

    return 0;
}