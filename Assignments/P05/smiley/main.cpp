#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Smiley!");

    Tile smiley(128,128,"./smiley.png");
    
    smiley.setPosition(sf::Vector2f(100.0, 100.0));
    smiley.setSize(64,64);
    smiley.setOrigin(64.0,64.0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            smiley.setTileTexture("./surprised.png");
        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            smiley.setTileTexture("./smiley.png");
        }

        window.clear();
        window.draw(smiley);
        window.display();
    }

    return 0;
}