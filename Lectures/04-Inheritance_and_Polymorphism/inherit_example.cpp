#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Base class with generic character traits. 
 * 
 */
class Character {
protected:
  string name;
  float power;
  float manna;
  float wisdom;
  float defense;

public:
  /**
   * @brief Construct a new Character object
   * 
   * @param (string) name 
   */
  Character(string name) {
    power = rand() % 100;
    this->name = name;
  }
  virtual void printName() { cout << name << endl; }
};

/**
 * @brief Wizard class that extends Character 
 * What makes a wizard different is her/his ability to cast spells.
 * 
 */
class Wizard : public Character {
protected:
  vector<string> spells;

public:
  Wizard(string _name) : Character(_name) {}
  void printName() { cout << "The magnificant: " << name << endl; }
};

/**
 * @brief Warrior class that extends Character 
 * What makes a warrior different is her/his added strength and speed.
 * 
 */
class Warrior : public Character {
protected:
  vector<string> weapons;
  float strength;
  float speed;

public:
  Warrior(string _name) : Character(_name) {}
  void printName() { cout << "The powerful: " << name << endl; }
};

class MountainDwarf : public Warrior, public Wizard{

};

int main() {
  vector<Character *> characters;
  Character *c;
  Wizard Wz("moldour");
  Warrior Wa("conan");

  // vector<Character*> characters;

  Wz.printName();

  Wa.printName();

  c = &Wz;
  (*c).printName();

  c = &Wa;
  c->printName();

  ifstream fin;

  fin.open("names.txt");

  string name;
  int id;

  while (!fin.eof()) {
    fin >> id >> name;

    if (id % 2 == 0) {
      characters.push_back(new Warrior(name));
    } else {
      characters.push_back(new Wizard(name));
    }
  }

  for (int i = 0; i < 100; i++) {
    c = characters[i];
    c->printName();
  }
}