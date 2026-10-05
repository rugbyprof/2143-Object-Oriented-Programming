/**
 * 08 - A Mixed Party in One Container
 *
 * Read names from dnd_last_names.txt and randomly make each one a Warrior,
 * Wizard, or Rogue. They all go in ONE vector, and ONE loop handles them
 * all. The loop never checks which kind each character is.
 *
 * Why unique_ptr instead of raw `new`?
 *   vector<Character*> with `new` means YOU have to `delete` every one, and
 *   the original version of this example never did (a memory leak).
 *   unique_ptr deletes its object automatically when the vector goes away.
 *   (See SmartPointers.md.)
 *
 * Adding a new class (say, Bard) means writing the class and one line in
 * makeCharacter. The loop in main doesn't change at all.
 */

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
  string name;

public:
  Character(string name) : name(name) {}
  virtual ~Character() {}

  virtual void printName() { cout << name << endl; }
  virtual void attack() { cout << name << " swings wildly." << endl; }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}
  void printName() override { cout << "The powerful " << name << endl; }
  void attack() override { cout << name << " cleaves with an axe!" << endl; }
};

class Wizard : public Character {
public:
  Wizard(string name) : Character(name) {}
  void printName() override { cout << "The magnificent " << name << endl; }
  void attack() override { cout << name << " hurls a fireball!" << endl; }
};

class Rogue : public Character {
public:
  Rogue(string name) : Character(name) {}
  // no printName override: Rogue uses Character's version
  void attack() override { cout << name << " stabs from the shadows!" << endl; }
};

// The only place in the program that knows about specific classes
unique_ptr<Character> makeCharacter(string name) {
  switch (rand() % 3) {
  case 0:
    return make_unique<Warrior>(name);
  case 1:
    return make_unique<Wizard>(name);
  default:
    return make_unique<Rogue>(name);
  }
}

int main() {
  srand(time(0));

  ifstream fin("dnd_last_names.txt");
  if (!fin) {
    cout << "Could not open dnd_last_names.txt" << endl;
    return 1;
  }

  vector<unique_ptr<Character>> party;
  string name;

  // `while (fin >> name)` stops as soon as a read fails.
  // `while (!fin.eof())` would process the last name twice.
  while (fin >> name && party.size() < 8) {
    party.push_back(makeCharacter(name));
  }

  cout << "Party of " << party.size() << ":" << endl;
  for (auto &c : party) {
    c->printName();
  }

  cout << "\nBattle!" << endl;
  for (auto &c : party) {
    c->attack();
  }
} // every unique_ptr deletes its character here, with no leaks
