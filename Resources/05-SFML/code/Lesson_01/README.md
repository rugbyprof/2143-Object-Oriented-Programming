## Lesson 1: Setting Up the Game Window

### Objective:

Learn how to create and manage an SFML window, handle basic events, and set up a game loop.

### Key Concepts

1. `sf::RenderWindow`: The main class for creating and managing a window in SFML.
2. Game Loop: The continuous loop that keeps the game running, handles events, updates the game state, and renders graphics.
3. Event Handling: Managing user input (e.g., keyboard and mouse) using `sf::Event`.

### Code Example

Here’s a simple program that creates a window and closes it when the user presses the Escape key or clicks the close button:

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
// Create a window with a title and dimensions (800x600)
sf::RenderWindow window(sf::VideoMode(800, 600), "Knucklebones Game");

    // Main game loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user presses Escape or clicks the close button
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Clear the window with a specific color
        window.clear(sf::Color::Black);

        // Display the contents of the window
        window.display();
    }

    return 0;

}
```

### Step-by-Step Explanation

1. Create a Window:
   - `sf::RenderWindow` is used to create a window object.
   - `sf::VideoMode(800, 600)` specifies the width and height of the window (800x600 pixels).
   - "Knucklebones Game" sets the title of the window.
2. Game Loop:
   - The while (window.isOpen()) loop keeps the window open as long as it hasn’t been closed by the user.
3. Event Handling:
   - `window.pollEvent(event)` retrieves all pending events (e.g., key presses, mouse clicks).
   - `sf::Event::Closed`: Fired when the user clicks the close button.
   - `sf::Keyboard::Escape`: Fired when the user presses the Escape key.
4. Rendering:
   - `window.clear(sf::Color::Black)`: Clears the window to a black background.
   - `window.display()`: Displays the current frame to the screen.

Activity

1. Basic Window:
   - Modify the window dimensions (e.g., 1024x768) and change the title to your name (e.g., "YourName's Knucklebones").
2. Background Color:
   - Change the background color in window.clear() to something other than black (e.g., sf::Color::Blue).
3. Add an FPS Counter:
   - Calculate and print the frame rate (FPS) to the console:

```cpp
sf::Clock clock;
while (window.isOpen()) {
    sf::Time elapsed = clock.restart();
    float fps = 1.0f / elapsed.asSeconds();
    std::cout << "FPS: " << fps << std::endl;

    // Rest of the game loop...

}
```

### Discussion Questions

1. Why do you need both `window.clear()` and `window.display()` in the game loop?
2. What happens if you omit `pollEvent()` from the game loop?
3. How might you detect other key presses (e.g., W, A, S, D)?

### Expected Output

When you run the program:

1. A window titled “Knucklebones Game” opens with dimensions 800x600.
2. The window can be closed by clicking the close button or pressing Escape.
3. The background of the window is black (or the color you set in window.clear()).

This lesson establishes the foundation for building more complex game functionality. Let me know when you’re ready for Lesson 2: Drawing Shapes and Textures!
