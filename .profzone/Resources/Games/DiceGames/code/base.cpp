#include <iostream>
#include <string>

using namespace std;

// Strength, Constitution, Dexterity, Intelligence, Wisdom, and Charisma.

// Base class representing a Dungeons and Dragons character
class Character {
protected:
    string name;
    int level;
    int hitPoints;

public:
    Character(string name, int level, int hitPoints) {
        this->name = name;
        this->level = level;
        this->hitPoints = hitPoints;
    }
    virtual void attack() {
        cout << "The character attacks with a generic attack." << endl;
    }
};

// Child class representing a warrior character
class Warrior : public Character {
public:
    Warrior(string name, int level, int hitPoints) : Character(name, level, hitPoints) {}
    void attack() override {
        cout << "The warrior attacks with a sword." << endl;
    }
};

// Child class representing a wizard character
class Wizard : public Character {
public:
    Wizard(string name, int level, int hitPoints) : Character(name, level, hitPoints) {}
    void attack() override {
        cout << "The wizard attacks with a magic missile." << endl;
    }
};

// Child class representing a rogue character
class Rogue : public Character {
public:
    Rogue(string name, int level, int hitPoints) : Character(name, level, hitPoints) {}
    void attack() override {
        cout << "The rogue attacks with a sneak attack." << endl;
    }
};

// Child class representing an elf character
class Elf : public Character {
public:
    Elf(string name, int level, int hitPoints) : Character(name, level, hitPoints) {}
    void attack() override {
        cout << "The elf attacks with a bow and arrow." << endl;
    }
};

// Child class representing a dwarf character
class Dwarf : public Character {
public:
    Dwarf(string name, int level, int hitPoints) : Character(name, level, hitPoints) {}
    void attack() override {
        cout << "The dwarf attacks with an axe." << endl;
    }
};

int main() {
    // Create a warrior character and attack
    Warrior warrior("Grog", 5, 50);
    warrior.attack();

    // Create a wizard character and attack
    Wizard wizard("Gandalf", 10, 30);
    wizard.attack();

    // Create a rogue character and attack
    Rogue rogue("Remy", 3, 40);
    rogue.attack();

    // Create an elf character and attack
    Elf elf("Legolas", 7, 35);
    elf.attack();

    // Create a dwarf character and attack
    Dwarf dwarf("Gimli", 6, 45);
    dwarf.attack();

    return 0;
}
