#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 4: Animations");

    // Load textures for animation frames
    std::vector<sf::Texture> textures;
    for (int i = 1; i <= 24; ++i) {  // Assume dice frames are named frame1.png to frame6.png
        sf::Texture texture;
        std::string filename = (i < 10) ? "00" + std::to_string(i) + ".png" : "0" + std::to_string(i) + ".png";
        if (!texture.loadFromFile("./images/frame_" + filename)) {
            // if (!texture.loadFromFile("./images/" + std::to_string(i) + ".png")) {
            std::cerr << "Error loading frame" << i << ".png" << std::endl;
            return -1;
        }

        textures.push_back(texture);
    }

    // Create a sprite to display the current frame
    sf::Sprite sprite;
    sprite.setTexture(textures[0]);  // Start with the first frame
    sprite.setPosition(300.f, 200.f);

    // Timing variables
    sf::Clock clock;
    const sf::Time frameDuration = sf::milliseconds(5);  // 200ms per frame
    size_t currentFrame          = 0;

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
            clock.restart();  // Reset the clock

            // Advance to the next frame
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
        }

        // Render
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}