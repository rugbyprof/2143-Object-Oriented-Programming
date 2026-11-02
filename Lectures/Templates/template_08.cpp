/*****************************************************************************
 * template_08.cpp — Passing Behavior as a Template Parameter
 *
 * What's new:
 *   - A template parameter that is a function, lambda, or function object
 *   - Function objects (functors): classes with operator()
 *   - A class template whose BEHAVIOR is chosen by a type: SortedList<T, Compare>
 *   - Default template argument  Compare = less<T>  (from the standard library)
 *
 * OOP angle: this is the Strategy design pattern, decided at compile time.
 * SortedList doesn't hard-code what "in order" means; you plug in a strategy.
 * The standard library does the same thing: sort, map, set, priority_queue.
 *
 * Compile:  g++ -std=c++20 template_08.cpp -o template_08
 *****************************************************************************/
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Part 1: function templates that take behavior as an argument.
// Predicate can be ANY type you can call like  keep(item)  that returns bool.
// ---------------------------------------------------------------------------
template <typename T, typename Predicate>
vector<T> Filter(const vector<T>& items, Predicate keep) {
    vector<T> result;
    for (const T& item : items) {
        if (keep(item)) {
            result.push_back(item);
        }
    }
    return result;
}

template <typename T>
void PrintAll(const string& label, const vector<T>& items) {
    cout << label << ":";
    for (const T& item : items) {
        cout << " " << item;
    }
    cout << "\n";
}

// A function object: an ordinary class that overloads operator().
// Unlike a plain function, it can carry state (here, the threshold).
class AtLeast {
public:
    explicit AtLeast(int threshold)
        : threshold_(threshold) {
    }

    bool operator()(int value) const {
        return value >= threshold_;
    }

private:
    int threshold_;
};

bool IsEven(int value) {
    return value % 2 == 0;
}

// ---------------------------------------------------------------------------
// Part 2: a class template whose ordering strategy is a type parameter.
// ---------------------------------------------------------------------------
template <typename T, typename Compare = less<T>>
class SortedList {
public:
    // Insert in order, so the list is always sorted.
    void Insert(const T& item) {
        auto position = items_.begin();
        while (position != items_.end() && compare_(*position, item)) {
            ++position;
        }
        items_.insert(position, item);
    }

    const vector<T>& Items() const {
        return items_;
    }

private:
    vector<T> items_;
    Compare compare_;   // compare_(a, b) is true if a belongs before b.
};

// A custom strategy: order strings by length, shortest first.
struct ByLength {
    bool operator()(const string& left, const string& right) const {
        return left.size() < right.size();
    }
};

int main() {
    vector<int> scores = {72, 95, 88, 41, 100, 63};

    PrintAll("all", scores);
    PrintAll("even (function)", Filter(scores, IsEven));
    PrintAll(">= 80 (functor)", Filter(scores, AtLeast(80)));
    auto failing = [](int score) {
        return score < 70;
    };
    PrintAll("< 70 (lambda)", Filter(scores, failing));

    SortedList<int> ascending;                    // Uses less<int> by default
    SortedList<int, greater<int>> descending;     // Standard library strategy
    SortedList<string, ByLength> by_length;       // Our own strategy

    for (int score : scores) {
        ascending.Insert(score);
        descending.Insert(score);
    }
    vector<string> words = {"dragon", "elf", "wizard", "orc", "paladin"};
    for (const string& word : words) {
        by_length.Insert(word);
    }

    PrintAll("ascending", ascending.Items());
    PrintAll("descending", descending.Items());
    PrintAll("by length", by_length.Items());

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Write a functor  Between  that keeps values in [low, high].
 *   2. Write a strategy so SortedList<string, ...> ignores upper/lowercase.
 *   3. Are SortedList<int> and SortedList<int, greater<int>> the same type?
 *      Could you assign one to the other?
 *   4. Compare this with a design where SortedList holds a pointer to an
 *      abstract  Comparator  base class with a virtual Compare() method.
 *      When would you want the virtual version instead?
 *****************************************************************************/
