#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class DiceAnimation {
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    sf::Clock clock;
    sf::Time frameDuration;  // 100ms per frame
    int currentFrame;

   public:
    DiceAnimation() {
        for (int i = 1; i <= 24; ++i) {  // Assume dice frames are named frame1.png to frame6.png
            sf::Texture texture;
            std::string filename = (i < 10) ? "00" + std::to_string(i) + ".png" : "0" + std::to_string(i) + ".png";
            if (!texture.loadFromFile("./images/frame_" + filename)) {
                // if (!texture.loadFromFile("./images/" + std::to_string(i) + ".png")) {
                std::cerr << "Error loading frame" << i << ".png" << std::endl;
                return;
            }

            textures.push_back(texture);
        }
        frameDuration = sf::milliseconds(100);  // 100ms per frame
        currentFrame  = 0;
        sprite.setTexture(textures[currentFrame]);  // Start with the first frame
        sprite.setPosition(300.f, 200.f);
    }

    void update() {
        // Update animation frame
        if (clock.getElapsedTime() >= frameDuration) {
            clock.restart();  // Reset the clock

            // Advance to the next frame
            currentFrame = (currentFrame + 1) % textures.size();
            sprite.setTexture(textures[currentFrame]);
        }
    }
    // void setFrameDuration(sf::Time frameDuration) { this->frameDuration = sf::milliseconds(frameDuration); }
    // int getFrameDuration() { return frameDuration.asMilliseconds(); }
    sf::Sprite draw() { return sprite; }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 4: Animations");
    DiceAnimation dice;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Get mouse position relative to the window
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;
                    sf::Time frameDuration = dice.getFrameDuration();
                    dice.setFrameDuration(frameDuration + sf::milliseconds(10));
                }
            }
        }
        dice.update();
        // Render
        window.clear(sf::Color::Black);
        window.draw(dice.draw());
        window.display();
    }

    return 0;
}