# Copy Constructors (C++)

Now we’re getting into where C++ politely says:

> “Sure, I’ll copy that for you.”
>
> …and sometimes ruins your life.

Let’s cleanly separate:

- Do we have to write our own?
- When is it invoked?
- What does the compiler do by default?
- What happens with linked lists?

---

# 1️⃣ What Is a Copy Constructor?

A copy constructor creates a **new object** as a copy of an existing object.

Its signature looks like:

```cpp
ClassName(const ClassName& other);
```

Example:

```cpp
class Person {
private:
    std::string name;

public:
    Person(const std::string& n) : name(n) {}

    // Copy constructor
    Person(const Person& other)
        : name(other.name)
    {}
};
```

---

# 2️⃣ When Is the Copy Constructor Invoked?

It is invoked when:

### ✔ A new object is created from an existing one

```cpp
Person a("Alice");
Person b = a;     // copy constructor
Person c(a);      // copy constructor
```

### ✔ An object is passed **by value**

```cpp
void print(Person p) { }  // copy occurs

print(a);
```

### ✔ An object is returned **by value**

```cpp
Person makePerson() {
    Person p("Bob");
    return p;   // copy (sometimes optimized away)
}
```

---

# 3️⃣ Is It Invoked in This Example?

> `A = B;`

No.

That is **copy assignment**, not copy construction.

Important distinction:

| Situation                       | What Happens             |
| ------------------------------- | ------------------------ |
| `A = B;` where A already exists | Copy Assignment Operator |
| `A B = C;` (new object)         | Copy Constructor         |

Example:

```cpp
Person a("Alice");
Person b("Bob");

b = a;  // assignment, NOT copy constructor
```

The copy constructor is only used when the object is being created.

---

# 4️⃣ Do We Have to Write Our Own?

Short answer:

> Not always. But sometimes absolutely yes.

If you do not define one, the compiler generates a **default copy constructor**.

It performs a **member-wise copy**.

That means:

- Built-in types → copied
- Objects → their copy constructor is called
- Pointers → pointer address is copied

That last one is where things explode.

---

# 5️⃣ The Dangerous Case: Raw Pointers

Example:

```cpp
class BadArray {
private:
    int* data;

public:
    BadArray(int size) {
        data = new int[size];
    }
};
```

Now:

```cpp
BadArray a(10);
BadArray b = a;   // compiler-generated copy
```

What happens?

Both `a.data` and `b.data` now point to the SAME memory.

That’s called a **shallow copy**.

When destructors run?

💥 Double delete.
💥 Undefined behavior.
💥 Chaos.

---

# 6️⃣ When Is a Custom Copy Constructor Required?

You must define one when your class:

- Owns dynamic memory (`new`)
- Manages resources (files, sockets, mutexes)
- Contains raw pointers
- Needs deep copy semantics

---

# 7️⃣ Deep Copy Example

```cpp
class SafeArray {
private:
    int* data;
    int size;

public:
    SafeArray(int s) : size(s) {
        data = new int[size];
    }

    // Copy constructor
    SafeArray(const SafeArray& other)
        : size(other.size)
    {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    ~SafeArray() {
        delete[] data;
    }
};
```

Now each object owns its own memory.

No shared pointer disaster.

---

# 8️⃣ What About a Linked List?

You asked:

> If we have a class that uses a linked list to store sorted integers, will the default copy constructor handle that?

If your linked list uses raw pointers like this:

```cpp
struct Node {
    int data;
    Node* next;
};
```

And your class stores:

```cpp
Node* head;
```

Then the default copy constructor will:

- Copy the pointer
- Not copy the list
- Result in two objects pointing to the same list

Which means:
- Mutating one mutates both
- Deleting one breaks the other

So no.
The default copy constructor will NOT correctly deep-copy a linked list.

You must write your own.

---

# 9️⃣ When Is the Default Copy Constructor Fine?

It works perfectly when:

- All members are value types
- No raw pointer ownership
- No manual memory management
- You use STL containers (`vector`, `list`, `map`)

Example:

```cpp
class GoodStack {
private:
    std::vector<int> data;
};
```

`std::vector` already handles deep copying internally.

The compiler-generated copy constructor works beautifully.

---

# 1️⃣0️⃣ Big Concept: Shallow vs Deep Copy

| Type         | What Happens                                |
| ------------ | ------------------------------------------- |
| Shallow Copy | Copies pointer addresses                    |
| Deep Copy    | Allocates new memory and copies actual data |

Default copy constructor = shallow for raw pointers.

---

# 1️⃣1️⃣ Summary

- Copy constructor creates a new object from an existing one.
- It is invoked during initialization, not assignment.
- The compiler provides one automatically if you don’t.
- The default version performs member-wise copy.
- If your class owns dynamic memory, you must define your own.
- Linked lists require deep copy logic.
- STL containers generally do not require custom copy constructors.

---

