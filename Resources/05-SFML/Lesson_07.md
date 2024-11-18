## Lesson 7: User Text Input

Here’s a snippet for an SFML program that lets a user enter their name and displays it at the top of the game screen.

```cpp
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enter Name Example");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return -1;
    }

    // Text objects for instructions and name display
    sf::Text instructionText("Enter your name:", font, 24);
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    sf::Text nameText("", font, 24);
    nameText.setPosition(50, 250);
    nameText.setFillColor(sf::Color::Green);

    sf::Text displayName("", font, 30);
    displayName.setPosition(50, 50);
    displayName.setFillColor(sf::Color::Yellow);

    // Variables for input handling
    std::string userInput;
    bool nameEntered = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!nameEntered) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        // Handle backspace
                        if (!userInput.empty()) {
                            userInput.pop_back();
                        }
                    } else if (event.text.unicode == '\r') {
                        // Handle enter
                        nameEntered = true;
                        displayName.setString("Hello, " + userInput + "!");
                    } else if (event.text.unicode < 128) {
                        // Handle valid characters
                        userInput += static_cast<char>(event.text.unicode);
                    }

                    nameText.setString(userInput);
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the appropriate text
        if (!nameEntered) {
            window.draw(instructionText);
            window.draw(nameText);
        } else {
            window.draw(displayName);
        }

        // Display everything
        window.display();
    }

    return 0;
}
```

### Explanation of the Code

1. Window and Font:
   - The sf::RenderWindow is used to create the game window.
   - A font is loaded for text rendering. Ensure arial.ttf or your chosen font is in the executable directory.
2. Input Handling:
   - When the user types, characters are added to the userInput string.
   - Backspace ('\b') removes the last character.
   - Enter ('\r') sets nameEntered to true and finalizes the input.
3. Rendering:
   - Before the name is finalized, instructions and the current input are displayed.
   - Once the name is finalized, it is displayed at the top of the screen.

### Usage

1. Place an appropriate .ttf font file (like Arial) in the directory.
2. Compile with SFML:

```bash
g++ -o name_entry name_entry.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

3. Run the executable. Type a name, press Enter, and see it displayed!
