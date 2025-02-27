# Decoupling Interface from Implementation: A Dungeons & Dragons Example in C++

In object-oriented programming, decoupling the interface from the implementation allows you to write code that depends on an abstract interface rather than on concrete classes. This makes your code flexible and easier to extend. In a role-playing game (RPG) setting, you might have different types of characters (like Warriors, Wizards, and Rogues) that all perform an attack, but each in their own unique way. By defining a common interface, you can write functions that work with any character without knowing its concrete type.

Below is a complete C++ example that demonstrates this concept.

---

## C++ Code Example

```cpp
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Abstract base class defining the interface for all characters.
class Character {
public:
    // Pure virtual function: all characters must implement their own version of attack().
    virtual void attack() const = 0;

    // Virtual destructor to ensure proper cleanup of derived classes.
    virtual ~Character() {}
};

// Derived class: Warrior
class Warrior : public Character {
public:
    // Warrior-specific implementation of attack().
    void attack() const override {
        cout << "Warrior swings his mighty sword!" << endl;
    }
};

// Derived class: Wizard
class Wizard : public Character {
public:
    // Wizard-specific implementation of attack().
    void attack() const override {
        cout << "Wizard casts a powerful fireball!" << endl;
    }
};

// Derived class: Rogue
class Rogue : public Character {
public:
    // Rogue-specific implementation of attack().
    void attack() const override {
        cout << "Rogue strikes swiftly from the shadows!" << endl;
    }
};

// Function that demonstrates decoupling by using the interface only.
// It accepts any character that implements the Character interface.
void engageInBattle(const Character &character) {
    // The function doesn't care about the character's concrete type;
    // it only calls the attack() method defined in the interface.
    character.attack();
}

int main() {
    // Create a party of adventurers using smart pointers for automatic memory management.
    vector<unique_ptr<Character>> party;
    party.push_back(make_unique<Warrior>());
    party.push_back(make_unique<Wizard>());
    party.push_back(make_unique<Rogue>());

    // Engage in battle: each character performs their attack.
    // The function 'engageInBattle' is decoupled from the concrete implementations.
    for (const auto &member : party) {
        engageInBattle(*member);
    }

    return 0;
}
```

### Explanation

- Abstract Base Class (Character):
  - Defines the interface with a pure virtual function attack().
  - Ensures that every derived class implements its own version of attack().
  - The virtual destructor ensures proper cleanup of derived classes.
- Derived Classes (Warrior, Wizard, Rogue):
  - Each class provides a unique implementation of the attack() method, appropriate to its character type.
- Decoupling in engageInBattle():
  - This function takes a reference to a Character and calls attack() without knowing the concrete type of the object.
  - This is the essence of decoupling: the function depends only on the interface, not on the specific implementation.
- Using Smart Pointers and Containers:
  - The party of characters is stored in a vector of unique_ptr<Character>, showcasing polymorphic behavior.
  - This makes it easy to add new character types in the future without modifying the engageInBattle() function.

### Benefits

- Flexibility: You can add new character classes without changing the code that interacts with the Character interface.
- Maintainability: Functions like engageInBattle() remain simple and focused, working only with the abstract interface.
- Extensibility: This approach supports open-closed principle—classes are open for extension but closed for modification.
