## Test 1 - Basic Stuff
#### Due: 09-24-2021 (Friday @ 12:00 p.m.)

## Study Guide

#### Class Syntax

- Be able to write a complete class definition (**no implementation**)
- For example: 
  - Write a class that represents a point in 2D space.
  - Your point does not need to hold floating point numbers 
  - It should have a default constructor, and an overloaded constructor
  - You should be able to `Move` a point by adding some values to the x and y 
  - You should be able to `Jump` the point by resetting the x and y values

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

#### Other Concepts

- Given a struct or class, overload ostream to print out each data member.

- Given a struct or class, overload a specified set of operators in order to compare or assign
  one item to another.

- Read about "self assignment" and what you need to do to handle it.

- Be able to explain Deep Copy vs Shallow Copy and when you should write a method to handle copying.

- Whats the difference between copy constructor and an overloaded assignment operator?

- There are 3 major concepts when we think about OOP. What are they, and be able to discuss them. 
  
- Static keyword

- Friend functions



### Some References

- [Course Notes](../../CourseNotes.pdf)
- https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/
- https://www.learncpp.com/cpp-tutorial/overloading-the-assignment-operator/
- https://www.learncpp.com/cpp-tutorial/the-copy-constructor/