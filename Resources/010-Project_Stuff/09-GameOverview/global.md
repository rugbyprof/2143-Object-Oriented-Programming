## Global Sum using Static

- You can design a dice class where each player contributes to a global sum by using the **`static`** keyword.
- The `static` keyword allows you to declare a class variable that is shared among all instances of the class.
- This global sum would be a `static` variable that accumulates the dice rolls of all players.

Here’s how we do it:

### Design Overview:

- **Static Variable**: You will create a static variable, `globalSum`, which is shared across all players. Every time a player rolls the dice, their result will be added to this global sum.
- **Static Method**: You can also create a static method to access the global sum for printing or other operations, since static methods can interact with static members.

### Example Implementation in C++:

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

using namespace std;

class Dice {
private:
    int sides;
    static int globalSum;  // Static variable to track the global sum

public:
    // Constructor initializes the dice sides (default is 6)
    Dice(int s = 6) : sides(s) {}

    // Roll the dice and add the result to the global sum
    int roll() {
        int result = (rand() % sides) + 1;
        globalSum += result;  // Add result to the global sum
        return result;
    }

    // Static method to return the global sum
    static int getGlobalSum() {
        return globalSum;
    }

    // Static method to reset the global sum (if needed for a new game)
    static void resetGlobalSum() {
        globalSum = 0;
    }
};

// Initialize the static variable
int Dice::globalSum = 0;

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create a team of players, each rolling a dice
    vector<Dice> teamDice = {Dice(6), Dice(6), Dice(8), Dice(10)};  // Different sided dice

    // Each player rolls and adds to the global sum
    for (auto &dice : teamDice) {
        int result = dice.roll();
        cout << "Player rolled: " << result << endl;
    }

    // Access the global sum
    cout << "Global sum of all rolls: " << Dice::getGlobalSum() << endl;

    return 0;
}
```

### Explanation:

1. **Static Variable (`globalSum`)**:

   - The `static int globalSum` is a class-level variable that tracks the total sum of all dice rolls.
   - It is shared among all instances of the `Dice` class, so any modification to it from any instance affects the global sum.

2. **Static Method (`getGlobalSum`)**:
   - This static method is used to access the `globalSum` since static variables need to be accessed either via the class name (`Dice::getGlobalSum()`) or through static methods.
3. **`resetGlobalSum`**:
   - You can use this method to reset the global sum to 0, which would be useful if you want to start a new round or game.

### Output Example:

```
Player rolled: 4
Player rolled: 5
Player rolled: 7
Player rolled: 8
Global sum of all rolls: 24
```

### Use of `static`:

- The `static` keyword ensures that `globalSum` is **shared** across all `Dice` objects. Every player (represented by a `Dice` object) contributes to the same global total.
- Without `static`, each `Dice` object would have its own independent sum, defeating the purpose of a team-based score aggregation.

---

## Global Sum for Teams

- We can use **static variables** to track sums for each team
- Since we now need to track multiple teams, the static variable should be associated with each team separately rather than globally across all instances.
- This can be achieved by creating a **`Team`** class where each team has its own static sum, and the `Dice` class rolls for a specific team.
- You can use a **static member map** or an **array** inside the `Team` class to track the sums for multiple teams.

### Design Overview:

- **Static map/array**: The `Team` class will use a static map (or an array) to store the sum for each team, indexed by the team name or ID.
- **Dice rolls for team**: Each `Dice` object can belong to a specific team, and the roll results are added to that team's total score.

### Example Implementation:

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <map>      // To store multiple team scores

using namespace std;

class Team {
private:
    static map<string, int> teamScores;  // Static map to store scores for multiple teams

public:
    // Add score to the specified team's total sum
    static void addToTeamScore(string teamName, int score) {
        teamScores[teamName] += score;
    }

    // Get the score of a specific team
    static int getTeamScore(string teamName) {
        return teamScores[teamName];
    }

    // Print all team scores
    static void printAllTeamScores() {
        for (const auto& team : teamScores) {
            cout << "Team " << team.first << " Score: " << team.second << endl;
        }
    }

    // Reset all team scores
    static void resetAllScores() {
        teamScores.clear();
    }
};

// Initialize the static teamScores map
map<string, int> Team::teamScores;

class Dice {
private:
    int sides;
    string teamName;  // Name of the team this dice is rolling for

public:
    // Constructor initializes the dice sides (default is 6) and the team it belongs to
    Dice(string team, int s = 6) : teamName(team), sides(s) {}

    // Roll the dice and add the result to the team's sum
    int roll() {
        int result = (rand() % sides) + 1;
        Team::addToTeamScore(teamName, result);  // Add result to the team's score
        return result;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    // Create dice for two different teams
    vector<Dice> teamADice = {Dice("TeamA", 6), Dice("TeamA", 6)};
    vector<Dice> teamBDice = {Dice("TeamB", 6), Dice("TeamB", 6)};

    // Each player in Team A rolls their dice
    cout << "Team A rolls:" << endl;
    for (auto &dice : teamADice) {
        int result = dice.roll();
        cout << "Player rolled: " << result << endl;
    }

    // Each player in Team B rolls their dice
    cout << "Team B rolls:" << endl;
    for (auto &dice : teamBDice) {
        int result = dice.roll();
        cout << "Player rolled: " << result << endl;
    }

    // Print all team scores
    Team::printAllTeamScores();

    return 0;
}
```

### Explanation:

1. **Static Map (`teamScores`)**:

   - The `Team` class has a static map, `teamScores`, where each key is a team name (e.g., "TeamA" or "TeamB") and the value is the cumulative score for that team.
   - The static map allows all `Dice` objects for a specific team to update the same team score.

2. **`addToTeamScore` Method**:

   - This static method is used to update the score for a specific team by adding the dice roll result to the corresponding team’s sum.

3. **`Dice` Class**:

   - Each `Dice` object is associated with a specific team (`teamName`), and when the dice is rolled, the result is added to that team’s cumulative score by calling `Team::addToTeamScore(teamName, result)`.

4. **`Team::printAllTeamScores`**:
   - This static method prints the scores of all teams by iterating over the `teamScores` map.

### Output Example:

```
Team A rolls:
Player rolled: 4
Player rolled: 2
Team B rolls:
Player rolled: 5
Player rolled: 3
Team TeamA Score: 6
Team TeamB Score: 8
```

### Extension Ideas:

- **Multiple Teams**: You can easily extend this to support multiple teams by adding more `Dice` objects with different team names.
- **Multiple Rounds**: You can implement rounds by rolling for each team in different rounds and accumulating the scores.
- **Score Limits**: You can add logic to stop the game once a team reaches a certain score.

---
