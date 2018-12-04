#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <limits>
#include "TimeFormat.h"
#include "GameClock.h"
#include "Tile.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png



class Smiley : public Group{
private:
    Tile smiley;
    Tile tile;
    float angle;
    float dx;
    float dy;
public:
    Smiley(){
        //Tile methods
        smiley.initTile(128,128,"./assets/smiley.png");
        smiley.setSize(80,80);
        smiley.setOrigin(40.0,40.0);
        smiley.setPosition(sf::Vector2f(115.0, 115.0));

        tile.initTile(240,240,"./assets/0.png");
        tile.setSize(120,120);
        tile.setOrigin(60.0,60.0);
        tile.setPosition(sf::Vector2f(100.0, 100.0));

        angle = .01;
        
        this->push_back(tile);
        this->push_back(smiley);

        dx = .5;
        dy = .5;

    }

    void changeSmiley(string image){
        smiley.setTileTexture(image);
    }

    void update(int width,int height){

        int buffer = 25;

        sf::Vector2f pos = smiley.getPosition();

        tile.rotate(angle);

        if(pos.x > (width-buffer) || pos.x < (0 + buffer)){
            dx = dx * -1;
        }

        if(pos.y > (height-buffer) || pos.y < (0 + buffer)){
            dy = dy * -1;
        }

        smiley.move(dx,dy);
        tile.move(dx,dy);

        angle += .0001;
    }
};



int main()
{
    int wWidth=sf::VideoMode::getDesktopMode().width / 4;
    int wHeight=sf::VideoMode::getDesktopMode().height / 4;

    sf::RenderWindow window(sf::VideoMode(wWidth,wHeight), "Game Clock Example");

    GameClock G(wWidth,wHeight);
    Smiley S;

    G.setBackgroundColor(sf::Color(0,0,0));
    G.setBorder(sf::Color(0,255,0),3);
    G.setClockPosition("E");


    string locations[] = {"E","NE","SE","N","W","S","SW","NW"};

    int i = 0;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            G.setClockPosition(locations[rand()%8]);
        }

        
        G.updateClock();
        //S.update(wWidth,wHeight);
        window.clear();
        window.draw(G);
        window.draw(S);

        i++;

        if(i % 5000 == 0){
            G.setClockPosition(locations[rand()%8]);
        }
        
        window.display();
    }


    return 0;
}