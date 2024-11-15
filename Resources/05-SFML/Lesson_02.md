## Lesson 2: Drawing Shapes and Textures

### Objective:

Learn to draw basic shapes and load textures for sprites in SFML. This lesson builds on Lesson 1 by introducing graphical elements for your Knucklebones game.

### Key Concepts

1. Basic Shapes: Use SFML’s sf::RectangleShape, sf::CircleShape, and sf::ConvexShape to create simple geometric elements.
2. Sprites and Textures: Use sf::Sprite to display images in the window by loading them into sf::Texture.

### Code Example

Here’s a program that:

1. Draws a circle and a rectangle.
2. Loads a texture and displays it as a sprite.

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
// Create a window
sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 2: Drawing Shapes and Textures");

    // Create a rectangle
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f)); // 200x100 rectangle
    rectangle.setFillColor(sf::Color::Blue);                  // Set the fill color
    rectangle.setPosition(100.f, 100.f);                      // Set the position

    // Create a circle
    sf::CircleShape circle(50.f); // Circle with radius 50
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(400.f, 100.f);

    // Load a texture
    sf::Texture texture;
    if (!texture.loadFromFile("dice_face.png")) {
        std::cerr << "Error: Could not load texture 'dice_face.png'\n";
        return -1;
    }

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(300.f, 300.f); // Set sprite position

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a white background
        window.clear(sf::Color::White);

        // Draw the shapes and sprite
        window.draw(rectangle);
        window.draw(circle);
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return 0;

}
```

### Explanation

#### Shapes

1. Rectangle (`sf::RectangleShape`):

- sf::RectangleShape(sf::Vector2f(width, height)) creates a rectangle of the specified size.
- setFillColor(sf::Color::Blue) sets the rectangle’s color.
- setPosition(x, y) moves the rectangle to a specific position.

2. Circle (`sf::CircleShape`):

- sf::CircleShape(radius) creates a circle with the given radius.
- Other options include setting an outline color and thickness.

#### Sprites

1. Loading a Texture:

- Use sf::Texture::loadFromFile() to load an image file (e.g., a dice face).
- Always check for errors if the file is missing or incorrectly named.

2. Creating a Sprite:

- `sf::Sprite` represents an image that can be drawn in the window.
- Use sprite.setTexture(texture) to link the sprite with a loaded texture.
- Use sprite.setPosition(x, y) to place the sprite in the window.

### Drawing to the Window

- `window.draw(rectangle)`, `window.draw(circle)`, and `window.draw(sprite)` add these objects to the frame.
- Use `window.clear()` to set a background color before drawing.

### Activity

1. Basic Shapes:

   - Add another shape (e.g., a triangle using sf::ConvexShape).
   - Experiment with outline colors and thickness using setOutlineColor and setOutlineThickness.

2. Positioning:

   - Move the rectangle and circle to different positions.
   - Align the sprite with the circle or rectangle for practice.

3. Using a Different Texture:

   - Replace dice_face.png with another image and test loading it.
   - Try resizing the sprite using `sprite.setScale(2.0f, 2.0f)` to make it larger or smaller.

### Discussion Questions

1. What happens if the texture file is missing or the path is incorrect? How can you handle this?
2. How might you align shapes and sprites dynamically (e.g., centered on the screen)?
3. What is the difference between setPosition and setScale when applied to sprites?

### Expected Output

1. A blue rectangle and a green circle displayed at their specified positions.
2. A sprite (image) drawn in the lower part of the window.
3. A white background.

This lesson introduces students to shapes and textures, both of which are essential for creating the game board and dice visuals in Knucklebones.
