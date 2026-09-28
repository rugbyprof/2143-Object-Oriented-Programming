/**
 * 11 - Multiple Inheritance and the Diamond (advanced / optional)
 *
 * A MountainDwarf is BOTH a Warrior and a Wizard:
 *
 *              Character
 *              /       \
 *         Warrior     Wizard
 *              \       /
 *            MountainDwarf
 *
 * Problem: without special handling, MountainDwarf contains TWO Character
 * objects, one inherited through Warrior and one through Wizard. Two names,
 * two healths, and `name` is ambiguous.
 *
 * Fix: virtual inheritance.
 *   class Warrior : virtual public Character
 *   class Wizard  : virtual public Character
 * Now there is only ONE shared Character inside a MountainDwarf.
 *
 * Catch: the shared Character is built by the MOST DERIVED class. When you
 * create a MountainDwarf, the Character(...) calls in Warrior's and
 * Wizard's initializer lists are IGNORED. MountainDwarf must call
 * Character(name) itself, or Character's default constructor is used.
 * (That's why the original example needed an empty Character() {}.)
 *
 * In practice, many designs avoid the diamond by using composition or
 * interfaces instead. It's still good to know why it's tricky.
 */

#include <iostream>
#include <string>

using namespace std;

class Character {
protected:
  string name;

public:
  Character(string name) : name(name) {
    cout << "  Character(" << name << ")" << endl;
  }
  virtual ~Character() {}
  virtual void printName() { cout << name << endl; }
};

class Warrior : virtual public Character {
public:
  Warrior(string name) : Character(name) { cout << "  Warrior" << endl; }
  void printName() override { cout << "The powerful " << name << endl; }
  void swing() { cout << name << " swings a hammer!" << endl; }
};

class Wizard : virtual public Character {
public:
  Wizard(string name) : Character(name) { cout << "  Wizard" << endl; }
  void printName() override { cout << "The magnificent " << name << endl; }
  void cast() { cout << name << " casts a rune of stone!" << endl; }
};

class MountainDwarf : public Warrior, public Wizard {
public:
  // Character(name) MUST be called here. Warrior's and Wizard's calls to it
  // are skipped for a MountainDwarf.
  MountainDwarf(string name)
      : Character(name), Warrior(name), Wizard(name) {
    cout << "  MountainDwarf" << endl;
  }

  // Warrior and Wizard both override printName, so MountainDwarf must pick
  // one or write its own, otherwise the call is ambiguous.
  void printName() override { cout << "The mountain dwarf " << name << endl; }
};

int main() {
  cout << "Building a MountainDwarf (note: Character built ONCE):" << endl;
  MountainDwarf gimli("Gimli");

  gimli.printName();
  gimli.swing(); // from Warrior
  gimli.cast();  // from Wizard

  // It can be used as any of its bases:
  Character *c = &gimli;
  Warrior *w = &gimli;
  Wizard *z = &gimli;
  c->printName();
  w->printName();
  z->printName();
}
