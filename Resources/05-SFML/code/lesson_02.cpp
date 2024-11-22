/**
 * 	1.	SFML Shapes:
 * 		- sf::RectangleShape and sf::CircleShape are predefined classes for drawing basic shapes.
 * 		- These shapes can have properties like size, color, and position customized.
 * 	2.	Textures and Sprites:
 * 		- A texture (sf::Texture) is an image loaded from a file that can be applied to a sprite.
 * 		- A sprite (sf::Sprite) is a drawable object that can display a texture.
 * 	3.	Game Loop:
 * 		- The game loop continuously checks for events, clears the screen, draws objects, and updates the display.
 * 		- window.clear() erases the previous frame, and window.display() renders the new frame.
 */
#include <SFML/Graphics.hpp>  // Include SFML Graphics module for window, shapes, textures
#include <iostream>           // Include for input/output operations (e.g., error messages)

int main() {
    // Create a window with dimensions 800x600 and title "Lesson 2: Drawing Shapes and Textures"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 2: Drawing Shapes and Textures");

    // Create a rectangle shape with a size of 200x100
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 100.f));  // Dimensions: 200 pixels wide, 100 pixels tall
    rectangle.setFillColor(sf::Color::Blue);                   // Set the rectangle's fill color to blue
    rectangle.setPosition(100.f, 100.f);                       // Set the rectangle's position to (100, 100)

    // Create a circle shape with a radius of 50 pixels
    sf::CircleShape circle(50.f);           // Radius is 50 pixels
    circle.setFillColor(sf::Color::Green);  // Set the circle's fill color to green
    circle.setPosition(400.f, 100.f);       // Set the circle's position to (400, 100)

    // Load a texture from an external image file
    sf::Texture texture;
    if (!texture.loadFromFile("./media/images/6.png")) {  // Attempt to load the texture file
        // If the texture file fails to load, print an error message and exit the program
        std::cerr << "Error: Could not load texture 'dice_face.png'\n";
        return -1;  // Return error code
    }

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);        // Assign the loaded texture to the sprite
    sprite.setPosition(300.f, 300.f);  // Set the sprite's position to (300, 300)

    // Main game loop (runs until the window is closed)
    while (window.isOpen()) {
        sf::Event event;
        // Poll for events (e.g., window close, keyboard input)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)  // If the close event is triggered
                window.close();                   // Close the window
        }

        // Clear the window and set the background color to white
        window.clear(sf::Color::White);

        // Draw the rectangle, circle, and sprite onto the window
        window.draw(rectangle);  // Draw the rectangle
        window.draw(circle);     // Draw the circle
        window.draw(sprite);     // Draw the sprite

        // Display everything that has been drawn (render the frame)
        window.display();
    }

    return 0;  // Indicate successful execution
}