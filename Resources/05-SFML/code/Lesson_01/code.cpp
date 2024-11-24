/**
 * LESSON 01 - Basic SFML Loop That prints the frame rate with a random background color
 *
 *
 */
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window with a title and dimensions (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Knucklebones Game");
    sf::Clock clock;           // SFML clock object to keep track of time
    int red   = rand() % 255;  // Random color value for red channel
    int green = rand() % 255;  // Random color value for green channel
    int blue  = rand() % 255;  // Random color value for blue channel

    // Main game loop
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();             // Restart the clock and return the elapsed time
        float fps        = 1.0f / elapsed.asSeconds();  // Calculate the frames per second
        std::cout << "FPS: " << fps << std::endl;       // Print the frames per second to console

        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user presses Escape or clicks the close button
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Clear the window with a specific color

        window.clear(sf::Color(red, green, blue));

        // Display the contents of the window
        window.display();
    }

    return 0;
}