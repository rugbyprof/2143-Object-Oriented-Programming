## Counter Class - Creating a counter for our game
#### Due: Friday November 2<sup>nd</sup> by classtime.

### Overview:

Write a class that uses the SFML `Clock` and `Time` classes to create us a counter class. Your class will allow a user to do the following:

- Start a timer.
- Reset a timer.
- Set a length of time to run.
- Allow your timer to count up to some value (or have no ending time).
- Allow your timer to count down to some value (or have no ending time).
- For this class assume the user wants to display only discrete seconds (1,2,3) not (1.23,1.24,1.25.....,2.0)
- When your timer is finished, it will close the sfml window.
- The example below prints to stdout but you can print your timer text to the sfml window. 


```cpp
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

```
