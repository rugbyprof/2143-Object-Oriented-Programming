#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Templated type for the value stored in the rectangle
/**
 *
 * Example:
 * DataRectangle<int> rect(sf::Vector2f(100.f, 100.f), 42, "arial.ttf", sf::Vector2f(0.f, 0.f));
 */
template <typename T>
class DataRectangle : public sf::Drawable {
   private:
    T value;                  // Custom value to store
    sf::RectangleShape rect;  // Rectangle shape
    sf::Text valueText;       // Text to display the value
    sf::Font* font;           // Font for the text
    sf::Vector2f size;        // Size of the rectangle
    sf::Vector2f pos;         // Position of the rectangle

    // Custom draw method
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(rect, states);       // Draw the rectangle
        target.draw(valueText, states);  // Draw the value text
    }

   public:
    // Constructor
    DataRectangle(const sf::Vector2f& rectSize, const T& initialValue, const sf::Font& sharedFont, sf::Vector2f pos)
        : size(rectSize), value(initialValue), pos(pos) {
        font = const_cast<sf::Font*>(&sharedFont);  // Store a reference to the shared font
        rect.setPosition(pos.x, pos.y);
        rect.setSize(size);
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.f);

        initText(value);
    }

    sf::FloatRect getGlobalBounds() const { return rect.getGlobalBounds(); }

    void initText(T& value) {
        valueText = sf::Text(std::to_string(value), *font, 16);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(rect.getPosition().x + rect.getSize().x / 2 - valueText.getLocalBounds().width / 2,
                              rect.getPosition().y + rect.getSize().y / 2 - valueText.getLocalBounds().height / 2);
        sf::Vector2f vt = valueText.getPosition();
        std::cout << "Rect: " << rect.getPosition().x << " " << rect.getPosition().y << std::endl;
        std::cout << "VT: " << vt.x << " " << vt.y << std::endl;
    }

    void setFillColor(const sf::Color& color) { rect.setFillColor(color); }
    void setOutlineColor(const sf::Color& color) { rect.setOutlineColor(color); }
    void setOutlineThickness(float thickness) { rect.setOutlineThickness(thickness); }
    void setFont(const sf::Font& newFont) {
        font = &newFont;
        valueText.setFont(*font);
    }
    void setCharacterSize(unsigned int size) { valueText.setCharacterSize(size); }
    void setTextColor(const sf::Color& color) { valueText.setFillColor(color); }

    // Setter for the value
    void setValue(const T& newValue) {
        value = newValue;
        updateText();
    }

    // Getter for the value
    T getValue() const { return value; }

    sf::Vector2f getPos() const { return sf::Vector2f(size.x, size.y); }

    // Set the position of the rectangle and align the text
    void setPosition(float x, float y) {
        rect.setPosition(x, y);

        // Center the text within the rectangle
        sf::FloatRect rectBounds = rect.getGlobalBounds();
        sf::FloatRect textBounds = valueText.getLocalBounds();
        valueText.setPosition(rectBounds.left + (rectBounds.width - textBounds.width) / 2 - textBounds.left,
                              rectBounds.top + (rectBounds.height - textBounds.height) / 2 - textBounds.top);
    }

   private:
    // Update the text to reflect the current value
    void updateText() { valueText.setString(std::to_string(value)); }
};