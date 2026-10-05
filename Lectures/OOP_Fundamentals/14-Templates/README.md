# Introduction to C++ Templated Types: A Character-Based Adventure

- In this document, we will introduce **C++ templates** using a character-based theme inspired by RPG games like Dungeons & Dragons. 
- Sorry, but it makes learning OOP so much better. 
- **Templates** allow us to write **generic, reusable code** that can work with different data types while keeping our code **efficient and flexible**.

## 🎭 **What Are Templates?**

- A **template** in C++ is a feature that allows functions and classes to operate on **generic types**.
- This means we can write a function or a class **once** and use it with multiple data types, without rewriting the code for each type.
- Think of templates like a **blueprint**—you design it once and reuse it for different materials (types).

## 🏹 **1. Basic Function Template: A Magical Inventory System**

Let’s say we want to create an inventory system that allows characters to store different types of items: **weapons, potions, or gold**. Instead of writing separate functions for `int`, `double`, or `string`, we can **use a template**.

```cpp
#include <iostream>
using namespace std;

// Template function for storing items in inventory
template <typename T>
void storeItem(T item) {
    cout << "Stored item: " << item << endl;
}

int main() {
    storeItem(100);          // Store gold (int)
    storeItem(3.5);          // Store a potion (double)
    storeItem("Excalibur");  // Store a sword (string)
    return 0;
}
```

### Explanation:

- template <typename T>: Defines a templated function, where T is a placeholder for any data type.
- storeItem(T item): Accepts an item of any type and prints it.
- We call storeItem() with an int, double, and string, but we don’t need separate functions for each type!

## ⚔️ 2. Class Template: A Generic Character Class

- Imagine a generic RPG character who can have different types of health values:
  - An int for a warrior (exact hit points).
  - A double for a wizard (floating-point mana).
  - A float for a rogue (stamina-based health).

Instead of creating multiple character classes, we use a templated class.

```cpp
#include <iostream>
using namespace std;

// Templated Character class
template <typename T>
class Character {
private:
    string name;
    T health;
public:
    Character(string n, T h) : name(n), health(h) {}

    void display() {
        cout << name << " has " << health << " health points." << endl;
    }
};

int main() {
    Character<int> warrior("Thorin", 150);    // Warrior with int health
    Character<double> wizard("Gandalf", 99.5); // Wizard with double health
    Character<float> rogue("Locke", 75.3f);   // Rogue with float health

    warrior.display();
    wizard.display();
    rogue.display();

    return 0;
}
```

### Explanation:

- template <typename T> allows us to define a Character class that works with any type of health value.
- We create characters with different health types (int, double, float).
- The display() function prints their health, showing how the same class works for different data types.

## 🧙 3. Multiple Template Parameters: A Spellbook System

- Sometimes we need multiple template parameters. For example, a spellbook might store:
  - A spell name (string).
  - A power level (int or double).

We can use two template parameters:

```cpp
#include <iostream>
using namespace std;

// Spellbook class with two template parameters
template <typename NameType, typename PowerType>
class Spell {
private:
NameType spellName;
PowerType powerLevel;
public:
Spell(NameType name, PowerType power) : spellName(name), powerLevel(power) {}

    void cast() {
        cout << "Casting " << spellName << " with power " << powerLevel << "!" << endl;
    }

};

int main() {
Spell<string, int> fireball("Fireball", 50);
Spell<string, double> frostbolt("Frostbolt", 42.7);

    fireball.cast();
    frostbolt.cast();

    return 0;

}
```

### Explanation:

- template <typename NameType, typename PowerType>: The Spell class has two template types.
- We create spells with different power types (int or double).
- This makes the spell system flexible—you can define spells with different kinds of power levels.

## 🎲 4. Specializing Templates: Legendary Items

Sometimes, we want specific behavior for a particular type while keeping the generic template. This is called template specialization.

For example, legendary weapons need a special announcement when stored.

```cpp
#include <iostream>
using namespace std;

// Generic template function
template <typename T>
void storeItem(T item) {
cout << "Stored item: " << item << endl;
}

// Template specialization for legendary weapons
template <>
void storeItem<string>(string item) {
cout << "🔥 A legendary item has been stored: " << item << "! 🔥" << endl;
}

int main() {
storeItem(100); // Normal item
storeItem(3.5); // Normal item
storeItem("Excalibur"); // Special case for legendary weapon

    return 0;

}
```

### Explanation:

- Normal items print “Stored item: …”.
- Legendary items (string) print a special message.
- This allows custom behavior for specific types while keeping the function generic.

## 🏰 5. Advanced: Template Class with Default Type

If we want a class to default to a specific type but still allow customization, we can provide a default template type.

```cpp
#include <iostream>
using namespace std;

template <typename T = int> // Default type is int
class Potion {
private:
T healingAmount;
public:
Potion(T heal) : healingAmount(heal) {}

    void drink() {
        cout << "You drink the potion and recover " << healingAmount << " health points!" << endl;
    }

};

int main() {
Potion<> smallPotion(20); // Uses default int type
Potion<double> bigPotion(50.5); // Uses double

    smallPotion.drink();
    bigPotion.drink();

    return 0;

}
```

### Explanation:

- The default type is int, but we can override it by specifying another type (double in this case).
- This is useful when we want flexibility but still provide sensible defaults.

## 🏆 Final Thoughts

- Templates increase code reusability and flexibility, allowing us to create generic, type-safe components.
- In this adventure, we explored:
  - **1**. **Function Templates** - Storing different items without duplicating code.
  - **2**. **Class Templates** - Creating a flexible character class.
  - **3**. **Multiple Template Parameters** - Designing a spellbook system.
  - **4**. **Template Specialization** - Customizing legendary item storage.
  - **5**. **Default Template Types** - Creating potions with sensible defaults.

By mastering templates, your code will be more reusable, scalable, and powerful ⚔️🔥.
