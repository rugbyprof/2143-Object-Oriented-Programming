## Test 1 - OOP Concepts
#### Due: 02-18-2021 (Thursday @ 9:30 a.m.)

### Instructions

- Do not be late. I may not let you in.
- Bring a pencil and eraser.
  
---------

### Key Words

- Abstraction
- Attributes / Properties
- Class
- Class Variable
- Composition
- Encapsulation
- Friends
- Inheritance
- Instance Variable
- Member Variable
- Method
- Multiple Inheritance
- Object
- Overloading
- Polymorphism
- Public / Private / Protected
- Virtual

### Class Syntax

- Be able to write a complete class definition (**no implementation**)
- For example: 
  - Write a class that represents a point in 2D space.
  - Your point does not need to hold floating point numbers.
  - It should have a default constructor, and an overloaded constructor.
  - You should be able to `Move` a point by adding some values to the x and y. 
  - You should be able to `Jump` the point by resetting the x and y values.

```cpp
class Point{
private:
  int x;
  int y;
public:
  Point();
  Point(int,int);
  Move(int,int);
  Jump(int,int);
};
```

- Show the implementation for the `Move` method:

```cpp
Point::Move(int _x,int _y){
  x += _x;
  y += _y;
}
```

### Course Notes

Read the following sections:
- Introduction
- Classes and Objects
- C++ Operator Overloading
- Using Friend Functions
- Inheritance

### Know The Difference
 
- Discuss Inheritance vs Composition (Is-A vs Has-A relationship)


A polygon `Has-A` ordered sequence of points (composition).

```cpp
struct Polygon {
  std::vector<Point> points;
};
```
While an logic_error `Is-A` exception (inheritance):
```cpp
struct logic_error : public exception {
};
```

### Example Questions

- Given a struct or class, overload ostream to print out each private data member.

- Given a struct or class, overload a specified set of operators in order to compare or assign
  one item to another.

- Read about "self assignment" and what you need to do to handle it.

- There are 3 major concepts when we think about OOP. What are they, and be able to discuss them. 

-**Abstraction vs Encapsulation**:
  - Abstraction: 
    - Abstraction is one of the key concepts of object-oriented programming (OOP) languages. Its main goal is to handle complexity by hiding unnecessary details from the user. That enables the user to implement more complex logic on top of the provided abstraction without understanding or even thinking about all the hidden complexity.
  - Encapsulation:
    - Encapsulation is one of the fundamental concepts in object-oriented programming (OOP). It describes the idea of bundling  data and methods that work on that data within one unit. This concept is also often used to hide the internal representation, or state, of an object from the outside. This is called information hiding. The general idea of this mechanism is simple. If you have an attribute that is not visible from the outside of an object, and bundle it with methods that provide read or write access to it, then you can hide specific information and control access to the internal state of the object.
