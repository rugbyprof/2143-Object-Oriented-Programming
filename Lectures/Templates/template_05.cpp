/*****************************************************************************
 * template_05.cpp — Non-Type Parameters and Default Template Arguments
 *
 * What's new:
 *   - A template parameter can be a VALUE, not just a type:
 *       template <typename T, size_t Capacity>
 *   - That value must be known at compile time
 *   - The value becomes part of the type:  Inventory<int, 4> != Inventory<int, 8>
 *   - Default template arguments:  template <typename T = int>
 *
 * Compile:  g++ -std=c++20 template_05.cpp -o template_05
 *****************************************************************************/
#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// A fixed-size inventory. Capacity is baked in at compile time, so it can
// back the storage with std::array (no dynamic memory needed).
template <typename T, size_t Capacity>
class Inventory {
public:
    bool Add(const T& item) {
        if (count_ == Capacity) {
            return false;
        }
        items_[count_] = item;
        ++count_;
        return true;
    }

    const T& At(size_t index) const {
        if (index >= count_) {
            throw out_of_range("Inventory::At: bad index");
        }
        return items_[index];
    }

    size_t Count() const {
        return count_;
    }

    // constexpr: this can be evaluated at compile time, because Capacity is.
    constexpr size_t MaxSize() const {
        return Capacity;
    }

private:
    array<T, Capacity> items_{};
    size_t count_ = 0;
};

// Default template argument: if you don't say, T is int.
template <typename T = int>
class Counter {
public:
    void Increment() {
        ++value_;
    }

    T Value() const {
        return value_;
    }

private:
    T value_{};   // {} gives a "zero" value for any T: 0, 0.0, false, ...
};

int main() {
    Inventory<string, 3> backpack;
    backpack.Add("Longsword");
    backpack.Add("Shield");
    backpack.Add("Torch");

    if (!backpack.Add("Rope")) {
        cout << "Backpack is full (" << backpack.MaxSize() << " slots)\n";
    }

    for (size_t i = 0; i < backpack.Count(); ++i) {
        cout << "  slot " << i << ": " << backpack.At(i) << "\n";
    }

    Inventory<int, 4> small;
    Inventory<int, 8> large;
    // small = large;   // Error: different capacities => different types.

    // Capacity must be a compile-time constant:
    // size_t n = 5;
    // Inventory<int, n> bad;   // Error: n is not a constant expression.
    constexpr size_t kSlots = 5;
    Inventory<int, kSlots> fine;   // OK

    Counter<> turns;            // Counter<int>
    Counter<double> distance;
    turns.Increment();
    turns.Increment();
    distance.Increment();
    cout << "Turns: " << turns.Value() << ", distance: " << distance.Value() << "\n";

    cout << small.MaxSize() << " " << large.MaxSize() << " " << fine.MaxSize() << "\n";

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Design question: when would you pass Capacity as a constructor
 *      argument instead of a template argument? List one pro and one con
 *      of each.
 *   2. Would Counter<string> compile? Would it compile if you never called
 *      Increment()? Explain.
 *   3. Add a default for Capacity so  Inventory<string> pouch;  holds 10.
 *   4. Find a standard library template that takes a non-type parameter.
 *****************************************************************************/
