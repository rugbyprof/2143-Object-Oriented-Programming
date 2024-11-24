#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// used for file system operations like iterating through directories
namespace fs = std::filesystem;

/**
 * @brief Glob function to match files in a folder using a regex pattern
 * @param folderPath The folder path to search
 * @param pattern The regex pattern to match filenames
 * @return A vector of matched filenames
 *
 */
std::vector<std::string> glob(const std::string& folderPath, const std::string& pattern) {
    std::vector<std::string> matchedFiles;

    try {
        // Ensure the folder exists and is a directory
        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            throw std::runtime_error("Invalid folder path");
        }

        // Use regex to match the pattern
        std::regex regexPattern(pattern);

        // Iterate through the folder
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string fileName = entry.path().filename().string();
                if (std::regex_match(fileName, regexPattern)) {
                    matchedFiles.push_back(entry.path().string());
                }
            }
        }

        // Sort filenames to maintain a consistent order
        std::sort(matchedFiles.begin(), matchedFiles.end());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return matchedFiles;
}

/**
 * 
 * @brief AnimatedSprite class that handles multiple textures for animation
 * 
 * 
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable {
   private:
    std::vector<std::unique_ptr<sf::Texture>> textures;  // Vector of unique_ptr to textures
    sf::Sprite sprite;                                   // The sprite to render
    std::size_t currentFrame;                            // Index of the current frame
    sf::Clock animationClock;                            // Timer for animation updates
    float frameDuration;                                 // Duration of each frame in seconds
    bool clicked;

    // Override the draw method
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();  // Apply transformations
        target.draw(sprite, states);         // Draw the sprite
    }

   public:
    // Constructor
    AnimatedSprite(float frameDuration = 0.1f) : currentFrame(0), frameDuration(frameDuration) {}
    AnimatedSprite(vector<string> frames, float frameDuration = 0.1f) : currentFrame(0), frameDuration(frameDuration) {
        for (auto& frame : frames) {
            addFrame(frame);
        }

        sprite.setTexture(*textures[0]);
        clicked = false;
    }

    // Add a texture (by file path) to the animation
    void addFrame(const std::string& textureFile) {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(textureFile)) {
            throw std::runtime_error("Failed to load texture: " + textureFile);
        }
        textures.push_back(std::move(texture));
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                clicked = true;
            }
        }
    }

    bool isClicked() { return clicked; }

    // Update the animation
    void update() {
        if (textures.empty())
            return;  // No frames to animate

        if (animationClock.getElapsedTime().asSeconds() > frameDuration) {
            // Update the current frame index
            currentFrame = (currentFrame + 1) % textures.size();

            // Set the sprite to use the new frame's texture
            sprite.setTexture(*textures[currentFrame]);

            // Restart the clock
            animationClock.restart();
        }
    }

    // Set the sprite's position (can also use Transformable's methods)
    void setPosition(float x, float y) { sprite.setPosition(x, y); }

    // Move the sprite (relative movement)
    void move(float offsetX, float offsetY) { sprite.move(offsetX, offsetY); }

    // Set the size of the sprite (optional)
    void setScale(float scaleX, float scaleY) { sprite.setScale(scaleX, scaleY); }
};

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Sprite with Multiple Textures");

    std::string dsfolder = "./media/animations/dancing_skeleton";
    std::string drfolder = "./media/animations/dice_roll";

    std::string pattern = R"(frame_\d+\.png)";  // Regex pattern for filenames like "image_1.jpg"

    std::vector<std::string> dsfiles = glob(dsfolder, pattern);
    std::vector<std::string> drfiles = glob(drfolder, pattern);

    // std::cout << "Matched files:\n";
    // for (const auto& file : files) {
    //     std::cout << file << '\n';
    // }

    // Create an AnimatedSprite instance
    AnimatedSprite dancingSkeleton(dsfiles, 0.01f);  // Frame duration = 0.2 seconds
    AnimatedSprite diceRoll(drfiles, 0.2f);          // Frame duration = 0.2 seconds

    // // Add frames (images) to the animation
    // try {
    //     animatedSprite.addFrame("frame1.png");
    //     animatedSprite.addFrame("frame2.png");
    //     animatedSprite.addFrame("frame3.png");
    //     animatedSprite.addFrame("frame4.png");
    // } catch (const std::runtime_error& e) {
    //     std::cerr << e.what() << '\n';
    //     return -1;  // Exit if texture loading fails
    // }

    // Set the initial position
    dancingSkeleton.setPosition(100, 100);
    diceRoll.setPosition(400, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        diceRoll.handleEvent(event, window);

        if (diceRoll.isClicked()) {
            diceRoll.update();
        }

        // Update the animation
        dancingSkeleton.update();

        // Move sprite with arrow keys
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cout << "Right key pressed\n";
            dancingSkeleton.move(5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cout << "Left key pressed\n";
            dancingSkeleton.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dancingSkeleton.move(0.f, -5.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dancingSkeleton.move(0.f, 5.f);

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case 71:  // Left arrow
                    std::cout << "Left arrow pressed!" << std::endl;
                    dancingSkeleton.move(-.01f, 0.f);
                    break;
                case 72:  // Right arrow
                    std::cout << "Right arrow pressed!" << std::endl;
                    dancingSkeleton.move(.01f, 0.f);
                    break;
                case 73:  // Up arrow
                    std::cout << "Up arrow pressed!" << std::endl;
                    dancingSkeleton.move(0.f, -.01f);
                    break;
                case 74:  // Down arrow
                    std::cout << "Down arrow pressed!" << std::endl;
                    dancingSkeleton.move(0.f, .01f);
                    break;
                default:
                    break;
            }
        }

        // Clear and draw
        window.clear(sf::Color::Black);
        window.draw(diceRoll);
        window.draw(dancingSkeleton);
        window.display();
    }

    return 0;
}