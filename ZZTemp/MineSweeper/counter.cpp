#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter{

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    sf::Clock clock; 
    sf::Time start;
    sf::Time end;
    sf::Time elapsed;
    start = sf::seconds(50);
    end = sf::seconds(50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        elapsed = clock.getElapsedTime();
        cout<<"Incrementing Clock: "<<elapsed.asSeconds()<<endl;

        elapsed = clock.getElapsedTime();
        cout<<"Decrementing Clock: "<<start.asSeconds()-elapsed.asSeconds()<<endl;

        window.clear();
        //window.draw(shape);
        window.display();
    }

    return 0;
}
