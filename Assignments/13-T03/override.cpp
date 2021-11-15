// C++ program to demonstrate function overriding

#include <iostream>
using namespace std;

class Base {
   public:
    virtual void print() {
        cout << "Base Function" << endl;
    }
};

class Derived : public Base {
   public:
    void print() {
        cout << "Derived Function" << endl;
    }
};

void test1(){
    Base base;
    base.print();

    Derived derived;
    derived.print();
}

void test2(){
    // Run with the virtual keyword on Base::print() 
    // Then remove  the virtual keyword
    
    Base* base = new Base;
    base->print();

    base = new Derived;
    base->print();
}

int main() {
    test1();
    cout<<"==================="<<endl;
    test2();
    return 0;
}

