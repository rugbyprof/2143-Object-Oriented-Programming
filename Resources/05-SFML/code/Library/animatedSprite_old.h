#pragma once
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
    AnimatedSprite(float frameDuration = 0.1f) : currentFrame(0), frameDuration(frameDuration) {
    }
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

    bool isClicked() {
        return clicked;
    }

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
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // Move the sprite (relative movement)
    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    // Set the size of the sprite (optional)
    void setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }
};
