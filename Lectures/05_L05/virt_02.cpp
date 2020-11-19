#include <iostream>

using namespace std;

// The following code shows that the inherited member is accessible within the 
// class. But still even the inherited member accessing outside a class is not 
// allowed (b.xProtected) because the same rule applies to the inherited 
// member: protected member cannot be accessed from outside of a class (inherited 
// member of a parent class remains as a protected member of a child class).

class A {
public:
    int xPublic;

protected:
    int xProtected;

private:
    int xPrivate;
};

class B : public A {
public:
    void foo(A *a, B *b) {
        //a->xProtected = 0.0; // error: A::xProtected inaccessible
        b->xProtected = 0.0; // OK: inherited member
        this->xProtected = 0.0;
    }
};

int main(int argc, char **argv) {
    A a;
    B b;
    //b.xProtected = 0.0; // error: inaccessible outside of a class - inherited xProtected
    b.foo(&a, &b);

    return 0;
}