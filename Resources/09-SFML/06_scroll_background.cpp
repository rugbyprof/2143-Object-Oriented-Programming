#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 440), "SFML works!");
    //sf::CircleShape shape(100.f);
    sf::Sprite spriteBall;
    sf::Sprite spriteBg;
    sf::Texture golfBall;
    sf::Texture background;

    //shape.setFillColor(sf::Color::Green);

    if (!golfBall.loadFromFile("./images/golf_ball.png"))
    {
        std::cout<<"Error loading texture..."<<std::endl;
    }

    if (!background.loadFromFile("./images/scroll_bg2.png"))
    {
        std::cout<<"Error loading texture..."<<std::endl;
    }

    spriteBall.setTexture(golfBall);
    spriteBall.setScale(.1,.1);
    spriteBg.setTexture(background);
    spriteBg.setPosition(1,1);

    sf::Vector2u size;

    size = background.getSize();

    std::cout<<size.x<<std::endl;

    float x = 1.0;
    float y = 1.0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        spriteBg.setPosition(x,y);

        x-=.075;

        std::cout<<x<<std::endl;

        if(x <= -1440+600){
            x=1;
        }

        window.clear();
        //window.draw(shape);
        window.draw(spriteBg);
        window.draw(spriteBall);
        window.display();
    }

    return 0;
}