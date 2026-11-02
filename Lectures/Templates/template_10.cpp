/*****************************************************************************
 * template_10.cpp — Templates AND Inheritance, Working Together
 *
 * What's new:
 *   - Compile-time polymorphism (templates) vs runtime polymorphism (virtual)
 *   - Using a template to store polymorphic objects:
 *       vector<unique_ptr<Character>>
 *   - A function template factory that builds any Character subclass
 *   - Using a class template to remove copy/paste from a class hierarchy
 *
 * OOP angle: this isn't "templates OR inheritance." Real designs use both:
 *   - Inheritance when you need DIFFERENT types mixed together at runtime
 *     (a party of Fighters and Mages in one vector)
 *   - Templates when the SAME code should work for many types
 *     (a container, a factory, a reusable utility)
 *
 * Compile:  g++ -std=c++20 template_10.cpp -o template_10
 *****************************************************************************/
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Runtime polymorphism: an abstract base class.
// ---------------------------------------------------------------------------
class Character {
public:
    explicit Character(const string& name)
        : name_(name) {
    }

    virtual ~Character() = default;

    virtual string Attack() const = 0;

    const string& Name() const {
        return name_;
    }

private:
    string name_;
};

class Fighter : public Character {
public:
    using Character::Character;   // Inherit Character's constructor.

    string Attack() const override {
        return "swings a sword";
    }
};

class Mage : public Character {
public:
    using Character::Character;

    string Attack() const override {
        return "casts a fireball";
    }
};

// ---------------------------------------------------------------------------
// A factory function template. One function builds ANY Character subclass.
// Derived must have a constructor that takes a name.
// ---------------------------------------------------------------------------
template <typename Derived>
unique_ptr<Character> Spawn(const string& name) {
    return make_unique<Derived>(name);   // make_unique is itself a template!
}

// ---------------------------------------------------------------------------
// Compile-time polymorphism: works with ANYTHING that has Name() and Attack(),
// whether or not it inherits from Character.
// ---------------------------------------------------------------------------
template <typename Actor>
void TakeTurn(const Actor& actor) {
    cout << actor.Name() << " " << actor.Attack() << "\n";
}

// A totally separate class. NOT a Character, but it still fits TakeTurn.
class Trap {
public:
    string Name() const {
        return "A pressure plate";
    }

    string Attack() const {
        return "fires darts";
    }
};

// ---------------------------------------------------------------------------
// A class template that is ALSO polymorphic-friendly: Party<Base> can hold any
// family of classes through pointers to their common base.
// ---------------------------------------------------------------------------
template <typename Base>
class Party {
public:
    void Recruit(unique_ptr<Base> member) {
        members_.push_back(std::move(member));   // unique_ptr can't be copied, only moved.
    }

    void AllTakeTurns() const {
        for (const unique_ptr<Base>& member : members_) {
            TakeTurn(*member);   // Template call; virtual Attack() inside it.
        }
    }

private:
    vector<unique_ptr<Base>> members_;
};

int main() {
    cout << "--- Runtime polymorphism through a template container ---\n";
    Party<Character> party;
    party.Recruit(Spawn<Fighter>("Thorin"));
    party.Recruit(Spawn<Mage>("Malakai"));
    party.Recruit(Spawn<Fighter>("Rhea"));
    party.AllTakeTurns();

    cout << "\n--- Compile-time polymorphism, no shared base ---\n";
    Fighter solo("Jordan");
    Trap trap;
    TakeTurn(solo);   // Instantiates TakeTurn<Fighter>
    TakeTurn(trap);   // Instantiates TakeTurn<Trap>

    // Party<Trap> traps;  would also work: Party doesn't require inheritance.

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Add a Rogue class. How many lines did you need to change in Spawn,
 *      Party, or TakeTurn? (That's the payoff of combining both tools.)
 *   2. Could you put a Trap in Party<Character>? Why not? What would you
 *      have to change in the design to allow it?
 *   3. Why does Party store unique_ptr<Base> instead of Base?
 *      (Hint: what happens to a Mage copied into a Character variable?)
 *   4. Try  Spawn<int>("oops").  Where does the error appear?
 *****************************************************************************/
