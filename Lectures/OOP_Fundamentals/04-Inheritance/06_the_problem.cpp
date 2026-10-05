/**
 * 06 - The Problem (cliffhanger)
 *
 * Same classes as 05. Now we want a whole PARTY of mixed characters, so we
 * can loop over them without caring which kind each one is.
 *
 * Attempt 1: vector<Character>
 *   Copying a Wizard into a Character keeps only the Character part.
 *   The Wizard part is "sliced" off. This is called OBJECT SLICING.
 *
 * Attempt 2: Character* pointing at a Wizard
 *   No slicing, because the pointer refers to the real Wizard object.
 *   But c->printName() STILL calls Character::printName!
 *
 * Why? Without `virtual`, the compiler decides which function to call from
 * the type of the POINTER (Character*), not the type of the actual OBJECT
 * (Wizard). That decision is made at compile time.
 *
 * Fix: 13-Run_Time_Polymorphism/07_virtual_override.cpp
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

  void printName() { cout << name << endl; }
};

class Wizard : public Character {
public:
  Wizard(string name) : Character(name) {}
  void printName() { cout << "The magnificent " << name << endl; }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}
  void printName() { cout << "The powerful " << name << endl; }
};

int main() {
  Wizard merlin("Merlin");
  Warrior conan("Conan");

  cout << "Called on the objects (works):" << endl;
  merlin.printName();
  conan.printName();

  cout << "\nAttempt 1: vector<Character> (sliced):" << endl;
  vector<Character> party = {merlin, conan};
  for (auto &c : party) {
    c.printName();
  }

  cout << "\nAttempt 2: Character* (not sliced, still wrong):" << endl;
  vector<Character *> party2 = {&merlin, &conan};
  for (auto c : party2) {
    c->printName();
  }
}
