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
    Character() {};
    Character(string name) {
        power      = rand() % 100;
        this->name = name;
    }
    virtual void printName() {
        cout << name << endl;
    }
    virtual ~Character() {
    }
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
    Wizard(string _name) {
        this->name = _name;
    }
    void printName() {
        cout << "The magnificant: " << name << endl;
    }
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
    Warrior(string _name) {
        this->name = _name;
    }
    void printName() {
        cout << "The powerful: " << name << endl;
    }
};

class MountainDwarf : public Warrior, public Wizard {
   public:
    MountainDwarf(string _name) : Warrior(_name), Wizard(_name) {
        this->name = _name;
    }
    void printName() {
        cout << "The mountain dwarf: " << name << endl;
    }
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

    fin.open("dnd_last_names.txt");

    string name;
    int id;
    int n = 0;

    while (!fin.eof()) {
        fin >> name;

        id = rand() % 3;

        if (id % 3 == 0) {
            characters.push_back(new Warrior(name));
        } else if (id % 3 == 1) {
            characters.push_back(new Wizard(name));
        } else {
            characters.push_back(new MountainDwarf(name));
        }
        n++;
    }

    for (int i = 0; i < n; i++) {
        c = characters[i];
        c->printName();
    }
}