#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>

using namespace std;

// 12:00

sf::Color getRandomColor() {
    // Seed the random number generator with a random device
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Define a range for the color channels (0-255)
    std::uniform_int_distribution<int> dist(0, 255);

    // Generate random RGB values
    int red   = dist(gen);
    int green = dist(gen);
    int blue  = dist(gen);

    // Return a random color
    return sf::Color(red, green, blue);
}

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
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Backspace) {
                return true;
            }
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
    instructionText.setFillColor(getRandomColor());

    sf::RectangleShape inputBox(sf::Vector2f(250, 30));
    inputBox.setPosition(250, 250);
    inputBox.setFillColor(getRandomColor());
    inputBox.setOutlineColor(getRandomColor());
    inputBox.setOutlineThickness(2);

    sf::Text nameText("", font, 24);
    nameText.setPosition(250, 250);
    nameText.setFillColor(getRandomColor());

    vector<sf::Text> nameTexts;

    sf::Text displayName("", font, 30);
    displayName.setPosition(50, 50);
    displayName.setFillColor(getRandomColor());

    // Variables to store input state
    string userInput;                // For storing typed characters
    sf::Vector2i lastMouseClickPos;  // Last mouse click position
    string lastMouseButton;          // Last mouse button clicked

    bool nameEntered = false;

    int xcharpos = 250;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Handle window close
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // meat and potatoes

            if (input.textEntered(event)) {
                char ch = input.getTextEntered(event);
                nameTexts.push_back(sf::Text(ch, font, 24));
                nameTexts.back().setPosition(xcharpos, 250);
                xcharpos += 24;
                nameTexts.back().setFillColor(getRandomColor());
                input.putUserInput(ch);
                cout << "input: " << input.getUserInput() << endl;
                nameText.setString(input.getUserInput());
            }

            if (input.enterKey(event)) {
                displayName.setString("Hello:" + input.getUserInput() + "!!!");
                nameEntered = true;
                input.clearInput();
            }
            // end meat and potatoes

            // **Key Presses**: Handle specific key events
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) {
                    cout << "Backspace key pressed\n";
                } else if (event.key.code == sf::Keyboard::Enter) {
                    cout << "Enter key pressed\n";
                    cout << "Final Input: " << input.getUserInput() << '\n';
                    // input.clearInput();
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
        }

        // Clear the window and display
        // added in class to handle input
        window.clear(sf::Color::Black);
        if (!nameEntered) {
            window.draw(instructionText);
            window.draw(inputBox);
            // window.draw(nameText);
            for (auto const& a : nameTexts) {
                window.draw(a);
            }
        } else {
            window.draw(displayName);
        }

        window.display();
    }

    return 0;
}