/*****************************************************************************
 * template_13.cpp — Capstone: A Generic Battle Roster
 *
 * Everything so far, in one small design:
 *   - A concept describing what a fighter must be able to do   (template_12)
 *   - A class template that stores and manages any such type  (template_06)
 *   - Unrelated classes that fit one interface                (template_07)
 *   - Behavior passed in as a lambda                          (template_08)
 *   - A function template with two different type parameters  (template_02)
 *
 * Design question to keep in mind: Hero and Monster share NO base class, yet
 * one Roster class and one Battle function handle both. What did the template
 * buy us? What would change if we had used inheritance instead?
 *
 * Compile:  g++ -std=c++20 template_13.cpp -o template_13
 *****************************************************************************/
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// The interface every fighter must satisfy.
// ---------------------------------------------------------------------------
template <typename T>
concept Combatant = requires(T fighter, const T& const_fighter, int amount) {
    { const_fighter.Name() } -> convertible_to<string>;
    { const_fighter.Health() } -> integral;
    { const_fighter.Power() } -> integral;
    fighter.TakeDamage(amount);
};

// ---------------------------------------------------------------------------
// A generic team. Same behavior no matter what kind of fighter it holds.
// ---------------------------------------------------------------------------
template <Combatant T>
class Roster {
public:
    explicit Roster(const string& team_name)
        : team_name_(team_name) {
    }

    void Add(const T& fighter) {
        fighters_.push_back(fighter);
    }

    const string& TeamName() const {
        return team_name_;
    }

    bool HasSurvivors() const {
        return any_of(fighters_.begin(), fighters_.end(), [](const T& fighter) {
            return fighter.Health() > 0;
        });
    }

    // The living fighter with the most health. It's the one that steps up.
    T& Champion() {
        T* best = nullptr;
        for (T& fighter : fighters_) {
            if (fighter.Health() > 0 && (best == nullptr || fighter.Health() > best->Health())) {
                best = &fighter;
            }
        }
        if (best == nullptr) {
            throw logic_error(team_name_ + " has no one left to fight");
        }
        return *best;
    }

    // Run any action on every fighter. Action is a lambda, function, or functor.
    template <typename Action>
    void ForEach(Action action) const {
        for (const T& fighter : fighters_) {
            action(fighter);
        }
    }

private:
    string team_name_;
    vector<T> fighters_;
};

// ---------------------------------------------------------------------------
// Two unrelated fighter classes. Each satisfies Combatant in its own way.
// ---------------------------------------------------------------------------
class Hero {
public:
    Hero(const string& name, int health, int strength, int armor)
        : name_(name), health_(health), strength_(strength), armor_(armor) {
    }

    string Name() const {
        return name_;
    }

    int Health() const {
        return health_;
    }

    int Power() const {
        return strength_;
    }

    // Heroes wear armor, which soaks up part of every hit.
    void TakeDamage(int amount) {
        int actual = max(0, amount - armor_);
        health_ = max(0, health_ - actual);
    }

private:
    string name_;
    int health_;
    int strength_;
    int armor_;
};

class Monster {
public:
    Monster(const string& species, int health, int bite)
        : species_(species), health_(health), bite_(bite) {
    }

    string Name() const {
        return "the " + species_;
    }

    int Health() const {
        return health_;
    }

    // Monsters get weaker as they get hurt.
    int Power() const {
        return bite_ * health_ / 100 + 1;
    }

    void TakeDamage(int amount) {
        health_ = max(0, health_ - amount);
    }

private:
    string species_;
    int health_;
    int bite_;
};

// ---------------------------------------------------------------------------
// One battle function for ANY two kinds of rosters.
// A and B are separate parameters, so Heroes can fight Monsters,
// Monsters can fight Monsters, and so on.
// ---------------------------------------------------------------------------
template <Combatant A, Combatant B>
void Battle(Roster<A>& left, Roster<B>& right) {
    cout << "*** " << left.TeamName() << " vs " << right.TeamName() << " ***\n";
    int round = 1;
    while (left.HasSurvivors() && right.HasSurvivors()) {
        A& attacker = left.Champion();
        B& defender = right.Champion();

        defender.TakeDamage(attacker.Power());
        if (defender.Health() > 0) {
            attacker.TakeDamage(defender.Power());
        }

        cout << "Round " << round << ": " << attacker.Name() << " (" << attacker.Health() << " hp) vs "
             << defender.Name() << " (" << defender.Health() << " hp)\n";
        ++round;
    }
    cout << (left.HasSurvivors() ? left.TeamName() : right.TeamName()) << " win!\n\n";
}

template <Combatant T>
void Report(const Roster<T>& roster) {
    cout << roster.TeamName() << ":\n";
    roster.ForEach([](const T& fighter) {
        cout << "  " << fighter.Name() << " - " << fighter.Health() << " hp\n";
    });
}

int main() {
    Roster<Hero> heroes("The Heroes");
    heroes.Add(Hero("Thorin", 60, 18, 4));
    heroes.Add(Hero("Malakai", 45, 24, 1));

    Roster<Monster> monsters("The Horde");
    monsters.Add(Monster("troll", 80, 20));
    monsters.Add(Monster("goblin", 30, 12));

    Battle(heroes, monsters);
    Report(heroes);
    Report(monsters);

    // Roster<string> words("nope");   // Error: string is not a Combatant

    return 0;
}

/*****************************************************************************
 * Try it / Design exercises:
 *   1. Add a third class, Golem, that takes no damage from hits under 5.
 *      Make Monsters fight Golems without changing Roster or Battle.
 *   2. Add  template <typename Predicate> size_t CountIf(Predicate) const
 *      to Roster. Use it to count fighters with more than 20 hp.
 *   3. Can one Roster hold BOTH Heroes and Monsters? Redesign it so it can.
 *      (Hint: template_10.) What did you have to give up?
 *   4. Add a Healer whose  TakeDamage  does nothing on even rounds. What
 *      information is missing? Should it be part of the Combatant concept?
 *   5. In one paragraph: when would you choose a template over an abstract
 *      base class for a design in your own project?
 *****************************************************************************/
