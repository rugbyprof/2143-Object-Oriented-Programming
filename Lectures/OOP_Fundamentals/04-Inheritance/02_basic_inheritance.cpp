/**
 * 02 - Basic Inheritance
 *
 * Character is the base class (aka super class, parent class).
 * Warrior is the derived class (aka sub class, child class).
 *
 * `class Warrior : public Character` means:
 *   - a Warrior gets everything a Character has (data + methods)
 *   - a Warrior can add its own data and methods on top
 *
 * Notice we write printName() once, in Character, and Warrior gets it for
 * free. That's code reuse.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character {
public:
  string name;
  int health = 100;

  void printName() { cout << name << endl; }

  void takeDamage(int amount) {
    health -= amount;
    cout << name << " takes " << amount << " damage, health now " << health
         << endl;
  }
};

class Warrior : public Character {
public:
  // things only a Warrior has
  vector<string> weapons;
  int strength = 15;

  void addWeapon(string w) { weapons.push_back(w); }

  void listWeapons() {
    cout << name << " carries:";
    for (auto &w : weapons) {
      cout << " " << w;
    }
    cout << endl;
  }
};

int main() {
  Warrior conan;

  // inherited from Character
  conan.name = "Conan";
  conan.printName();
  conan.takeDamage(20);

  // Warrior's own additions
  conan.addWeapon("sword");
  conan.addWeapon("axe");
  conan.listWeapons();

  Character villager;
  villager.name = "Bob";
  villager.printName();
  // villager.addWeapon("pitchfork");  // ERROR: a Character is not a Warrior
}
