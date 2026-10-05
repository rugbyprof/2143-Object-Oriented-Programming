## Encapsulation

**Encapsulation** is one of the four fundamental principles of object-oriented programming (OOP), alongside [abstraction](03-Abstraction.md), [inheritance](04-Inheritance.md), and [polymorphism](02-Polymorphism.md). It means two things:

1. **Bundling** the data (attributes) and the methods that operate on that data into a single unit: the class.
2. **Restricting access** to the object's internals, so the outside world can only interact with it through a small, well-defined public interface.

In practice we make data members **private** and expose **public** methods (often getters and setters) that control how that data is read or changed. The goal is to **protect the object's invariants**: the rules that must always be true for the object to be valid (a `Fraction` never has a zero denominator, a `BankAccount` balance never goes negative, etc.).

> A good way to think about it: the class is responsible for its own data. Nobody else gets to reach in and mess with it.

### Key Benefits of Encapsulation:

1. **Data Hiding**: Internal details of an object are hidden from the outside world.
2. **Controlled Access**: The only way to access or modify an object's data is through well-defined interfaces, which can **validate** changes and prevent misuse.
3. **Modularity / Easier Maintenance**: You can change *how* a class stores or computes something without breaking the code that uses it, as long as the public interface stays the same.
4. **Valid State**: Objects can guarantee they are never left in a broken or inconsistent state.

### Example of Encapsulation in C++:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;   // Private: only Person's methods can touch these
    int age;

public:
    Person(string n, int a) : name("Unknown"), age(0) {
        setName(n);    // Reuse the setters so the constructor validates too
        setAge(a);
    }

    // Getters: read-only access (const means they can't change the object)
    string getName() const { return name; }
    int getAge() const { return age; }

    // Setters: controlled write access with validation
    void setName(const string& n) {
        if (!n.empty()) {
            name = n;
        } else {
            cout << "Invalid name!" << endl;
        }
    }

    void setAge(int a) {
        if (a > 0) {
            age = a;
        } else {
            cout << "Invalid age!" << endl;
        }
    }
};

int main() {
    Person person("Alice", 30);

    cout << person.getName() << endl;  // Alice
    cout << person.getAge() << endl;   // 30

    person.setName("Bob");
    person.setAge(-5);                 // Invalid age! (age stays 30)

    // person.age = -5;                // Compile error: 'age' is a private member

    return 0;
}
```

### Explanation:

1. `name` and `age` are declared under `private:`, so code outside the class **cannot** read or write them directly. The compiler enforces this.
2. The getters (`getName`, `getAge`) are marked `const`, promising they don't modify the object.
3. The setters (`setName`, `setAge`) are the *only* way to change the data, and they reject bad values.
4. The constructor calls the setters, so even a newly created `Person` gets validated.

### Encapsulation in Python:

Python has no `private` keyword. Instead it relies on **conventions**:

- `_name` (one underscore): "this is internal, please don't touch it."
- `__name` (two underscores): triggers **name mangling**. Python renames it to `_Person__name`, so `person.__name` fails from outside. This makes accidental access harder, but it is **not** truly private.

The Pythonic way to write getters and setters is with `@property`:

```python
class Person:
    def __init__(self, name, age):
        self.name = name   # Goes through the setter below
        self.age = age

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        if value <= 0:
            raise ValueError("Age must be positive")
        self._age = value

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        if not value:
            raise ValueError("Name cannot be empty")
        self._name = value


person = Person("Alice", 30)
print(person.age)   # 30  (looks like a plain attribute, but calls the getter)
person.age = 35     # calls the setter, which validates
# person.age = -5   # ValueError: Age must be positive
```

### C++ vs Python at a Glance:

| | C++ | Python |
| --- | --- | --- |
| Access control | `public`, `protected`, `private` keywords | Naming conventions (`_x`, `__x`) |
| Enforced by | The compiler (hard error) | Convention (and name mangling for `__x`) |
| Getter/setter style | `getX()` / `setX()` methods | `@property` |

### Common Mistakes:

- **Making everything public.** If every member is public, you have a struct with extra steps and no protection.
- **Writing a getter and setter for every field without thinking.** A setter that accepts anything is no better than a public variable. Only expose what users of the class actually need.
- **Returning a non-const reference to private data** (e.g., `vector<int>& getData()`). This lets callers modify your internals directly, bypassing encapsulation.

### Summary:

Encapsulation keeps an object's data private and forces all access through a controlled public interface. This protects the object's state, lets the class validate changes, and lets you change the implementation later without breaking code that uses the class.
