/*
Griffins scratch pad, nothing to see here.
*/
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template <typename T>
T Larger(T first, T second) {
    return first > second ? first : second;
}

#include <string>

template <typename T>
class Rankable {
public:
    ~Rankable() = default;

    std::string Name() const = 0;

    T Score() const = 0;

    // TODO:
    // Overload operator< to compare two Rankable objects.
    // Comparison must use Score().
};

class A {
public:
    A() {
        printf("hello A\n");
    }
    void doit() {
        printf("doit A\n");
    }
};

class B : public A {
public:
    B() {
        printf("hello B\n");
    }
    void doit() {
        printf("doit B\n");
    }
};

int main() {
    A a;
    B b;

    Rankable r;

    a.doit();
    b.doit();

    return 0;
}