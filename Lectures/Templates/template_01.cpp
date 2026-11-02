/*****************************************************************************
 * template_01.cpp — From Copy/Paste to a Function Template
 *
 * What's new:
 *   - The problem templates solve: identical algorithms that differ only by type
 *   - Writing a function template with  template <typename T>
 *   - Template argument deduction (the compiler figures out T)
 *   - Explicitly choosing T with  Larger<double>(...)
 *
 * Compile:  g++ -std=c++20 template_01.cpp -o template_01
 *****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// The "before" picture: three functions, one algorithm.
// If we find a bug, we have to fix it in three places.
// ---------------------------------------------------------------------------
int LargerInt(int first, int second) {
    return first > second ? first : second;
}

double LargerDouble(double first, double second) {
    return first > second ? first : second;
}

string LargerString(string first, string second) {
    return first > second ? first : second;
}

// ---------------------------------------------------------------------------
// The "after" picture: one function template.
// T is a placeholder for a type. The compiler writes the real functions
// (called instantiations) for each type we actually use.
// ---------------------------------------------------------------------------
template <typename T>
T Larger(T first, T second) {
    return first > second ? first : second;
}

int main() {
    cout << "--- Hand-written versions ---\n";
    cout << LargerInt(3, 7) << "\n";
    cout << LargerDouble(2.5, 1.5) << "\n";
    cout << LargerString("apple", "banana") << "\n";

    cout << "\n--- One template, many types ---\n";
    cout << Larger(3, 7) << "\n";                          // T deduced as int
    cout << Larger(2.5, 1.5) << "\n";                      // T deduced as double
    cout << Larger(string("apple"), string("banana")) << "\n";  // T is string
    cout << Larger('a', 'z') << "\n";                      // T is char

    // Deduction needs ONE consistent T. These disagree (int vs double):
    // cout << Larger(4, 9.2) << "\n";   // Error: conflicting types for T

    // Fix 1: tell the compiler what T is.
    cout << Larger<double>(4, 9.2) << "\n";

    // Fix 2: make the argument types agree.
    cout << Larger(4.0, 9.2) << "\n";

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Uncomment the Larger(4, 9.2) line. Read the compiler error. What two
 *      types did the compiler deduce for T?
 *   2. What does Larger("apple", "banana") (no string(...)) return, and why
 *      might it be wrong? Hint: what type is "apple"?
 *   3. Write a function template Smaller(T, T).
 *   4. How many versions of Larger does the compiler generate for main()?
 *****************************************************************************/
