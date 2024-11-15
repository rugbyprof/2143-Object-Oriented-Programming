## Lesson 4: Animations in SFML

### Objective:

Learn to create animations using SFML’s `sf::Clock` and `sf::Sprite` by cycling through frames of an animated texture (e.g., dice rolling). This lesson focuses on displaying sequential images to simulate motion, a key feature for making the dice roll animation in Knucklebones.

### Key Concepts

1. Frame-Based Animation:
   - Load a series of texture frames (e.g., frame1.png, frame2.png, …).
   - Update the displayed frame at a fixed interval.
2. Time Management:
   - Use `sf::Clock` to control the timing between frame updates.
3. Sprite Updates:
   - Dynamically change the texture of an `sf::Sprite` to display the next frame.

## Code Example: Basic Animation

Here’s a program that animates a dice roll using a sequence of images.

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 4: Animations");

    // Load textures for animation frames
    std::vector<sf::Texture> textures;
    for (int i = 1; i <= 6; ++i) { // Assume dice frames are named frame1.png to frame6.png
        sf::Texture texture;
        if (!texture.loadFromFile("frame" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading frame" << i << ".png" << std::endl;
            return -1;
        }
        textures.push_back(texture);
    }

    // Create a sprite to display the current frame
    sf::Sprite sprite;
    sprite.setTexture(textures[0]); // Start with the first frame
    sprite.setPosition(300.f, 200.f);

    // Timing variables
    sf::Clock clock;
    const sf::Time frameDuration = sf::milliseconds(200); // 200ms per frame
    size_t currentFrame = 0;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update animation frame
        if (clock.getElapsedTime() >= frameDuration) {
            clock.restart(); // Reset the clock

            // Advance to the next frame
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
        }

        // Render
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
```

### Explanation

#### Animation Basics

1. Load Frames:
   - Each frame of the animation is loaded as a texture (e.g., frame1.png, frame2.png, …).
   - These textures are stored in a std::vector for easy access.
2. Update Frames:
   - sf::Clock measures the time since the last frame update.
   - When the elapsed time exceeds frameDuration, the next frame is displayed.
3. Sprite Rendering:
   - The sf::Sprite object dynamically updates its texture to match the current frame.

### Activity

1. Adjust Timing:
   - Change the frameDuration value to make the animation faster or slower.
   - Test durations like sf::milliseconds(100) (faster) or sf::milliseconds(300) (slower).
2. Loop Animation:
   - The current implementation loops automatically by using:

```cpp
currentFrame = (currentFrame + 1) % textures.size();
```

Experiment with stopping the animation after one loop.

3. Trigger Animation:
   - Add keyboard or mouse input to trigger the animation.

## Advanced Example: Random Final Dice Face

After animating through all frames, display a random dice face from frame1.png to `frame6.png` as the final result.

```cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Roll Animation");

    // Load textures for animation frames
    std::vector<sf::Texture> textures;
    for (int i = 1; i <= 6; ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile("frame" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading frame" << i << ".png" << std::endl;
            return -1;
        }
        textures.push_back(texture);
    }

    sf::Sprite sprite;
    sprite.setTexture(textures[0]);
    sprite.setPosition(300.f, 200.f);

    sf::Clock clock;
    const sf::Time frameDuration = sf::milliseconds(100);
    size_t currentFrame = 0;
    bool isRolling = true;

    std::srand(std::time(nullptr)); // Seed for random number generation

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Start dice roll on mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isRolling = true;
                currentFrame = 0;
                clock.restart();
            }
        }

        // Update animation
        if (isRolling && clock.getElapsedTime() >= frameDuration) {
            clock.restart();
            currentFrame++;

            if (currentFrame >= textures.size()) {
                isRolling = false; // Stop rolling
                sprite.setTexture(textures[std::rand() % 6]); // Display random final frame
            } else {
                sprite.setTexture(textures[currentFrame % textures.size()]);
            }
        }

        // Render
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
```

### Discussion Questions

1. How can you make the animation start automatically and stop after a set number of frames?
2. What would you change to make the dice roll sound play during the animation?
3. How might you scale the dice animation to fit different screen sizes?

### Expected Output

1. A dice animation that cycles through frames.
2. Clicking the window resets the animation, ending with a random dice face.
3. Frames update smoothly at the specified interval.

This lesson introduces time-based animation and frame handling, essential for dice rolls and visual effects in Knucklebones.
