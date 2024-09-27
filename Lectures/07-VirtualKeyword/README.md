## Virtual Keyword

In C++, when a method in a subclass (derived class) overrides a method in a parent class (base class), there are a few scenarios in which the overridden method in the subclass will **not** be executed:

### 1. **The Method is Not Declared as `virtual` in the Base Class**

If the method in the base class is not declared as `virtual`, then when you invoke the method on a base class pointer or reference, the method from the base class will be executed, even if the object is actually of the subclass type.

#### Example:

```cpp
#include <iostream>

class Base {
public:
    void display() {  // Not virtual
        std::cout << "Base display" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() {  // Overrides base method, but no virtual in Base
        std::cout << "Derived display" << std::endl;
    }
};

int main() {
    Base* obj = new Derived();  // Base class pointer to Derived object
    obj->display();             // Calls Base::display() because display() is not virtual
    return 0;
}
```

### Output:

```
Base display
```

#### Explanation:

Since `display()` is not marked `virtual` in the base class, C++ uses **static binding**, and the method of the **pointer's declared type** (`Base`) is called, not the actual object's method (`Derived`).

### 2. **Calling the Base Class Method Explicitly**

If you explicitly call the base class method from the derived class, the base class method will run instead of the overridden method.

#### Example:

```cpp
#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base display" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() override {
        std::cout << "Derived display" << std::endl;
    }

    void callBaseDisplay() {
        Base::display();  // Explicitly call the base class's display method
    }
};

int main() {
    Derived obj;
    obj.callBaseDisplay();  // Calls Base::display()
    return 0;
}
```

### Output:

```
Base display
```

#### Explanation:

Here, although `Derived` overrides `display()`, the base class method `Base::display()` is explicitly called using the scope resolution operator (`Base::`).

### 3. **Object Slicing**

If an object of a derived class is assigned to a variable of the base class type (not a pointer or reference), **object slicing** occurs. In this case, the base class's method will be called, even if it is declared `virtual`.

#### Example:

```cpp
#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base display" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() override {
        std::cout << "Derived display" << std::endl;
    }
};

int main() {
    Derived derivedObj;
    Base baseObj = derivedObj;  // Object slicing occurs here
    baseObj.display();          // Calls Base::display()
    return 0;
}
```

### Output:

```
Base display
```

#### Explanation:

In this case, the `Derived` object is sliced when assigned to the `Base` object, meaning only the `Base` part of the object is retained. As a result, calling `display()` on `baseObj` will execute `Base::display()`.

### 4. **Calling the Base Class Method Inside the Overridden Method**

If the subclass method explicitly calls the base class version of the method within the overridden method, the base class method will be executed as part of the overridden method.

#### Example:

```cpp
#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base display" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() override {
        Base::display();  // Explicitly calling the base class's display method
        std::cout << "Derived display" << std::endl;
    }
};

int main() {
    Derived obj;
    obj.display();  // Calls both Base::display() and Derived::display()
    return 0;
}
```

### Output:

```
Base display
Derived display
```

#### Explanation:

In this scenario, although `Derived::display()` overrides `Base::display()`, the `Base::display()` is called explicitly inside `Derived::display()`, so both methods are executed.

### 5. **Accessing the Method via the Base Class Without a Virtual Destructor**

If a base class has a non-virtual destructor, deleting a derived class object through a base class pointer can cause undefined behavior and potentially prevent the subclass’s destructor (and possibly overridden methods) from being called.

#### Example:

```cpp
#include <iostream>

class Base {
public:
    virtual void display() {
        std::cout << "Base display" << std::endl;
    }
    ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
public:
    void display() override {
        std::cout << "Derived display" << std::endl;
    }
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};

int main() {
    Base* obj = new Derived();
    delete obj;  // Only Base destructor will be called, not Derived
    return 0;
}
```

### Output:

```
Base destructor
```

#### Explanation:

Since the base class does not have a virtual destructor, deleting a derived class object through a base class pointer only calls the base class destructor, potentially leading to resource leaks or undefined behavior if the subclass's destructor relies on virtual dispatch. While this is more about destructors, it affects overall object lifecycle behavior.

---

### Conclusion:

A method in a subclass that overrides a method in the parent class might not be run in the following situations:

1. The method in the base class is not marked as `virtual`.
2. The base class method is explicitly called using the scope resolution operator.
3. Object slicing occurs when a derived object is assigned to a base class variable.
4. The base class method is called inside the overridden method.
5. The base class has a non-virtual destructor, leading to incomplete object cleanup.

Ensuring that methods are marked `virtual` and understanding these scenarios helps manage inheritance and method overriding effectively in C++.
