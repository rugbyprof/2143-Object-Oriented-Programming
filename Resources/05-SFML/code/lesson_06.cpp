
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState { Menu, Playing, GameOver };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lesson 6: Game States");

    // Current game state
    GameState currentState = GameState::Menu;

    // Menu text
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
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