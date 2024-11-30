
#include "animatedSprite.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Animations");

    vector<AnimatedSprite> diceAnimations;

    std::string folder             = "../media/animations/dice_roll_away_right";
    std::string pattern            = R"(frame_\d+\.png)";  // Regex pattern for
    std::vector<std::string> files = glob(folder, pattern);
    diceAnimations.push_back(AnimatedSprite(files, 0.03f));

    files.clear();
    folder = "../media/animations/dice_roll_away_left";
    files  = glob(folder, pattern);
    diceAnimations.push_back(AnimatedSprite(files, 0.03f));
    files.clear();
    folder = "../media/animations/dice_roll";
    files  = glob(folder, pattern);
    diceAnimations.push_back(AnimatedSprite(files, 0.03f));
    files.clear();
    folder = "../media/animations/dice_roll_0";
    files  = glob(folder, pattern);
    diceAnimations.push_back(AnimatedSprite(files, 0.03f));
    files.clear();
    folder = "../media/animations/dice_roll_away_wow";
    files  = glob(folder, pattern);
    diceAnimations.push_back(AnimatedSprite(files, 0.03f));

    int offset = 50 * diceAnimations.size() * -1;
    for (auto& diceAnimation : diceAnimations) {
        diceAnimation.setScale(0.5f, 0.5f);
        diceAnimation.setPosition(400 + offset, 300);
        diceAnimation.setCurrentFrame(0);
        offset += 100;
    }

    float scale = 0.5f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            for (auto& diceAnimation : diceAnimations) {
                diceAnimation.handleEvent(event, window);
            }
            // Additional event handling for changing the animation speed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // diceAnimation.changeSpeed(-1);
                    // std::cout << "Frame duration: " << diceAnimation.getFrameDuration() << " ms" << std::endl;
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    // diceAnimation.changeSpeed(1);
                    // std::cout << "Frame duration: " << diceAnimation.getFrameDuration() << " ms" << std::endl;
                }
            }
        }
        for (auto& diceAnimation : diceAnimations) {
            scale -= 0.00001f;
            diceAnimation.setScale(scale, scale);
        }

        for (auto& diceAnimation : diceAnimations) {
            diceAnimation.update();
        }
        window.clear();
        for (auto& diceAnimation : diceAnimations) {
            window.draw(diceAnimation);
        }
        window.display();
    }

    return 0;
}