/*****************************************************************************
 * template_06.cpp — Building a Generic Container: Stack<T>
 *
 * What's new:
 *   - A useful, reusable class template (the reason templates exist)
 *   - Composition: Stack<T> HAS-A vector<T> and exposes a smaller interface
 *   - Encapsulation: users can only push/pop/peek; they can't reach inside
 *   - Error handling in a template (throw when popping an empty stack)
 *   - One design, reused for ints, strings, and a user-defined Card class
 *
 * OOP angle: notice that Stack's behavior never depends on WHAT it stores.
 * "Same behavior, different stored type" is the classic signal for a template.
 *
 * Compile:  g++ -std=c++20 template_06.cpp -o template_06
 *****************************************************************************/
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class Stack {
public:
    void Push(const T& item) {
        items_.push_back(item);
    }

    T Pop() {
        if (IsEmpty()) {
            throw underflow_error("Stack::Pop on empty stack");
        }
        T top = items_.back();
        items_.pop_back();
        return top;
    }

    const T& Peek() const {
        if (IsEmpty()) {
            throw underflow_error("Stack::Peek on empty stack");
        }
        return items_.back();
    }

    bool IsEmpty() const {
        return items_.empty();
    }

    size_t Size() const {
        return items_.size();
    }

private:
    vector<T> items_;   // Composition: the vector does the storage work.
};

// A user-defined type to store. Stack<Card> needs nothing special from Card
// except that it can be copied (push_back and Pop make copies).
class Card {
public:
    Card(const string& rank, const string& suit)
        : rank_(rank), suit_(suit) {
    }

    string ToString() const {
        return rank_ + " of " + suit_;
    }

private:
    string rank_;
    string suit_;
};

int main() {
    // Stack<int>: undo history of moves
    Stack<int> undo;
    undo.Push(10);
    undo.Push(20);
    undo.Push(30);
    cout << "Undo " << undo.Pop() << ", next undo would be " << undo.Peek() << "\n";

    // Stack<string>: browser-style back button
    Stack<string> history;
    history.Push("home");
    history.Push("lectures");
    history.Push("templates");
    while (!history.IsEmpty()) {
        cout << "Back to: " << history.Pop() << "\n";
    }

    // Stack<Card>: a draw pile
    Stack<Card> draw_pile;
    draw_pile.Push(Card("Ace", "Spades"));
    draw_pile.Push(Card("7", "Hearts"));
    cout << "Drew the " << draw_pile.Pop().ToString() << "\n";
    cout << draw_pile.Size() << " card(s) left\n";

    try {
        Stack<double> empty;
        empty.Pop();
    } catch (const underflow_error& error) {
        cout << "Caught: " << error.what() << "\n";
    }

    return 0;
}

/*****************************************************************************
 * Try it:
 *   1. Write Queue<T> with Enqueue, Dequeue, Front, IsEmpty, Size.
 *      Which member variable type would you compose it from, and why?
 *   2. Why does Stack<T> use composition (HAS-A vector) instead of
 *      inheritance (IS-A vector)? What could a user do to a Stack that
 *      inherited publicly from vector<T>?
 *   3. Add  void Clear()  and  bool Contains(const T& item) const.
 *      Which one adds a new requirement on T?
 *   4. Pop() returns T by value. Why not const T&?
 *****************************************************************************/
