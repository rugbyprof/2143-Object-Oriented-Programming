/**
 * 09 - Virtual Destructors
 *
 * When you delete a derived object through a base pointer:
 *
 *   Character* c = new Wizard("Merlin");
 *   delete c;
 *
 * the destructor is looked up like any other method. If ~Character() is
 * NOT virtual, only ~Character() runs. ~Wizard() is skipped, so anything the
 * Wizard owned (here, a spellbook on the heap) leaks. Technically, the
 * behavior is undefined.
 *
 * Rule: if a class has ANY virtual function, give it a virtual destructor.
 *
 * (clang warns about the `delete b;` line below. That warning is the point
 * of this example.)
 */

#include <iostream>
#include <string>

using namespace std;

// ---------- WITHOUT virtual destructor ----------
class BadCharacter {
protected:
  string name;

public:
  BadCharacter(string name) : name(name) {}
  ~BadCharacter() { cout << "  ~BadCharacter()" << endl; } // not virtual!
  virtual void printName() { cout << name << endl; }
};

class BadWizard : public BadCharacter {
  string *spellbook;

public:
  BadWizard(string name) : BadCharacter(name) {
    spellbook = new string("Fireball, Frost Nova");
  }
  ~BadWizard() {
    cout << "  ~BadWizard() freeing spellbook" << endl;
    delete spellbook;
  }
};

// ---------- WITH virtual destructor ----------
class Character {
protected:
  string name;

public:
  Character(string name) : name(name) {}
  virtual ~Character() { cout << "  ~Character()" << endl; }
  virtual void printName() { cout << name << endl; }
};

class Wizard : public Character {
  string *spellbook;

public:
  Wizard(string name) : Character(name) {
    spellbook = new string("Fireball, Frost Nova");
  }
  ~Wizard() override {
    cout << "  ~Wizard() freeing spellbook" << endl;
    delete spellbook;
  }
};

int main() {
  cout << "Deleting through a base pointer, NON-virtual destructor:" << endl;
  BadCharacter *b = new BadWizard("Merlin");
  delete b; // ~BadWizard never runs, so the spellbook leaks

  cout << "\nDeleting through a base pointer, virtual destructor:" << endl;
  Character *c = new Wizard("Merlin");
  delete c; // ~Wizard runs first, then ~Character
}
