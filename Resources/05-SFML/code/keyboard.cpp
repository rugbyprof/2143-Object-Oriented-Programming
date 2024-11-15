#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Key Diagnostic");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key Pressed: " << event.key.code << std::endl;
            }
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}