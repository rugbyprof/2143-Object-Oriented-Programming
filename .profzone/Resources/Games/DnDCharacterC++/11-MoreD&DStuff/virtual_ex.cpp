#include <iostream>
using namespace std;

// Base class
class Animal {
   public:
    void sound() const {
        cout << "Some generic animal sound" << endl;
    }
};

// // Derived class - Dog
// class Dog : public Animal {
//    public:
//     void sound() const override {
//         cout << "Woof! Woof!" << endl;
//     }
// };

// // Derived class - Cat
// class Cat : public Animal {
//    public:
//     void sound() const override {
//         cout << "Meow! Meow!" << endl;
//     }
// };

// Derived class - Dog
class Dog : public Animal {
   public:
    void sound() {
        cout << "Woof! Woof!" << endl;
    }
};

// Derived class - Cat
class Cat : public Animal {
   public:
    void sound() {
        cout << "Meow! Meow!" << endl;
    }
};

// Function to demonstrate polymorphism
void makeSound(const Animal& animal) {
    animal.sound();  // Calls the appropriate sound() method based on the actual object type
}

int main() {
    Animal* animal;
    Dog myDog;
    Cat myCat;

    animal = &myDog;
    animal->sound();  // Output: Woof! Woof!

    animal = &myCat;
    animal->sound();  // Output: Meow! Meow!

    makeSound(myDog);  // Output: Woof! Woof!
    makeSound(myCat);  // Output: Meow! Meow!

    myDog.sound();
    myCat.sound();

    return 0;
}