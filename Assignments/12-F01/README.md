## Final Exam - Study Help
#### Due: 5-11-2023 (Thursday @ 1:00 p.m.)

### Topics

- **Abstract classes**: classes that contain pure virtual functions and cannot be instantiated, used as base classes for other classes
- **Abstraction**: the process of simplifying complex systems by breaking them down into smaller, more manageable parts
- **Class**: a user-defined data type that contains data members and member functions
- **Constructors**: special member functions that are called when an object of a class is created, used to initialize its data members
  - **Default Constructor**
  - **Overloaded Constructor**
  - **Copy Constructor**
- **Destructors**: special member functions that are called when an object of a class is destroyed, used to free up any resources it was using
- **Encapsulation**: the process of hiding the implementation details of a class from the outside world, and exposing only the necessary interface for using it
- **Exceptions**: a mechanism for handling runtime errors and abnormal program termination, by throwing and catching objects that represent specific error conditions.
- **Friend functions**: functions that are not members of a class but have access to its private and protected members
- **Inheritance**: a mechanism for creating a new class (derived class) from an existing class (base class), inheriting its data members and member functions
- **Object**: an instance of a class, which can be used to access its data members and member functions
- **Operator overloading**: the process of defining custom behavior for operators such as +, -, *, /, etc. in user-defined classes
- **Overloading**: the process of defining multiple functions with the same name but different parameters, allowing them to be called with different arguments
- **Overriding**: a method in a sub class with the same name as a method in the base class. 
- **Polymorphism**: the ability of objects of different classes to be used interchangeably, by defining functions in the base class that can be overridden by derived classes
- **Static Polymorphism**: Also known as compile-time polymorphism or method overloading, it allows different functions to have the same name, but different parameters or argument types, and the compiler determines which function to call at compile-time based on the types of arguments passed to it.
- **Dynamic Polymorphism**: Also known as runtime polymorphism or method overriding, it allows a derived class to provide its own implementation of a virtual function that is already defined in its base class, and the function to be called is determined at runtime based on the actual type of the object that calls it.
- **Public**, **private**, and **protected** access modifiers: used to control the visibility of data members and member functions within a class and its derived classes
- **Pure virtual functions**: virtual functions that have no implementation in the base class, and must be overridden in derived classes
- **Shallow copy**: A shallow copy creates a new object, but its contents are still references to the original object's contents, so modifying the original object will also affect the copied object.
- **Deep copy**: A deep copy creates a new object with its own memory space, and its contents are not references to the original object's contents, so modifying the original object will not affect the copied object.
- **Static**: keyword is used to define a class member (variable or function) that belongs to the class itself, rather than to individual instances of the class.
- **Templates**: a mechanism for creating generic classes and functions that can work with any data type
- **Virtual functions**: member functions that can be overridden in derived classes, allowing for polymorphism and dynamic binding

### Some Questions

- When do we need to overload the assignment operator?
- When do we need a copy constructor?
- Do we need to use the virtual keyword if we want to override a method?
- What are the ways for an external class to access another classes private data members?

---

- Is the following snippet a good example of encapsulation?
```cpp
struct Fraction { 
	int numerator; 
	int denominator;
		
	void set(int n,int d){ 
		numerator = n;
		denominator = d;
	} 
	
	void print(){ 
		cout<<numerator<<"/"<<denominator<<endl;
	} 
}; 
```

---

- Given the struct below that represents an account, create a BankClient class that extends Account but does NOT give the BankClient direct access to the balance in its parent. We don’t want any public access to the balance. Rewrite any existing code to meet your needs if necessary

```cpp
struct Account {

    double balance;

    bool withDraw (double amnt){
        if (balance - amnt > 0){
            balance -= amnt;
            return true;
        }
        return false;
    }
};
```

---

- (a) Write a class to define a Point which holds an x and a y.
- (b) Overload ostream to print out a Point
- (c) Overload the addition operator to add two Points
- (d) Extend the Point class to now also hold a z value.

```cpp
//usage
Point2d P1;               // inits to 1,1
Point2d P2(3.4,5.6);      // inits to 3.4 , 5.6
Point2d P3 = P2;          // inits to 3.4 , 5.6
Point2d P4 = P3 + P2;     // inits to 6.8 , 11.2
point3d P5;               // inits to 0, 0, 0
Point3d P6(2.2, 2.3, 3.4) 
```

---
### The Diamond Problem

```txt
        +---------+
        |  Base   |
        +---------+
           /     \
          /       \
         /         \
+-------------+  +-------------+
|  Derived1   |  |  Derived2   |
+-------------+  +-------------+
         \         /
          \       /
           \     /
        +---------+
        | Derived3|
        +---------+

```

In this example, there is a base class Base, and two derived classes Derived1 and Derived2, both of which inherit from Base. Then, there is a third class Derived3 which inherits from both Derived1 and Derived2.

The problem arises when there is a member function or variable in Base that is overridden in both Derived1 and Derived2. When Derived3 calls that member function or variable, it is unclear which version of the function or variable to use, as there are multiple paths to the base class. This can result in unexpected behavior or compiler errors.

There are different ways to solve the diamond problem, depending on the programming language and its features. In C++, for example, the virtual keyword can be used to specify that a member function should be dynamically bound, which can resolve the ambiguity. Another approach is to use [virtual inheritance](https://en.wikipedia.org/wiki/Virtual_inheritance), which allows Derived3 to inherit only a single instance of Base, shared by both Derived1 and Derived2.

