/*****************************************************************************
 * template_03.cpp — Your First Class Template
 *
 * What's new:
 *   - template <typename T> in front of a class
 *   - Box<int> and Box<string> are two DIFFERENT classes made from one recipe
 *   - Normal OOP rules still apply: private data, public interface,
 *     constructors, const methods
 *   - Class template argument deduction (CTAD):  Box b{42};  (C++17)
 *
 * Compile:  g++ -std=c++20 template_03.cpp -o template_03
 *****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Box {
public:
    explicit Box(const T& value)
        : value_(value), changes_(0) {
    }

    const T& Get() const {
        return value_;
    }

    void Set(const T& value) {
        value_ = value;
        ++changes_;
    }

    // Store the new value and hand back the old one.
    T Replace(const T& new_value) {
        T old_value = value_;
        Set(new_value);
        return old_value;
    }

    int Changes() const {
        return changes_;
    }

private:
    T value_;       // The type of this member depends on T.
    int changes_;   // This member is always an int, no matter what T is.
};

struct Point {
    int x;
    int y;
};

int main() {
    Box<int> lives(3);
    Box<string> player_name("Thorin");
    Box<Point> spawn(Point{10, 20});

    lives.Set(5);
    string old_name = player_name.Replace("Malakai");

    cout << "Lives: " << lives.Get() << "\n";
    cout << "Name: " << player_name.Get() << " (was " << old_name << ")\n";
    cout << "Spawn: " << spawn.Get().x << "," << spawn.Get().y << "\n";
    cout << "Name changed " << player_name.Changes() << " time(s)\n";

    // CTAD: the compiler deduces Box<double> from the constructor argument.
    Box gold(12.5);
    cout << "Gold: " << gold.Get() << "\n";

    // Box<int> and Box<string> are unrelated types:
    // lives = player_name;   // Error: no conversion from Box<string> to Box<int>

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Add a method  bool IsEqualTo(const T& other) const. What does it
 *      require of T? Does Box<Point> still compile? Does it compile if you
 *      never CALL IsEqualTo on a Box<Point>? (Surprise!)
 *   2. Why is the constructor marked explicit? Try  Box<int> b = 5;
 *   3. What type does  Box message("hi");  deduce? Is that what you want?
 *   4. Draw a UML class diagram for Box<T>. Where does T go?
 *****************************************************************************/
