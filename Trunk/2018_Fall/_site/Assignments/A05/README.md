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


### Example SFML

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter{
    // Your awesomeness here...
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

### Class Usage

This is just a snippet without the SFML, but your clock should be used something like the following:

```cpp

#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter{
    // Your awesomeness here...
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    Counter myClock1(5,0); // start at 5 and decrement to 0

    Counter myClock2(0,5); // start at 0 and increment to 5

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        myClock1.update();
        //Draw your clock 
        // Method 1: window.draw(myClock1);
        //or
        // Method 2: myClock.draw(window);
        window.display();

        if(myClock1.isFinished()){
            window.close();
        }
    }

    return 0;
}

```

### Deliverables:

- Turn in a copy of your completely commented code at the beginning of class.
- The name of your `cpp` file should be `counter.cpp`.
- Make sure your code makes it onto github in your assignments folder under a folder called `A05`.
- Along with your code, your folder should contain 2 animated gifs of your clock running: one with an incrementing clock, and one with a decrementing clock. 
- Name your two gifs `increment.gif` and `decrement.gif`

> https://www.getcloudapp.com/ has a free "gif capture" feature to record a portion of your screen. You can use this (or some other software of your choice) to create an animated gif of your clock running. The gif should include only the portion of your screen that has the clock.

