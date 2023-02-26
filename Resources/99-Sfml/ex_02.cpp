#include <SFML/Graphics.hpp>

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");

    // Set up the ball
    sf::CircleShape ball(50.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400.f, 300.f);
    float dx = 5.f;
    float dy = 5.f;

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Move the ball
        ball.move(dx, dy);

        // Bounce off walls
        if (ball.getPosition().x <= 0 || ball.getPosition().x >= 800 - ball.getRadius() * 2) {
            dx = -dx;
        }
        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 600 - ball.getRadius() * 2) {
            dy = -dy;
        }

        // Clear the window
        window.clear();

        // Draw the ball
        window.draw(ball);

        // Display the window
        window.display();
    }

    return 0;
}
