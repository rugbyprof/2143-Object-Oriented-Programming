/**
 * 04 - public / protected / private members
 *
 *               | the class itself | derived classes | everyone else
 *   ------------+------------------+-----------------+--------------
 *   public      |       yes        |       yes       |      yes
 *   protected   |       yes        |       yes       |      no
 *   private     |       yes        |       no        |      no
 *
 * Use protected for data that child classes need to work with, but that
 * outside code (like main) shouldn't touch directly.
 *
 * This file is about member access. For `: public` vs `: protected` vs
 * `: private` inheritance, see 12-Inheritance_Access_Levels.
 */

#include <iostream>
#include <string>

using namespace std;

class Character {
private:
  string secretPassword = "hunter2"; // only Character can see this

protected:
  string name; // Character + derived classes can see this
  int health = 100;

public:
  Character(string name) : name(name) {}

  string getName() const { return name; } // anyone can call this
  bool checkPassword(string guess) const { return guess == secretPassword; }
};

class Warrior : public Character {
public:
  Warrior(string name) : Character(name) {}

  void rage() {
    health += 20; // OK: protected, and Warrior is derived
    cout << name << " rages! health now " << health << endl;

    // cout << secretPassword;  // ERROR: private to Character
    // Warrior can still use the public interface:
    cout << "password ok? " << checkPassword("hunter2") << endl;
    
  }
};

int main() {
  Warrior conan("Conan");
  conan.rage();

  cout << conan.getName() << endl; // OK: public
  // cout << conan.name;           // ERROR: protected
  // cout << conan.health;         // ERROR: protected
}
