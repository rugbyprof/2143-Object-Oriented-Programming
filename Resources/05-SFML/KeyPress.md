## Key Press

SFML handles key presses in two ways: event-based key handling and real-time key state checking. The issue you’re describing—where a single key press registers multiple times—is common when relying on event-based key handling (KeyPressed) without proper handling of key repeat events.

Here’s how SFML deals with this and how you can solve the issue:

## Understanding Key Repeats

1. Key Repeats:
   - By default, SFML generates multiple KeyPressed events when a key is held down. This behavior is called key repeat and mimics how keyboards work (e.g., holding down a key in a text editor).
   - If you want to treat each key press as a single action, you’ll need to disable key repeats or handle it manually.
2. KeyReleased Events:
   - SFML generates a KeyReleased event only once when a key is released. Using this event can help distinguish between intentional single presses and repeated presses.

### Solution 1: Disable Key Repeat

You can disable key repeat for the window using `sf::Window::setKeyRepeatEnabled`:

```cpp
window.setKeyRepeatEnabled(false);
```

This ensures that only a single KeyPressed event is registered when the key is initially pressed, even if the key is held down.

Updated Code

```cpp
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
sf::RenderWindow window(sf::VideoMode(800, 600), "Key Repeat Disabled");
window.setKeyRepeatEnabled(false); // Disable key repeat

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        circle.move(-10.f, 0.f);
                        break;
                    case sf::Keyboard::Right:
                        circle.move(10.f, 0.f);
                        break;
                    case sf::Keyboard::Up:
                        circle.move(0.f, -10.f);
                        break;
                    case sf::Keyboard::Down:
                        circle.move(0.f, 10.f);
                        break;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }

    return 0;

}
```

### Solution 2: Use KeyReleased Events

Instead of responding to `KeyPressed`, respond to `KeyReleased`. This ensures the action is triggered only after the key is released, avoiding repeated events.

### Updated Code

```cpp
if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
    case sf::Keyboard::Left:
        circle.move(-10.f, 0.f);
        break;
    case sf::Keyboard::Right:
        circle.move(10.f, 0.f);
        break;
    case sf::Keyboard::Up:
        circle.move(0.f, -10.f);
        break;
    case sf::Keyboard::Down:
        circle.move(0.f, 10.f);
        break;
    }
}
```

### Solution 3: Track Key State

If you want more control over how often an action is performed (e.g., throttling input), you can manually track whether a key is currently pressed using a `std::map` or `std::set`.

### Example: Single Action Per Press

```cpp
#include <SFML/Graphics.hpp>
#include <set>

int main() {
sf::RenderWindow window(sf::VideoMode(800, 600), "Track Key State");
sf::CircleShape circle(50.f);
circle.setFillColor(sf::Color::Green);
circle.setPosition(300.f, 300.f);

    std::set<sf::Keyboard::Key> activeKeys;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (activeKeys.find(event.key.code) == activeKeys.end()) {
                    activeKeys.insert(event.key.code); // Mark the key as active

                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            circle.move(-10.f, 0.f);
                            break;
                        case sf::Keyboard::Right:
                            circle.move(10.f, 0.f);
                            break;
                        case sf::Keyboard::Up:
                            circle.move(0.f, -10.f);
                            break;
                        case sf::Keyboard::Down:
                            circle.move(0.f, 10.f);
                            break;
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                activeKeys.erase(event.key.code); // Mark the key as released
            }
        }

        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }

    return 0;

}
```

### Comparison of Solutions

| Approach           | When to Use                                                                   |
| :----------------- | :---------------------------------------------------------------------------- |
| Disable Key Repeat | For simple single-action responses (e.g., moving one step at a time).         |
| Use KeyReleased    | When you want actions to occur only after the key is released.                |
| Track Key State    | When you need granular control over key states, especially for complex input. |

### Recommendation

For your Knucklebones project:

- Use Solution 1 (disable key repeat) if you want simple, step-based input.
- Use Solution 3 (track key state) if you anticipate complex interactions, like simultaneous key presses or a mix of keyboard and mouse input.

Let me know which approach works best for your project!
