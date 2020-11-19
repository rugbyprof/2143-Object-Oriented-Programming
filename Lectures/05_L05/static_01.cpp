#include <iostream>
#include <string>

using namespace std;

class Box {
public:
    static int boxCount;
    Box() {
        cout << "Box default Constructor called." << endl;
        length = 0;
        breadth = 0;
        height = 0;
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

    //   void printCount(){
    //       cout<<boxCount<<endl;
    //   }

    //   void setCount(int x){
    //       boxCount = x;
    //   }
    
    void printme() {
        cout << length << " " << breadth << " " << height << endl;
    }

protected:
    double length;  // Length of a box
    double breadth; // Breadth of a box
    double height;  // Height of a box
};

class subBox : public Box {
public:
    string color;
    subBox() {
        cout << "subbox default constructor called" << endl;
        color = "none";
    }
    subBox(string c, double l, double b, double h) : Box(l, b, h) {
        cout << "subbox overloaded constructor called" << endl;
        color = c;
        // length = l;
        // breadth = b;
        height = 9;
    }
};

// Initialize static member of class Box
int Box::boxCount = 0;

int main(void) {
    Box Box1(3.3, 1.2, 1.5); // Declare box1

//    Box Box2(8.5, 6.0, 2.0);    // Declare box2
//    Box Box3(8.5, 6.0, 2.0);    // Declare box2
//    Box Box4(8.5, 6.0, 2.0);    // Declare box2

    // Print total number of objects.
    cout << "Total objects: " << Box::boxCount << endl;

    subBox Bs1;
    subBox Bs2("red", 4, 5, 6);

    Bs2.printme();

    //cout<<Bs1.boxCount<<endl;

    //    Box2.setCount(88);

    //    Box4.printCount();
    return 0;
}