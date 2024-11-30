#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

struct Sprixture : public sf::Drawable {
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(sprite, states);
    }

    sf::Texture texture;
    sf::Sprite sprite;
    bool clicked = false;
    Sprixture() {
    }
    Sprixture(std::string imgPath) {
        if (!texture.loadFromFile(imgPath)) {
            std::cerr << "Error: Could not load sprite texture." << std::endl;
            return;
        }
        std::cout << "Texture loaded" << std::endl;
        sprite.setTexture(texture);
    }
    Sprixture(sf::Sprite sprite) : sprite(sprite) {
        texture = *sprite.getTexture();
    }

    Sprixture(sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    void setScale(float x, float y) {
        sprite.setScale(x, y);
    }
    bool isClicked() {
        return clicked;
    }
    void unClick() {
        clicked = false;
    }
    sf::Sprite getSprite() {
        return sprite;
    }
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                // std::cout << "Button clicked!" << std::endl;
                clicked = true;
            } else {
                clicked = false;
            }
        }
    }
};