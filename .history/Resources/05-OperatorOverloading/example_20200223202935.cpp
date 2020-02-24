#include <iostream>

using namespace std;

class MyClass {
private:
    string id;
    int a;
    int b;
    int c;

public:
    MyClass() {
        id = "";
        a = b = c = 0;
    }

    /**
     * Constructor
     * 
     * Params:
     *      string  id  : name of instance (for display purposes)
     *      int     a   : so we have an val to overload operators with
     *      int     b   : same
     *      int     c   : same
     */
    MyClass(string id,int a, int b, int c) : id{id}, a{a}, b{b}, c{c} {}

    friend ostream& operator<<(ostream&, const MyClass&);
    MyClass& operator=(const MyClass &);
    const MyClass operator+(const MyClass &) const;
    MyClass& operator+=(const MyClass &);
    bool operator==(const MyClass &) const;
};

/**
 * []
 */
MyClass& MyClass::operator=(const MyClass &rhs){
    if (this == &rhs){      // Same object?
        cout<<"oops: self assignment ..."<<endl;
        return *this;
    }
    this->id = rhs.id;
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;

    return *this;

}

ostream& operator<<(ostream& os, const MyClass &rhs){
    return os << rhs.id << ": " <<rhs.a << "," << rhs.b << "," << rhs.c << "\n"; 
}

bool MyClass::operator==(const MyClass &rhs) const{
    return (this->id == rhs.id) && (this->a == rhs.a) && (this->b == rhs.b) && (this->c ==  rhs.c);
}

MyClass &MyClass::operator+=(const MyClass &rhs) {
    this->id += rhs.id;
    this->a += rhs.a;
    this->b += rhs.b;
    this->c += rhs.c;
    return *this;
}

const MyClass MyClass::operator+(const MyClass &other) const {
    MyClass result = *this; // Make a copy of myself.  Same as MyClass result(\*this);
    result += other;        // Use += to add other to the copy.
    return result;          // All done!
}

int main() {
    MyClass A("A",1,2,3);
    MyClass B("B",4,5,6);

    MyClass C = A+B;

    cout<<C<<endl;

    cout<<(C+B)<<endl;
    A += C;
    cout<<A<<endl;

    B = B;

    cout<<B<<endl;

    return 0;
}
