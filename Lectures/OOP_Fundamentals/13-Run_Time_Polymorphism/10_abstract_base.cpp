/**
 * 10 - Abstract Base Classes (pure virtual functions)
 *
 * In 08, Character::attack() printed "swings wildly." But what does a plain
 * Character actually do? There's no good answer, because nobody in the game
 * is just a "Character." It's a concept, not a real thing.
 *
 *   virtual void attack() = 0;     // pure virtual: no body
 *
 * A class with at least one pure virtual function is ABSTRACT:
 *   - you cannot create an object of it
 *   - every concrete derived class MUST override the pure virtual function,
 *     or it is abstract too
 *
 * The base class becomes a contract: "every Character can attack(). HOW is
 * up to you." You can still have normal (non-virtual) methods like
 * getName() and shared data in an abstract class.
 *
 * (An abstract class with ONLY pure virtual functions and no data is
 * called an interface. See Decoupling.md for IBehavior.)
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
  string name;
  int health = 100;

public:
  Character(string name) : name(name) {}
  virtual ~Character() {}

  string getName() const { return name; } // shared, not virtual

  virtual void attack(Character &target) = 0; // pure virtual

  void takeDamage(int amount) {
    health -= amount;
    cout << "  " << name << " has " << health << " health left" << endl;
  }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}
  void attack(Character &target) override {
    cout << name << " cleaves " << target.getName() << "!" << endl;
    target.takeDamage(25);
  }
};

class Wizard : public Character {
public:
  Wizard(string name) : Character(name) {}
  void attack(Character &target) override {
    cout << name << " hurls a fireball at " << target.getName() << "!"
         << endl;
    target.takeDamage(30);
  }
};

// class Bard : public Character {
// public:
//   Bard(string name) : Character(name) {}
//   // forgot attack()...
// };
// Bard b("Jaskier");  // ERROR: Bard is abstract because attack() is missing

int main() {
  // Character c("Bob");  // ERROR: cannot instantiate abstract class

  vector<unique_ptr<Character>> party;
  party.push_back(make_unique<Warrior>("Conan"));
  party.push_back(make_unique<Wizard>("Merlin"));

  Warrior goblin("Goblin");
  for (auto &c : party) {
    c->attack(goblin);
  }
}
