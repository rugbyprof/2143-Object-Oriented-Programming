## Dice Game

Here’s a simple class structure and design for a two-player dice game where:

- Each player will roll 1-N dice
- Their scores will accumulate until one of them reaches the predetermined target score

### Class Design Overview

1. **Player**: Represents a player in the game, including the player's current score and the ability to roll dice.
2. **Dice**: Represents a die with the ability to generate a random roll value.
3. **Game**: Manages the overall game flow, including turns, checking for game end conditions, and determining the winner.

---

### **Class: Player**

- The `Player` class keeps track of a player's name and their total score.
- It allows the player to roll the dice and update their score.

```cpp
class Player {
private:
    std::string name;  // Player's name
    int score;         // Player's total score

public:
    // Constructor to initialize player with a name and starting score of 0
    Player(std::string playerName);

    // Roll the dice and update the player's score
    void rollDice(int numberOfDice, Dice& dice);

    // Get the player's current score
    int getScore() const;

    // Get the player's name
    std::string getName() const;

    // Reset the player's score to 0 (for starting a new game)
    void resetScore();
};
```

**Method Descriptions**:

- **`Player(std::string playerName)`**: Constructor that initializes the player's name and sets the initial score to 0.
- **`void rollDice(int numberOfDice, Dice& dice)`**: Rolls `numberOfDice` dice, adds the rolled values to the player's score.
- **`int getScore() const`**: Returns the player's current score.
- **`std::string getName() const`**: Returns the player's name.
- **`void resetScore()`**: Resets the player's score to 0 for a new game.

---

### **Class: Dice**

- The `Dice` class represents a single die.
- It contains methods to roll the die and return a random value between 1 and the number of sides on the die (default to 6 sides).

```cpp
class Dice {
private:
    int sides;  // Number of sides on the die

public:
    // Constructor to initialize the dice with a specified number of sides (default to 6)
    Dice(int numSides = 6);

    // Roll the die and return a random number between 1 and the number of sides
    int roll() const;
};
```

**Method Descriptions**:

- **`Dice(int numSides = 6)`**: Constructor that initializes the dice with the given number of sides (defaults to 6).
- **`int roll() const`**: Rolls the dice and returns a random number between 1 and `sides`.

---

### **Class: Game**

- The `Game` class manages the game flow such as:
  - alternating turns between players
  - checking if a player has won by reaching a predetermined score
  - handling the start and end of the game

```cpp
class Game {
private:
    Player player1;
    Player player2;
    Dice dice;
    int winningScore;  // The score required to win the game

public:
    // Constructor to initialize the game with two players and a winning score
    Game(std::string name1, std::string name2, int targetScore, int diceSides = 6);

    // Start the game and alternate turns between players
    void startGame();

    // Check if a player has reached the winning score
    bool checkForWin(const Player& player) const;

    // Display the current scores of both players
    void displayScores() const;

    // Announce the winner of the game
    void announceWinner(const Player& winner) const;
};
```

**Method Descriptions**:

- **`Game(std::string name1, std::string name2, int targetScore, int diceSides = 6)`**: Initializes the game with two players and a winning score. Also sets the number of dice sides (default to 6).
- **`void startGame()`**: Begins the game loop, alternating between players until one player wins.
- **`bool checkForWin(const Player& player) const`**: Checks if a player has reached or exceeded the winning score.
- **`void displayScores() const`**: Displays the current score of both players.
- **`void announceWinner(const Player& winner) const`**: Announces the winner once the game has concluded.

---

### Example Expansion Ideas:

- **Extend to multiplayer**: Allow more than two players by storing a list of `Player` objects.
- **Customize dice**: Allow each player to roll with different types of dice (e.g., 6-sided, 8-sided, etc.).
- **Penalty rolls**: Introduce penalties for rolling certain values.
- **Rounds and Turn Limits**: Add a limit on the number of rounds or turns.
- **Multilevel scoring**: Award bonus points for certain rolls or combinations.
