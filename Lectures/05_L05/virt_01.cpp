#include <iostream>

using namespace std;

class Animal {
public:
    virtual void eat() { std::cout << "I'm eating generic food.\n"; }
};

// class Animal{
// public:
//     virtual void eat() = 0;
// };

void func(Animal *xyz) { xyz->eat(); }

class Cat : public Animal {
public:
    void eat() { std::cout << "I'm eating a rat.\n"; }
};

class Dog : public Animal {
public:
    void eat() { std::cout << "I'm eating my own poop.\n"; }
};

int main() {
    Animal *a = new Animal;

    func(a); // Outputs: "I'm eating generic food."
    a = new Cat;

    a->eat();
    func(a); // Outputs: "I'm eating generic food."
    a = new Dog;

    a->eat();
    func(a); // Outputs: "I'm eating generic food."
    // Cat *cat = new Cat;

    // animal->eat(); // Outputs: "I'm eating generic food."
    // cat->eat();    // Outputs: "I'm eating a rat."

    func(a); // Outputs: "I'm eating generic food."
}