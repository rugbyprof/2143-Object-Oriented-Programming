 
**QUESTION:** What is the difference between private and protected class members.

-----

**QUESTION:** What is the **`this`** keyword. Give an example of when you would use `this`

-----

**QUESTION:** 

In geometry, a point is a position in space. We can define a point in 3d-space as the set of coordinates x, y, and z. For example, the Point(2.0, 1.0, 0.0) would be the point at coordinate space x=2.0, y=1.0, and z=0.0.

In physics, a vector is a quantity that has a magnitude (length) and a direction (but no position). We can define a vector in 3d-space as an x, y, and z value representing the direction of the vector along the x, y, and z axis (the length can be derived from these). For example, the Vector(2.0, 0.0, 0.0) would be a vector representing a direction along the positive x-axis (only), with length 2.0.

A Vector can be applied to a Point to move the Point to a new position. This is done by adding the vector’s direction to the point’s position to yield a new position. For example, Point(2.0, 1.0, 0.0) + Vector(2.0, 0.0, 0.0) would yield the point (4.0, 1.0, 0.0).

Points and Vectors are often used in computer graphics (the point to represent vertices of shape, and vectors represent movement of the shape).

Given the following program:

```cpp
#include <iostream>

class Vector3d {
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0): m_x{x}, m_y{y}, m_z{z} {}

    void print() const {
        std::cout << "Vector(" << m_x << " , " << m_y << " , " << m_z << ")\n";
    }
};

class Point3d {
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point3d(double x = 0.0, double y = 0.0, double z = 0.0): m_x{x}, m_y{y}, m_z{z} {}

    void print() const {
        std::cout << "Point(" << m_x << " , " << m_y << " , " << m_z << ")\n";
    }

    void moveByVector(const Vector3d &v) {
        // implement this function as a friend of class Vector3d
    }
};

int main() {
    Point3d p{1.0, 2.0, 3.0};
    Vector3d v{2.0, 2.0, -3.0};

    p.print();
    p.moveByVector(v);
    p.print();

    return 0;
}
```
1. Make `Point3d` a friend class of `Vector3d`, and implement function `Point3d::moveByVector()`
2. Instead of making class `Point3d` a friend of class `Vector3d`, make member function `Point3d::moveByVector` a friend of class `Vector3d`.

-----

**QUESTION:**  Whats the output?

```cpp
#include <iostream>
using namespace std;
class Top {
public:
    virtual void MyMemory() { cout << "I forget" << endl; };
    void Disk() { cout << "Space" << endl; };
    void Erased() { cout << "For good" << endl; };
    void ThisExam() {
        Erased();
        MyMemory();
    };
    virtual ~Top() {}
};
class Bottom : public Top {
public:
    void MyMemory() { cout << "Gone" << endl; };
    void Disk() { cout << "Slipped" << endl; };
    void virtual Erased() { cout << "Rubbed out" << endl; };
};
int main() {
    Top *Hat = new Bottom;
    Hat->MyMemory();
    Hat->Disk();
    Hat->ThisExam();
    Top Dog = *(new Bottom);
    Dog.MyMemory();
    Dog.Disk();
    Dog.ThisExam();
}
```

-----

**QUESTION:**  Whats the output?

```cpp
#include <iostream>
using namespace std;

class Polygon {
protected:
    int width, height;

public:
    void set_values(int a, int b) {
        width = a;
        height = b;
    }
};

class Rectangle : public Polygon {
public:
    int area() { return width * height; }
};

class Triangle : public Polygon {
public:
    int area() { return width * height / 2; }
};

int main() {
    Rectangle rect;
    Triangle trgl;
    Polygon *ppoly1 = &rect;
    Polygon *ppoly2 = &trgl;
    ppoly1->set_values(4, 5);
    ppoly2->set_values(4, 5);
    cout << rect.area() << '\n';
    cout << trgl.area() << '\n';
    return 0;
}
```
-----

**QUESTION:**  If a class has a pointer as a data member, what items should be part of the class to prevent various pointer problems and why?

-----

**QUESTION:**  Whats the output?

```cpp
#include <iostream>
using namespace std;
class Container {
public:
    int value;
    Container(int amount) {
        value = amount;
        cout << "Value " << value << endl;
    };
    ~Container() { cout << " You just killed: " << value << endl; };
};
class ExamQuestion {
public:
    Container data;
    ExamQuestion(int A) : data(A) { cout << "New Object\n"; };
    ExamQuestion(const ExamQuestion &X) : data(X.data.value + 10) { cout << "Special\n"; };
};
void TrickyPart(ExamQuestion why) {
    ExamQuestion PartB = why;
    cout << "After PartB\n";
}
int main() {
    ExamQuestion Answer(1);
    cout << "Call TrickyPart\n";
    TrickyPart(Answer);
    cout << "end" << endl;
}
```

-----

**QUESTION:**  Fix the following to make it work.

```cpp
#include <iostream>
using namespace std;
class Test {
private:
    float data;

public:
    void setData(int &value) { data = value; };
    static float getData() { return data; };
    Test(int value) : data(value){};
};
int main() {
    Test me = 10.5;
    cout << me.getData() << endl;
}
```

-----

**QUESTION:**  Fix the following to make it work.

```cpp
#include <iostream>
using namespace std;
int A = 10;
float functionB(int A, char B = 5, float C) {
    return ::A + B + C;
}
int main() {
    int A = 2;
    float X = 11.1;
    cout << functionB(A, X);
}
```

-----

**QUESTION:**  Whats the output?

```cpp
#include <iostream>
using namespace std;
class One {
public:
    void f() {
        g();
        cout << "One::f" << endl;
    }
    void g() { cout << "One::g" << endl; }
    virtual void h() { cout << "One::h" << endl; }
};
class Two : public One {
public:
    void g() { cout << "Two::g" << endl; }
    virtual void h() {
        f();
        cout << "Two::h" << endl;
    }
};
class Three : public Two {
public:
    virtual void h() {
        g();
        cout << "Three::h" << endl;
    }
};
int main() {
    One *a = new Two();
    a->h();
    cout << "----" << endl;
    One *b = new Three();
    b->h();
    cout << "----" << endl;
    b->f();
    return 0;
}
```

-----

**QUESTION:** 

In `C++`, there are many different ways to store values in variables. For a class `foo`, three of them are: 
1. the ordinary constructor(s):  `foo::foo(...)`
2. the copy constructor:  `foo::foo(const & foo other)`
3. and the assignment operator: `foo::operator=(const & foo other)`

Describe briefly how these differ by giving a one- or two-sentence explanation of what each one does, and be sure it is clear what is unique about each one that differentiates it from the others.

-----

**QUESTION:** 

Suppose we are to simulate a fast-food hamburger restaurant. Use your knowledge of fast food joints to describe at least four (4) different kinds of objects (along with their responsibilities and interactions) that would be likely to appear in an object-oriented design of running a fast food place.

-----

**QUESTION:** 

Does the default copy constructor and assignment operators provided for C++ classes perform `deep copying`, `shallow copying`, or `neither`?