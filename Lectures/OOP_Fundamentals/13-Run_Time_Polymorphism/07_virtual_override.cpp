/**
 * 07 - virtual + override (the fix for 04-Inheritance/06_the_problem.cpp)
 *
 * Adding `virtual` to the base class method changes ONE thing:
 * which version runs is now decided at RUN TIME, from the type of the
 * actual object, instead of at compile time from the pointer's type.
 *
 *   virtual void printName();          // in the base class
 *   void printName() override;         // in derived classes
 *
 * `override` isn't required, but use it anyway. It tells the compiler "I
 * mean to replace a virtual base method." If you misspell the name or get
 * the parameters wrong, you get a compile error instead of a silent bug.
 * (See 08-Override&Const.)
 *
 * Polymorphism works through POINTERS and REFERENCES only. A plain
 * vector<Character> still slices, even with virtual.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
  string name;

public:
  Character(string name) : name(name) {}
  virtual ~Character() {} // why this matters: see 09

  virtual void printName() { cout << name << endl; }
};

class Wizard : public Character {
public:
  Wizard(string name) : Character(name) {}
  void printName() override { cout << "The magnificent " << name << endl; }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}
  void printName() override { cout << "The powerful " << name << endl; }

  // void printname() override {}  // ERROR: no virtual printname to override
};

// Works with references too: one function that handles every Character
void announce(Character &c) {
  cout << "Now entering: ";
  c.printName();
}

int main() {
  Wizard merlin("Merlin");
  Warrior conan("Conan");

  cout << "Through Character* (now works):" << endl;
  vector<Character *> party = {&merlin, &conan};
  for (auto c : party) {
    c->printName();
  }

  cout << "\nThrough Character&:" << endl;
  announce(merlin);
  announce(conan);

  cout << "\nvector<Character> (still sliced, virtual can't help):" << endl;
  vector<Character> copies = {merlin, conan};
  for (auto &c : copies) {
    c.printName();
  }
}
