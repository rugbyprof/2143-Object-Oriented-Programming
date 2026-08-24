# The Rule of Three

The Rule of Three exists because C++ will happily generate special member functions for you…  
and those generated versions will happily destroy your program if you’re managing resources manually.

The rule states:

> If your class defines **any one** of the following:
>
> - Destructor  
> - Copy Constructor  
> - Copy Assignment Operator  
>
> You almost certainly need to define **all three**.

Why?

Because these three control **resource ownership and copying semantics**.

---

# Why This Rule Exists

The problem begins when a class owns a resource:

- Dynamic memory (`new`)
- File handles
- Sockets
- Mutexes
- Anything that must be manually released

If you define a destructor to clean it up, but leave copy behavior to the compiler, you create shallow-copy disasters.

---

# The Three Members

## 1️⃣ Destructor

Responsible for cleanup.

```cpp
~MyClass();
```

---

## 2️⃣ Copy Constructor

Creates a new object from an existing one.

```cpp
MyClass(const MyClass& other);
```

---

## 3️⃣ Copy Assignment Operator

Handles assignment between already-existing objects.

```cpp
MyClass& operator=(const MyClass& other);
```

---

# Example: A Broken Class (Violates Rule of Three)

```cpp
class BadBuffer {
private:
    int* data;
    int size;

public:
    BadBuffer(int s) : size(s) {
        data = new int[size];
    }

    ~BadBuffer() {
        delete[] data;
    }
};
```

Looks fine, right?

Now:

```cpp
BadBuffer a(10);
BadBuffer b = a;   // compiler-generated copy constructor
```

What happens?

- `a.data` and `b.data` point to same memory
- Destructor runs twice
- Double delete
- Undefined behavior

Boom.

---

# Correct Version (Rule of Three Applied)

```cpp
class GoodBuffer {
private:
    int* data;
    int size;

public:
    GoodBuffer(int s) : size(s) {
        data = new int[size];
    }

    // Copy Constructor
    GoodBuffer(const GoodBuffer& other)
        : size(other.size)
    {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    // Copy Assignment Operator
    GoodBuffer& operator=(const GoodBuffer& other) {
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];

        return *this;
    }

    // Destructor
    ~GoodBuffer() {
        delete[] data;
    }
};
```

Now:

- Each object owns its own memory
- No shared pointer problems
- No double free

That’s the Rule of Three in action.

---

# Why All Three?

Because:

| If You Define | You Probably Need |
|---------------|------------------|
| Destructor | Copy constructor + copy assignment |
| Copy constructor | Destructor + assignment |
| Copy assignment | Destructor + copy constructor |

They form a package deal when owning resources.

---

# When Rule of Three Is NOT Needed

If your class only contains:

- `int`, `double`, etc.
- `std::string`
- `std::vector`
- Other well-behaved STL containers

Then the compiler-generated versions are correct.

Modern C++ encourages:

> Use RAII classes (like `std::vector`) so you don’t manage memory manually.

---

# Enter the Rule of Five (Modern C++)

C++11 introduced move semantics.

Now we have two additional special members:

- Move Constructor
- Move Assignment Operator

Thus:

> Rule of Three → becomes Rule of Five

---

# The Five Special Members

1. Destructor
2. Copy Constructor
3. Copy Assignment Operator
4. Move Constructor
5. Move Assignment Operator

---

# Why Moves Exist

Copying large objects is expensive.

Move semantics allow:

- Transferring ownership instead of copying
- Avoiding deep copies when possible

---

# Move Constructor Example

```cpp
GoodBuffer(GoodBuffer&& other) noexcept
    : data(other.data), size(other.size)
{
    other.data = nullptr;
    other.size = 0;
}
```

Instead of copying memory:
- We steal the pointer
- Null out the source
- No allocation
- No copying loop

Much faster.

---

# Move Assignment Operator

```cpp
GoodBuffer& operator=(GoodBuffer&& other) noexcept {
    if (this == &other)
        return *this;

    delete[] data;

    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;

    return *this;
}
```

Now ownership transfers cleanly.

---

# Summary Table

| Concept | Purpose |
|----------|----------|
| Destructor | Cleanup resource |
| Copy Constructor | Deep copy when creating |
| Copy Assignment | Deep copy when assigning |
| Move Constructor | Transfer ownership during creation |
| Move Assignment | Transfer ownership during assignment |

---

# Modern Advice

If you manage resources manually:

→ Implement all five.

If you don’t want to:

→ Use smart pointers or STL containers.

Example:

```cpp
std::unique_ptr<int[]>
```

Then you probably don’t need to define any of them.

---

# Key Exam Takeaways

- Rule of Three applies when owning raw resources.
- Default copy constructor performs shallow copy.
- Shallow copy + destructor = double delete.
- Move semantics extend Rule of Three to Rule of Five.
- Modern C++ prefers RAII over manual memory management.

---
