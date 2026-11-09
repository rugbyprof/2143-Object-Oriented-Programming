<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: Factory_Pattern_Example
name: Factory_Pattern_Example
title: Static Members in C++
description: Singleton and Borg Design Patterns 
category: Assignments
date_due:
  month: 11
  day: 09
  year: 2026
  hour: 11
```

</details>

# Static Members in C++: Singleton and Borg Patterns

## 1. Introduction

In object-oriented programming, objects normally maintain their own independent state. Creating two instances of the same class produces two objects, each with its own non-static data members.

However, some applications require information to be shared across all instances of a class.

C++ provides the `static` keyword to support class-level data and behavior.

Two interesting design patterns demonstrate different approaches to sharing information:

- **Singleton:** Ensures that only one instance of a class exists through the controlled interface.
- **Borg (Monostate):** Allows multiple instances of a class while sharing their internal state.

These patterns provide an opportunity to explore static members, constructors, object identity, encapsulation, and shared state.

## 2. Learning Objectives

After completing this material, students should be able to:

1. Distinguish static members from instance members.
2. Explain how static data members are shared across objects.
3. Implement a Singleton using a static local variable.
4. Implement the Borg pattern using static class members.
5. Compare object identity with shared object state.
6. Identify advantages and disadvantages of globally shared state.

---

## 3. Static vs. Instance Members

Consider a class representing a game player.

```cpp
class Player {
private:
    std::string name;
    int score = 0;

public:
    Player(std::string n) : name(n) {}

    void addPoints(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }
};
```

Each `Player` object has its own `name` and `score`.

```cpp
Player alice("Alice");
Player bob("Bob");

alice.addPoints(10);
bob.addPoints(5);
```

Alice's score is independent of Bob's score.

Now suppose the application needs to count the total number of players created.

```cpp
class Player {
private:
    std::string name;

    inline static int playerCount = 0;

public:
    Player(std::string n) : name(n) {
        ++playerCount;
    }

    static int getPlayerCount() {
        return playerCount;
    }
};
```

Usage:

```cpp
Player alice("Alice");
Player bob("Bob");

std::cout << Player::getPlayerCount();
```

Output:

```text
2
```

The variable `playerCount` belongs to the class rather than any particular object.

All instances access the same variable.

### Important properties of static members

- Static data members exist independently of individual objects.
- Static member functions can be called using the class name.
- Static member functions do not have a `this` pointer.
- Static functions cannot directly access non-static members without an object.
- Static members can be public, protected, or private.

The `inline static` syntax, introduced in C++17, allows the variable to be initialized directly inside the class definition.

**Note:** The example counts objects constructed, not necessarily objects currently alive. Counting live objects would also require careful handling of destruction and copying.

---

# Part I — The Singleton Pattern

## 4. What Is a Singleton?

The Singleton pattern is a creational design pattern that restricts a class to one accessible instance and provides a global access point to that instance.

The central idea is simple:

**One class. One object. One shared state.**

A Singleton commonly uses:

- A private constructor.
- Deleted copy and assignment operations.
- A static member function to access the instance.
- A static local object to hold the instance.

## 5. Implementing a Singleton

Consider a game application that maintains a shared scoreboard.

```cpp
#include <iostream>

class Scoreboard {
private:
    int score = 0;

    Scoreboard() = default;

public:
    Scoreboard(const Scoreboard&) = delete;
    Scoreboard& operator=(const Scoreboard&) = delete;

    static Scoreboard& instance() {
        static Scoreboard board;
        return board;
    }

    void addPoints(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }
};
```

### Using the Singleton

```cpp
int main() {
    Scoreboard& a = Scoreboard::instance();
    Scoreboard& b = Scoreboard::instance();

    a.addPoints(10);
    b.addPoints(5);

    std::cout << a.getScore() << '\n';
    std::cout << b.getScore() << '\n';

    std::cout << (&a == &b) << '\n';
}
```

Output:

```text
15
15
1
```

Both references refer to the same object.

### How does it work?

The key statement is:

```cpp
static Scoreboard board;
```

Unlike a normal local variable, a static local variable is initialized only once and persists for the remainder of the program's execution.

Every call to `instance()` returns a reference to that same object.

This implementation is commonly called a **Meyers Singleton**.

Since C++11, initialization of a function-local static variable is thread-safe. This guarantees safe one-time initialization, not automatic thread safety for subsequent operations such as `addPoints()`.

### Why make the constructor private?

Without a private constructor, the following would be possible:

```cpp
Scoreboard anotherBoard;
```

That would defeat the goal of controlling object creation.

Deleting copy operations also prevents callers from creating additional objects by copying the Singleton.

---

# Part II — The Borg (Monostate) Pattern

## 6. What Is the Borg Pattern?

The Borg pattern takes a different approach.

Instead of restricting the number of objects, it allows any number of instances while ensuring they share the same internal state.

**Many objects. One shared state.**

In C++, this can be implemented naturally using static data members.

## 7. Implementing Borg

Consider the same scoreboard example.

```cpp
#include <iostream>

class BorgScoreboard {
private:
    inline static int score = 0;

public:
    void addPoints(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }
};
```

Notice what is missing:

- No private constructor.
- No `instance()` method.
- No restrictions on creating objects.
- No inheritance or virtual functions.

### Using Borg

```cpp
int main() {
    BorgScoreboard a;
    BorgScoreboard b;
    BorgScoreboard c;

    a.addPoints(10);
    b.addPoints(5);

    std::cout << a.getScore() << '\n';
    std::cout << b.getScore() << '\n';
    std::cout << c.getScore() << '\n';

    std::cout << (&a == &b) << '\n';
}
```

Output:

```text
15
15
15
0
```

Three different objects exist, but all share the same score.

The objects have different addresses, yet their static member variable refers to the same storage.

### Why does this work?

The declaration:

```cpp
inline static int score = 0;
```

creates a single shared variable associated with the class.

Every instance reads and modifies that variable.

The non-static methods `addPoints()` and `getScore()` operate on shared state rather than instance-specific state.

In this example, the Borg objects have no non-static data members. Each is still a distinct C++ object.

---

## 8. Singleton vs. Borg

| Characteristic                | Singleton               | Borg                   |
| ----------------------------- | ----------------------- | ---------------------- |
| Number of objects             | One controlled instance | Multiple               |
| Shared state                  | Through one object      | Through static members |
| Public construction           | Usually prohibited      | Allowed                |
| Object identity               | Same object             | Different objects      |
| Static data required          | Not necessarily         | Typically              |
| Static access method          | Common                  | Not required           |
| Copying                       | Usually disabled        | Usually allowed        |
| Global state concerns         | Yes                     | Yes                    |
| Thread-safe shared operations | Not automatic           | Not automatic          |

### Conceptual difference

**Singleton**

```text
Reference A ──┐
              ├──> Scoreboard Object
Reference B ──┘       score = 15
```

**Borg**

```text
Object A ──┐
           │
Object B ──┼──> Shared Static State
           │        score = 15
Object C ──┘
```

Singleton controls **object identity**.

Borg controls **shared state**.

That distinction is the most important concept in this handout.

---

## 9. When Might These Patterns Be Useful?

### Singleton examples

Potential applications include:

- A process-wide configuration manager.
- A centralized application coordinator.
- A registry that must have a single authoritative instance.
- A specialized manager for a uniquely owned resource.

Singleton can be useful when having exactly one instance is a genuine requirement.

However, simply wanting convenient global access is not sufficient justification.

### Borg examples

Potential applications include:

- A shared settings interface.
- A common application statistics counter.
- A global feature-flag collection.
- A shared cache accessed through multiple lightweight objects.

Borg is useful when separate object identities are acceptable but all instances must observe the same data.

### A practical warning

Both patterns introduce shared state.

Shared state can make software harder to test, debug, and maintain because changes made in one part of the program may affect seemingly unrelated code.

In larger applications, explicit dependency injection is often preferable.

---

## 10. Thread Safety and Static Members

Static data members are shared, but they are not automatically protected from concurrent access.

Consider:

```cpp
inline static int score = 0;
```

If multiple threads execute:

```cpp
score++;
```

without synchronization, the program can have a data race and undefined behavior.

One solution is to use an atomic integer:

```cpp
#include <atomic>

class ThreadSafeScoreboard {
private:
    inline static std::atomic<int> score{0};

public:
    void addPoints(int points) {
        score.fetch_add(points);
    }

    int getScore() const {
        return score.load();
    }
};
```

Atomic operations are appropriate for simple independent counters.

More complicated shared state may require a `std::mutex` or another synchronization mechanism.

**Important:** Thread-safe Singleton initialization does not imply thread-safe Singleton behavior.

---

# Part III — Design and Application

## 11. Applying the Patterns to a Card Game

Suppose a card-game application needs to track the total number of games played.

A Borg-style statistics class could be:

```cpp
class GameStatistics {
private:
    inline static int gamesPlayed = 0;
    inline static int totalRounds = 0;

public:
    void recordGame() {
        ++gamesPlayed;
    }

    void recordRound() {
        ++totalRounds;
    }

    int games() const {
        return gamesPlayed;
    }

    int rounds() const {
        return totalRounds;
    }
};
```

Different game objects can maintain local statistics interfaces while contributing to the same global counters.

```cpp
GameStatistics warStats;
GameStatistics pokerStats;

warStats.recordGame();
pokerStats.recordGame();

std::cout << warStats.games();
```

Output:

```text
2
```

The shared counter records both games.

This is useful for illustrating static members, although a production application might instead give each game an explicit reference to a statistics service.

---

## 12. Is Borg Really Necessary?

Consider the following:

```cpp
class Counter {
public:
    inline static int count = 0;
};
```

Usage:

```cpp
Counter::count++;
```

This already provides shared class-level state.

Why introduce Borg objects?

The Borg pattern allows the application to interact with shared state through ordinary object instances.

That can be useful when an API expects objects or when a class provides a meaningful set of operations.

However, if the only requirement is a global counter, a simple static member may be sufficient.

This raises an important design principle:

**Not every use of a static member needs a design pattern.**

Sometimes a static member is just a static member.

---

# Part IV — Student Exercises

## Exercise 1: Static Member Counter

Create a class named `Enemy` containing:

- A non-static integer `health`.
- A static integer `enemyCount`.
- A constructor that increments `enemyCount`.
- A static method `getEnemyCount()`.

Create five enemies and display the total count.

Then answer:

1. Does each enemy have its own health?
2. Does each enemy have its own copy of `enemyCount`?
3. Can `getEnemyCount()` be called without creating an `Enemy`?

**Challenge:** Modify the implementation to count currently living objects correctly, including handling copies and destruction.

## Exercise 2: Singleton Logger

Implement a class named `Logger` that:

- Has a private constructor.
- Provides a static `instance()` method.
- Contains a method `log(const std::string&)`.
- Prevents copying and assignment.

Example usage:

```cpp
Logger::instance().log("Game started");
Logger::instance().log("Player 1 wins");
```

Verify that repeated calls to `instance()` return the same object address.

## Exercise 3: Borg Configuration

Implement a class named `GameConfig` containing shared settings:

```cpp
int difficulty;
bool soundEnabled;
int maxRounds;
```

Use static data members to ensure that all `GameConfig` instances share the same settings.

Example:

```cpp
GameConfig a;
GameConfig b;

a.setDifficulty(3);

std::cout << b.getDifficulty();
```

Expected output:

```text
3
```

## Exercise 4: Compare Object Identity

Create two Singleton references and two Borg objects.

Compare their addresses using the address-of operator.

Explain why the results differ even though both patterns provide shared state.

## Exercise 5: Design Discussion

A game application needs to store:

- The current player's score.
- The total number of games played.
- The application's display settings.
- The cards in a player's hand.

For each item, determine whether instance data, static data, Singleton, or Borg is appropriate.

Justify the choice. More than one solution may be reasonable.

---

## 13. Key Takeaways

1. Static data members belong to a class and are shared by its instances.
2. Static member functions can be called without an existing object.
3. Singleton restricts construction to one controlled object.
4. Borg allows multiple objects to share the same state.
5. Object identity and object state are separate concepts.
6. Shared static data does not automatically provide thread safety.
7. Singleton and Borg can introduce hidden dependencies and complicate testing.
8. The simplest appropriate design is generally preferable to unnecessary abstraction.

### Final Design Principle

**Singleton answers: "How many objects should exist?"**

**Borg answers: "How many copies of the state should exist?"**

Both patterns demonstrate how static members affect object-oriented design, but neither should be used merely because the language makes it possible.

A design pattern should solve a problem—not create one.