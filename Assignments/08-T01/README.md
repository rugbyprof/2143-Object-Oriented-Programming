## Test 1 - OOP Concepts

#### Due: 02-27-2020 (Thursday @ 12:30 p.m.)

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

### Local References

  - [Concepts](../../Resources/00-OOP/01-Concepts.md)
  - [Shallow Vs Deep Copy](../../Resources/00-OOP/02-ShallowVSDeep.md)
  - [Copy Constructor](../../Resources/00-OOP/03-CopyConstructor.md)
  - [Overloaded Assignment Operator](../../Resources/00-OOP/04-OverloadAssign.md)
  - [Abstraction vs Encapsulation](../../Resources/00-OOP/05-AbsVSEnc.md)

### Know The Difference
  - Point by point comparison with Examples:
    - Discuss Encapsulation vs Abstraction
    - Discuss Inheritance vs Composition (Is-A vs Has-A relationship)

Since I didn't put anything more substantial for inheritance vs compostion in the resources folder, here is a simple example. 

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

### Overloading

  - Read this doc carefully: [Overloading](../../Resources/05-OperatorOverloading/README.md)\!
    Questions dealing with overloading will come from here.
  - Some (not all) examples:
      - Given a struct or class, overload ostream to print out each private data member.
      - Given a struct or class, overload a specified set of operators in order to compare or assign
        one item to another.

### Copy Constructors

  - Shallow vs Deep copy
  - Given a class definition, write a copy contructor insuring that a shallow copy doesn’t happen
