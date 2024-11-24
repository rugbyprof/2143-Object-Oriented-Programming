/*
 * This program demonstrates how to use SFML sprites and textures to create an animation
 * It features:
 * - A series of images loaded for each frame of the animation (texture)
 * - A sprite that displays each texture one after the other to create an animation
 * - A game loop that handles window events, clears the screen, draws the
 *   objects, and updates the display continuously.
 * Downsides:
 *  - It is hard coded for a single animation (dice animation) and the class isn't usefull otherwise
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

// A little beyond the README, but even better to have a class for the animation
// This animation class is hard coded for the dice animation
class DiceAnimation {
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    sf::Clock clock;
    sf::Time frameDuration;  // Frame duration (e.g., 100ms per frame)
    int currentFrame;

   public:
    DiceAnimation() : frameDuration(sf::milliseconds(100)), currentFrame(0) {
        // Load textures
        for (int i = 1; i <= 24; ++i) {
            sf::Texture texture;
            string prefix        = (i < 10) ? "00" : "0";
            std::string filename = "frame_" + prefix + std::to_string(i) + ".png";
            if (!texture.loadFromFile("../media/animations/dice_roll/" + filename)) {
                std::cerr << "Error loading " << filename << std::endl;
                return;
            }
            textures.push_back(texture);
        }

        if (!textures.empty()) {
            sprite.setTexture(textures[currentFrame]);
        }
        sprite.setPosition(300.f, 200.f);
    }

    void update() {
        if (clock.getElapsedTime() >= frameDuration) {
            clock.restart();

            // Advance to the next frame
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
        }
    }

    void setFrameDuration(sf::Time duration) { frameDuration = duration; }

    int getFrameDuration() const { return frameDuration.asMilliseconds(); }

    const sf::Sprite& draw() const { return sprite; }

    void changeSpeed(int delta) {
        frameDuration += sf::milliseconds(50 * delta);  // Add 50ms to slow down animation
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 4: Dice Animation");
    DiceAnimation diceAnimation;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Additional event handling for changing the animation speed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    diceAnimation.changeSpeed(-1);
                    std::cout << "Frame duration: " << diceAnimation.getFrameDuration() << " ms" << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    diceAnimation.changeSpeed(1);
                    std::cout << "Frame duration: " << diceAnimation.getFrameDuration() << " ms" << std::endl;
                }
            }
        }

        diceAnimation.update();

        window.clear();
        window.draw(diceAnimation.draw());
        window.display();
    }

    return 0;
}