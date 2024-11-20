#include "logger_class.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
using namespace std;

/*
   _____ _                _____ _____   _   _  ____ _______   _____   ____  _   _ ______   _ _ _
  / ____| |        /\    / ____/ ____| | \ | |/ __ \__   __| |  __ \ / __ \| \ | |  ____| | | | |
 | |    | |       /  \  | (___| (___   |  \| | |  | | | |    | |  | | |  | |  \| | |__    | | | |
 | |    | |      / /\ \  \___ \\___ \  | . ` | |  | | | |    | |  | | |  | | . ` |  __|   | | | |
 | |____| |____ / ____ \ ____) |___) | | |\  | |__| | | |    | |__| | |__| | |\  | |____  |_|_|_|
  \_____|______/_/    \_\_____/_____/  |_| \_|\____/  |_|    |_____/ \____/|_| \_|______| (_|_|_)

*/

class InputHandler {
    sf::Event event;
    sf::RenderWindow& window;
    sf::Vector2i mouseClickPos;
    sf::Vector2i mouseReleasePos;
    sf::Vector2i mouseMovePos;
    bool mouseClick;
    bool mouseRelease;
    bool mouseMove;
    char enteredChar;             // For storing typed characters
    std::string lastMouseButton;  // Last mouse button clicked
    std::string userInput;        // For storing typed characters
   public:
    InputHandler(sf::RenderWindow& win) : window(win) {
        enteredChar     = ' ';
        userInput       = "";
        lastMouseButton = "";
        mouseClick = mouseMove = mouseRelease = false;
    }
    void text(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {  // Only handle ASCII characters
                enteredChar = static_cast<char>(event.text.unicode);
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
    }

    char getEnteredChar() { return enteredChar; }

    bool shiftKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            // Detect modifier keys (Shift, Control, Alt)
            if (event.key.shift) {
                return true;
            }
        }
        return false;
    }
    bool ctrlKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            // Detect modifier keys (Shift, Control, Alt)
            if (event.key.control) {
                return true;
            }
        }
        return false;
    }
    bool altKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.alt) {
                return true;
            }
        }
        return false;
    }
    bool backspaceKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Backspace) {
                enteredChar = '\b';
                return true;
            }
        }
        return false;
    }
    bool enterKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                return true;
            }
        }
        return false;
    }
    bool escapeKey(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                return true;
            }
        }
        return false;
    }
    bool keyPress(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        // **Key Presses**: Handle specific key events
        if (event.type == sf::Event::KeyPressed) {
            if (event.text.unicode < 128) {  // Only handle ASCII characters
                enteredChar = (char)(event.text.unicode + 'a');
            }
            return true;
        }
        return false;
    }
    bool keyRelease(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        // **Key Releases**: Handle specific key events
        if (event.type == sf::Event::KeyReleased) {
            return true;
        }
        return false;
    }

    sf::Vector2i mouseEvent(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        mouseClickPos   = sf::Vector2i(-1, -1);
        mouseReleasePos = sf::Vector2i(-1, -1);
        mouseMovePos    = sf::Vector2i(-1, -1);

        if (mouseClicked(event) || mouseReleased(event) || mouseMoved(event)) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                lastMouseButton = "Left";
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                lastMouseButton = "Right";
            } else if (event.mouseButton.button == sf::Mouse::Middle) {
                lastMouseButton = "Middle";
            }
        }
        return mouseClickPos;
    }

    bool mouseClicked(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        // **Mouse Input**: Handle mouse button presses
        if (event.type == sf::Event::MouseButtonPressed) {
            mouseClick    = true;
            mouseClickPos = sf::Mouse::getPosition(window);
            return true;
        }
        return false;
    }

    bool mouseReleased(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        // **Mouse Input**: Handle mouse button presses
        if (event.type == sf::Event::MouseButtonReleased) {
            mouseRelease    = true;
            mouseReleasePos = sf::Mouse::getPosition(window);
            return true;
        }
        return false;
    }

    bool mouseMoved(sf::Event inEvent = sf::Event{sf::Event::Count}) {
        if (inEvent.type != sf::Event::Count) {
            event = inEvent;
        }
        // **Mouse Input**: Handle mouse button presses
        if (event.type == sf::Event::MouseMoved) {
            mouseMove    = true;
            mouseMovePos = sf::Mouse::getPosition(window);
            return true;
        }
        return false;
    }

    ~InputHandler() {}
};

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enter Name Example");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    InputHandler input(window);

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
    std::string userInput;           // For storing typed characters
    sf::Vector2i lastMouseClickPos;  // Last mouse click position
    std::string lastMouseButton;     // Last mouse button clicked

    bool nameEntered = false;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (input.escapeKey(event)) {
                window.close();
            }

            if (input.mouseClicked(event)) {
                std::cout << "Mouse clicked at: " << input.mouseEvent().x << ", " << input.mouseEvent().y << '\n';
            }

            if (input.keyPress(event)) {
                if (input.backspaceKey()) {
                    cout << "Backspace key pressed\n";
                    userInput.pop_back();
                } else if (input.enterKey()) {
                    nameEntered = true;
                    displayName.setString("Hello, " + userInput);
                } else {
                    userInput += input.getEnteredChar();
                    std::cout << "User Inputty: " << userInput << std::endl;
                    nameText.setString(userInput);
                }
            }

            // Clear the window
            window.clear(sf::Color::Black);

            // Draw the appropriate text
            // if (!nameEntered) {
            window.draw(inputBox);
            window.draw(instructionText);
            window.draw(nameText);
            // } else {
            //     window.draw(nameText);
            window.draw(displayName);
            //}

            // Display everything
            window.display();
        }
    }
    return 0;
}