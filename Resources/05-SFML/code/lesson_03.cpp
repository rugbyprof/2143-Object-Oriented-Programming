/*
 * This program demonstrates how to create a window using SFML and draw
 * various graphical objects, including shapes and textures.
 * It features:
 * - A blue rectangle and a green circle positioned on the window.
 * - A sprite that displays a texture loaded from an external image file.
 * - A game loop that handles window events, clears the screen, draws the
 *   objects, and updates the display continuously.
 *
 * Key concepts covered:
 * - Creating and positioning shapes (rectangle, circle).
 * - Loading and displaying textures using sprites.
 * - Handling events such as window closing.
 * - Managing the rendering loop with clear, draw, and display operations.
 */
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 3: User Input");

    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));  // 200x100 rectangle
    rectangle.setFillColor(sf::Color::Blue);                   // Initial color
    rectangle.setPosition(300.f, 200.f);                       // Position in the window

    // Create a circle
    sf::CircleShape circle(50.f);  // Circle with radius 50
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(100.f, 100.f);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window when requested
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Detect mouse clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get mouse position relative to the window
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;

                    // Check if the rectangle was clicked
                    if (rectangle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        rectangle.setFillColor(sf::Color::Red);  // Change rectangle color
                    } else {
                        rectangle.setFillColor(sf::Color::Yellow);
                    }
                }
            }

            // Detect key presses
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();  // Close the window on Escape
                }
            }
        }

        // Allows you to move the green circle by pressing the arrow keys
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case 71:  // Left arrow
                    std::cout << "Left arrow pressed!" << std::endl;
                    circle.move(-.01f, 0.f);
                    break;
                case 72:  // Right arrow
                    std::cout << "Right arrow pressed!" << std::endl;
                    circle.move(.01f, 0.f);
                    break;
                case 73:  // Up arrow
                    std::cout << "Up arrow pressed!" << std::endl;
                    circle.move(0.f, -.01f);
                    break;
                case 74:  // Down arrow
                    std::cout << "Down arrow pressed!" << std::endl;
                    circle.move(0.f, .01f);
                    break;
                default:
                    break;
            }
        }

        // Clear the window and draw everything
        window.clear(sf::Color::White);
        window.draw(rectangle);
        window.draw(circle);
        window.display();
    }

    return 0;
}