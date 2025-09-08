# What Is a `unique_ptr`?

A `unique_ptr` is a smart pointer in C++ (introduced in C++11) that manages an object obtained via dynamic memory allocation. It is defined in the `<memory>` header.

## Key Characteristics

- **Exclusive Ownership:**  
  A `unique_ptr` maintains exclusive ownership of a dynamically allocated object. This means there can be only one `unique_ptr` pointing to a given object at a time. When the `unique_ptr` goes out of scope, it automatically deletes the managed object.

- **Automatic Resource Management:**  
  It implements RAII (Resource Acquisition Is Initialization), ensuring that resources are released when they are no longer needed, which helps prevent memory leaks.

- **Non-Copyable but Movable:**  
  `unique_ptr` cannot be copied (to maintain unique ownership), but it can be moved using `std::move()`, transferring ownership to another `unique_ptr`.

## Basic Example

```cpp
#include <iostream>
#include <memory>

class Monster {
public:
    Monster() { std::cout << "Monster created\n"; }
    ~Monster() { std::cout << "Monster destroyed\n"; }
    void attack() { std::cout << "Monster attacks!\n"; }
};

int main() {
    // Create a unique_ptr that manages a new Monster object.
    std::unique_ptr<Monster> monsterPtr = std::make_unique<Monster>();

    // Use the unique_ptr like a regular pointer.
    monsterPtr->attack();

    // Ownership can be transferred (moved), but not copied.
    std::unique_ptr<Monster> anotherPtr = std::move(monsterPtr);
    if (!monsterPtr) {
        std::cout << "monsterPtr is now empty after moving ownership.\n";
    }

    // When anotherPtr goes out of scope, the Monster is automatically destroyed.
    return 0;
}
```

### Benefits

- Safety:
  - Automatic deletion prevents memory leaks.
- Clear Ownership Semantics:
  - Only one owner exists at a time, reducing potential errors from multiple deletions.
- Performance:
  - unique_ptr has minimal overhead compared to raw pointers, since it doesn’t require reference counting (unlike shared_ptr).

In summary, unique_ptr is a powerful tool for managing dynamic memory in C++ safely and efficiently, ensuring that each dynamically allocated object is owned by exactly one pointer at any time.
