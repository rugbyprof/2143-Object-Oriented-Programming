#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    //sf::CircleShape shape(100.f);
    sf::Sprite spriteBall;
    sf::Sprite spriteBox;
    sf::Texture golfBall;
    sf::Texture swirly;

    //shape.setFillColor(sf::Color::Green);

    if (!golfBall.loadFromFile("./images/golf_ball.png"))
    {
        std::cout<<"Error loading texture..."<<std::endl;
    }

    if (!swirly.loadFromFile("./images/marble_texture.jpg", sf::IntRect(10, 10, 40, 40)))
    {
        std::cout<<"Error loading texture..."<<std::endl;
    }

    spriteBall.setTexture(golfBall);
    spriteBall.setScale(.1,.1);
    spriteBox.setTexture(swirly);
    spriteBox.setPosition(400,400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
        window.draw(spriteBox);
        window.draw(spriteBall);
        window.display();
    }

    return 0;
}