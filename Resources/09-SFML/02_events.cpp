#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    sf::Event event;

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

    while (window.isOpen()) {
        
        // while there are pending events...
        while (window.pollEvent(event)) {

            // check the type of the event...
            switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
                if (event.text.unicode < 128)
                    std::cout << "int(" << event.key.code << ") letter(" << char(event.key.code + 65) << ")" << std::endl;
                break;

            // window resized
            case sf::Event::Resized:

                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
                break;

            // mouse button pressed
            case sf::Event::MouseButtonPressed:

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                }

                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                break;

            // mouse moved on window
            case sf::Event::MouseMoved:

                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;

                break;

            // mouse is now back on window
            case sf::Event::MouseEntered:
                std::cout << "the mouse cursor has entered the window" << std::endl;

                break;

            // mouse has left the window
            case sf::Event::MouseLeft:
                std::cout << "the mouse cursor has left the window" << std::endl;

                break;

            // we don't process other types of events
            default:
                break;
            }
        }
    }
}