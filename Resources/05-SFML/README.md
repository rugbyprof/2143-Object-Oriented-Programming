## Lesson 1: Setting Up the Game Window

#### Goal: Understand how to create and manage an SFML window.

- Creating an SFML window (sf::RenderWindow).
- Handling basic events (e.g., window close).
- Setting up a game loop.
- Activity:
- Create a game window titled “Knucklebones.”
- Close the window when the user presses the Escape key.

## Lesson 2: Drawing Shapes and Textures

#### Goal: Learn to draw basic shapes and use textures.

- Drawing sf::RectangleShape, sf::CircleShape, and sf::Sprite.
- Loading and displaying a texture (e.g., a dice face image).
- Activity:
- Display a textured dice face in the center of the game window.

## Lesson 3: Capturing and Handling User Input

#### Goal: Understand how to capture mouse and keyboard input.

- Detecting mouse clicks and keyboard presses.
- Using sf::Event for real-time interaction.
- Activity:
- Allow the user to “click” on a dice face to simulate rolling the dice (e.g., display a random dice face).

## Lesson 4: Animations in SFML

#### Goal: Create basic animations using SFML’s tools.

- Using sf::Clock to manage frame timing.
- Loading and displaying a sequence of images (e.g., animated dice roll).
- Activity:
- Animate the dice roll by cycling through a sequence of frames before displaying the final result.

## Lesson 5: Drawing the Game Grid

#### Goal: Build the game board for Knucklebones.

- Drawing a grid using sf::RectangleShape.
- Positioning shapes and sprites in the grid.
- Activity:
- Create a 3x3 grid to represent one player’s game board.

## Lesson 6: Handling Game States

#### Goal: Introduce game state management.

- Defining and transitioning between states (e.g., Start, Player Turn, Game Over).
- Using enums or simple state management techniques.
- Activity:
- Display a “Start Game” screen, then transition to the game grid when the user presses a key.

## Lesson 7: Managing Text and Fonts

#### Goal: Display text for scores, player names, and instructions.

- Loading and using custom fonts (sf::Font).
- Drawing and updating sf::Text objects.
- Activity:
- Display player names and scores above each grid in the game.

## Lesson 8: Working with Sounds and Music

#### Goal: Add sound effects for dice rolls and game interactions.

- Loading and playing sound effects using sf::Sound and sf::SoundBuffer.
- Adding background music using sf::Music.
- Activity:
- Play a sound when the dice is rolled and another when a dice is placed in the grid.

## Lesson 9: Implementing Game Logic

#### Goal: Code the basic rules and mechanics of Knucklebones.

- Placing dice in the grid based on player input.
- Scoring system and dice multipliers.
- Switching turns between players.
- Activity:
- Implement dice placement and scoring rules, allowing turns to alternate.

## Lesson 10: Adding Polish and Finishing Touches

#### Goal: Complete the game with additional features and polish.

- Adding transitions (e.g., fade in/out effects).
- Implementing a simple menu system (e.g., Start, Restart, Quit).
- Improving visuals with animations and effects.
- Activity:
- Finalize the game, ensuring all features are implemented.
- Add a “Game Over” screen with the option to restart or quit.
