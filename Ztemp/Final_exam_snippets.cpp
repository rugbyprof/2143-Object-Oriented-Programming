#include <iostream>

using namespace std;

class Base
{
    int X;

public:
    Base() { cout << "Base" << endl; }
    Base(int i) { cout << "Base " << i << endl; }
    //void setX(int x){ X = x;cout<<"Base SetX "<<x<<endl;}
    virtual void setX(int) = 0;
    ~Base() { cout << "Destruct Base" << endl; }
};

class Derived : public Base
{
    int X;

public:
    Derived() { cout << "Derived" << endl; }
    Derived(int i) : Base(i) { cout << "Derived " << i << endl; }
    void setX(int x)
    {
        X = x;
        cout << "Derived SetX " << x << endl;
    }
    ~Derived() { cout << "Destruct Derived" << endl; }
};

class A
{
  public:
    int f() { return 1; }
    virtual int g() { return 2; }
};

class B : public A
{
  public:
    int f() { return 3; }
    virtual int g() { return 4; }
};

class C : public A
{
  public:
    virtual int g() { return 5; }
};

int main()
{
    // Base a;
    // Derived d(2);
    // d.setX(5);

    // Base *pb;
    // Derived dp;

    // pb = &dp;

    // pb->setX(3);

    /////////////////////////
    A *pa;
    A a;
    B b;
    C c;

    pa = &a;
    cout << pa->f() << endl;
    cout << pa->g() << endl;

    pa = &b;
    cout << pa->f() + pa->g() << endl;

    pa = &c;
    cout << pa->f() << endl;
    cout << pa->g() << endl;

    return 0;
}