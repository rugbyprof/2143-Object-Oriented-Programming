/**
 * Copy Constructor (shallow) example.
 * 
 * The compiler will create a copy constructor for you when you use the assignment
 * operator directly after creating a new instance of an object. But it could be 
 * beneficial to create one so you can do additional things if necessary. Otherwise
 * its ok to let the system create one for you. However if you have dynamic memory
 * (pointers) you need to create one since a shallow copy will not be ok. 
 * 
 */

#include <iostream>
#include <string>

using namespace std;

class Point {
private:
    int x;
    int y;

public:
    Point();          // Default constructor
    Point(int, int);  // Parameterized constructor
    //Point(const Point &);   // Copy constructor
    friend ostream &operator<<(ostream &, const Point &);
    Point           operator+(const Point &);
};

ostream &operator<<(ostream &os, const Point &p) {
    return os << "[" << p.x << "," << p.y << "]";
}

/**
 * @description: Default constructor. A constructor with no params.
 * 
 */
Point::Point() {
    cout << "default\n";
    x = 0;
    y = 0;
}

/**
 * @description: Parameterized constructor. A constructor with params.
 * 
 */
Point::Point(int _x, int _y) {
    cout << "params\n";
    x = _x;
    y = _y;
}

Point Point::operator+(const Point &rhs) {
    Point temp;
    temp.x = this->x + rhs.x;
    temp.y = this->y + rhs.y;
    return temp;
}

/**
 * @description: Copy constructor. A constructor that passes in another instance of
 *               the same type of object.
 * 
 * BUT is this needed?? There are no dynamically allocated items in this 
 * class. The copy constructor created by the compiler would workk just fine!
 */
// Point::Point(const Point &p) {
//     cout << "copy\n";
//     x = p.x;
//     y = p.y;
// }

// There is a copy constructor defined, but it is not needed.
// Uncomment the method definition in the class on line 25 then
// run this code. You will get an error!
//
// Why? (because you are saying you WILL define a method that
// recieves another copy of THIS class. We don't though so
// we get an error because .)
//
// Now uncomment the method on lines 60 - 64. And the code will run again.
//
// The bottom line is ... a copy constructor for a class without data elements that
// are dynamically allocated, are not necessary. We made one in this example,
// but it's not necessary.

int main() {
    Point P0;        // use default constructor
    Point P1(5, 5);  // use parameterized constructor
    Point P2(2, 3);  // use parameterized constructor
    Point P3 = P2;   // use copy constructor
    Point P4 = (P3 + P1); // use overloaded + sign AND then copy constructor

    cout << P2 << endl;
    cout << P3 << endl;
    cout << P4 << endl;
}