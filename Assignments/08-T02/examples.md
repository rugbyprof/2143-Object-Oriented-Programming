## Review Test2 - Example code

I used chat-gpt to generate most of this, but I had to correct the AI multiple times.

## Inheritance Vs Composition

### Inheritance:

Use inheritance when you have a class hierarchy where a subclass `is a` specialized version of its superclass. For example, you might have a `Character` `superclass` that has `subclasses` like `Warrior`, `Mage`, and `Rogue` that inherit their basic properties and behaviors from the Character class. In this case, inheritance is appropriate because each subclass shares many of the same properties and methods as the superclass, but also has its own unique behaviors.

```cpp
class Character {
public:
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class Warrior : public Character {
public:
    void attack() override {
        // Perform warrior-specific attack
    }

    void defend() override {
        // Perform warrior-specific defense
    }
};

class Mage : public Character {
public:
    void attack() override {
        // Perform mage-specific attack
    }

    void defend() override {
        // Perform mage-specific defense
    }
};
```

### Composition:

Use composition when you have a class that `has a` member that is an instance of another class. For example, you might have a `Weapon` class that is a separate class from `Character`, but each `Character` object has an associated `Weapon` object. In this case, `composition` is appropriate because `Weapon` is not a specialized version of `Character`, but rather an independent entity that is associated with `Character`.

```cpp
class Weapon {
public:
    virtual void attack() = 0;
};

class Sword : public Weapon {
public:
    void attack() override {
        // Perform sword attack
    }
};

class Character {
public:
    void set_weapon(Weapon* weapon) {
        weapon_ = weapon;
    }

    void attack() {
        weapon_->attack();
    }

private:
    Weapon* weapon_;
};
```

In this example, `Sword` is a `subclass` of `Weapon`, but is not related to `Character` via `inheritance`. Instead, each Character object has a `Weapon` object that is set via the `set_weapon` method. The attack method of Character delegates to the attack method of the associated Weapon object.

## Is-A, Has-A, Kind-Of

### Is-A relationship:

This relationship represents inheritance, where a subclass "is a" specialized version of its superclass. For example, a "Warrior" class might inherit from a more generic "Character" class, since a warrior is a kind of character.

```cpp
class Character {
public:
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class Warrior : public Character {
public:
    void attack() override {
        // Perform warrior-specific attack
    }

    void defend() override {
        // Perform warrior-specific defense
    }
};
```

In this example, `Warrior` is a `subclass` of `Character`, and `inherits` its `interface` for `attack` and `defend` methods. The `Warrior class` implements these methods in a way that is specific to warriors.

### Has-A relationship:

This relationship represents composition, where an object `has a` member that is an instance of another class. For example, a "Party" class might have a collection of "Character" objects.

```cpp

class Character {
public:
    void attack();
    void defend();
};

class Party {
public:
    void add_character(Character* character);
    void remove_character(Character* character);

private:
    std::vector<Character*> members_;
};
```

In this example, the Party class has a collection of Character objects as a private member variable. The add_character and remove_character methods allow other code to add or remove members from the party.

### Kind-Of relationship:

this relationship represents a more specialized version of a class, where the subclass shares many of the same properties and methods as the superclass, but has additional functionality or constraints. For example, a "Sorcerer" class might be a kind of "Magic-User" class, since they both have access to spells, but sorcerers use a different mechanism for casting spells.

```cpp
class MagicUser {
public:
    virtual void cast_spell() = 0;
};

class Sorcerer : public MagicUser {
public:
    void cast_spell() override {
        // Cast spell using sorcerer-specific mechanism
    }

private:
    int spell_slots_;
};
```

In this example, `Sorcerer` is a `subclass` of `MagicUser`, and has access to the same interface for casting spells. However, the `Sorcerer` class has an additional private member variable for `spell_slots_`, which represents a resource that is unique to sorcerers.

## Multilevel vs Hierarchical vs Multiple Inheritance

### Multilevel:

In a multilevel inheritance relationship, the subclass is situated below its immediate superclass, and further below the ultimate superclass. It might be visualized as a pyramid or a tree, with the ultimate superclass at the top and each subsequent level representing a subclass that inherits from the level above it.

This relationship represents inheritance where a subclass inherits from another subclass. For example, a "Sorcerer" class might inherit from a "Mage" class, which in turn inherits from a "Character" class.

```cpp
class Character {
public:
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class Mage : public Character {
public:
    virtual void cast_spell() = 0;
};

class Sorcerer : public Mage {
public:
    void cast_spell() override {
        // Cast spell using sorcerer-specific mechanism
    }

private:
    int spell_slots_;
};
```

```
              Character
                /   
               /     
              /       
             Mage 
             |
             |
             |
             Sorcerer
```

In this example, Sorcerer inherits from Mage, which in turn inherits from Character. The Sorcerer class has access to the same interface as Mage, but also has a private member variable for spell*slots* that is unique to sorcerers.

### Hierarchical:

In a hierarchical inheritance relationship, multiple subclasses inherit from the same superclass. It might be visualized as a branching tree, with the superclass at the center and each subclass extending out from it as a branch.

This relationship represents inheritance where multiple subclasses inherit from the same superclass. For example, a "Weapon" class might be a superclass to "Sword" and "Bow" classes.

```cpp
class Weapon {
public:
    virtual void attack() = 0;
};

class Sword : public Weapon {
public:
    void attack() override {
        // Perform sword attack
    }
};

class Bow : public Weapon {
public:
    void attack() override {
        // Perform bow attack
    }
};

```

```
          Weapon
            / \
           /   \
        Sword  Bow

```

In this example, both Sword and Bow inherit from Weapon. Each subclass overrides the attack method to perform a different kind of attack.

### Multiple Inheritance:

In a multiple inheritance relationship, the subclass inherits from multiple superclasses. It might be visualized as a Venn diagram or a combination of two or more branching trees, with each superclass represented by its own branch.

This relationship represents inheritance where a subclass inherits from multiple superclasses. For example, a "Fighter" class might inherit from both "Character" and "Weapon" classes.

```cpp
class Character {
public:
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class Weapon {
public:
    virtual void attack() = 0;
};

class Fighter : public Character, public Weapon {
public:
    void attack() override {
        // Perform fighter-specific attack
    }

    void defend() override {
        // Perform fighter-specific defense
    }
};
```

```
            Character    Weapon
               |           |
               |          /
                \        /
                 \     /
                  \  /
                 Fighter


```

In this example, `Fighter` inherits from both `Character` and `Weapon`. The `attack` and `defend` methods are overridden to perform fighter-specific actions.

## Abstract Classes

You've seen examples above already, but here is a directed definition of only that concept: In object-oriented programming, an `abstract class` (or `abstract base class`) is a class that is declared with at least one `pure virtual function`. A `pure virtual function` is a virtual function that has `no implementation` in the base class, but instead is meant to be **overridden by derived classes**. An abstract class `cannot be instantiated directly`, but must be `subclassed to provide implementations` for the pure virtual functions.

Here's an example of an abstract class in the D&D theme:

```cpp
class Character {
public:
    virtual void attack(Character* target) = 0;

    virtual int hit_points() const {
        return hit_points_;
    }

protected:
    int hit_points_;
};
```

In this example, the Character class is declared as an abstract class by including a `pure virtual function` (`attack`). The `attack` function is meant to be overridden by derived classes to `provide specific attack behavior`. The `hit_points` function is also declared as `virtual`, but has an implementation in the base class, which means that it can be overridden by derived classes if necessary. The hit*points* variable is declared as protected to allow access by derived classes.

Here's an example of a derived class that inherits from the Character abstract base class:

```cpp

class Fighter : public Character {
public:
    void attack(Character* target) override {
        int damage = roll_dice(weapon_damage_);
        target->hit_points_ -= damage;
    }

private:
    int weapon_damage_;
};
```

In this example, the `Fighter class` inherits from the `Character abstract base class` and provides an implementation for the `pure virtual attack function`. The attack function rolls a number of dice specified by the `weapon_damage_` variable and subtracts the result from the target's hit points.

## Static / Class Level Variables

### Basic Overview

In object-oriented programming, a "class level" variable (also known as a "static variable") is a variable that is associated with a class, rather than with an instance of the class. This means that there is only one copy of the variable, which is shared amongst all instances of the class.

A class level variable is declared using the static keyword in C++ and other object-oriented programming languages. In C++, a class level variable is typically declared outside of any method in the class, like this:

```cpp
class MyClass {
public:
    static int count;

    MyClass() {
        count++;
    }
};

int MyClass::count = 0;
```

In this example, the `count` variable is a class level variable that is shared amongst all instances of the `MyClass` class. The variable is declared as `static int` and is initialized to `0` outside of any method in the class. The constructor of the class increments the `count` variable each time a new instance of the class is created.

Class level variables are useful for storing information that is shared amongst all instances of a class, such as a global counter or a shared resource. However, they should be used sparingly, as they can make it difficult to reason about the state of a program and can lead to unexpected behavior if not used carefully.

Here's a more specific or "useful" example of how a shared value may help a D&D `Party class`. Every member of the party, shares an attack bonus:

```cpp
class Party {
public:
    static int attack_bonus() {
        return attack_bonus_;
    }

    static void set_attack_bonus(int bonus) {
        attack_bonus_ = bonus;
    }

private:
    static int attack_bonus_;
};

int Party::attack_bonus_ = 0;
```

In this example, the Party class has a `attack_bonus_` variable that is shared by all members of the party. The variable is declared as `static` and is initialized to `0`. The `attack_bonus method` is also declared as static and returns the value of attack*bonus*. The `set_attack_bonus method` is also declared as `static` and allows the attack bonus to be set for the entire party.

To use this "class level" variable, a character in the party can simply call the `attack_bonus method` to get the current attack bonus value for the entire party:

```cpp

class Fighter : public Character {
public:
    void attack(Character* target) {
        int attack_roll = roll_dice() + Party::attack_bonus();
        if (attack_roll >= target->armor_class()) {
            // Hit the target
        }
    }
};
```

In this example, the `Fighter class` calls the `Party::attack_bonus` method to get the current attack bonus for the entire party, which is added to the attack roll. This allows the attack bonus to be easily shared amongst all members of the party.

## Virtual Destructor

The `destructor` of a `base class` should always be declared as `virtual` if the class is intended to be used as a base class for derived classes. This is because when a derived class object is destroyed, the destructor of the derived class is called first, followed by the destructor of the base class.

If the base class destructor is not declared as virtual, and a derived class object is destroyed through a pointer to the base class, only the base class destructor will be called, and the derived class destructor will be skipped. This can lead to memory leaks and undefined behavior.

Here's an example to illustrate this:

```cpp

class Base {
public:
    ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called" << std::endl;
    }
};

int main() {
    Derived* d = new Derived();
    Base* b = d;

    delete b;
    return 0;
}
```

In this example, `Derived` is a `derived class` of `Base`, and both classes have a destructor that prints a message when called. In `main`, a new `Derived` object is created and assigned to a pointer to `Base`. When delete is called on the pointer to `Base`, the `Base destructor` is called, but the `Derived destructor` is not called. This can cause issues if the Derived class has resources that need to be cleaned up in its destructor.

To avoid this issue, the `Base` `destructor` should be declared as `virtual`, like this:

```cpp

class Base {
public:
    virtual ~Base() {
        std::cout << "Base destructor called" << std::endl;
    }
};
```

By declaring the Base destructor as virtual, the Derived destructor will be called when a Derived object is destroyed through a pointer to Base.
