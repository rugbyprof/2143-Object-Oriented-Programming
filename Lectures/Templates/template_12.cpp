/*****************************************************************************
 * template_12.cpp — Concepts: Writing the Interface Down (C++20)
 *
 * What's new:
 *   - concept: a named, compile-time check on a type
 *   - requires-expression: list the operations a type must support
 *   - Constraining a template:  template <Scorable T> class Leaderboard
 *   - Standard concepts from <concepts>: integral, floating_point, totally_ordered
 *   - Abbreviated syntax:  void Announce(const Scorable auto& entry)
 *
 * In template_07, Leaderboard's requirements lived in a COMMENT. If you got
 * them wrong, the error showed up deep inside the template. A concept turns
 * that comment into code the compiler checks at the point of use, much like
 * an abstract base class documents an interface (but checked at compile time
 * and with no inheritance needed).
 *
 * Compile:  g++ -std=c++20 template_12.cpp -o template_12
 *****************************************************************************/
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Standard concepts on a function template.
// ---------------------------------------------------------------------------
template <integral T>
T Half(T value) {
    return value / 2;   // Integer division, guaranteed.
}

template <floating_point T>
T Half(T value) {
    return value / 2.0;
}

// ---------------------------------------------------------------------------
// Our own concept: the "interface" from template_07, written as code.
// ---------------------------------------------------------------------------
template <typename T>
concept Scorable = requires(const T& item) {
    { item.Name() } -> convertible_to<string>;
    { item.Score() } -> totally_ordered;   // Must support < > <= >= == !=
};

template <Scorable T>
class Leaderboard {
public:
    explicit Leaderboard(size_t max_entries)
        : max_entries_(max_entries) {
    }

    void Submit(const T& entry) {
        entries_.push_back(entry);
        sort(entries_.begin(), entries_.end(), [](const T& left, const T& right) {
            return left.Score() > right.Score();
        });
        if (entries_.size() > max_entries_) {
            entries_.pop_back();
        }
    }

    void Print() const {
        for (size_t i = 0; i < entries_.size(); ++i) {
            cout << i + 1 << ". " << entries_[i].Name() << " (" << entries_[i].Score() << ")\n";
        }
    }

private:
    vector<T> entries_;
    size_t max_entries_;
};

// Abbreviated function template: same as  template <Scorable T> void Announce(const T&)
void Announce(const Scorable auto& entry) {
    cout << "New entry: " << entry.Name() << "\n";
}

class Player {
public:
    Player(const string& name, int points)
        : name_(name), points_(points) {
    }

    string Name() const {
        return name_;
    }

    int Score() const {
        return points_;
    }

private:
    string name_;
    int points_;
};

class Monster {
public:
    explicit Monster(const string& species)
        : species_(species) {
    }

    string Species() const {
        return species_;
    }

private:
    string species_;
};

// You can ask a concept a yes/no question at compile time.
static_assert(Scorable<Player>, "Player should be Scorable");
static_assert(!Scorable<Monster>, "Monster should not be Scorable");
static_assert(!Scorable<int>, "int has no Name() or Score()");

int main() {
    cout << "Half(7)   = " << Half(7) << "\n";     // integral version
    cout << "Half(7.0) = " << Half(7.0) << "\n";   // floating_point version
    // Half(string("7"));   // Error: no Half accepts a string

    Leaderboard<Player> board(3);
    Player thorin("Thorin", 85);
    Announce(thorin);
    board.Submit(thorin);
    board.Submit(Player("Malakai", 92));
    board.Submit(Player("Rhea", 99));
    board.Print();

    // Compare this error with the one from template_07. It now fails HERE,
    // on this line, and the message says Monster doesn't satisfy Scorable.
    // Leaderboard<Monster> monsters(5);

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Uncomment  Leaderboard<Monster>.  Compare the error message with the
 *      Monster error from template_07. Which is easier to understand?
 *   2. Write a concept  Printable  that requires  cout << item  to compile.
 *      Use it to constrain PrintAll from template_08.
 *   3. Write a concept  Combatant  requiring  Name(), Health() returning
 *      something integral, and  TakeDamage(int).
 *   4. A concept checks that Score() EXISTS. What doesn't it check? (Does
 *      the score make sense? Is higher better?) Who is responsible for that?
 *****************************************************************************/
