## Public vs Private - Intro to Access Control in OOP

#### Due: NA

In object-oriented programming (OOP), **methods** (functions within a class) can have different **access levels** depending on their intended use. The two main levels you'll encounter are **public** and **private**. These access levels control whether other parts of a program can directly interact with the methods of a class.

#### Public Methods

- **Definition**: A **public method** is a method that can be accessed from outside the class. This means any other part of the program (other objects, functions, etc.) can call and use this method.

- **Usage**: Public methods are generally part of the **interface** that a class provides to interact with other parts of the program. They represent the behavior of the class that is meant to be publicly available.

- **Example**: In a `Fraction` class, methods like `add()`, `subtract()`, or an overloaded `+` operator might be public, since these operations are intended to be used outside the class by users of the class.

```cpp
class Fraction {
public:
    // Public constructor
    Fraction(int num, int den) : numerator(num), denominator(den) {}

    // Public method to add fractions
    Fraction operator+(const Fraction& other) {
        // Implementation for adding fractions
    }
};
```

In this example, the `operator+` method is public and allows anyone to add fractions by simply using `+`.

#### **Private Methods**

- **Definition**: A **private method** is a method that can only be accessed from within the class where it is defined. No other part of the program, not even derived classes, can directly call a private method.

- **Usage**: Private methods are usually **helper functions** or methods that handle internal operations of the class. These methods are not intended to be accessed by outside code and are only used by other methods within the class.

- **Example**: In a `Fraction` class, you might have methods like `lcd()` (to find the least common denominator) or `lcm()` (to find the least common multiple). These methods are used internally by the `+` operator and are not meant to be accessed directly by the user.

```cpp
class Fraction {
private:
    int numerator;
    int denominator;

    // Private helper method to calculate LCM
    int lcm(int a, int b) {
        // Implementation to find least common multiple
    }

    // Private helper method to calculate LCD
    int lcd(int a, int b) {
        // Implementation to find least common denominator
    }

public:
    // Public method to add fractions using private LCM/LCD methods
    Fraction operator+(const Fraction& other) {
        // Calls lcm() and lcd() internally
    }
};
```

In this example, the `lcm()` and `lcd()` methods are private because they are internal details of how the class works. They are not meant to be called directly by users of the class.

---

### **When to Use Public vs Private**

- **Public Methods**: Use public methods when you want to provide an **interface** for external code to interact with your class. These methods define how users of the class can manipulate and access its data.

  - Example: You would likely make the `operator+` in a `Fraction` class public, so that users can easily add fractions using `fraction1 + fraction2`.

- **Private Methods**: Use private methods for **internal logic** that shouldn’t be exposed to users of the class. These methods are only needed to support the internal workings of other public methods.
  - Example: The methods to calculate the least common denominator (LCD) or least common multiple (LCM) would likely be private, since they are just tools used to implement public operations like addition or subtraction of fractions.

---

### **Conclusion**

- **Public methods** provide a way for the user to interact with an object, and they form the class’s interface to the outside world.

- **Private methods** encapsulate internal details that are not meant to be accessed or modified directly by the user. This allows the class to maintain control over how its internal operations are handled, ensuring that external code does not interfere with its internal logic.

This distinction helps maintain **encapsulation**, a key principle of OOP, where the internal state and behavior of a class are protected from unintended interference, while still offering a well-defined interface for interacting with the class.
