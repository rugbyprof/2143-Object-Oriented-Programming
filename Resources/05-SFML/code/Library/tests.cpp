
#include "grid.h"
#include "slider.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Pad an integer with zeros to ensure it is 3 digits long
 * @param num (int) The number to pad
 * @return (std::string) The padded number as a string
 */
std::string padInt(int num) {
    if (num < 10) {
        return "00" + std::to_string(num);
    }
    if (num < 100) {
        return "0" + std::to_string(num);
    }
    return std::to_string(num);
}

int main() {
    // Create a window with a title and dimensions (800x600)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Knucklebones Game");
    sf::Clock fps_clock;    // SFML clock object to keep track of time
    sf::Clock print_clock;  // SFML clock object to keep track of time

    sf::Font font;
    std::string font_path = "../media/fonts/Arial.ttf";
    if (!font.loadFromFile("../media/fonts/Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    int red   = 255 / 2;  // Random color value for red channel
    int green = 255 / 2;  // Random color value for green channel
    int blue  = 255 / 2;  // Random color value for blue channel

    Grid<int> grid(3, 3, sf::Vector2f(100.f, 100.f), 0, font_path, sf::Color(128, 255, 0), sf::Color(50, 50, 50), 1.f);

    DataRectangle<int> rect(sf::Vector2f(100.f, 100.f), 42, font, sf::Vector2f(400.f, 300.f));

    // RGB Sliders and Text Display
    sf::Text red_text;
    red_text.setFont(font);
    red_text.setCharacterSize(18);
    red_text.setFillColor(sf::Color::Black);
    red_text.setPosition(680.f, 80.f);

    sf::Text green_text;
    green_text.setFont(font);
    green_text.setCharacterSize(18);
    green_text.setFillColor(sf::Color::Black);
    green_text.setPosition(710.f, 80.f);

    sf::Text blue_text;
    blue_text.setFont(font);
    blue_text.setCharacterSize(18);
    blue_text.setFillColor(sf::Color::Black);
    blue_text.setPosition(740.f, 80.f);

    Slider red_slider(700.f, 100.f, 2.f, 400.0f, 0.f, 255.f, 10.f);
    red_slider.setKnobColor(sf::Color::Red);
    Slider green_slider(730.f, 100.f, 2.f, 400.0f, 0.f, 255.f, 10.f);
    green_slider.setKnobColor(sf::Color::Green);
    Slider blue_slider(760.f, 100.f, 2.f, 400.0f, 0.f, 255.f, 10.f);
    blue_slider.setKnobColor(sf::Color::Blue);

    // Main game loop
    while (window.isOpen()) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(10.f, 10.f);

        sf::Time elapsed = fps_clock.restart();         // Restart the clock and return the elapsed time
        float fps        = 1.0f / elapsed.asSeconds();  // Calculate the frames per second
        // std::cout << "FPS: " << fps << std::endl;       // Print the frames per second to console

        if (print_clock.getElapsedTime().asSeconds() > 0.5f) {
            text.setString("FPS: " + std::to_string(fps));  // Set the string to display the frames per seconds
            print_clock.restart();
        }

        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user presses Escape or clicks the close button
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            red_slider.handleEvent(event, window);
            green_slider.handleEvent(event, window);
            blue_slider.handleEvent(event, window);
        }

        red   = red_slider.getValue();
        green = green_slider.getValue();
        blue  = blue_slider.getValue();

        red_text.setString(padInt(red));
        green_text.setString(padInt(green));
        blue_text.setString(padInt(blue));

        // Clear the window with a specific color

        window.clear(sf::Color(red, green, blue));
        window.draw(grid);
        window.draw(red_slider);
        window.draw(green_slider);
        window.draw(blue_slider);
        window.draw(red_text);
        window.draw(green_text);
        window.draw(blue_text);
        window.draw(rect);
        window.draw(text);

        // Display the contents of the window
        window.display();
    }

    return 0;
}