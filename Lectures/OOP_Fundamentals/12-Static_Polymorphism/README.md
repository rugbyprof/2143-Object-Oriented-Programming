## Static Polymorphism

**Static polymorphism** is a type of polymorphism that is resolved at **compile-time** rather than at runtime. It is typically achieved using **templates** or **function overloading** in C++, where the exact method to be called is determined during the compilation process based on the types of the arguments or the template parameters.

Static polymorphism contrasts with **dynamic polymorphism**, where the method to be invoked is determined at runtime, usually using virtual functions and inheritance.

### Key Concepts of Static Polymorphism:

1. **Compile-Time Resolution**: The method or function is chosen during compilation, leading to faster execution because no dynamic dispatch is required.
2. **No Runtime Overhead**: Since the method resolution occurs at compile-time, there is no need for runtime checks or vtables, making static polymorphism more efficient than dynamic polymorphism.
3. **Function Overloading and Template Specialization**: Static polymorphism is typically implemented through function overloading or templates, where multiple methods with the same name exist, but with different parameter types.

### Techniques for Static Polymorphism:

#### 1. **Function Overloading**

In function overloading, multiple functions with the same name but different parameter types are defined. The appropriate function is selected at compile-time based on the types of arguments passed.

```cpp
#include <iostream>

void print(int value) {
    std::cout << "Integer: " << value << std::endl;
}

void print(double value) {
    std::cout << "Double: " << value << std::endl;
}

int main() {
    print(10);       // Calls print(int)
    print(10.5);     // Calls print(double)
}
```

In this example, the function `print()` is overloaded, and the correct version is chosen at compile-time based on the type of the argument.

#### 2. **Templates**

Templates allow functions and classes to work with generic types, and the appropriate type is determined at compile-time.

```cpp
#include <iostream>

template<typename T>
void print(T value) {
    std::cout << "Value: " << value << std::endl;
}

int main() {
    print(10);       // Calls print<int>
    print(10.5);     // Calls print<double>
}
```

In this case, the `print()` function works with any type (`T`), and the exact version of the function is instantiated at compile-time based on the argument type passed.

#### 3. **CRTP (Curiously Recurring Template Pattern)**

The **Curiously Recurring Template Pattern (CRTP)** is a technique used to implement static polymorphism in C++. It involves a derived class inheriting from a base class that is templated on the derived class itself. This allows compile-time polymorphic behavior.

```cpp
#include <iostream>

// Base class templated on the derived class
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }

    // Default implementation
    void implementation() {
        std::cout << "Base implementation" << std::endl;
    }
};

// Derived class inheriting from Base
class Derived : public Base<Derived> {
public:
    // Override implementation in derived class
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

int main() {
    Derived d;
    d.interface();   // Calls Derived::implementation() through CRTP
}
```

In this example, `Derived` inherits from `Base<Derived>`, and the method `implementation()` is statically chosen during compile-time without the need for dynamic dispatch. This provides polymorphic behavior without the runtime cost of virtual function calls.

### Advantages of Static Polymorphism:

- **Efficiency**: Since everything is resolved at compile-time, static polymorphism avoids the runtime overhead of virtual function dispatch, making it more efficient for performance-critical applications.
- **Type Safety**: Static polymorphism is type-safe because the type checking happens during compilation, reducing the chances of runtime errors.

### Disadvantages of Static Polymorphism:

- **Code Bloat**: Since each type instantiates a new version of a template or function, static polymorphism can lead to code bloat if many different types are used.
- **Reduced Flexibility**: Unlike dynamic polymorphism, static polymorphism requires that all types and methods be known at compile-time, making it less flexible for situations where runtime behavior needs to be modified.

### Summary:

Static polymorphism is a compile-time mechanism that provides polymorphic behavior through function overloading, templates, or CRTP, allowing for highly efficient code without the runtime overhead associated with dynamic polymorphism. It’s widely used in situations where performance is critical, such as in template-based programming and libraries like the C++ Standard Template Library (STL).
