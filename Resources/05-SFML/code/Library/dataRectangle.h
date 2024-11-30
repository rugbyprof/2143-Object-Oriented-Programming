#pragma once
#include "sprixture.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Templated type for the value stored in the rectangle
/**
 *
 * Example:
 * DataRectangle<int> rect(sf::Vector2f(100.f, 100.f), 42, "arial.ttf", sf::Vector2f(0.f, 0.f));
 */
class DataRectangle : public sf::Drawable {
   private:
    std::string value;        // Custom value to store
    sf::RectangleShape rect;  // Rectangle shape
    sf::Text valueText;       // Text to display the value
    sf::Font* font;           // Font for the text
    sf::Vector2f size;        // Size of the rectangle
    sf::Vector2f pos;         // Position of the rectangle
    sf::Sprite sprite;        // Optional sprite
    bool hasSprite = false;   // Flag to check if a sprite is used
    bool noText    = false;   // Flag to check if text is used

    // Custom draw method
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(rect, states);  // Draw the rectangle
        if (hasSprite) {
            target.draw(sprite, states);  // Draw the sprite
        }
        target.draw(valueText, states);  // Draw the value text
    }

    void init(const sf::Font& sharedFont) {
        if (font != nullptr) {
            font = const_cast<sf::Font*>(&sharedFont);  // Store a reference to the shared font
        }
        rect.setPosition(pos);
        rect.setSize(size);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.f);
    }
    // (sf::Vector2f, const sf::Vector2f, sf::Font, sf::Sprite)
   public:
    DataRectangle(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, const std::string& value = "null")
        : size(size), pos(pos), font(const_cast<sf::Font*>(&font)), value(value) {
        init(font);
        initText(value);  // Initialize text with the provided or default value
    }

    DataRectangle(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, sf::Sprite& sprite, float scale, const std::string& value = "null")
        : size(size), pos(pos), font(const_cast<sf::Font*>(&font)), value(value), sprite(sprite), hasSprite(true), noText(true) {
        init(font);
        sprite.scale(scale, scale);

        std::cout << "Sprite: " << size.x << " " << sprite.getGlobalBounds().width << size.y << " " << sprite.getGlobalBounds().height
                  << std::endl;
    }
    // std::string& initialValue, Sprixture& spright

    sf::FloatRect getGlobalBounds() const {
        return rect.getGlobalBounds();
    }

    void initText(const std::string& value) {
        valueText = sf::Text(value, *font, 16);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(rect.getPosition().x + rect.getSize().x / 2 - valueText.getLocalBounds().width / 2,
                              rect.getPosition().y + rect.getSize().y / 2 - valueText.getLocalBounds().height / 2);
        sf::Vector2f vt = valueText.getPosition();
        // std::cout << "Rect: " << rect.getPosition().x << " " << rect.getPosition().y << std::endl;
        // std::cout << "VT: " << vt.x << " " << vt.y << std::endl;
    }

    void setFillColor(const sf::Color& color) {
        rect.setFillColor(color);
    }
    void setOutlineColor(const sf::Color& color) {
        rect.setOutlineColor(color);
    }
    void setOutlineThickness(float thickness) {
        rect.setOutlineThickness(thickness);
    }
    void setFont(sf::Font& newFont) {
        font = &newFont;
        valueText.setFont(*font);
    }

    void setCharacterSize(unsigned int size) {
        valueText.setCharacterSize(size);
    }
    void setTextColor(const sf::Color& color) {
        valueText.setFillColor(color);
    }

    void setValue(const std::string& value) {
        valueText.setString(value);
    }

    void setSprite(const sf::Sprite& newSprite) {
        sprite    = newSprite;
        hasSprite = true;
        noText    = true;
        sprite.setScale(rect.getSize().x / sprite.getGlobalBounds().width,
                        rect.getSize().y / sprite.getGlobalBounds().height);  // Scale to fit
    }
    const sf::Text& getValueText() const {
        return valueText;
    }

    const std::string& getValue() const {
        return value;
    }

    sf::Vector2f getPos() const {
        return sf::Vector2f(size.x, size.y);
    }

    // Set the position of the rectangle and align the text
    void setPosition(float x, float y) {
        rect.setPosition(x, y);

        // Center the text within the rectangle
        sf::FloatRect rectBounds = rect.getGlobalBounds();
        sf::FloatRect textBounds = valueText.getLocalBounds();
        valueText.setPosition(rectBounds.left + (rectBounds.width - textBounds.width) / 2 - textBounds.left,
                              rectBounds.top + (rectBounds.height - textBounds.height) / 2 - textBounds.top);
        if (hasSprite) {
            sprite.setPosition(x, y);
            sprite.setScale(10.0f, 10.0f);
        }
    }

   private:
    // Update the text to reflect the current value
    void updateText() {
        valueText.setString(value);
    }
};