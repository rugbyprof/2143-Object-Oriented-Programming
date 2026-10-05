## Polymorphism

**Polymorphism** ("many forms") is the ability for one interface to work with many different types. It lets objects of different classes be treated as objects of a common base type, while each still behaves according to its **actual** type. This lets you write code that is flexible and easy to extend.

C++ supports two kinds of polymorphism:

| | Static (Compile-Time) | Dynamic (Runtime) |
| --- | --- | --- |
| Decided | When the program is compiled | While the program is running |
| Mechanisms | Function overloading, operator overloading, templates | `virtual` functions called through a base-class **pointer or reference** |
| Needs `virtual`? | No | Yes |
| Needs inheritance? | No | Yes |

---

### Static Polymorphism (Compile-Time)

With static polymorphism, the compiler picks which function to call based on the **types it can see at compile time**. The most common forms are **function overloading** and **operator overloading**.

```cpp
#include <iostream>
#include <string>
using namespace std;

// Function overloading: same name, different parameter lists
void print(int x)            { cout << "int: " << x << endl; }
void print(double x)         { cout << "double: " << x << endl; }
void print(const string& s)  { cout << "string: " << s << endl; }

// Operator overloading: give '+' a meaning for our own type
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

int main() {
    print(42);          // int: 42
    print(3.14);        // double: 3.14
    print("hello");     // string: hello

    Point a(1, 2), b(3, 4);
    Point c = a + b;    // Calls Point::operator+
    cout << c.x << ", " << c.y << endl;  // 4, 6

    return 0;
}
```

The compiler looks at the argument types and picks the matching `print`. No inheritance, no `virtual`, and no runtime cost. Templates are also a form of static polymorphism (see [12-Static_Polymorphism](../12-Static_Polymorphism/README.md)).

---

### Dynamic Polymorphism (Runtime)

Dynamic polymorphism is what people usually mean when they say "polymorphism" in OOP. It requires three ingredients:

1. **Inheritance**: derived classes inherit from a common base class.
2. **A `virtual` function** in the base class that derived classes **override**.
3. **A base-class pointer or reference** used to call that function.

When all three are present, C++ decides **at runtime** which version to call, based on the object's actual type rather than the pointer's type.

### Example of Dynamic Polymorphism in C++:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Base class
class Animal {
public:
    virtual void sound() const {           // virtual enables runtime dispatch
        cout << "Some generic animal sound" << endl;
    }
    virtual ~Animal() {}                   // Always give a polymorphic base a virtual destructor
};

class Dog : public Animal {
public:
    void sound() const override {          // override: compiler checks we really override something
        cout << "Woof! Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void sound() const override {
        cout << "Meow! Meow!" << endl;
    }
};

// Works with ANY Animal, including kinds that don't exist yet
void makeSound(const Animal& animal) {
    animal.sound();
}

int main() {
    Dog myDog;
    Cat myCat;

    // 1. Through a reference
    makeSound(myDog);   // Woof! Woof!
    makeSound(myCat);   // Meow! Meow!

    // 2. Through a pointer
    Animal* animalPtr = &myDog;
    animalPtr->sound(); // Woof! Woof!
    animalPtr = &myCat;
    animalPtr->sound(); // Meow! Meow!

    // 3. A collection of mixed types: the classic use case
    vector<Animal*> zoo = { new Dog(), new Cat(), new Dog() };
    for (Animal* a : zoo) {
        a->sound();     // Woof! / Meow! / Woof!
    }
    for (Animal* a : zoo) {
        delete a;       // Safe because ~Animal() is virtual
    }

    return 0;
}
```

### Explanation:

1. **Base Class (`Animal`)**: `sound()` is declared `virtual`, meaning "derived classes may replace this, and calls through a base pointer/reference should use their version."
2. **Derived Classes (`Dog`, `Cat`)**: each overrides `sound()`. The `override` keyword is optional but strongly recommended. If you misspell the name or get the signature wrong, the compiler will give you an error instead of silently creating a new, unrelated function.
3. **Polymorphism in Action**: `makeSound()` and the `zoo` loop only know about `Animal`. At runtime, C++ looks up the real type of each object and calls the right `sound()`.
4. **Virtual Destructor**: when you `delete` a derived object through a base pointer, the base class **must** have a virtual destructor. Otherwise only `~Animal()` runs and the derived part is never cleaned up (undefined behavior).

---

### What Happens Without `virtual`? (Static Binding)

Remove `virtual` and the call is bound at compile time using the **pointer's type**, not the object's type:

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    void sound() const {                   // NOT virtual
        cout << "Some generic animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void sound() const {                   // Hides Animal::sound, does not override it
        cout << "Woof! Woof!" << endl;
    }
};

int main() {
    Dog myDog;

    myDog.sound();          // Woof! Woof!   (called directly on a Dog)

    Animal* ptr = &myDog;
    ptr->sound();           // Some generic animal sound   <-- the surprise!

    Animal& ref = myDog;
    ref.sound();            // Some generic animal sound

    return 0;
}
```

- Calling `myDog.sound()` directly works because the compiler knows it's a `Dog`. That isn't really polymorphism. It's just an ordinary function call.
- Through an `Animal*` or `Animal&`, the compiler only knows "this is an `Animal`," so it calls `Animal::sound()`, even though the object is really a `Dog`.
- This is why `virtual` matters: **it is the switch that turns on runtime dispatch.**

### Watch Out: Object Slicing

Dynamic polymorphism only works through pointers and references. If you copy a derived object **by value** into a base object, the derived part is "sliced off":

```cpp
void makeSoundByValue(Animal a) {  // Takes a COPY, and the copy is just an Animal
    a.sound();
}

makeSoundByValue(myDog);           // Some generic animal sound  (even with virtual!)
```

Pass polymorphic objects by **reference** (`const Animal&`) or **pointer** (`Animal*`), never by value.

---

### Advantages of Polymorphism:

- **Flexibility**: `makeSound()` handles any `Animal` without knowing its specific type.
- **Extensibility**: add a `Cow` class tomorrow and `makeSound()` works with it without changing a single line.
- **Cleaner Code**: replaces long `if/else` or `switch` chains on "what type is this?" with a single virtual call.

### Summary:

- **Static polymorphism** is resolved at **compile time** (overloading, operators, templates). No `virtual` needed.
- **Dynamic polymorphism** is resolved at **runtime** and requires **inheritance + `virtual` + a base pointer/reference**.
- Use `override` on overriding functions and give polymorphic base classes a **virtual destructor**.
- Passing by value **slices** the object and disables dynamic polymorphism.
