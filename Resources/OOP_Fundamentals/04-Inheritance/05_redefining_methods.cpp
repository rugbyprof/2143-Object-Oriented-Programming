/**
 * 05 - Redefining Methods in a Derived Class
 *
 * A derived class can write its own version of a method it inherited.
 * When you call the method ON THE OBJECT, you get that class's version.
 *
 * The derived version can still call the base version with the scope
 * operator:  Character::printName();
 * This lets you extend behavior instead of copying and pasting it.
 *
 * (Note: none of these methods are virtual yet. See 06 for why that
 * matters.)
 */

#include <iostream>
#include <string>

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

  // replaces Character::printName for Wizard objects
  void printName() { cout << "The magnificent " << name << endl; }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}

  // extends Character::printName instead of replacing it
  void printName() {
    cout << "The powerful... ";
    Character::printName();
  }
};

int main() {
  Character bob("Bob");
  Wizard merlin("Merlin");
  Warrior conan("Conan");

  bob.printName();    // Bob
  merlin.printName(); // The magnificent Merlin
  conan.printName();  // The powerful... Conan
}
