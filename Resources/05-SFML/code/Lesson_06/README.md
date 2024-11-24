## Lesson 6: Handling Game States

### Objective:

Learn how to manage game states in SFML to control the flow of a game. This lesson introduces the concept of game states (e.g., menu, playing, paused, game over) and how to structure your program to switch between them dynamically.

### Key Concepts

1. Game States:
   - Represent the different stages of a game (e.g., menu, playing, paused).
   - Use an enumeration or constants to define these states.
2. State Management:
   - Implement logic to switch between states and execute state-specific behavior.
3. Separation of Concerns:
   - Keep the code for each state isolated to avoid clutter.

## Code Example: Basic Game States

This example introduces a game with three states: Menu, Playing, and GameOver.

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState {
    Menu,
    Playing,
    GameOver
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 6: Game States");

    // Current game state
    GameState currentState = GameState::Menu;

    // Menu text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }
    sf::Text menuText("Press Enter to Play", font, 30);
    menuText.setFillColor(sf::Color::Black);
    menuText.setPosition(250.f, 250.f);

    sf::Text gameOverText("Game Over! Press R to Restart", font, 30);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(150.f, 250.f);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // State-specific input handling
            if (currentState == GameState::Menu) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    currentState = GameState::Playing;
                }
            } else if (currentState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::GameOver;
                }
            } else if (currentState == GameState::GameOver) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    currentState = GameState::Menu;
                }
            }
        }

        // Render based on state
        window.clear(sf::Color::White);

        if (currentState == GameState::Menu) {
            window.draw(menuText);
        } else if (currentState == GameState::Playing) {
            // Placeholder for game logic
            sf::CircleShape player(50.f);
            player.setFillColor(sf::Color::Blue);
            player.setPosition(300.f, 300.f);
            window.draw(player);
        } else if (currentState == GameState::GameOver) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
```

## Explanation

### Game States

- GameState::Menu: Display a menu screen with instructions.
- GameState::Playing: Simulate gameplay with a placeholder object (a circle).
- GameState::GameOver: Show a “Game Over” screen with an option to restart.

### State Transitions

- Menu to Playing: Press Enter.
- Playing to Game Over: Press Escape.
- Game Over to Menu: Press R.

### State-Specific Logic

- Each state has its own rendering and input logic.
- For example:
  - `GameState::Menu` displays menu text and listens for the Enter key.
  - `GameState::Playing` contains game objects like a player character.
  - `GameState::GameOver` displays “Game Over” text and waits for a restart command.

### Activity

1. Add a Pause State:
   - Introduce a new `GameState::Paused` that activates when the player presses P during gameplay.
   - Display a “Paused” message and resume the game with R.
2. Animate Transitions:
   - Add a fade-in/out effect when switching between states using `sf::Clock`.
3. Handle Multiple Keys:
   - Allow keys like `W, A, S, D `to control the player in the Playing state.

### Discussion Questions

1. How can you structure the program to load assets (e.g., fonts, textures) only once for all states?
2. What additional states might be useful for Knucklebones (e.g., Player Turn, Dice Roll)?
3. How would you prevent accidental state transitions from multiple key presses?

### Expected Output

1. A simple menu with instructions (Press Enter to Play).
2. A gameplay screen with a blue circle.
3. A “Game Over” screen with restart instructions (Press R to Restart).

This lesson lays the groundwork for managing the flow of Knucklebones.
