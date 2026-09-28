#include <fstream>
#include <iostream>
#include <string>
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
  string currency;

public:
  /**
   * @brief Construct a new Characte` q12r object
   *
   * @param (string) name
   */
  Character() {};
  Character(string name) {
    power = rand() % 100;
    this->name = name;
  }
  void printName() { cout << name << endl; }
  virtual void money(string m) = 0;
  virtual ~Character() {}
};

/**
 * @brief Wizard class that extends Character
 * What makes a wizard different is her/his ability to cast spells.
 *
 */
class Wizard : virtual public Character {
protected:
  vector<string> spells;

public:
  Wizard(string _name) { this->name = _name; }
  void money(string m) { this->currency = m; }
  void printName() { cout << "The magnificant: " << name << endl; }
};

/**
 * @brief Warrior class that extends Character
 * What makes a warrior different is her/his added strength and speed.
 *
 */
class Warrior : virtual public Character {
protected:
  vector<string> weapons;
  float strength;
  float speed;

public:
  Warrior(string _name) { this->name = _name; }
  void money(string m) { this->currency = m; }
  void printName() { cout << "The powerful: " << name << endl; }
};

class MountainDwarf : public Warrior, public Wizard {
public:
  MountainDwarf(string _name) : Warrior(_name), Wizard(_name) {
    this->name = _name;
  }
  void money(string m) { this->currency = m; }
  void printName() { cout << "The mountain dwarf: " << name << endl; }
};

int main() {

  vector<Warrior> warriors;
  vector<Wizard> wizards;
  vector<MountainDwarf> awesome;
  string og = "papadopolous";

  ifstream fin;

  fin.open("dnd_last_names.txt");

  string name;
  int id;
  int n = 0;

  while (!fin.eof()) {
    fin >> name;

    id = rand() % 3;

    if (id % 3 == 0) {
      warriors.push_back(Warrior(name));
    } else if (id % 3 == 1) {
      wizards.push_back(Wizard(name));
    } else {
      awesome.push_back(MountainDwarf(name));
    }
    n++;
  }

  cout << warriors.size() << endl;
  cout << wizards.size() << endl;
  cout << awesome.size() << endl;
  // for (int i = 0; i < n; i++) {
  //     c = characters[i];
  //     c->printName();
  // }

  for (auto &c : warriors) {
    c.printName();
  }
  for (auto &c : wizards) {
    c.printName();
  }
  for (auto &c : awesome) {
    c.printName();
  }

  for (int i = 0; i < og.size(); i++) {
    cout << og[i];
  }
  cout << endl;

  for (auto &c : og) {
    cout << c << endl;
  }
}