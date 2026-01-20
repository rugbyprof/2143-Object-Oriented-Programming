#include <iostream>
#include <string>

using namespace std;
// ================== BASE CLASS ====================
class Character {
   protected:
    string name;
    int health;

    // Shared logic, but not public.
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0)
            health = 0;
        cout << name << " takes " << amount << " damage! Remaining HP: " << health << endl;
    }

   public:
    Character(string n, int h) : name(n), health(h) {
    }

    virtual void attack(Character &target) = 0;  // pure virtual
    bool isAlive() const {
        return health > 0;
    }
};

// ================== WARRIOR ====================
class Warrior : public Character {
    int armor;

   public:
    Warrior(string n) : Character(n, 120), armor(10) {
    }

    void attack(Character &target) override {
        cout << name << " swings a mighty sword!" << endl;
        target.defend(25);
    }

   protected:
    virtual void defend(int dmg) {
        int reduced = dmg - armor;
        if (reduced < 0)
            reduced = 0;
        takeDamage(reduced);  // ✅ allowed: protected in base
    }
};

// ================== MAGICIAN ====================
class Magician : public Character {
    int manaShield;

   public:
    Magician(string n) : Character(n, 80), manaShield(20) {
    }

    void attack(Character &target) override {
        cout << name << " casts a Fireball!" << endl;
        target.defend(35);
    }

   protected:
    void defend(int dmg) override {
        int reduced = dmg - manaShield;
        manaShield -= 5;  // shield weakens
        if (reduced < 0)
            reduced = 0;
        takeDamage(reduced);  // ✅ allowed: protected base method
    }
};

// ================== MAIN ====================
int main() {
    Warrior w("Thorin");
    Magician m("Merlin");

    cout << "\n--- Battle Begins! ---\n\n";

    w.attack(m);
    m.attack(w);

    cout << "\n--- Battle Ends! ---\n";
}