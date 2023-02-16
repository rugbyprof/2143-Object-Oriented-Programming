## Test 1 - Basic Stuff

#### Due: 02-23-2023 (Thursday @ 2:00 p.m.)

## Study Guide

#### Class Syntax

-   Be able to write a complete class definition (**no implementation**)
-   For example:

    -   Write a class that represents a fraction.
    -   Your fraction needs a numerator and denominator
    -   It should have a default constructor that sets the fraction to 1/1, and an overloaded constructor that sets the fraction to passed in params
    -   The arithmetic for this fraction is different then reality, any arithmetic operation will simply by applied from numerator => numerator and denominator=>denominator. For example: `3/4 + 5/11 = 8/15` or `1/2 * 3/8 = 3/16`
        -   Overload ostream to print a fraction so it prints like `[1/2]`
        -   Overload + sign for fractions
        -   Overload \* sign for fractions

-   If we were writing a class definition for a `Point`, here would be the `definition`. No implementation (as mentioned above) means NO CODE in the body of any function.

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

-   When I want the implementation I will ask on the exam: Show the implementation for the `Move` method:

```cpp
Point::Move(int _x,int _y){
  x += _x;
  y += _y;
}
```

### Other Study Questions

-   Given **any** struct or class, overload ostream to print out **each data member**.

-   Given a struct or class, overload a specified set of operators in order to compare or assign one item to another.

-   Read about "**self assignment**" and what you need to do to handle it.

-   Be able to explain Deep Copy vs Shallow Copy and when you should write a method to handle copying.

-   Whats the difference between copy constructor and an overloaded assignment operator?

-   There are 3 major concepts when we think about OOP. What are they, and be able to discuss them.

### Summary

-   Class syntax
-   Constructors (default, overloaded, copy)
-   Friend functions (page 45 course notes)
-   Overload Operators (page 29 course notes)
-   Overloading Assignment Operator (page 29 course notes)
-   Shallow Vs Deep Copy

### Course Notes

-   [Course Notes](../../CourseNotes.pdf)
