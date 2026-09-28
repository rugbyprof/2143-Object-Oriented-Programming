## Inheritance (and Composition)

#### Due: None

## Examples

Read the files in order. Each one adds one idea to the same `Character` / `Warrior` / `Wizard` classes.

| #   | File                                                   | New idea                                                                  |
| --- | ------------------------------------------------------ | ------------------------------------------------------------------------- |
| 01  | [01_is_a_vs_has_a.cpp](01_is_a_vs_has_a.cpp)           | When to inherit ("is-a") vs. compose ("has-a"): `Point` / `Line`          |
| 02  | [02_basic_inheritance.cpp](02_basic_inheritance.cpp)   | `Warrior : public Character` inherits members and adds its own            |
| 03  | [03_constructor_chaining.cpp](03_constructor_chaining.cpp) | `Warrior(n) : Character(n)`, plus construction/destruction order     |
| 04  | [04_protected_access.cpp](04_protected_access.cpp)     | `public` / `protected` / `private` members from a derived class           |
| 05  | [05_redefining_methods.cpp](05_redefining_methods.cpp) | A derived class redefines a method, or calls `Character::printName()`     |
| 06  | [06_the_problem.cpp](06_the_problem.cpp)               | **Cliffhanger:** base pointers call the base version, and copies slice    |

The fix for 06 is in [13-Run_Time_Polymorphism](../13-Run_Time_Polymorphism/), starting with `07_virtual_override.cpp`.

```bash
clang++ -std=c++17 01_is_a_vs_has_a.cpp -o runit && ./runit
```

The original lecture code is kept in [\_old/](_old/).

## Key Words

The major topic of this lecture was Inheritance Vs Composition. Some other concepts that were mixed in:

- `Polymorphism`
  - `Dynamic Polymorphism` (aka Run Time Polymorphism)
  - `Static Polymorphism` (aka Compile Time Polymorphism)
  - `Overload`
  - `Override`
- Synonyms for classes that **get inherited from**:
  - `Base Class`
  - `Super Class`
  - `Parent Class`
- Synonyms for classes that **do the inheriting**:
  - `Sub Class`
  - `Derived Class`
  - `Child Class`
- Access Specifiers
  - `Public`
  - `Private`
  - `Protected`

The order above matters, meaning, always pair `base` with `sub`, `super` with `derived`, and `parent` with `child`.
