/*****************************************************************************
 * template_11.cpp — Reusable Behavior with Base-Class Templates (CRTP)
 *
 * What's new:
 *   - A base class that is a template, parameterized by the class deriving
 *     from it:   class Coin : public Comparable<Coin>
 *   - This pattern is called CRTP: the Curiously Recurring Template Pattern
 *   - Write a behavior ONCE in the base, get it in every derived class
 *   - No virtual functions: everything is resolved at compile time
 *   - Bonus: a static member is separate for every instantiation
 *
 * OOP angle: inheritance is usually used for "IS-A." Here the base classes are
 * "mixins": they add abilities to a class. Comparable<T> gives a class all six
 * comparison operators if it defines just one function, LessThan().
 *
 * Compile:  g++ -std=c++20 template_11.cpp -o template_11
 *****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// Mixin 1: write LessThan() in your class, get <, >, <=, >=, ==, != for free.
// ---------------------------------------------------------------------------
template <typename Derived>
class Comparable {
public:
    friend bool operator<(const Derived& left, const Derived& right) {
        return left.LessThan(right);
    }

    friend bool operator>(const Derived& left, const Derived& right) {
        return right.LessThan(left);
    }

    friend bool operator<=(const Derived& left, const Derived& right) {
        return !right.LessThan(left);
    }

    friend bool operator>=(const Derived& left, const Derived& right) {
        return !left.LessThan(right);
    }

    friend bool operator==(const Derived& left, const Derived& right) {
        return !left.LessThan(right) && !right.LessThan(left);
    }

    friend bool operator!=(const Derived& left, const Derived& right) {
        return !(left == right);
    }
};

// ---------------------------------------------------------------------------
// Mixin 2: count how many objects of each class are alive.
// Counted<Coin> and Counted<Gem> are different classes, so each one gets its
// OWN static counter. (Compare with the static keyword lecture.)
// ---------------------------------------------------------------------------
template <typename Derived>
class Counted {
public:
    Counted() {
        ++alive_;
    }

    Counted(const Counted&) {
        ++alive_;
    }

    ~Counted() {
        --alive_;
    }

    static int Alive() {
        return alive_;
    }

private:
    static inline int alive_ = 0;   // inline: defined right here (C++17)
};

// ---------------------------------------------------------------------------
// Classes that use the mixins. Note the "curious" part: each class passes
// ITSELF as the template argument to its base.
// ---------------------------------------------------------------------------
class Coin : public Comparable<Coin>, public Counted<Coin> {
public:
    explicit Coin(int cents)
        : cents_(cents) {
    }

    bool LessThan(const Coin& other) const {
        return cents_ < other.cents_;
    }

    int Cents() const {
        return cents_;
    }

private:
    int cents_;
};

class Gem : public Comparable<Gem>, public Counted<Gem> {
public:
    Gem(const string& name, int carats)
        : name_(name), carats_(carats) {
    }

    bool LessThan(const Gem& other) const {
        return carats_ < other.carats_;
    }

    const string& Name() const {
        return name_;
    }

private:
    string name_;
    int carats_;
};

int main() {
    Coin dime(10);
    Coin quarter(25);
    Coin another_dime(10);

    cout << boolalpha;
    cout << "dime < quarter:       " << (dime < quarter) << "\n";
    cout << "dime >= quarter:      " << (dime >= quarter) << "\n";
    cout << "dime == another_dime: " << (dime == another_dime) << "\n";

    Gem ruby("Ruby", 3);
    Gem emerald("Emerald", 5);
    cout << "Bigger gem: " << (ruby > emerald ? ruby : emerald).Name() << "\n";

    // Comparable<T> lets each class compare with ITSELF only:
    // cout << (dime < ruby);   // Error: no operator< for Coin and Gem

    cout << "Coins alive: " << Counted<Coin>::Alive() << "\n";   // 3
    cout << "Gems alive:  " << Counted<Gem>::Alive() << "\n";    // 2
    {
        Coin penny(1);
        cout << "Coins alive inside block: " << Coin::Alive() << "\n";   // 4
    }
    cout << "Coins alive after block:  " << Coin::Alive() << "\n";   // 3

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Make a  Level  class (with a number) Comparable and Counted.
 *      How many comparison operators did you have to write?
 *   2. Make Coin inherit from Counted<Gem> by mistake. What happens to
 *      the counts? Why does the compiler not catch it?
 *   3. Why can't Comparable just be a normal (non-template) base class
 *      with a virtual LessThan()? (Hint: what type would the parameter be?)
 *   4. C++20 adds operator<=> (the "spaceship" operator), which generates
 *      comparisons for you. Look it up and compare it to this mixin.
 *****************************************************************************/
