## Inheritance

In **C++**, inheritance lets a class (the **derived** or **child** class) acquire the data members and methods of another class (the **base** or **parent** class). The derived class can then **add** new members or **override** inherited behavior.

Inheritance models an **"is-a"** relationship: a `Dog` *is an* `Animal`. If the relationship is really **"has-a"** (a `Car` *has an* `Engine`), use **composition** (make it a member variable) instead. See [04-Inheritance](../04-Inheritance/README.md) for more on is-a vs. has-a.

### Basic Syntax and Key Rules

```cpp
class Derived : public Base {
    // new members, overrides, etc.
};
```

- **`public` inheritance** (almost always what you want): public members of `Base` stay public in `Derived`.
- A derived class can access the base class's `public` and `protected` members, but **not** its `private` members. (See [12-Inheritance_Access_Levels](../12-Inheritance_Access_Levels/README.md).)
- **Constructors run base-first**, and **destructors run derived-first**:

```cpp
#include <iostream>
using namespace std;

class Animal {
public:
    Animal()  { cout << "Animal constructor" << endl; }
    ~Animal() { cout << "Animal destructor" << endl; }
};

class Dog : public Animal {
public:
    Dog()  { cout << "Dog constructor" << endl; }
    ~Dog() { cout << "Dog destructor" << endl; }
};

int main() {
    Dog d;
    return 0;
}
// Animal constructor
// Dog constructor
// Dog destructor
// Animal destructor
```

There are several **types** of inheritance, depending on how the classes relate. All the examples below assume:

```cpp
#include <iostream>
using namespace std;
```

### 1. **Single Inheritance**:

One base class, one derived class.

```
 Animal
   |
  Dog
```

```cpp
class Animal {
public:
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        cout << "Dog is barking" << endl;
    }
};

int main() {
    Dog d;
    d.eat();    // Inherited from Animal
    d.bark();   // Dog's own method
}
```

`Dog` inherits from `Animal`, so it can use both the `eat()` method from `Animal` and its own `bark()` method.

### 2. **Multiple Inheritance**:

A class inherits from **more than one** base class and gets the members of all of them.

```
 Flyer   Swimmer
    \     /
     Duck
```

```cpp
class Flyer {
public:
    void fly() {
        cout << "Flying" << endl;
    }
};

class Swimmer {
public:
    void swim() {
        cout << "Swimming" << endl;
    }
};

class Duck : public Flyer, public Swimmer {
public:
    void quack() {
        cout << "Quack!" << endl;
    }
};

int main() {
    Duck d;
    d.fly();    // From Flyer
    d.swim();   // From Swimmer
    d.quack();  // Duck's own
}
```

A `Duck` *is a* `Flyer` and *is a* `Swimmer`, so multiple inheritance fits. (A classic bad example is `class Car : public Engine, public Wheels`. A car is not an engine; it *has* an engine. That should be composition.)

### 3. **Multilevel Inheritance**:

A class derives from another derived class, forming a **chain**.

```
 Animal
   |
 Mammal
   |
  Dog
```

```cpp
class Animal {
public:
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Mammal : public Animal {
public:
    void breathe() {
        cout << "Mammal is breathing" << endl;
    }
};

class Dog : public Mammal {
public:
    void bark() {
        cout << "Dog is barking" << endl;
    }
};
```

`Dog` inherits from `Mammal`, which inherits from `Animal`, so `Dog` has `eat()`, `breathe()`, and `bark()`.

### 4. **Hierarchical Inheritance**:

**Multiple** classes inherit from the **same** base class.

```
     Animal
    /      \
  Dog      Cat
```

```cpp
class Animal {
public:
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        cout << "Dog is barking" << endl;
    }
};

class Cat : public Animal {
public:
    void meow() {
        cout << "Cat is meowing" << endl;
    }
};
```

Both `Dog` and `Cat` inherit `eat()` from `Animal`. This is the structure that makes [polymorphism](02-Polymorphism.md) useful: code written for `Animal` works for both.

### 5. **Hybrid Inheritance**:

A **combination** of two or more of the types above.

```
 Animal
   |
 Mammal    WingedAnimal
     \       /
        Bat
```

```cpp
class Animal {
public:
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Mammal : public Animal {           // Multilevel: Animal -> Mammal -> Bat
public:
    void breathe() {
        cout << "Mammal is breathing" << endl;
    }
};

class WingedAnimal {
public:
    void fly() {
        cout << "Winged animal is flying" << endl;
    }
};

class Bat : public Mammal, public WingedAnimal {   // Multiple: Mammal + WingedAnimal
public:
    void sound() {
        cout << "Bat is making a sound" << endl;
    }
};

int main() {
    Bat myBat;
    myBat.eat();       // Inherited from Animal via Mammal
    myBat.breathe();   // Inherited from Mammal
    myBat.fly();       // Inherited from WingedAnimal
    myBat.sound();     // Bat's own method
    return 0;
}
```

This combines **multilevel** inheritance (`Animal → Mammal → Bat`) with **multiple** inheritance (`Bat` from both `Mammal` and `WingedAnimal`).

---

### 6. **The Diamond Problem**:

The **diamond problem** happens when two classes inherit from the same base, and a fourth class inherits from **both** of them:

```
    Animal
     /  \
 Mammal  Bird
     \  /
      Bat
```

```cpp
class Animal {
public:
    int age = 0;
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Mammal : public Animal {};
class Bird   : public Animal {};

class Bat : public Mammal, public Bird {};

int main() {
    Bat bat;
    bat.eat();   // ERROR: 'eat' found in multiple base-class subobjects of type 'Animal'
    bat.age = 3; // ERROR: which age? Mammal's copy or Bird's copy?
}
```

With normal inheritance, `Mammal` and `Bird` each contain their **own separate copy** of `Animal`. So a `Bat` has **two** `Animal`s inside it: two `age` variables and two `eat()` paths. The compiler refuses to guess which one you mean.

You *could* disambiguate by naming the path (`bat.Mammal::eat()` or `bat.Bird::age = 3`), but you still have two copies of `Animal`, which is almost never what you want. A bat has one age, not two.

### Solving the Diamond Problem with Virtual Inheritance:

Mark the **middle** classes with `virtual` inheritance. This tells C++ to share **one** `Animal` among everything that inherits it virtually:

```cpp
class Animal {
public:
    int age = 0;
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Mammal : virtual public Animal {};   // virtual here
class Bird   : virtual public Animal {};   // and here

class Bat : public Mammal, public Bird {};

int main() {
    Bat bat;
    bat.eat();   // OK: "Animal is eating"
    bat.age = 3; // OK: there is only one age
}
```

Now `Bat` contains exactly **one** `Animal`, so there is nothing ambiguous about `eat()` or `age`. Note that `virtual` goes on `Mammal` and `Bird`, **not** on `Bat`.

### Or Does It? The Remaining Ambiguity

Virtual inheritance fixes the *duplicate data* problem. But there is still one situation it can't solve: when **both** middle classes **override the same virtual function**.

```cpp
class Animal {
public:
    virtual void eat() {
        cout << "Animal is eating" << endl;
    }
    virtual ~Animal() {}
};

class Mammal : virtual public Animal {
public:
    void eat() override { cout << "Mammal is eating" << endl; }
};

class Bird : virtual public Animal {
public:
    void eat() override { cout << "Bird is eating" << endl; }
};

class Bat : public Mammal, public Bird {};
// ERROR: virtual function 'Animal::eat' has more than one final overrider in 'Bat'
//        (GCC words it: "no unique final overrider")
```

There is only one `Animal`, but it has one `eat()` slot, and **two** classes are fighting over what goes in it. If someone does `Animal* a = new Bat(); a->eat();`, should it print "Mammal is eating" or "Bird is eating"? C++ won't guess.

#### Solution 1: Override in `Bat` and pick a side

```cpp
class Bat : public Mammal, public Bird {
public:
    void eat() override {
        Mammal::eat();   // Explicitly choose Mammal's version
    }
};
```

#### Solution 2: Override in `Bat` with new behavior

```cpp
class Bat : public Mammal, public Bird {
public:
    void eat() override {
        cout << "Bat is eating fruit and insects" << endl;
    }
};
```

Either way, `Bat` provides the single **final overrider**, so the ambiguity is gone.

#### Solution 3: Avoid the diamond

Most of the time, the best fix is a different design. Prefer **composition** or small **interfaces** (abstract classes with no data, see [Abstraction](03-Abstraction.md)) over deep multiple-inheritance hierarchies. Languages like Java and C# don't allow multiple inheritance of classes at all, largely to avoid this problem.

### Diamond Problem Summary:

| Situation | What happens | Fix |
| --- | --- | --- |
| Normal inheritance in a diamond | Two copies of the base, so calls/fields are ambiguous | `virtual` inheritance on the middle classes |
| Virtual inheritance, base method **not** overridden | One shared base, works fine | Nothing needed |
| Virtual inheritance, **both** middle classes override the same virtual function | "More than one final overrider" error | Override the function in the bottom class |

---

### Summary of Inheritance Types:

1. **Single Inheritance**: One base class, one derived class.
2. **Multiple Inheritance**: A derived class inherits from more than one base class.
3. **Multilevel Inheritance**: A class derives from another derived class (a chain).
4. **Hierarchical Inheritance**: Multiple classes inherit from a single base class.
5. **Hybrid Inheritance**: A combination of the types above.
6. **Diamond Problem**: A shared base inherited through two paths. Fixed with **virtual inheritance**, plus an override in the bottom class if both paths override the same virtual function.

Inheritance promotes code reuse and makes [polymorphism](02-Polymorphism.md) possible, but use it only for true "is-a" relationships and keep hierarchies shallow. When in doubt, prefer composition.
