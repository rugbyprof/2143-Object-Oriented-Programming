#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

/**
 * A class to represent a slider: a bar with a knob that can be dragged along the bar to select a value within a range.
 * The slider can be horizontal or vertical and the knob can be dragged along the track to select a value.
 * The slider can be used to control volume, brightness, etc.
 *
 * The slider has the following properties:
 * - track: The bar that acts as the slider track
 * - knob: The draggable circle
 * - radius: The radius of the knob (its size) (default 10)
 * - minValue: The minimum value of the slider (default 0)
 * - maxValue: The maximum value of the slider (default 100)
 * - left: The left bound of the track
 * - right: The right bound of the track
 * - value: The current value of the slider (location of the knob)
 * - isDragging: Flag to indicate if the knob is being dragged (mouse button pressed)
 * - horizontal: Flag to indicate if the slider is horizontal or vertical
 * Example Usage:
 *      Slider slider(200.f, 300.f, 400.f, 3.0f, 0.f, 100.f, 10.f);
 *      ...
 *      while (window.isOpen()) {
 *          sf::Event event;
 *          while (window.pollEvent(event)) {
 *              slider.handleEvent(event, window);
 *          ...
 *          }
 * *       float volume = slider.getValue();
 *         music.setVolume(volume);
 *      }

 *
 */
class Slider : public sf::Drawable {
   private:
    sf::RectangleShape track;  // The bar that acts as the slider track
    sf::CircleShape knob;      // The draggable circle
    float radius;              // The radius of the knob (its size) (default 10)
    float minValue;            // The minimum value of the slider (default 0)
    float maxValue;            // The maximum value of the slider (default 100)
    float left;                // The left bound of the track
    float right;               // The right bound of the track
    float top;                 // The top bound of the track
    float bottom;              // The bottom bound of the track
    float value;               // The current value of the slider (location of the knob)
    bool isDragging;           // Flag to indicate if the knob is being dragged (mouse button pressed)
    bool horizontal;           // Flag to indicate if the slider is horizontal or vertical

    // Overriding the draw method from sf::Drawable to draw the track and the knob
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        // Draw the rectangle first
        target.draw(track, states);
        target.draw(knob, states);
    }

    float clicktoValue(float mouseX, float mouseY) {
        if (horizontal) {
            return minValue + ((mouseX - left) / track.getSize().x) * (maxValue - minValue);
            // If the slider is vertical do the same as above but for the y-axis
        } else {
            return minValue + ((mouseY - top) / track.getSize().y) * (maxValue - minValue);
        }
    }

   public:
    Slider() {
    }  // Default constructor
    Slider(float x, float y, float width, float height, float min, float max, float radius)
        : minValue(min), maxValue(max), value(min), isDragging(false) {
        // Configure the track
        track.setSize(sf::Vector2f(width, height));
        track.setFillColor(sf::Color::White);
        track.setOutlineColor(sf::Color::Black);
        track.setPosition(x, y);

        // Calculate the horizontal bounds of the track
        left  = track.getPosition().x;
        right = left + track.getSize().x;
        // Calculate the vertical bounds of the track
        top    = track.getPosition().y;
        bottom = top + track.getSize().y;

        // Configure the knob
        knob.setRadius(radius);
        knob.setFillColor(sf::Color::Red);
        knob.setOrigin(knob.getRadius(), knob.getRadius());

        if (width > height) {
            horizontal = true;
        } else {
            horizontal = false;
        }

        // std::cout << "Horizontal: " << horizontal << std::endl;

        if (horizontal) {
            knob.setPosition(x, y + track.getSize().y / 2);
        } else {
            knob.setPosition(x + track.getSize().x / 2, y);
        }

        // Set initial value
        setValue(min + max / 2);
    }

    void setKnobColor(const sf::Color& color) {
        knob.setFillColor(color);
    }

    /**
     * Handle events for the slider
     * @param event The event to handle
     * @param window The window to handle the event for
     * @return void
     * @note This function is called in the main game loop
     * Event Types:
     *  - MouseButtonPressed
     *  - MouseButtonReleased
     *  - MouseMoved
     */
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
        float mouseX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
        float mouseY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;
        // If Mouse Button Pressed Down
        if (event.type == sf::Event::MouseButtonPressed) {
            if (knob.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
            } else if (track.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                setValue(clicktoValue(mouseX, mouseY));
            }
            // If Mouse Button Released
        } else if (event.type == sf::Event::MouseButtonReleased) {
            isDragging = false;
            // If Mouse Moving and isDragging is true (mouse button pressed)
        } else if (event.type == sf::Event::MouseMoved && isDragging) {
            // If the slider is horizontal calculate the "value" based on the mouse position
            // such that the knob moves along the track and stays within the track bounds
            setValue(clicktoValue(mouseX, mouseY));
        }
    }

    // void draw(sf::RenderTarget& target) const {
    //     target.draw(track);
    //     target.draw(knob);
    // }

    float getValue() const {
        return value;
    }

    /**
     * Set the value of the slider
     * @param newValue The new value to set the slider to
     * @return void
     * @note This function is called in the main game loop
     */
    void setValue(float newValue) {
        if (newValue < minValue)
            newValue = minValue;
        if (newValue > maxValue)
            newValue = maxValue;

        value = newValue;

        if (horizontal) {
            // Update knob position based on value
            float left      = track.getPosition().x;
            float right     = left + track.getSize().x;
            float positionX = left + ((value - minValue) / (maxValue - minValue)) * (right - left);
            knob.setPosition(positionX, knob.getPosition().y);
        } else {
            // Update knob position based on value
            float top       = track.getPosition().y;
            float bottom    = top + track.getSize().y;
            float positionY = top + ((value - minValue) / (maxValue - minValue)) * (bottom - top);
            knob.setPosition(knob.getPosition().x, positionY);
        }
    }
};
