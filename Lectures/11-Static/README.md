Below is an example of a C++ class representing a dice, where the class has a static data member and a static method to access or modify it. This way, the dice can be shared and accessed globally by all instances.

### Code Example:

```cpp
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

class Dice {
private:
    // Static data member to represent the dice roll
    static int lastRoll;

public:
    // Static method to roll the dice and update the last roll
    static int roll() {
        lastRoll = (std::rand() % 6) + 1;  // Generates a number between 1 and 6
        return lastRoll;
    }

    // Static method to get the last rolled value
    static int getLastRoll() {
        return lastRoll;
    }
};

// Initialize the static member outside the class
int Dice::lastRoll = 0;

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Roll the dice using the static method
    std::cout << "Rolling the dice: " << Dice::roll() << std::endl;
    std::cout << "Last roll was: " << Dice::getLastRoll() << std::endl;

    // Another roll
    std::cout << "Rolling the dice again: " << Dice::roll() << std::endl;
    std::cout << "Last roll was: " << Dice::getLastRoll() << std::endl;

    return 0;
}
```

### Explanation:

- **Static Data Member (`lastRoll`)**:
  - `lastRoll` keeps track of the last value that was rolled. Since it's static, this value is shared among all instances of the `Dice` class (or even without any instance). It exists globally for the class.
- **Static Methods (`roll()` and `getLastRoll()`)**:
  - `roll()` is a static method that simulates rolling a six-sided dice. It updates the `lastRoll` variable and returns the new value.
  - `getLastRoll()` returns the value of `lastRoll`, which is the most recent roll of the dice.

### Output Example:

```
Rolling the dice: 4
Last roll was: 4
Rolling the dice again: 2
Last roll was: 2
```

Since `lastRoll` is a static member, it will persist across all accesses, even if you had multiple instances of the `Dice` class. However, in this case, we're not even creating instances of the class, and we're just accessing the static methods directly using the class name.

---

What if we wanted the `Dice` class to remember everyone's history? To do so we can modify the `Dice` class to store the history of rolls for each player by using a `std::map` or `std::unordered_map`, where the key is the player's ID (e.g., username), and the value is a list or vector of rolls.

First we need a `Player` class that interacts with the `Dice` class, passing the player's ID to track individual roll histories.

### Player and Dice Tracking Rolls by Username:

```cpp
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <map>
#include <vector>
#include <string>

class Dice {
private:
    // Static map to store the roll history for each player (by username)
    static std::map<std::string, std::vector<int>> rollHistory;

public:
    // Static method to roll the dice for a specific player
    static int roll(const std::string& playerID) {
        int rollValue = (std::rand() % 6) + 1;  // Generates a number between 1 and 6
        rollHistory[playerID].push_back(rollValue);  // Add roll to player's history
        return rollValue;
    }

    // Static method to get a player's roll history
    static const std::vector<int>& getRollHistory(const std::string& playerID) {
        return rollHistory[playerID];
    }
};

// Initialize the static member outside the class
std::map<std::string, std::vector<int>> Dice::rollHistory;

class Player {
private:
    std::string username;

public:
    // Constructor to set player's unique ID (username)
    Player(const std::string& name) : username(name) {}

    // Method for the player to roll the dice
    void rollDice() const {
        int rollValue = Dice::roll(username);
        std::cout << username << " rolled: " << rollValue << std::endl;
    }

    // Method to show the player's roll history
    void showRollHistory() const {
        const std::vector<int>& history = Dice::getRollHistory(username);
        std::cout << "Roll history for " << username << ": ";
        for (int roll : history) {
            std::cout << roll << " ";
        }
        std::cout << std::endl;
    }

    // Get the player's username
    std::string getUsername() const {
        return username;
    }
};

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Create players
    Player player1("Alice");
    Player player2("Bob");

    // Players roll the dice
    player1.rollDice();
    player2.rollDice();
    player1.rollDice();
    player2.rollDice();
    player2.rollDice();

    // Show each player's roll history
    player1.showRollHistory();
    player2.showRollHistory();

    return 0;
}
```

### Key Features:

1. **Dice Class:**

   - Now includes a static `std::map<std::string, std::vector<int>>` called `rollHistory`, which keeps track of each player's dice rolls using their username as the key.
   - The static `roll()` method now accepts a `playerID` (username), rolls the dice, and records the result in the `rollHistory` map.
   - `getRollHistory()` returns a player's entire roll history by looking it up in the `rollHistory` map.

2. **Player Class:**
   - Each `Player` object is initialized with a unique username.
   - The `rollDice()` method allows the player to roll the dice, using their username to log the roll in the `Dice` class.
   - The `showRollHistory()` method displays the player's roll history.

### Example Output:

```
Alice rolled: 4
Bob rolled: 2
Alice rolled: 6
Bob rolled: 5
Bob rolled: 1
Roll history for Alice: 4 6
Roll history for Bob: 2 5 1
```

### Explanation:

- Each player (e.g., "Alice" and "Bob") rolls the dice using their unique username. The dice rolls are tracked by the static `Dice` class in the `rollHistory` map, associating each roll with the player's username.
- The `Player` class interacts with the `Dice` class, ensuring that the dice rolls are logged and can be retrieved or displayed later for each individual player.
