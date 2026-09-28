/**
 * 03 - Constructor Chaining
 *
 * A derived object has a base object "inside" it. Before the Warrior part
 * of the object can be built, the Character part has to be built.
 *
 *   Warrior(string n) : Character(n) { ... }
 *                       ^^^^^^^^^^^^
 *                       call the base constructor FIRST, in the
 *                       initializer list, so the base sets up its own data
 *
 * If you leave the call out, C++ quietly calls Character() (the default
 * constructor) instead, and the name never gets set. That was a bug in the
 * original example, where power was left uninitialized.
 *
 * Order:  construction = base first, then derived
 *         destruction  = derived first, then base (reverse order)
 */

#include <iostream>
#include <string>

using namespace std;

class Character {
protected:
  string name;
  int health;

public:
  Character(string name) : name(name), health(100) {
    cout << "  Character(" << name << ") constructor" << endl;
  }
  ~Character() { cout << "  ~Character(" << name << ") destructor" << endl; }
};

class Warrior : public Character {
protected:
  int strength;

public:
  Warrior(string name, int strength) : Character(name), strength(strength) {
    cout << "  Warrior(" << name << ") constructor" << endl;
  }
  ~Warrior() { cout << "  ~Warrior(" << name << ") destructor" << endl; }

  void print() {
    cout << "  " << name << " health:" << health << " strength:" << strength
         << endl;
  }
};

int main() {
  cout << "Creating a Warrior:" << endl;
  {
    Warrior conan("Conan", 18);
    conan.print();
    cout << "Leaving scope:" << endl;
  } // conan is destroyed here
  cout << "Done." << endl;
}
