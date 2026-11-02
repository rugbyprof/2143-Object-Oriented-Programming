/*****************************************************************************
 * template_09.cpp — Specialization: When One Type Needs Different Behavior
 *
 * What's new:
 *   - Full specialization:     template <> class Formatter<bool> { ... }
 *   - Partial specialization:  template <typename T> class Formatter<vector<T>>
 *   - The compiler picks the MOST specialized version that matches
 *   - Function templates can't be partially specialized; overload them instead
 *
 * The generic Formatter<T> uses <<. That is fine for int and string, but
 * prints bool as 1/0 and can't print a vector at all. Specialization lets us
 * keep one name (Formatter) while customizing specific types.
 *
 * Compile:  g++ -std=c++20 template_09.cpp -o template_09
 *****************************************************************************/
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Primary template: works for anything that supports <<.
template <typename T>
class Formatter {
public:
    static string Format(const T& value) {
        ostringstream out;
        out << value;
        return out.str();
    }
};

// Full specialization: the version used when T is EXACTLY bool.
template <>
class Formatter<bool> {
public:
    static string Format(const bool& value) {
        return value ? "yes" : "no";
    }
};

// Full specialization for string: wrap it in quotes.
template <>
class Formatter<string> {
public:
    static string Format(const string& value) {
        return "\"" + value + "\"";
    }
};

// Partial specialization: the version used for vector<ANYTHING>.
// It reuses Formatter<T> for each element, so nesting works for free.
template <typename T>
class Formatter<vector<T>> {
public:
    static string Format(const vector<T>& values) {
        string result = "[";
        for (size_t i = 0; i < values.size(); ++i) {
            if (i > 0) {
                result += ", ";
            }
            result += Formatter<T>::Format(values[i]);
        }
        return result + "]";
    }
};

// A convenient function template that picks the right Formatter for you.
template <typename T>
void Show(const string& label, const T& value) {
    cout << label << " = " << Formatter<T>::Format(value) << "\n";
}

// ---------------------------------------------------------------------------
// Function templates: overload instead of partially specializing.
// ---------------------------------------------------------------------------
template <typename T>
T Total(const vector<T>& values) {
    T sum{};
    for (const T& value : values) {
        sum += value;
    }
    return sum;
}

// An overload (NOT a specialization) for vector<bool>: count the trues.
int Total(const vector<bool>& values) {
    int count = 0;
    for (bool value : values) {
        if (value) {
            ++count;
        }
    }
    return count;
}

int main() {
    Show("level", 7);
    Show("ratio", 0.75);
    Show("alive", true);
    Show("name", string("Thorin"));
    Show("scores", vector<int>{90, 85, 77});
    Show("flags", vector<bool>{true, false, true});
    Show("party", vector<string>{"Thorin", "Malakai"});
    Show("grid", vector<vector<int>>{{1, 2}, {3, 4}});

    cout << "Total damage: " << Total(vector<int>{5, 10, 15}) << "\n";
    cout << "Total gold:   " << Total(vector<double>{1.5, 2.25}) << "\n";
    cout << "Hits landed:  " << Total(vector<bool>{true, true, false, true}) << "\n";

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Delete the Formatter<bool> specialization. What does Show("alive",
 *      true) print now? Which version handles it?
 *   2. Show("name", "Thorin") (no string(...)) does NOT use Formatter<string>.
 *      What is T? How could you fix it?
 *   3. Write a Formatter<Card> specialization for a Card class of your own.
 *      Then Show a vector<Card>. Did you have to write anything extra?
 *   4. Specialization lets you change behavior for ONE type. Why is that
 *      risky in a big project? (Think: someone reads Formatter<T> and
 *      assumes it always uses <<.)
 *****************************************************************************/
