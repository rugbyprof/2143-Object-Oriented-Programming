#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// generic fail safe capture input
// all done in the main loop

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Input Handling Example");

    // Variables to store input state
    std::string userInput;           // For storing typed characters
    sf::Vector2i lastMouseClickPos;  // Last mouse click position
    std::string lastMouseButton;     // Last mouse button clicked

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // **Text Input**: Handle typed characters
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {  // Only handle ASCII characters
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b') {  // Backspace handling
                        if (!userInput.empty()) {
                            userInput.pop_back();
                        }
                        std::cout << "Backspace detected. Current input: " << userInput << '\n';
                    } else if (enteredChar == '\r') {  // Enter handling
                        std::cout << "Enter key detected. Final input: " << userInput << '\n';
                        userInput.clear();  // Clear input after pressing Enter
                    } else {
                        userInput += enteredChar;
                        std::cout << "Character entered: " << enteredChar << " | Current input: " << userInput << '\n';
                    }
                }
            }

            // **Key Presses**: Handle specific key events
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) {
                    std::cout << "Backspace key pressed\n";
                } else if (event.key.code == sf::Keyboard::Enter) {
                    std::cout << "Enter key pressed\n";
                } else if (event.key.code == sf::Keyboard::Escape) {
                    std::cout << "Escape key pressed. Exiting.\n";
                    window.close();  // Close the window on Escape
                } else {
                    std::cout << "Key pressed: " << event.key.code << '\n';
                }
            }

            // **Mouse Input**: Handle mouse button presses
            if (event.type == sf::Event::MouseButtonPressed) {
                lastMouseClickPos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    lastMouseButton = "Left";
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    lastMouseButton = "Right";
                } else if (event.mouseButton.button == sf::Mouse::Middle) {
                    lastMouseButton = "Middle";
                }
                std::cout << "Mouse " << lastMouseButton << " button clicked at position: " << lastMouseClickPos.x << ", "
                          << lastMouseClickPos.y << '\n';
            }

            // **Mouse Input**: Handle mouse button releases
            if (event.type == sf::Event::MouseButtonReleased) {
                std::cout << "Mouse " << lastMouseButton << " button released\n";
            }

            // **Mouse Movement**: Handle mouse movement
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                std::cout << "Mouse moved to: " << mousePos.x << ", " << mousePos.y << '\n';
            }
        }

        // Clear the window and display
        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}