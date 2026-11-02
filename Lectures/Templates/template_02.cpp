/*****************************************************************************
 * template_02.cpp — More Function Templates: References, Several Types,
 *                   and What a Template Requires
 *
 * What's new:
 *   - Passing T by reference (T& and const T&) to avoid copies
 *   - More than one type parameter:  template <typename A, typename B>
 *   - A template only works for types that support the operations it uses
 *   - Making YOUR class work with a template by overloading an operator
 *
 * Compile:  g++ -std=c++20 template_02.cpp -o template_02
 *****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

// Swap must change the caller's variables, so it takes T& (non-const refs).
template <typename T>
void Swap(T& first, T& second) {
    T temp = first;
    first = second;
    second = temp;
}

// const T& avoids copying large objects (like long strings) just to compare them.
template <typename T>
const T& Larger(const T& first, const T& second) {
    return first > second ? first : second;
}

// Two independent type parameters. A and B may be the same or different.
template <typename A, typename B>
void PrintPair(const A& left, const B& right) {
    cout << "(" << left << ", " << right << ")\n";
}

// ---------------------------------------------------------------------------
// A user-defined type. Out of the box, Larger(Player, Player) will NOT compile,
// because Larger uses  first > second  and Player has no operator>.
// ---------------------------------------------------------------------------
class Player {
public:
    Player(const string& name, int score)
        : name_(name), score_(score) {
    }

    const string& Name() const {
        return name_;
    }

    int Score() const {
        return score_;
    }

private:
    string name_;
    int score_;
};

// Teach C++ what "larger" means for a Player. Now Larger<Player> compiles.
bool operator>(const Player& left, const Player& right) {
    return left.Score() > right.Score();
}

// Teach C++ how to print a Player. Now PrintPair can print one too.
ostream& operator<<(ostream& out, const Player& player) {
    out << player.Name() << ":" << player.Score();
    return out;
}

int main() {
    int a = 1;
    int b = 2;
    Swap(a, b);
    cout << "a=" << a << " b=" << b << "\n";

    string first = "left";
    string second = "right";
    Swap(first, second);
    cout << "first=" << first << " second=" << second << "\n";

    PrintPair(1, 2.5);
    PrintPair(string("score"), 100);
    PrintPair('X', true);

    Player thorin("Thorin", 85);
    Player malakai("Malakai", 92);

    cout << "Winner: " << Larger(thorin, malakai) << "\n";
    PrintPair(thorin, malakai);
    Swap(thorin, malakai);    // Works: Player can be copied and assigned.
    PrintPair(thorin, malakai);

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Comment out operator> for Player. Which line fails, and does the error
 *      point at main() or inside Larger()? Why?
 *   2. List every operation Swap requires from T. (Hint: look for copies
 *      and assignments.)
 *   3. Write a template  bool InRange(const T& value, const T& low,
 *      const T& high)  and list what it requires of T.
 *   4. Why does Swap take T& but Larger take const T&?
 *****************************************************************************/
