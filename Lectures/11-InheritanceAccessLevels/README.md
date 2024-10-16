In C++, when a class inherits from a base class, the level of access control determines how the members of the base class are treated in the derived class. The access specifier (`public`, `protected`, or `private`) changes how the base class members are accessed within the derived class and outside of it.

### 1. **Public Inheritance** (`class Derived : public Base`)

- **Public members** of the base class remain **public** in the derived class.
- **Protected members** of the base class remain **protected** in the derived class.
- **Private members** of the base class are **not accessible** directly by the derived class, but can still be accessed via public or protected base class methods (if any).

#### Example:

```cpp
class Base {
public:
    int pubVar;
protected:
    int protVar;
private:
    int privVar;
};

class Derived : public Base {
public:
    void accessMembers() {
        pubVar = 1;    // OK: public member
        protVar = 2;   // OK: protected member
        // privVar = 3; // Error: private member
    }
};
```

- `pubVar` is accessible as `public` in `Derived`.
- `protVar` is accessible as `protected` in `Derived`.
- `privVar` is **not accessible** in `Derived`.

### 2. **Protected Inheritance** (`class Derived : protected Base`)

- **Public members** of the base class become **protected** in the derived class.
- **Protected members** of the base class remain **protected** in the derived class.
- **Private members** are still **not accessible** directly in the derived class.

#### Example:

```cpp
class Derived : protected Base {
public:
    void accessMembers() {
        pubVar = 1;    // OK: public member, but now protected in Derived
        protVar = 2;   // OK: protected member
        // privVar = 3; // Error: private member
    }
};
```

- In this case, both `pubVar` and `protVar` are treated as **protected** in `Derived`. They are not accessible outside of `Derived`, but can still be accessed by further derived classes or from within `Derived`.

### 3. **Private Inheritance** (`class Derived : private Base`)

- **Public members** of the base class become **private** in the derived class.
- **Protected members** of the base class become **private** in the derived class.
- **Private members** are still **not accessible** directly in the derived class.

#### Example:

```cpp
class Derived : private Base {
public:
    void accessMembers() {
        pubVar = 1;    // OK: public member, but now private in Derived
        protVar = 2;   // OK: protected member, but now private in Derived
        // privVar = 3; // Error: private member
    }
};
```

- In this case, both `pubVar` and `protVar` are treated as **private** in `Derived`. This means they cannot be accessed outside the `Derived` class or in classes further derived from `Derived`.

### Summary of Inheritance Access Control:

| Base Class Member | Public Inheritance | Protected Inheritance | Private Inheritance |
| ----------------- | ------------------ | --------------------- | ------------------- |
| Public            | Public             | Protected             | Private             |
| Protected         | Protected          | Protected             | Private             |
| Private           | Not Accessible     | Not Accessible        | Not Accessible      |

### Example Usage:

```cpp
int main() {
    Derived d;
    d.pubVar = 1; // OK in public inheritance
    // d.protVar = 2; // Error: protected (not accessible in public inheritance)
    // d.privVar = 3; // Always an error, private in Base
}
```

In `public` inheritance, `pubVar` is accessible from `main()`, but not in `protected` or `private` inheritance.
