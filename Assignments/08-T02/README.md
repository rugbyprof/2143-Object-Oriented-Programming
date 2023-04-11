## Test 2 - Basic Concepts

#### Due: 10-22-2021 (Friday @ 12:00 p.m.)

## Study Guide

Some [examples](examples.md) for lots of these topics I placed [HERE](examples.md).

### Some Class Operators

- Operators:

  - What is the dot `.` operator for?
  - What does the tilde `~` imply? (And not bitwise operations).
  - What does the `->` arrow operator imply?

### Slightly Random Statements

- Write a single C++ statement that dynamically allocates a single int and initializes it to 99.
- Write one or more C++ statements that dynamically allocates an array of 99 `ints` and initializes each one to zero

### Inheritance

- https://www.programiz.com/cpp-programming/inheritance
- Super Class vs Sub Class
- Base Class vs Derived Class
- Parent Class vs Child Class
- Multilevel vs Hierarchical vs Multiple Inheritance
- Relationships:
  - Is-A, Has-A, Kind-Of,
  - Inherit vs Composition

### Friend Function

- When is the friend keyword used?
- Can you think of an example of when not to use it?
- Some claim that using the Friend keyword breaks encapsulation. What do you find to be the answer?
- https://stackoverflow.com/questions/17434/when-should-you-use-friend-in-c
- https://isocpp.org/wiki/faq/friends
- https://www.programiz.com/cpp-programming/friend-function-class

### Polymorphism

- Compile Time Polymorphism or Static Polymorphism
- (aka early binding or Static binding)
- Function overloading
- Operator overloading
- Runtime Polymorphism or Dynamic Polymorphism
  - (aka late binding or dynamic binding)
  - Function overriding
  - Virtual Functions
- Questions:
  - What is a virtual function? Is it necessary?
  - What is a pure virtual function?
  - The destructor of base class should always be virtual. Why is that?
- https://www.programiz.com/cpp-programming/polymorphism
- https://www.programiz.com/cpp-programming/function-overriding
- https://www.programiz.com/cpp-programming/virtual-functions
- https://www.programiz.com/cpp-programming/pure-virtual-funtion

### Abstract Classes

(Overlap with virtual and pure virtual above)

- What is an abstract class?
- How can we make a class abstract?
- How many objects can be created from an abstract class?
- https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
- https://isocpp.org/wiki/faq/abcs

### Protection / Access

- Default protection of a class is?
- Default protection of a struct is?
- What can access private data members or member functions of a class?
- What type type of data member can be shared by all instances of its class?

### Class vs Definition

- Be able to compare and contrast:
  - class definition vs class implementation
  - class vs object (aka instance)

### Constructors / Destructors

- Constructors and Destructors
  - Example:
    - Which can take parameters and which cannot?
    - When are each of them run?

### Why Inheritance?

- List three reasons why it is useful to be able to inherit characteristics from parent classes
  - Code reuse: Inheritance allows code to be reused across multiple classes. By defining common functionality in a parent class,derived classes can inherit that functionality without having to implement it again.
  - Polymorphism: Inheritance enables polymorphism, which allows objects of different classes to be treated as if they were of the same class. This can simplify code and make it more flexible.
  - Hierarchical organization: Inheritance allows classes to be organized hierarchically based on their relationships to one another. This can make the code easier to understand and maintain.

### Resources

- https://www.programiz.com/cpp-programming/function-template
- https://www.programiz.com/cpp-programming/polymorphism
- https://www.programiz.com/cpp-programming/inheritance
- https://www.programiz.com/cpp-programming/public-protected-private-inheritance
- https://www.programiz.com/cpp-programming/polymorphism
- https://www.programiz.com/cpp-programming/function-overriding
- https://www.programiz.com/cpp-programming/virtual-functions
- https://www.programiz.com/cpp-programming/pure-virtual-funtion
- https://www.programiz.com/cpp-programming/multilevel-multiple-inheritance
- https://www.programiz.com/cpp-programming/friend-function-class

The course I need the questions for is Object Oriented Programming. I would like to generate some questions that will ask a student to finish or add the necessary code to an existing C++ code sample. The theme for most of my questions dealing with inheritance happens to be dungeons and dragons since character classes fit with the inheritence model. So to get started, could we simply generate a single abstract base character class that has some standard data members, and at least three pure virtual functions assuming a sub class would implement them.
