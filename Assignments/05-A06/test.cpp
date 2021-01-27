#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Your Name Here!!");
    sf::CircleShape shape(100.f);

    shape.setFillColor(sf::Color::Green);

    shape.move(sf::Vector2f(100,100));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}