```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter{

};

int main(){
    sf::Clock clock; 
    sf::Time start;
    sf::Time end;
    sf::Time elapsed;
    start = sf::seconds(5);
    end = sf::seconds(3);
    
    // incrementing counter
    while(elapsed.asSeconds() < end.asSeconds()){
        
        elapsed = clock.getElapsedTime();
        cout<<elapsed.asSeconds()<<endl;

    }

    clock.restart();

    // decrementing counter
    while(start.asSeconds()-elapsed.asSeconds() > 0){
        
        elapsed = clock.getElapsedTime();
        cout<<start.asSeconds()-elapsed.asSeconds()<<endl;

    }
    

    return 0;
}
```
