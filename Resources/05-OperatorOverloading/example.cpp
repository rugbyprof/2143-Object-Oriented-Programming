#include <iostream>

using namespace std;

class MyClass {
private:
    string id; // unique class id (for example purposes)
    int a;     // value to help show change using overloaded assignment operators
    int b;     // same
    int c;     // same

public:
    /**
     * Default Constructor
     * 
     * Params:
     *      void
     */
    MyClass() {
        id = "";
        a = b = c = 0;
    }

    /**
     * Overloaded Constructor
     * 
     * Params:
     *      string  id  : name of instance (for display purposes)
     *      int     a   : so we have an val to overload operators with
     *      int     b   : same
     *      int     c   : same
     */
    MyClass(string id, int a, int b, int c) : id{id}, a{a}, b{b}, c{c} {}

    /**
     * Public Methods
     */
    friend ostream &operator<<(ostream &, const MyClass &);
    MyClass &operator=(const MyClass &);
    const MyClass operator+(const MyClass &) const;
    MyClass &operator+=(const MyClass &);
    bool operator==(const MyClass &) const;
};

/**
 * params:
 *      const MyClass &rhs : An instance of a `MyClass` passed in by reference
 * returns:
 *      a reference to "this" (current instance of the object MyClass)
 */
MyClass &MyClass::operator=(const MyClass &rhs) {
    if (this == &rhs) { // Same object?
        cout << "oops: self assignment ..." << endl;
        return *this;
    }
    this->id = rhs.id;
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;

    return *this;
}

/**
 * params:
 *      ostream &os         :   ostream to write to
 *      const MyClass &rhs  :   instance of class to write
 *      
 * returns:
 *      an instance of ostream (print to standard out)
 */
ostream &operator<<(ostream &os, const MyClass &rhs) {
    return os << rhs.id << ": " << rhs.a << "," << rhs.b << "," << rhs.c << "\n";
}

/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to compare with
 *      
 * returns:
 *      bool (equal : true / notequal : false)
 */
bool MyClass::operator==(const MyClass &rhs) const {
    return (this->id == rhs.id) && (this->a == rhs.a) && (this->b == rhs.b) && (this->c == rhs.c);
}

/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to compare with
 *      
 * returns:
 *      dereferenced instance of "this" (current instance representation)
 */
MyClass &MyClass::operator+=(const MyClass &rhs) {
    this->id += rhs.id;     // add rhs elements to local elements
    this->a += rhs.a;       // for each data member
    this->b += rhs.b;
    this->c += rhs.c;
    return *this;
}

/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to add to
 *      
 * returns:
 *      A new instance of "MyClass" with new results in it. 
 */
const MyClass MyClass::operator+(const MyClass &rhs) const {
    MyClass result = *this;     // Make a copy of myself.  Same as MyClass result(\*this);
    result += rhs;              // Use += to add other to the copy.
    return result;              // All done!
}


/**
 * Main Program Driver 
 */
int main() {
    MyClass A("A", 1, 2, 3);    // make an instance of the class
    MyClass B("B", 4, 5, 6);    // same

    MyClass C = A + B;          // make a new instance using A+B as the content 

    cout << C << endl;          // write out instance "C" to stdout

    cout << (C + B) << endl;    // write out C + B (see what prints out)
    A += C;                     // add C to A and save answer in A
    cout << A << endl;          // write out A to stdout

    B = B;                      // try to "self assign"

    cout << B << endl;          // see what B has now

    return 0;
}
