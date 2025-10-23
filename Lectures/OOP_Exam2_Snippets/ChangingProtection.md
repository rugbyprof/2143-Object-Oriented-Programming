## Changing Protection

What can happen when you change the protection of a pure virtual function?

### 🧩 **The setup**

You have a **pure virtual function** in a **base class**, like so:

```cpp
class Base {
public:
    virtual void speak() = 0;  // public pure virtual
};
```

Now, you derive from it:

```cpp
class Derived : public Base {
protected:
    void speak() override { std::cout << "Hello!\n"; }
};
```

---

### ⚙️ **So what happens?**

- The `Derived` class **successfully overrides** `speak()`. ✅
- But it **changes the access level** to `protected`. ⚠️

That means:

```cpp
Base* b = new Derived();
b->speak();   // ❌ error!  'speak' is protected in Derived
```

---

### 💡 **Key Insight**

> **Overriding a public pure virtual function does NOT force you to keep it public.**

C++ allows you to **change the access level** of an overridden function — the compiler only cares that the signature matches, not the visibility.

So even though the base class says “this function must exist,”  
it does _not_ enforce _how accessible_ it must be.

---

### 🚫 **Why this can be a problem**

If the pure virtual method was part of the **public interface** of the base class,  
then making it `protected` or `private` in the derived class **breaks the polymorphic contract** — external code can no longer call it through a base pointer or reference.

You haven’t violated syntax rules, but you’ve **broken design intent**.

---

### ✅ **Best Practice**

If the base class’s pure virtual is `public`,  
keep it `public` in all derived classes **to preserve polymorphism**.

If you intentionally want to restrict access in a derived class,  
that’s legal — but you’re effectively saying:

> “This class is still polymorphic, but not usable via the same interface.”

---

### 🧠 **Summary**

| Statement                                                                   | True/False | Why                                          |
| --------------------------------------------------------------------------- | ---------- | -------------------------------------------- |
| Defining a base method as `public` pure virtual guarantees it stays public. | ❌ False   | Derived classes can lower access level.      |
| Derived classes can override with `protected` or `private` access.          | ✅ True    | Access level is not part of the signature.   |
| Doing so can break polymorphic usability.                                   | ✅ True    | The interface contract is no longer honored. |

---

**Reflection takeaway:**

> In C++, “public” defines _who can call_ a function — not _who must keep it public_.  
> So even a `public` pure virtual function doesn’t guarantee consistent access across derived types — just consistent presence.
