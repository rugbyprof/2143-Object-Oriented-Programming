#include <iostream>
#include <string>

using namespace std;

/**
 * A simple class to show the use of a static class level
 * data member. This means that EVERY instance of the class
 * will have the same copy of "boxCount" and can update it
 * or access it.
 * 
 * The peculiar thing about static data members is that they 
 * need to be initialized outside of of the class before any
 * instance is created. But is it really "peculiar"? 
 * 
 * If we initialize "boxCount" in the constructor of every
 * class ... then we re-set the value every time we create 
 * an object. So ... It needs initialized somewhere outside of
 * all the instances so it doesn't get blown away every time we
 * create a new "box". 
 */
class Box {
public:
    static int boxCount;
    Box() {
        cout << "Box default Constructor called." << endl;
        length = 0;
        breadth = 0;
        height = 0;

        // Increase every time object is created
        boxCount++;

        // if we said boxCount=1 it would set it to one
        // every time we created a new instance of a box
    }
    // Constructor definition
    Box(double l, double b, double h) {
        cout << "Box overloaded Constructor called." << endl;
        length = l;
        breadth = b;
        height = h;

        // Increase every time object is created
        boxCount++;
    }
    double Volume() {
        return length * breadth * height;
    }

    void printCount() {
        cout << boxCount << endl;
    }

    /**
     * @brief Set the value of boxCount (not a good idea)
     * @param x 
     */
    void setCount(int x) {
        boxCount = x;
    }

    void printme() {
        cout << length << " " << breadth << " " << height << endl;
    }

protected:
    double length;   // Length of a box
    double breadth;  // Breadth of a box
    double height;   // Height of a box
};

class colorBox : public Box {
public:
    string color;
    colorBox() {
        cout << "colorBox default constructor called" << endl;
        color = "none";
    }
    colorBox(string c, double l, double b, double h) : Box(l, b, h) {
        cout << "colorBox overloaded constructor called" << endl;
        color = c;
        // length = l;
        // breadth = b;
        // height = h;
    }
};

// Initialize static member of class Box
int Box::boxCount = 0;

int main(void) {
    Box Box1(3.3, 1.2, 1.5);  // Declare box1

    Box Box2(8.5, 6.0, 2.0);  // Declare box2
    Box Box3(8.5, 6.0, 2.0);  // Declare box2
    Box Box4(8.5, 6.0, 2.0);  // Declare box2

    // Print total number of objects.
    cout << "Total objects: " << Box::boxCount << endl;

    colorBox Bs1;
    colorBox Bs2("red", 4, 5, 6);

    Bs2.printme();

    cout << Bs1.boxCount << endl;

    Box2.setCount(88);

    Box4.printCount();

    return 0;
}