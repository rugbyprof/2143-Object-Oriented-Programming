## Public, Private, Protected (2)

_protected_ is often the sneaky middle child between **public** and **private**. It’s the “family-only” access specifier. Students who already know _public_ (everyone can see it) and _private_ (only the class itself can see it) will benefit from learning _protected_ in the context of inheritance.

---

# 🛡️ Quick Explanation of `protected`

- **`public`**: “The town square.” Accessible everywhere.
- **`private`**: “Your diary.” Only you (the class itself) can read/write it.
- **`protected`**: “The family table.” You and your kids (subclasses) can use it, but outsiders cannot.

---

# 🎲 D&D Example with `protected`

Let’s enhance our **Character → Wizard → Fighter** world:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Character {
protected:        // accessible to Character and subclasses
    int hp;

public:
    string name;

    Character(string n, int h) : name(n), hp(h) {}

    void takeDamage(int dmg) {
        hp -= dmg;
        cout << name << " takes " << dmg << " damage! Remaining HP: " << hp << endl;
    }
};

class Wizard : public Character {
public:
    int mana;

    Wizard(string n, int h, int m) : Character(n, h), mana(m) {}

    void fireball(Character& target) {
        cout << name << " casts Fireball at " << target.name << "!\n";
        target.takeDamage(20);
    }

    void selfHeal() {
        // Accessing protected hp directly
        hp += 10;
        cout << name << " heals! HP is now " << hp << endl;
    }
};

class Rogue : public Character {
public:
    Rogue(string n, int h) : Character(n, h) {}

    void backstab(Character& target) {
        cout << name << " backstabs " << target.name << "!\n";
        target.takeDamage(15);
    }

    void stealthRegen() {
        // Accessing protected hp directly
        hp += 5;
        cout << name << " stealthily regains HP. New HP: " << hp << endl;
    }
};
```

---

# 🧾 What’s Happening

- `hp` is **protected** in `Character`.
- **Wizard** and **Rogue** can directly manipulate `hp` (healing, stealth regen), even though outside code **cannot**.
- This models the idea that subclasses get privileged access to their base class’s internals.

---

# ⚔️ UML with `protected`

```
Character
  - name : public
  - hp   : protected
  + takeDamage()
```

Inheritance:

```
Character <|-- Wizard
Character <|-- Rogue
```

---

# 🪙 Teaching Tip

Tell students:

- Use **private** unless you _intend_ for child classes to mess with it.
- Use **protected** for base class stuff that kids should manage, but the rest of the world shouldn’t.
- Use **public** when you really mean “API surface.”

---

👉 Terry — do you want me to **regenerate the PDF handout** with this _protected_ example integrated, or do you want me to make a **separate 1-pager “Protected vs Private vs Public” supplement** for your students?
