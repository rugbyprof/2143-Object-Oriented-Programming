## Lectures L01 - SFML

```cpp
// Get the size of your current window.
sf::Vector2u size = window.getSize();
unsigned int width = size.x;
unsigned int height = size.y;

// set the absolute position of the entity
entity.setPosition(10, 50);

// move the entity relatively to its current position
entity.move(5, 5);

// retrieve the absolute position of the entity
sf::Vector2f position = entity.getPosition(); // = (15, 55)


```