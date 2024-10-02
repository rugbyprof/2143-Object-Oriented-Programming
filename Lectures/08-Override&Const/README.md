## Override & Const

### Const

We already know that the `const` keyword is used to inform the compiler that no changes will be made to the item being associated with `const`. For example when used next to a parameter in a function call, we are saying we will not change the item being passed in to the function. Here are more examples of how `const` is used:

### Constant Member Function:

This snippet shows how a method can be marked as `const`, indicating that it will not modify any member variables of the class.

```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Const method - can't modify the object
    double getArea() const {
        return 3.14 * radius * radius;
    }

    // Non-const method - can modify the object
    void setRadius(double r) {
        radius = r;
    }
};

int main() {
    Circle circle(5.0);

    cout << "Area of circle: " << circle.getArea() << endl;  // Call to const method

    circle.setRadius(6.0);  // Modify radius
    cout << "New area of circle: " << circle.getArea() << endl;

    return 0;
}
```

#### Explanation:

- `getArea()` is marked as `const`, meaning it cannot modify any member variables. Attempting to modify `radius` inside this method would result in a compilation error.

### Constant Pointer to Constant Data:

This snippet shows how you can use the `const` keyword with pointers to indicate that both the pointer and the data it points to cannot be modified.

```cpp
#include <iostream>
using namespace std;

int main() {
    int value = 10;
    const int* const ptr = &value;  // Constant pointer to constant data

    // *ptr = 20;  // Error: can't modify the value
    // ptr = nullptr;  // Error: can't change where ptr points to

    cout << "Value: " << *ptr << endl;

    return 0;
}
```

#### Explanation:

- `const int* const ptr`: This declares `ptr` as a constant pointer to a constant integer. Neither the pointer itself nor the value it points to can be modified.
- Trying to modify `*ptr` or change the pointer `ptr` will result in a compilation error.

These two examples demonstrate the versatility of the `const` keyword in C++, allowing both data and function behaviors to be protected from unintended modifications.

You can also use the `const` keyword to mark a parameter passed into a function or method as **constant**, indicating that the function will not modify the parameter's value. This is especially useful when passing objects or references to ensure that they remain unchanged within the function.

### Example Passing a Constant Parameter by Reference

```cpp
#include <iostream>
using namespace std;

void printValue(const int& value) {  // The 'value' parameter is a constant reference
    // value = 10;  // Error! Cannot modify 'value' because it's declared as const
    cout << "Value: " << value << endl;
}

int main() {
    int num = 5;
    printValue(num);  // Outputs: Value: 5

    return 0;
}
```

#### Explanation:

- **`const int& value`**: The function takes a constant reference to an integer. This prevents the function from modifying the original value of `num` inside the function. Trying to modify `value` inside `printValue()` would result in a compilation error.

### Example Passing a Constant Object to a Method

```cpp
#include <iostream>
using namespace std;

class Rectangle {
private:
    double length, width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    // Const method with a const parameter
    double calculateArea(const Rectangle& rect) const {
        return rect.length * rect.width;
    }
};

int main() {
    Rectangle rect(4.0, 5.0);
    cout << "Area: " << rect.calculateArea(rect) << endl;  // Outputs: Area: 20

    return 0;
}
```

#### Explanation:

- **`const Rectangle& rect`**: The `calculateArea()` method accepts a constant reference to a `Rectangle` object, ensuring that the passed object cannot be modified within the method.
- The method itself is also marked as `const`, ensuring that it does not modify the internal state of the `Rectangle` object.

## `override`

The **`override`** keyword in C++ is used in **derived classes** to explicitly indicate that a method is intended to **override** a method in a **base class**. It is a part of C++11 and newer standards and helps make code safer by enforcing correct overriding behavior.

### Key Points:

1. **Intent Clarity**: By marking a function with `override`, you're explicitly telling the compiler that this function is meant to override a base class function.
2. **Error Detection**: If there is no matching function in the base class for the method in the derived class (either due to a typo or signature mismatch), the compiler will generate an error. This prevents silent failures where the derived class function doesn't actually override anything.

### Example of `override`:

```cpp
class Base {
public:
    virtual void display() {
        cout << "Base class display" << endl;
    }
};

class Derived : public Base {
public:
    void display() override {  // Correctly overrides the base class display method
        cout << "Derived class display" << endl;
    }
};
```

In this example, the `Derived` class correctly overrides the `display()` method from the `Base` class. If there were no matching base class method, the compiler would generate an error because of the `override` keyword.

### Why Use `override`?

Without `override`, if you mistakenly change the signature of a derived class method (or if the base class method signature changes), the compiler would assume you are creating a new method in the derived class rather than overriding the base class method. This could lead to unexpected behavior.

For example:

```cpp
class Derived : public Base {
public:
    void display(int x) override {  // Error! This doesn't match the base class method
        cout << "Derived class display" << endl;
    }
};
```

Here, the method in `Derived` has a different signature (`void display(int)` instead of `void display()`), so the compiler would throw an error because the `override` keyword is present.

### The `const` Keyword in Conjunction with `override`

In C++, the `const` keyword is used to indicate that a method does not modify the object it is called on. When used in conjunction with `override`, it ensures that the overriding method in the derived class also does not modify the object, matching the behavior of the base class method.

If the base class method is declared as `const`, the overriding method in the derived class **must** also be marked as `const`. Otherwise, the compiler will generate an error.

#### Example with `const` and `override`:

```cpp
class Base {
public:
    virtual void display() const {  // Const method in the base class
        cout << "Base class display" << endl;
    }
};

class Derived : public Base {
public:
    void display() const override {  // Correctly overrides the const base method
        cout << "Derived class display" << endl;
    }
};
```

In this case, the `display()` method in the `Base` class is marked as `const`, meaning that it cannot modify any member variables of the object. The `Derived` class method must also be marked `const` when overriding to ensure consistent behavior.

If you fail to include the `const` in the derived class method, the compiler will raise an error because the signatures won't match.

### Why Use `const`?

1. **Prevent Modifications**: Ensures that the function cannot modify the input parameter, protecting the integrity of the passed data.
2. **Efficiency**: Passing by `const` reference avoids copying large objects while ensuring the original object remains unchanged.
3. **Best Practices**: It’s considered a good practice to pass parameters by `const` reference when you don't need to modify the parameter, as it makes the intent clear.

#### Why Use `const` with `override`?

The `const` keyword ensures that:

1. The method **does not modify** the state of the object.
2. The compiler enforces **correct overriding** when the base class method is `const`.

If a method in the base class is `const`, any derived class override must also be `const` to ensure that the contract is respected, and the method doesn’t accidentally modify the object.

### Conclusion:

- **`override`** ensures that a method in a derived class actually overrides a method in the base class, preventing silent errors due to mismatched signatures.
- **`const`** in conjunction with `override` guarantees that the overriding method behaves similarly to the base class method by ensuring it cannot modify the object. If the base class method is `const`, the derived method must also be `const` to successfully override it.

These features provide stronger compile-time guarantees, helping to avoid subtle bugs related to inheritance and method overriding.


