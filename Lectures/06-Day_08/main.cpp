#include <iostream>
#include <string>

using namespace std;

// Base class
class Parent {
public:
  virtual void print() { cout << "Parent's print called..." << endl; }
};

// Derived Class 1
class Son : public Parent {
public:
  void print() { cout << "Son's print called..." << endl; }
  void print(string name) { cout << name << " print called..." << endl; }
};

// Derived Class 2
class Daughter : public Parent {
public:
  void print() { cout << "Daughter's print called..." << endl; }
};

int main() {

  Parent *P;  // Pointer to a base class type
  Son S;      // Instance of derived class 1
  Daughter D; // Instance of derived class 2

  // Without using pointers, the "virtual" keyword doesn't
  // effect which method gets called. So the following two
  // calls to print will work as expected. This is an example
  // of `compile time polymorphism`

  cout << endl;

  S.print("Arnold");
  D.print();

  cout << endl << "===================================" << endl << endl;

  // This code will also run as expected, however if you
  // remove the VIRTUAL key word from the parents print method
  // and then run this repl again, you will see that the wrong
  // print method gets called!
  // This is an example of `run time polymorphism`.
  // The compiler needs to be informed that a method
  // may be overridden so that it can handle it appropriately
  // during run time. That is what the `virtual` keyword is
  // for.

  // P = &S;
  // P->print("Arnold");
  // P = &D;
  // P->print();

  // When you remove the virtual keyword, you will see the
  // parents print method get invoked for both print calls.
  // Thats becuase the compiler didn't expect the print method
  // to be overridden (without the virtual keyword) so it
  // invoked the print method of the parent class. When you
  // add the `virtual` keyword, you're informing the compiler
  // to "look out" for sub classes to override the parents
  // method and call the appropriate one. This only matters
  // when POINTERS are involved!
}