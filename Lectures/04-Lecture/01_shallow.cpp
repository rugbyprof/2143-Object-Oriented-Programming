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
    Point();                // Default constructor
    Point(int, int);        // Parameterized constructor
    Point(const Point &);   // Copy constructor
    friend ostream &operator<<(ostream &, const Point &);
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

/**
 * @description: Copy constructor. A constructor that passes in another instance of
 *               the same type of object.
 */
Point::Point(const Point &p) {
    cout << "copy\n";
    x = p.x;
    y = p.y;
}


int main() {
    Point P1;       // use default constructor
    Point P2(2, 3); // use parameterized constructor
    Point P3 = P2;  // use copy constructor

    cout << P2 << endl;
    cout << P3 << endl;

}