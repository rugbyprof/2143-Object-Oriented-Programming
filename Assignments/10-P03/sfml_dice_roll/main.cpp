#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Animation {
public:
    // Constructor to initialize frame timing and load images
    Animation(int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isPlaying(false), folderName("") {}
    Animation(string folderName, string filePrefix, int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isPlaying(false), folderName(folderName), filePrefix(filePrefix) {}

    // Load a sequence of frames (e.g., 001.png to 024.png) into textures
    void loadFrames(int start, int end, const string& imageFolder = "") {
        if (imageFolder != "") {
            this->folderName = imageFolder;
        }
        vector< string > filenames;
        frames.clear();
        for (int i = start; i <= end; ++i) {
            string filename = (i < 10) ? "00" + to_string(i) + ".png" : "0" + to_string(i) + ".png";
            filenames.push_back(folderName + filePrefix + filename);
        }
        loadFrames(filenames);
    }

    void loadFrames(vector< string > filenames) {
        frames.clear();
        for (const auto& filename : filenames) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                cerr << "Error loading " << filename << endl;
                continue;
            }
            frames.push_back(texture);
        }
    }

    // Start the animation
    void play() {
        isPlaying = true;
        frameIndex = 0;
        clock.restart();
    }

    // Update the animation frame based on the elapsed time
    void update(sf::Sprite& sprite) {
        if (!isPlaying) return;

        if (clock.getElapsedTime().asMilliseconds() > frameDelay) {
            frameIndex++;
            if (frameIndex < frames.size()) {
                sprite.setTexture(frames[frameIndex]);
                clock.restart();
            } else {
                // End animation and display a random dice face (1 to 6)
                mt19937                         rng(static_cast< unsigned >(chrono::system_clock::now().time_since_epoch().count()));
                uniform_int_distribution< int > dist(1, 6);
                int                             finalDiceFace = dist(rng);
                string                          finalFilename = folderName + to_string(finalDiceFace) + ".png";
                if (!texture.loadFromFile(finalFilename)) {
                    cerr << "Error loading " << finalFilename << endl;
                    return;
                }
                sprite.setTexture(texture);
                isPlaying = false;
            }
        }
    }

    bool isAnimationPlaying() const { return isPlaying; }

private:
    vector< sf::Texture > frames;      // Vector to store frames for animation
    sf::Texture           texture;     // Texture for final dice face
    int                   frameIndex;  // Current frame index
    int                   frameDelay;  // Delay per frame in milliseconds
    bool                  isPlaying;   // Is the animation playing?
    sf::Clock             clock;       // Clock for frame timing
    string                folderName;  // Folder name for frame images
    string                filePrefix;  // Prefix for frame image files
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Dice Roll Animation");

    // Initialize animation with 24 frames at a 50ms delay
    Animation diceAnimation("./dice_roll/", "frame_", 30);
    diceAnimation.loadFrames(1, 24);

    // Sprite to display the animation
    sf::Sprite sprite;
    sprite.setPosition(100, 100);  // Adjust position as needed

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Start or restart animation on mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!diceAnimation.isAnimationPlaying()) {
                    diceAnimation.play();
                }
            }
        }

        // Update the animation
        diceAnimation.update(sprite);

        // Clear, draw, and display the window
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}