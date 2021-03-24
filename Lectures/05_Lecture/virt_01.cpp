/**
 * @file virt_01.cpp
 * @author Prof Griffin
 * @date 2021-03-18
 * 
 */
#include <iostream>

using namespace std;

class Animal {
public:
    virtual void eat() {
    cout << "I'm eating generic food.\n"; 
}
};

// Uncomment to show error in why this method is not implemented
// in a subclass.

// class Animal{
// public:
//     virtual void eat() = 0;
// };

/**
 * @brief simple function that receives an "Animal" as input
 *        and runs the "eat" method on that animal.
 * 
 * @param someAnimal 
 */
void func(Animal *someAnimal) { 
    someAnimal->eat(); 
}

class Cat : public Animal {
public:
    void eat() { std::cout << "I'm eating a rat.\n"; }
};

class Dog : public Animal {
public:
    void eat() { std::cout << "I'm eating my own poop (Yes I'm gross).\n"; }
};

int main() {
    Animal *a = new Animal;

    a->eat();

    a = new Cat;

    a->eat();

    a = new Dog;

    a->eat();

 
}