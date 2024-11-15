#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

class Animation : public sf::Drawable {
   private:
    vector<sf::Texture> frames;  // Vector to store frames for animation
    sf::Texture texture;         // Texture for final dice face
    int frameIndex;              // Current frame index
    int frameDelay;              // Delay per frame in milliseconds
    bool isPlaying;              // Is the animation playing?
    sf::Clock clock;             // Clock for frame timing
    string folderName;           // Folder name for frame images
    string filePrefix;           // Prefix for frame image files
    sf::Sprite sprite;           // Sprite to display the animation
   public:
    // Constructor to initialize frame timing and load images
    Animation(int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isPlaying(false), folderName("") {}
    Animation(string folderName, string filePrefix, int frameDelayMs = 50)
        : frameDelay(frameDelayMs), frameIndex(0), isPlaying(false), folderName(folderName), filePrefix(filePrefix) {}

    // Load a sequence of frames (e.g., 001.png to 024.png) into textures
    void loadFrames(int start, int end, const string& imageFolder = "") {
        if (imageFolder != "") {
            this->folderName = imageFolder;
        }
        vector<string> filenames;
        frames.clear();
        for (int i = start; i <= end; ++i) {
            string filename = (i < 10) ? "00" + to_string(i) + ".png" : "0" + to_string(i) + ".png";
            filenames.push_back(folderName + filePrefix + filename);
        }
        loadFrames(filenames);
    }

    void loadFrames(vector<string> filenames) {
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
        isPlaying  = true;
        frameIndex = 0;
        clock.restart();
    }

    // Update the animation frame based on the elapsed time
    void update() {
        if (!isPlaying)
            return;

        if (clock.getElapsedTime().asMilliseconds() > frameDelay) {
            frameIndex = (frameIndex + 1) % (frames.size() + 1);
            if(frameIndex == frames.size()-1) {
                frameIndex = 0;
            }
            cout << frameIndex << endl;
            if (frameIndex < frames.size()) {
                sprite.setTexture(frames[frameIndex]);
                clock.restart();
            } else {
                // End animation and display a random dice face (1 to 6)
                mt19937 rng(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
                uniform_int_distribution<int> dist(1, 6);
                int finalDiceFace    = dist(rng);
                string finalFilename = folderName + to_string(finalDiceFace) + ".png";
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

    void setPos(float x, float y) { sprite.setPosition(x, y); }
    void setScale(float x, float y) { sprite.setScale(x, y); }

    // Override the draw method to define custom drawing behavior
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);  // Draw the sprite to the target
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Dice Roll Animation");
    map<string, Animation> animations;

    animations["da1"] = Animation("./images/rotated/north/", "frame_", 30);
    animations["da1"].setPos(100, 100);
    animations["da1"].setScale(0.50f, 0.50f);
    animations["da1"].loadFrames(1, 24);

    animations["da2"] = Animation("./images/rotated/south/", "frame_", 30);
    animations["da2"].setPos(200, 100);
    animations["da2"].setScale(0.50f, 0.50f);
    animations["da2"].loadFrames(1, 24);

    animations["da3"] = Animation("./images/rotated/east/", "frame_", 30);
    animations["da3"].setPos(100, 200);
    animations["da3"].setScale(0.50f, 0.50f);
    animations["da3"].loadFrames(1, 24);

    animations["da4"] = Animation("./images/rotated/west/", "frame_", 30);
    animations["da4"].setPos(200, 200);
    animations["da4"].setScale(0.50f, 0.50f);
    animations["da4"].loadFrames(1, 24);

    // Sprite to display the animation
    // sf::Sprite sprite;
    // sprite.setPosition(100, 100);  // Adjust position as needed
    // sprite.setScale(0.25f, 0.25f);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Start or restart animation on mouse click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (auto& [id, anim] : animations) {
                    if (!anim.isAnimationPlaying()) {
                        anim.play();
                    }
                }
                // if (!animations["da1"].isAnimationPlaying()) {
                //     animations["da1"].play();
                // }
            }
        }

        // Update the animation

        // Clear, draw, and display the window
        window.clear();
        for (auto& [id, anim] : animations) {
            anim.update();
            window.draw(anim);
        }

        window.display();
    }

    return 0;
}