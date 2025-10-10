---
# :jigsaw: C++ Access Control & Inheritance 
*A Graylian-Approved Guide to Public, Protected, and Private Inheritance* 
---

## :brain: The Original Question

“Can a base class define a method as `protected`, where it can be accessed from a subclass?”
:white*check_mark: **YES.**
That’s \_exactly* what `protected` means.
It lets subclasses access a member, but keeps outsiders locked out.

---

## :gear: The Access Levels

| Access Specifier | Accessible in Same Class | Accessible in Derived Class | Accessible Outside Class |
| ---------------- | ------------------------ | --------------------------- | ------------------------ |
| `private`        | :white_check_mark:       | :x:                         | :x:                      |
| `protected`      | :white_check_mark:       | :white_check_mark:          | :x:                      |
| `public`         | :white_check_mark:       | :white_check_mark:          | :white_check_mark:       |

---

## :toolbox: Base + Derived Example

```cpp
class Base {
protected:
    void protectedMethod() {
        cout << "Base protected method called.\n";
    }
};
class Derived : public Base {
public:
    void callBaseProtected() {
        protectedMethod();  // :white_check_mark: Allowed
    }
};
int main() {
    Derived d;
    d.callBaseProtected();  // :white_check_mark: OK
    // d.protectedMethod(); // :x: Not allowed
}
```

:jigsaw: **Output:**

```
Base protected method called.
```

---

## :brain: Concept Summary

| Who Can Access? | Private            | Protected          | Public             |
| --------------- | ------------------ | ------------------ | ------------------ |
| Base Class      | :white_check_mark: | :white_check_mark: | :white_check_mark: |
| Derived Class   | :x:                | :white_check_mark: | :white_check_mark: |
| External Code   | :x:                | :x:                | :white_check_mark: |

## `protected` → “Visible to family only.”

## :compass: Inheritance Modes

Inheritance doesn’t just copy access — it _changes_ it.
| Base Member | `public` Inheritance | `protected` Inheritance | `private` Inheritance |
|--------------|----------------------|--------------------------|-----------------------|
| `public` | stays public | becomes protected | becomes private |
| `protected` | stays protected | stays protected | becomes private |
| `private` | inaccessible | inaccessible | inaccessible |

---

## :jigsaw: UML-Style Visualization

```
                +---------------------+
                |       Base          |
                +---------------------+
                | - priv : int        |
                | # prot : int        |
                | + pub  : int        |
                +---------------------+
                     ▲      ▲      ▲
                     |      |      |
      +--------------+      |      +---------------+
      |                     |                      |
+----------------+   +------------------+   +----------------+
| PublicDerived  |   | ProtectedDerived |   | PrivateDerived |
+----------------+   +------------------+   +----------------+
| +pub  (public) |   | #pub (protected) |   | -pub (private) |
| #prot (prot.)  |   | #prot (protected)|   | -prot (private)|
| -priv (none)   |   | -priv (none)     |   | -priv (none)   |
+----------------+   +------------------+   +----------------+
```

---

## :mortar_board: The Netflix Analogy

- **Public inheritance:** “My kids and the neighbors can use my Netflix.”
- **Protected inheritance:** “Only my kids can use it.”
- **Private inheritance:** “I changed the password.”

---

## :test_tube: Code Demonstration: Base + Three Derived

```cpp
class Base {
public: int pub = 1;
protected: int prot = 2;
private: int priv = 3;
};
class PublicDerived : public Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
class ProtectedDerived : protected Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
class PrivateDerived : private Base {
public:
    void show() { cout << pub << " " << prot << endl; }
};
```

From `main()`:

```cpp
PublicDerived pd;
cout << pd.pub;        // :white_check_mark: works
// cout << pd.prot;    // :x:
// cout << pd.priv;    // :x:
```

---

## :jigsaw: Output

```
[PublicDerived]  pub=1 prot=2
[ProtectedDerived] pub=1 prot=2
[PrivateDerived] pub=1 prot=2
```

Outside Access (in `main`):

```
pd.pub :white_check_mark:
pd.prot :x:
protD.pub :x:
privD.pub :x:
```

---

## :dna: Multi-Level Cascade Example

Add a **grandchild** to show inheritance visibility through generations.

```cpp
class PublicGrandchild : public PublicDerived {
    void show() { cout << pub << prot; }  // :white_check_mark: both visible
};
class ProtectedGrandchild : public ProtectedDerived {
    void show() { cout << pub << prot; }  // :white_check_mark: both visible to family only
};
class PrivateGrandchild : public PrivateDerived {
    void show() {
        // :x: pub & prot not accessible
        cout << "Base members are hidden!\n";
    }
};
```

---

## :jigsaw: Multi-Level Access Summary

| Inheritance Chain             | Base::public                 | Base::protected              | Base::private | Visibility Notes              |
| ----------------------------- | ---------------------------- | ---------------------------- | ------------- | ----------------------------- |
| Base → Public → Grandchild    | :white_check_mark: public    | :white_check_mark: protected | :x:           | fully accessible              |
| Base → Protected → Grandchild | :white_check_mark: protected | :white_check_mark: protected | :x:           | visible only within hierarchy |
| Base → Private → Grandchild   | :x:                          | :x:                          | :x:           | completely hidden             |

---

## :jigsaw: Final Rules of Thumb

| Intent                                         | Use This Inheritance |
| ---------------------------------------------- | -------------------- |
| “Is a kind of”                                 | `public`             |
| “Shares logic but not interface”               | `private`            |
| “Protected implementation for subclasses only” | `protected` (rare)   |

---

## :bulb: Key Takeaways

:white*check_mark: `protected` members are **visible to subclasses**, not outsiders.
:gear: Inheritance type \_transforms* visibility.
:lock: `private` members never pass down the line.
:dna: Access cascades: **public → protected → private** like a fading signal.
:exploding*head: Private inheritance hides base internals from \_everyone*, even grandkids.

---

## :mortar_board: “The Access Modifier Prayer”

“Grant me the serenity to `protect` what should not be public,
the courage to `public` what must be seen,
and the wisdom to `private` the rest.”
_(— Saint Stroustrup, probably)_

---

## :checkered_flag: Summary Slide

| Concept               | Description                                                                                       |
| --------------------- | ------------------------------------------------------------------------------------------------- |
| `protected` keyword   | Base method/attribute visible to derived classes                                                  |
| Public inheritance    | Keeps visibility the same                                                                         |
| Protected inheritance | Narrows public → protected                                                                        |
| Private inheritance   | Narrows everything to private                                                                     |
| Grandchild effect     | Access narrows further down the chain                                                             |
| Golden rule           | Use `public` for “is-a”, `private` for “has-a”, and rarely `protected` for “family-only helpers.” |

---
