# Inheritance Overview

This document was created because of a question asked in class. It was just about the `protected` keyword, but this covers much more than just that.

## 🧠 The Original Question

“Can a base class define a method as `protected`, where it can be accessed from a subclass?”
✅ **YES.**
That’s _exactly_ what `protected` means.
It lets subclasses access a member, but keeps outsiders locked out.

---

### ⚙️ The Access Levels

| Access Specifier | Accessible in Same Class | Accessible in Derived Class | Accessible Outside Class |
| ---------------- | ------------------------ | --------------------------- | ------------------------ |
| `private`        | ✅                        | ❌                           | ❌                        |
| `protected`      | ✅                        | ✅                           | ❌                        |
| `public`         | ✅                        | ✅                           | ✅                        |

---

### 🧰 Base + Derived Example

```cpp
class Base {
protected:
    void protectedMethod() {
        cout << "Base protected method called.\n";
    }
};
class Derived : public Base {
public:
    void callBaseProtected() {
        protectedMethod();  // ✅ Allowed
    }
};
int main() {
    Derived d;
    d.callBaseProtected();  // ✅ OK
    // d.protectedMethod(); // ❌ Not allowed
}
```

🧩 **Output:**

```
Base protected method called.
```

---

### 🧠 Concept Summary

| Who Can Access? | Private | Protected | Public |
| --------------- | ------- | --------- | ------ |
| Base Class      | ✅       | ✅         | ✅      |
| Derived Class   | ❌       | ✅         | ✅      |
| External Code   | ❌       | ❌         | ✅      |

- `protected` → “Visible to family only.”

### Inheritance Modes

Inheritance doesn’t just copy access — it _changes_ it.

| Base Member | `public` Inheritance | `protected` Inheritance | `private` Inheritance |
| ----------- | -------------------- | ----------------------- | --------------------- |
| `public`    | stays public         | becomes protected       | becomes private       |
| `protected` | stays protected      | stays protected         | becomes private       |
| `private`   | inaccessible         | inaccessible            | inaccessible          |

---

### 🧩 UML-Style Visualization

```
                +---------------------+
                |       Base          |
                +---------------------+
                | - priv : int        |
                | # prot : int        |
                | + pub  : int        |
                +---------------------+
                     ▲      ▲      ▲
                     |      |      |
      +--------------+      |      +---------------+
      |                     |                      |
+----------------+   +------------------+   +----------------+
| PublicDerived  |   | ProtectedDerived |   | PrivateDerived |
+----------------+   +------------------+   +----------------+
| +pub  (public) |   | #pub (protected) |   | -pub (private) |
| #prot (prot.)  |   | #prot (protected)|   | -prot (private)|
| -priv (none)   |   | -priv (none)     |   | -priv (none)   |
+----------------+   +------------------+   +----------------+
```

---

## 💡The Netflix Analogy

- **Public inheritance:** “My kids and the neighbors can use my Netflix.”
- **Protected inheritance:** “Only my kids can use it.”
- **Private inheritance:** “I changed the password.”

---

## Code Demonstration: Base + Three Derived

```cpp
class Base {
public: int pub = 1;
protected: int prot = 2;
private: int priv = 3;
};
class PublicDerived : public Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
class ProtectedDerived : protected Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
class PrivateDerived : private Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
```

From `main()`:

`PublicDerived pd;`<br>
`cout << pd.pub; //` ✅works<br>
`// cout << pd.prot; //` ❌<br>
`// cout << pd.priv; //` ❌<br>

---

## 🧩 Output

```
[PublicDerived]  pub=1 prot=2
[ProtectedDerived] pub=1 prot=2
[PrivateDerived] pub=1 prot=2
```

Outside Access (in `main`):

```
pd.pub :white_check_mark:
pd.prot ❌
protD.pub ❌
privD.pub ❌
```

---

## 🧬 Multi-Level Cascade Example

Add a **grandchild** to show inheritance visibility through generations.

```cpp
class PublicGrandchild : public PublicDerived {
    void show() { cout << pub << prot; }  // ✅both visible
};
class ProtectedGrandchild : public ProtectedDerived {
    void show() { cout << pub << prot; }  // ✅both visible to family only
};
class PrivateGrandchild : public PrivateDerived {
    void show() {
        // ❌ pub & prot not accessible
        cout << "Base members are hidden!\n";
    }
};
```

---

## 🧩 Multi-Level Access Summary

| Inheritance Chain             | Base::public | Base::protected | Base::private | Visibility Notes              |
| ----------------------------- | ------------ | --------------- | ------------- | ----------------------------- |
| Base → Public → Grandchild    | ✅public      | ✅protected      | ❌             | fully accessible              |
| Base → Protected → Grandchild | ✅protected   | ✅protected      | ❌             | visible only within hierarchy |
| Base → Private → Grandchild   | ❌            | ❌               | ❌             | completely hidden             |

---

## 🧩 Final Rules of Thumb

| Intent                                         | Use This Inheritance |
| ---------------------------------------------- | -------------------- |
| “Is a kind of”                                 | `public`             |
| “Shares logic but not interface”               | `private`            |
| “Protected implementation for subclasses only” | `protected` (rare)   |

---

## 💡 Key Takeaways

:white*check_mark: `protected` members are **visible to subclasses**, not outsiders.
⚙️ Inheritance type \_transforms* visibility.
🔒 `private` members never pass down the line.
🧬 Access cascades: **public → protected → private** like a fading signal.
🤯 Private inheritance hides base internals from **everyone**, even grandkids.

---

## :mortar_board: “The Access Modifier Prayer”

“Grant me the serenity to `protect` what should not be public,
the courage to `public` what must be seen,
and the wisdom to `private` the rest.”
_(— Saint Stroustrup, probably)_

---

## :checkered_flag: Summary

| Concept               | Description                                                                                       |
| --------------------- | ------------------------------------------------------------------------------------------------- |
| `protected` keyword   | Base method/attribute visible to derived classes                                                  |
| Public inheritance    | Keeps visibility the same                                                                         |
| Protected inheritance | Narrows public → protected                                                                        |
| Private inheritance   | Narrows everything to private                                                                     |
| Grandchild effect     | Access narrows further down the chain                                                             |
| Golden rule           | Use `public` for “is-a”, `private` for “has-a”, and rarely `protected` for “family-only helpers.” |

---

# 🧙‍♂️ Protected Access in C++: The D&D Example

> _“With great power comes great access control.” — Some wise wizard, probably Stroustrup._

---

## 🧩 Lesson Overview

This lesson explores **how `protected` members** in C++ give subclasses the ability to reuse and extend base functionality — without exposing those details to the outside world.

Using a **Dungeons & Dragons** theme:

- A base class `Character` defines the shared logic (HP, taking damage)
- Derived classes `Warrior` and `Magician` specialize defense and attack behavior
- The `protected` keyword allows controlled inheritance of core features

---

## 🧠 Takeaways

- ✅ Differentiate between `private`, `protected`, and `public` access
- ✅ Design base classes that expose internal helpers safely via `protected`
- ✅ Explain why `protected` is often the _Goldilocks zone_ of encapsulation
- ✅ Implement custom subclass behaviors that reuse base functionality

---

## ⚔️ Scenario: The D&D Character Hierarchy

Every character in D&D shares common traits:

- A **name**
- A **health pool**
- The ability to **take damage**

But subclasses differ:

- Warriors defend with armor.
- Magicians defend with mana shields.

---

## 🧩 The Class Structure

| Class       | Description                                               | Access Highlights                                           |
| ----------- | --------------------------------------------------------- | ----------------------------------------------------------- |
| `Character` | Base class with core functionality (name, HP, takeDamage) | `takeDamage()` is `protected` so only subclasses can use it |
| `Warrior`   | Physical fighter subclass                                 | Uses armor to reduce damage                                 |
| `Magician`  | Magic-based subclass                                      | Uses mana shield to reduce damage                           |

---

## ⚙️ Code Example

```cpp
#include <iostream>
#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health;

    // Shared logic, but not public.
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
        cout << name << " takes " << amount
             << " damage! Remaining HP: " << health << endl;
    }

public:
    Character(string n, int h) : name(n), health(h) {}

    virtual void attack(Character &target) = 0;  // pure virtual
    bool isAlive() const { return health > 0; }
};

// ================== WARRIOR ====================
class Warrior : public Character {
    int armor;
public:
    Warrior(string n) : Character(n, 120), armor(10) {}

    void attack(Character &target) override {
        cout << name << " swings a mighty sword!" << endl;
        target.defend(25);
    }

protected:
    virtual void defend(int dmg) {
        int reduced = dmg - armor;
        if (reduced < 0) reduced = 0;
        takeDamage(reduced);  // ✅ allowed: protected in base
    }
};

// ================== MAGICIAN ====================
class Magician : public Character {
    int manaShield;
public:
    Magician(string n) : Character(n, 80), manaShield(20) {}

    void attack(Character &target) override {
        cout << name << " casts a Fireball!" << endl;
        target.defend(35);
    }

protected:
    void defend(int dmg) override {
        int reduced = dmg - manaShield;
        manaShield -= 5; // shield weakens
        if (reduced < 0) reduced = 0;
        takeDamage(reduced);  // ✅ allowed: protected base method
    }
};

// ================== MAIN ====================
int main() {
    Warrior w("Thorin");
    Magician m("Merlin");

    cout << "\n--- Battle Begins! ---\n\n";

    w.attack(m);
    m.attack(w);

    cout << "\n--- Battle Ends! ---\n";
}
```

---

## 🧩 Sample Output

```
--- Battle Begins! ---

Thorin swings a mighty sword!
Merlin takes 15 damage! Remaining HP: 65
Merlin casts a Fireball!
Thorin takes 25 damage! Remaining HP: 95

--- Battle Ends! ---
```

---

## 🧠 Why Use `protected` Here?

| Member           | Access Level        | Why It Works                                        |
| ---------------- | ------------------- | --------------------------------------------------- |
| `takeDamage()`   | `protected`         | Subclasses can use it, but outsiders can’t abuse it |
| `defend()`       | `protected virtual` | Each subclass can override with its own logic       |
| `attack()`       | `public`            | Needed for character interactions                   |
| `health`, `name` | `protected`         | Common data available to subclasses only            |

---

## 🧙 D&D Analogy

> `protected` = “Guild secrets”
>
> Every member of the Adventurer’s Guild (derived class) can use them.  
> But common villagers (main program) can’t.

---

## 🧬 Optional Extension: Multi-Level Inheritance

Add a **MeleeFighter** class as an intermediate type:

```cpp
class MeleeFighter : public Character {
protected:
    void defend(int dmg) override {
        takeDamage(dmg / 2); // basic melee resilience
    }
};

class Warrior : public MeleeFighter {
public:
    void attack(Character &target) override {
        cout << name << " slashes twice!" << endl;
        target.defend(20);
    }
};
```

Here `MeleeFighter` acts as a _bridge_ — defining a generic defense pattern shared by all physical fighters.  
Because `takeDamage()` is `protected`, both `MeleeFighter` and `Warrior` can use it safely.

---

## ⚔️ Access Control Summary

| Access Specifier | Visible to Base | Visible to Derived | Visible to Outside |
| ---------------- | --------------- | ------------------ | ------------------ |
| `private`        | ✅               | ❌                  | ❌                  |
| `protected`      | ✅               | ✅                  | ❌                  |
| `public`         | ✅               | ✅                  | ✅                  |

---

## 🧩 Why Not Just Use `private`?

If `takeDamage()` were `private`, subclasses like `Warrior` and `Magician` would need to reimplement damage handling or rely on awkward friend relationships.  
`protected` lets subclasses **reuse logic safely** — while still enforcing encapsulation against the outside world.

---

## 🧠 Discussion Questions

1. What would happen if we made `takeDamage()` public?
2. Could we make `defend()` public — and should we?
3. Why might a base class want to hide some methods from both subclasses _and_ outsiders?
4. How would you add a “Healer” subclass that _restores_ HP using the same protected method?

---

## 💡 Challenge Exercise

> ✨ Extend the code so the `Magician`’s mana shield regenerates each turn.  
> Use `protected` methods to handle mana updates without exposing them publicly.

---

## 🏁 Key Takeaways

| Concept            | Summary                                                   |
| ------------------ | --------------------------------------------------------- |
| `protected`        | Balances access between reuse and security                |
| Base class role    | Provides internal mechanics for derived classes           |
| Derived class role | Specializes and extends base functionality                |
| Public interface   | Defines how the outside world interacts with your objects |
| OOP design tip     | Keep data hidden, share logic responsibly                 |

---

## 🧠 Final Thought

> “A good class hierarchy is like a party of adventurers —  
> each member knows their role, their secrets, and when to help the others.  
> The Dungeon Master (you) just makes sure the rules are fair.”
