#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter : public sf::Drawable{
private:
    sf::Clock clock; 
    sf::Time elapsed;
    sf::Text text;
    sf::Color textColor;
    sf::Font font; // clocks font
    int gameWidth;
    int gameHeight;


    void _setClockPosition(sf::Vector2f coord)
    {
        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;

        sf::Vector2f origin(textWidth / 2.0f, textHeight / 2.0f);

        text.setOrigin(origin);
        text.setPosition(coord);

    }
public:
    Counter(int game_width,int game_height){
        clock.restart();
        if (!font.loadFromFile("Segment7Standard.otf")) {
            cout << "Error loading font 'font'...";
            exit(0);
        }

        textColor = sf::Color(0, 255, 0); // green
        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("0");

        // set the character size
        text.setCharacterSize(48); // in pixels, not points!

        // set the color
        text.setFillColor(textColor);

        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        text.setStyle(sf::Text::Bold);
        _setClockPosition(sf::Vector2f(game_width/2,game_height/2));
    }

    void updateCounter(){
        int time = clock.getElapsedTime().asSeconds();
        string ptime = "";
        if(time < 10){
            ptime = "0" + to_string(time);
        }else{
            ptime = to_string(time);
        }
        std::cout<<ptime<<std::endl;
        text.setString(ptime);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(text, states);
    }

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    Counter gameCounter(400,400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        gameCounter.updateCounter();


        window.clear();
        window.draw(gameCounter);
        window.display();
    }

    return 0;
}

