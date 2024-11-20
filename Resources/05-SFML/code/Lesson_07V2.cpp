#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// 11:00 class

using namespace std;

class InputHandler {
    sf::RenderWindow& window;
    string userInput;
    sf::Vector2i lastMouseClickPos;
    string lastMouseButton;
    char enteredChar;

   public:
    InputHandler(sf::RenderWindow& win) : window(win) {
        userInput       = "";
        lastMouseButton = "";
        enteredChar     = ' ';
    }
    char getTextEntered(sf::Event e) {
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode < 128) {
                enteredChar = static_cast<char>(e.text.unicode);
                return enteredChar;
            }
        }
        return ' ';
    }
    string getUserInput() { return userInput; }
    void putUserInput(char c) { userInput += c; }
    bool textEntered(sf::Event e) {
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode < 128) {
                return true;
            }
        }
        return false;
    }
    bool enterKey(sf::Event e) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Enter) {
                return true;
            }
        }
        return false;
    }
    bool backspaceKey(sf::Event e) {
        if (e.type == sf::Event::TextEntered) {
            if (e.text.unicode < 128) {
                char enteredChar = static_cast<char>(e.text.unicode);
                return backspaceKey(enteredChar);
            }
        }
        return false;
    }
    // bool enterKey(char c) {
    //     if (c == '\r') {
    //         return true;
    //     }
    //     return false;
    // }
    bool backspaceKey(char c) {
        if (c == '\b') {
            return true;
        }
        return false;
    }
    void clearInput() { userInput.clear(); }
};

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Input Handling Example");

    InputHandler input(window);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    // Text objects for instructions and name display
    sf::Text instructionText("Enter your name:", font, 24);
    instructionText.setPosition(50, 250);
    instructionText.setFillColor(sf::Color::White);

    sf::RectangleShape inputBox(sf::Vector2f(250, 30));
    inputBox.setPosition(250, 250);
    inputBox.setFillColor(sf::Color::Black);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);

    sf::Text nameText("", font, 24);
    nameText.setPosition(250, 250);
    nameText.setFillColor(sf::Color::Green);

    sf::Text displayName("", font, 30);
    displayName.setPosition(50, 50);
    displayName.setFillColor(sf::Color::Yellow);

    // Variables to store input state
    string userInput;                // For storing typed characters
    sf::Vector2i lastMouseClickPos;  // Last mouse click position
    string lastMouseButton;          // Last mouse button clicked

    bool nameEntered = false;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (input.textEntered(event)) {
                input.putUserInput(input.getTextEntered(event));  // updating the class
                nameText.setString(input.getUserInput());         // grabbing it for display
            }

            if (input.enterKey(event)) {
                cout << "hit enter key" << endl;
                displayName.setString("Hello: " + input.getUserInput());
                nameEntered = true;
            }
            // // **Text Input**: Handle typed characters
            // if (event.type == sf::Event::TextEntered) {
            //     if (event.text.unicode < 128) {  // Only handle ASCII characters
            //         char enteredChar = static_cast<char>(event.text.unicode);
            //         if (enteredChar == '\b') {  // Backspace handling
            //             if (!userInput.empty()) {
            //                 userInput.pop_back();
            //             }
            //             cout << "Backspace detected. Current input: " << userInput << '\n';
            //         } else if (enteredChar == '\r') {  // Enter handling
            //             cout << "Enter key detected. Final input: " << userInput << '\n';
            //             userInput.clear();  // Clear input after pressing Enter
            //         } else {
            //             userInput += enteredChar;
            //             cout << "Character entered: " << enteredChar << " | Current input: " << userInput << '\n';
            //         }
            //     }
            // }

            // **Key Presses**: Handle specific key events
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) {
                    cout << "Backspace key pressed\n";
                    // } else if (event.key.code == sf::Keyboard::Enter) {
                    //     cout << "Enter key pressed\n";
                    //     cout << "Final Input: " << input.getUserInput() << '\n';
                    //     // input.clearInput();
                } else if (event.key.code == sf::Keyboard::Escape) {
                    cout << "Escape key pressed. Exiting.\n";
                    window.close();  // Close the window on Escape
                } else {
                    cout << "Key pressed: " << event.key.code << '\n';
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
                cout << "Mouse " << lastMouseButton << " button clicked at position: " << lastMouseClickPos.x << ", " << lastMouseClickPos.y
                     << '\n';
            }

            // **Mouse Input**: Handle mouse button releases
            if (event.type == sf::Event::MouseButtonReleased) {
                cout << "Mouse " << lastMouseButton << " button released\n";
            }

            // **Mouse Movement**: Handle mouse movement
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                cout << "Mouse moved to: " << mousePos.x << ", " << mousePos.y << '\n';
            }

            // window.draw(inputBox);
            // // Clear the window

            // // Draw the appropriate text
            // // if (!nameEntered) {
            // window.draw(inputBox);
            // window.draw(instructionText);
            // window.draw(nameText);

            // window.draw(displayName);

            // // Display everything
            // window.display();
        }

        // Clear the window and display
        window.clear(sf::Color::Black);
        if (!nameEntered) {
            window.draw(inputBox);
            window.draw(instructionText);
            window.draw(nameText);
        } else {
            window.draw(displayName);
        }

        // Clear the window

        // Draw the appropriate text
        // if (!nameEntered) {

        window.display();
    }

    return 0;
}