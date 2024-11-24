## Lesson 3: Capturing and Handling User Input

### Objective:

Learn how to capture user input (mouse clicks and keyboard presses) in SFML and respond to it by updating the game state or triggering actions. This lesson builds on Lessons 1 and 2 by enabling interaction with shapes and sprites.

### Key Concepts

1. sf::Event:
   - Used to handle discrete events like mouse clicks, key presses, and window resizing.
   - Retrieved using window.pollEvent(event).
2. Mouse Input:
   - Detect mouse button clicks and retrieve cursor position.
   - Use sf::Mouse to get mouse state.
3. Keyboard Input:
   - Detect key presses and releases.
   - Use sf::Keyboard for real-time state queries.

### Code Example

Here’s a program that: 1. Draws a rectangle and changes its color when clicked. 2. Moves a circle using the arrow keys.

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 3: User Input");

    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f)); // 200x100 rectangle
    rectangle.setFillColor(sf::Color::Blue);                  // Initial color
    rectangle.setPosition(300.f, 200.f);                      // Position in the window

    // Create a circle
    sf::CircleShape circle(50.f); // Circle with radius 50
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
                        rectangle.setFillColor(sf::Color::Red); // Change rectangle color
                    }
                }
            }

            // Detect key presses
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close(); // Close the window on Escape
                }
            }
        }

        // // Real-time keyboard movement for the circle
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        //     circle.move(0.f, -5.f);
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        //     circle.move(0.f, 5.f);
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        //     circle.move(-5.f, 0.f);
        // }
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        //     circle.move(5.f, 0.f);
        // }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case 71:  // Left arrow
                    std::cout << "Left arrow pressed!" << std::endl;
                    circle.move(-1.f, 0.f);
                    break;
                case 72:  // Right arrow
                    std::cout << "Right arrow pressed!" << std::endl;
                    circle.move(1.f, 0.f);
                    break;
                case 73:  // Up arrow
                    std::cout << "Up arrow pressed!" << std::endl;
                    circle.move(0.f, -1.f);
                    break;
                case 74:  // Down arrow
                    std::cout << "Down arrow pressed!" << std::endl;
                    circle.move(0.f, 1.f);
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
```

## Explanation

### Mouse Input

1. Event-Based Detection:
   - Use sf::Event::MouseButtonPressed to detect when a mouse button is clicked.
   - Retrieve the position using event.mouseButton.x and event.mouseButton.y.
2. Real-Time Mouse Position:
   - Use sf::Mouse::getPosition(window) to get the current mouse position relative to the window.
3. Checking Shape Bounds:
   - Use getGlobalBounds() on a shape or sprite to check if the mouse position intersects it.

### Keyboard Input

1. Event-Based Key Detection:
   - Use sf::Event::KeyPressed to detect when a key is pressed.
   - Use event.key.code to check which key was pressed (e.g., sf::Keyboard::Escape).
2. Real-Time Key Detection:
   - Use sf::Keyboard::isKeyPressed for continuous key states (e.g., moving an object as long as an arrow key is held down).

### Activity

1. Mouse Input:
   - Add another rectangle and detect clicks on it.
   - Change the shape’s outline thickness or position when clicked.
2. Keyboard Input:
   - Move the rectangle with WASD keys and the circle with arrow keys.
   - Add boundaries to prevent shapes from moving off-screen.
3. Custom Actions:
   - Display a message in the console when the spacebar is pressed.
   - Make the rectangle “jump” to a new random position when clicked.

### Discussion Questions

1. What happens if you click outside the rectangle?
2. How would you implement drag-and-drop functionality for a shape?
3. How can you handle simultaneous key presses (e.g., Up and Right together)?

### Expected Output

- A rectangle that changes color when clicked.
- A circle that moves in response to arrow key presses.
- Mouse click positions printed in the console.

This lesson introduces interaction with SFML windows and shapes, setting the stage for interactive game mechanics in Knucklebones.
