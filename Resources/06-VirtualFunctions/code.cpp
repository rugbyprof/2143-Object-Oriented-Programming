#include <iostream>
using namespace std;



class Animal
{
    public:
         void eat() { std::cout << "I'm eating generic food.\n"; }
};

void func(Animal *xyz) { xyz->eat(); }

class Cat : public Animal
{
    public:
        void eat() { std::cout << "I'm eating a rat.\n"; }
};

class Dog : public Animal
{
    public:
        void eat() { std::cout << "I'm eating m own poop.\n"; }
};

class Base {
public:
    void show() {
        cout << "In Base \n";
    }
};

class Derived : public Base {
public:
    void show() {
        cout << "In Derived \n";
    }
};

int main(void) {

    // Base *bp = new Derived;

    // Derived *d = new Derived;

    // // RUN-TIME POLYMORPHISM

    // bp->show();

    // d->show();

    Animal *animal = new Animal;
    Cat *cat = new Cat;

    animal->eat(); // Outputs: "I'm eating generic food."
    cat->eat();    // Outputs: "I'm eating a rat."

    func(animal); // Outputs: "I'm eating generic food."
    func(cat);    // Outputs: "I'm eating generic food."

    cout<<endl;
    Animal* A = new Cat;

    A->eat();

    A = new Dog;

     A->eat();

    return 0;
}