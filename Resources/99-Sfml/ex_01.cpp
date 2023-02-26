#include <SFML/Graphics.hpp>

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Centered Image");

    // Load the image from file
    sf::Texture texture;
    if (!texture.loadFromFile("banana.png")) {
        return EXIT_FAILURE;
    }

    // Create a sprite and set its texture
    sf::Sprite sprite(texture);

    // Center the sprite in the window
    double x = window.getSize().x / 2 - sprite.getLocalBounds().width / 2;
    double y = window.getSize().y / 2 - sprite.getLocalBounds().height / 2;

    sprite.setPosition(x, y);

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the window
        window.display();
    }

    return EXIT_SUCCESS;
}