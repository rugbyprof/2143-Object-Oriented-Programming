## History

History in this sense refers to the last X things to occur. In the terminal world its a list of your commands that you have typed into the terminal. For a dice game, we (possibly) want to remember the last N rolls made by a player. We could do this by creating a vector of ints in the dice class. However the OOP way would be to make a more generic History class and then specify how we would like to use it. Some like `History<T>` where T is the type we want to remember.

The `Dice` class could use the `History` class by extending it to store dice rolls in its history while keeping the other functionalities intact.

### Templated `History` Class:

```cpp
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class History {
protected:
    vector<T> history;  // Stores the history of any type

public:
    // Add an entry to the history
    void addToHistory(T entry) {
        history.push_back(entry);
    }

    // Retrieve the entire history
    vector<T> getHistory() const {
        return history;
    }

    // Print the history
    void printHistory() const {
        cout << "History: ";
        for (const auto &entry : history) {
            cout << entry << " ";
        }
        cout << endl;
    }
};
```

### Extend the `Dice` Class to Include History:

Now, we extend the `Dice` class to inherit from `History<int>` and track the history of the dice rolls.

```cpp
class Dice : public History<int> {
   private:
    vector<Die> dice;

   public:
    // Constructors (same as before)
    Dice() { init(1, 6); }
    Dice(int n, int s) { init(n, s); }
    Dice(string d) {
        vector<string> parts = tokenize(d, '.');
        int n = stoi(parts[0]);
        int s = stoi(parts[2]);
        init(n, s);
    }

    void init(int n, int s) {
        while (n--) {
            dice.push_back(Die(s));
        }
    }

    // Override the roll method to also store results in the history
    int roll(int rolls = 1) {
        int sum = 0;
        while (rolls--) {
            for (int i = 0; i < dice.size(); i++) {
                int rollResult = dice[i].roll();
                sum += rollResult;
                this->addToHistory(rollResult);  // Store roll result in history
            }
        }
        return sum;
    }

    // Method to get the history (already inherited from History<int>)
    void printRollHistory() {
        this->printHistory();  // Print the roll history
    }

    friend ostream &operator<<(ostream &os, const Dice &d) {
        for (int i = 0; i < d.dice.size(); i++) {
            os << d.dice[i];
        }
        return os;
    }
};
```

### Explanation:

- **`History<T>`**: This templated class can store any type of history (`T` can be `int`, `string`, etc.). It provides methods to add entries, retrieve the history, and print the history.
- **`Dice` class**: Now, the `Dice` class inherits from `History<int>` to store the history of dice rolls. Whenever a dice is rolled, the result is added to the `history` vector using the `addToHistory()` method.
- **`roll()`**: The `roll()` method has been modified to store each roll's result in the history, allowing you to track all the rolls.

### Example Usage:

```cpp
int main() {
    Dice d(2, 6);  // Two six-sided dice
    cout << "Rolling dice..." << endl;
    d.roll();      // Roll the dice and add to history
    d.roll();      // Roll the dice again

    // Print the roll history
    d.printRollHistory();

    return 0;
}
```

### Output Example:

```
Rolling dice...
History: 4 2 3 6
```

---

### Extension Ideas:

1. **Track Roll Counts**: Extend `History` to count how many times each value has been rolled.
2. **Different Types of History**: You could use the template to track other types of game-related history, such as player actions or game events.
3. **Limit History Size**: Add logic to limit the number of entries stored in the history (e.g., only store the last 10 rolls).

---

### Overloading `ostream` to Print a Range from History

First, we define a method that takes in the range you want to print and overloads the `<<` operator for the `History` class.

### Example:

```cpp
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class History {
protected:
    vector<T> history;

public:
    // Add an entry to the history
    void addToHistory(T entry) {
        history.push_back(entry);
    }

    // Overload ostream to print the entire history or a range of entries
    friend ostream& operator<<(ostream& os, const History<T>& h) {
        os << "Full History: ";
        for (const auto& entry : h.history) {
            os << entry << " ";
        }
        return os;
    }

    // Overload ostream to print a specific range
    friend ostream& operator<<(ostream& os, const pair<int, int>& range) {
        os << "History in Range: ";
        for (int i = range.first; i < range.second && i < h.history.size(); i++) {
            os << h.history[i] << " ";
        }
        return os;
    }
};
```

### Example Usage:

```cpp
int main() {
    History<int> h;
    h.addToHistory(5);
    h.addToHistory(7);
    h.addToHistory(9);
    h.addToHistory(11);
    h.addToHistory(13);

    // Print full history
    cout << h << endl;

    // Print history in a specific range (from index 1 to 4)
    cout << pair<int, int>(1, 4) << endl;

    return 0;
}
```

### Explanation:

1. **Full History Printing**: The overloaded `<<` operator for the `History` class prints all elements in the history vector.
2. **Range Printing**: The overloaded `<<` operator for `pair<int, int>` allows specifying a start and end range for printing part of the history. You pass in the pair as `(start, end)`.
