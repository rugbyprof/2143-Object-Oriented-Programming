<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-01
name: oop-battle-arena
title: "Python’s Object Model: Classes, Attributes, Methods, and Dunders"
description: "Lesson 1 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 12
  day: 15
  year: 2026
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 1

# Python’s Object Model: Classes, Attributes, Methods, and Dunders

> **Arena premise:** in Python, nearly everything is an object. Numbers, strings, lists, functions, classes, and the heroic gladiators you create all carry data and behavior. Today you learn how those pieces fit together.

## Learning objectives

By the end of this lesson, you should be able to:

- Define a class and create independent instances from it.
- Distinguish class attributes from instance attributes.
- Explain why methods receive `self` and use `__init__` to initialize objects.
- Inspect objects with `__dict__`, `type()`, `dir()`, and `help()`.
- Write useful `__str__` and `__repr__` methods.
- Recognize introductory special-method ("dunder") protocols.
- Translate the basic ideas to and from C++ without assuming the languages behave identically.

## 1. The object model in one picture

A **class** is a blueprint: it describes the attributes (data) and methods (behavior) its objects can have. An **instance** is one concrete object made from that blueprint.

```python
class Gladiator:
    """A fighter in the OOP Battle Arena."""

    def __init__(self, name, health):
        self.name = name
        self.health = health

    def cheer(self):
        return f"{self.name}: Ready for battle!"

aria = Gladiator("Aria", 100)
boris = Gladiator("Boris", 120)

print(aria.name)       # Aria
print(boris.health)    # 120
print(aria.cheer())    # Aria: Ready for battle!
```

`Gladiator` is a class object. `aria` and `boris` are instances. Each instance has its own `name` and `health`; they do not share a single health bar. That would be an unusually stressful arena.

### Attribute lookup, briefly

When Python evaluates `aria.cheer`, it first looks on the instance, then on its class, then on parent classes (inheritance comes in a later lesson). When it finds a function on a class and accesses it through an instance, Python binds the instance as the first argument. That is why `aria.cheer()` works even though the definition says `def cheer(self)`.

## 2. `self`: the current object

`self` is not a keyword; it is the standard name for the instance receiving a method call. Use it to read or change that instance’s attributes.

```python
class Scoreboard:
    def __init__(self, points=0):
        self.points = points

    def add(self, amount):
        self.points += amount
        return self.points

board = Scoreboard()
print(board.add(10))  # 10
print(board.points)   # 10
```

Calling `board.add(10)` is conceptually similar to calling `Scoreboard.add(board, 10)`. Usually, write the pleasant first version and let Python handle the binding.

**Common error:** forgetting `self` in an instance method.

```python
# Incorrect: def add(amount):
# Correct:
def add(self, amount):
    self.points += amount
```

## 3. `__init__`: setup, not quite a constructor

`__init__` runs after a new instance has been created. It is commonly called a constructor in introductory material, but technically Python creates the object first (through `__new__`) and then initializes it with `__init__`. For normal classes, `__init__` is the right place to establish initial state.

```python
class Potion:
    def __init__(self, kind, healing):
        self.kind = kind
        self.healing = healing
        self.used = False

    def drink(self):
        if self.used:
            return "The bottle is empty. Dramatic, but ineffective."
        self.used = True
        return f"You recover {self.healing} health."

potion = Potion("sunleaf", 25)
print(potion.drink())
print(potion.drink())
```

The double underscores are pronounced **dunder**: “double underscore init double underscore.” Names like `__init__` are special methods with meanings defined by Python’s data model.

## 4. Instance attributes vs. class attributes

An **instance attribute** belongs to one object. A **class attribute** belongs to the class and is shared as a fallback by its instances.

```python
class Gladiator:
    arena = "North Gate"       # class attribute: shared default

    def __init__(self, name):
        self.name = name        # instance attribute: individual data

aria = Gladiator("Aria")
boris = Gladiator("Boris")

print(aria.arena)   # North Gate
print(boris.arena)  # North Gate

Gladiator.arena = "Moon Coliseum"
print(aria.arena)   # Moon Coliseum
```

Assigning through an instance normally creates or changes an instance attribute instead of changing the class attribute:

```python
aria.arena = "Training Yard"
print(aria.arena)       # Training Yard
print(boris.arena)      # Moon Coliseum
print(Gladiator.arena)  # Moon Coliseum
```

### The mutable class-attribute pitfall

Avoid using a mutable object such as a list or dictionary as a per-instance class attribute. All instances will point to the *same* object.

```python
class BadTeam:
    members = []  # One shared list: a trap disguised as a shortcut.

    def __init__(self, captain):
        self.captain = captain

red = BadTeam("Aria")
blue = BadTeam("Boris")
red.members.append("Aria")

print(blue.members)  # ['Aria'] -- surprise!
```

Put per-instance mutable data in `__init__` instead:

```python
class Team:
    def __init__(self, captain):
        self.captain = captain
        self.members = []  # A fresh list for each Team instance.

red = Team("Aria")
blue = Team("Boris")
red.members.append("Aria")

print(red.members)   # ['Aria']
print(blue.members)  # []
```

## 5. Methods are behavior

Methods are functions stored on a class. Instance methods use `self`; they often read or update state. A method may return a value, change state, do both, or (less helpfully) do neither.

```python
class Monster:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, damage):
        self.health = max(0, self.health - damage)
        return self.health

    def is_defeated(self):
        return self.health == 0

slime = Monster("Gelatinous Slime", 12)
slime.take_damage(5)
print(slime.health)         # 7
print(slime.is_defeated())  # False
```

Use names that state an action (`take_damage`) or answer a question (`is_defeated`). Your future teammate might be you, several weeks from now, operating on insufficient sleep.

## 6. Peeking behind the curtain: introspection

Python makes inspection easy. This is powerful for learning and debugging, though output can be long.

```python
class Rune:
    """A magical object with a readable label."""

    rarity = "common"

    def __init__(self, label):
        self.label = label

rune = Rune("ember")

print(type(rune))        # <class '__main__.Rune'>
print(rune.__dict__)     # {'label': 'ember'}
print(Rune.__dict__)     # class namespace (includes rarity and __init__)
print("label" in dir(rune))
help(Rune)               # Shows the docstring, methods, and attributes
```

- `__dict__` is commonly a dictionary holding an object’s namespace. It shows attributes stored directly on the instance or class.
- `type(value)` tells you an object’s type (or class).
- `dir(value)` lists names Python can find on an object, including inherited ones.
- `help(value)` displays documentation. A class or method docstring is what gives `help()` something useful to say.

Do not expect every object to have an editable `__dict__`; some built-in types and classes using `__slots__` do not. That is a later-level boss.

## 7. Friendly object text: `__str__` and `__repr__`

Without a custom representation, printing an object produces a technical-looking memory-location label. Define `__str__` for people and `__repr__` for developers.

```python
class Weapon:
    def __init__(self, name, damage):
        self.name = name
        self.damage = damage

    def __str__(self):
        return f"{self.name} ({self.damage} damage)"

    def __repr__(self):
        return f"Weapon(name={self.name!r}, damage={self.damage!r})"

sword = Weapon("Bronze Sword", 8)
print(sword)       # Bronze Sword (8 damage)     -> __str__
print([sword])     # [Weapon(name='Bronze Sword', damage=8)] -> __repr__
```

Guideline: make `__str__` readable and make `__repr__` precise and unambiguous. When practical, `__repr__` should look like code that could recreate the object—but that is a goal, not a law of the arena.

## 8. Dunder protocols: Python asks objects questions

Dunder methods let your class participate in Python operations. You normally do not call these methods directly; use the ordinary syntax and let Python call them.

| Operation                           | Typical dunder | Meaning                         |
| ----------------------------------- | -------------- | ------------------------------- |
| `print(obj)` / `str(obj)`           | `__str__`      | Human-readable text             |
| `repr(obj)` / containers display it | `__repr__`     | Developer-facing representation |
| `len(obj)`                          | `__len__`      | Size or length                  |
| `a == b`                            | `__eq__`       | Equality comparison             |
| `a + b`                             | `__add__`      | Addition-like operation         |
| `for x in obj`                      | `__iter__`     | Iteration                       |
| `obj[key]`                          | `__getitem__`  | Indexing or key access          |

Here is a tiny inventory object that supports `len()` and indexing:

```python
class Inventory:
    def __init__(self, items):
        self.items = list(items)

    def __len__(self):
        return len(self.items)

    def __getitem__(self, index):
        return self.items[index]

bag = Inventory(["rope", "torch", "apple"])
print(len(bag))  # 3
print(bag[1])    # torch
for item in bag:
    print(item)
```

Why does the loop work? Python can iterate over an object with `__iter__`; as a fallback, an object supporting sequential `__getitem__` can also be iterated. You will study iteration more deeply later. The key idea is that familiar syntax is often an invitation for an object to follow a protocol.

### Equality deserves care

Default `==` behavior for ordinary objects is identity-like: two separately created objects are not automatically “equal” just because their data matches. Define `__eq__` when value equality makes sense.

```python
class Coordinates:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        if not isinstance(other, Coordinates):
            return NotImplemented
        return self.x == other.x and self.y == other.y

print(Coordinates(2, 3) == Coordinates(2, 3))  # True
```

Returning `NotImplemented` gives Python a chance to try the other operand’s comparison method or reach an appropriate default. It is polite protocol behavior—like returning the arena’s borrowed shield.

## 9. Python and C++: a useful comparison

| Idea                 | Python                                             | C++ (rough comparison)                                 |
| -------------------- | -------------------------------------------------- | ------------------------------------------------------ |
| Define a class       | `class Hero:`                                      | `class Hero { ... };`                                  |
| Instance state       | `self.health = 100`                                | often a data member such as `int health = 100;`        |
| Constructor setup    | `__init__(self, ...)` after creation               | constructor `Hero(...)` creates/initializes the object |
| Current object       | explicit `self` parameter                          | implicit `this` pointer                                |
| Visibility           | conventions (`_name`) and name mangling (`__name`) | `public`, `protected`, `private` keywords              |
| Operator behavior    | dunders such as `__add__`                          | operator overloading such as `operator+`               |
| Inheritance behavior | dynamic dispatch by default for methods            | virtual dispatch requires `virtual`                    |

The comparison is a bridge, not a dictionary. In Python, attributes may be added at runtime, functions can be descriptors, and “private” is mostly a convention. Write Pythonic code instead of trying to make Python wear a C++ costume.

## 10. Common mistakes and repairs

1. **Using a class name instead of an instance.**

   ```python
   # Gladiator.cheer()  # TypeError: no instance was supplied
   Gladiator("Aria", 100).cheer()
   ```

2. **Forgetting to assign with `self`.**

   ```python
   def __init__(self, name):
       name = name           # local variable; vanishes after __init__
       # self.name = name    # correct
   ```

3. **Returning a non-string from `__str__`.** `__str__` must return a `str`.

4. **Sharing a mutable class attribute accidentally.** Create lists and dictionaries inside `__init__` when each instance needs its own.

5. **Writing `__init__` with a return value.** Initializers must return `None`; just assign state.

6. **Calling a dunder manually when normal syntax is clearer.** Prefer `len(bag)` to `bag.__len__()` and `str(sword)` to `sword.__str__()`.

7. **Assuming `__private` makes a secret vault.** Double-leading underscores trigger name mangling; they are not security. Python trusts adults with sharp objects.

## 11. Exercises

### Exercise A — Build a combatant

Create a `Combatant` class with `name`, `health`, and `power` instance attributes. Add a `strike(self, target)` method that reduces `target.health` by this combatant’s power without letting health drop below zero. Create two combatants and test a strike.

**Hint:** the method needs both `self` and `target`; use `max(0, ...)`.

### Exercise B — Track the roster

Give `Combatant` a class attribute named `arena_name`. Print it through the class and through an instance. Then assign a different `arena_name` to one instance. What changed, and what did not?

**Hint:** inspect both `Combatant.__dict__` and that instance’s `__dict__`.

### Exercise C — Make your object readable

Add `__str__` and `__repr__` to `Combatant`. `__str__` should be short enough for a scoreboard; `__repr__` should include field names.

### Exercise D — Protocol practice

Write a `SpellBook` class that stores a list of spell names and supports both `len(book)` and `book[0]`.

## 12. Mini-lab — The Battle Party

Build a small `Party` class that owns a party name and a separate list of members for every party. It should:

- Start with an empty member list.
- Add a member with `add_member(name)`.
- Report the number of members with `len(party)`.
- Print a friendly summary with `print(party)`.

Use this test code:

```python
red = Party("Red Raptors")
blue = Party("Blue Basilisks")

red.add_member("Aria")
red.add_member("Chen")
blue.add_member("Boris")

print(red)        # Red Raptors: 2 members
print(len(blue))  # 1
print(blue.members)  # ['Boris']
```

### One possible solution

```python
class Party:
    def __init__(self, name):
        self.name = name
        self.members = []

    def add_member(self, name):
        self.members.append(name)

    def __len__(self):
        return len(self.members)

    def __str__(self):
        return f"{self.name}: {len(self)} members"
```

Try these extensions after the core version works:

- Add `remove_member(name)` that returns `True` when it removes a member and `False` otherwise.
- Add a class attribute `max_members = 4` and prevent additions after the party is full.
- Add `__repr__` so a list of parties is useful during debugging.

## 13. Review questions

1. What is the difference between a class and an instance?
2. Why is `self` present in the definition of an instance method but absent when calling it through an object?
3. Where should a list that belongs separately to every object be created, and why?
4. What does `__dict__` reveal about an instance? What can it miss?
5. When would you use `__str__` instead of `__repr__`?
6. What ordinary Python expression causes `__len__` to run?
7. Why is `__init__` more precisely an initializer than an object creator?
8. Name one Python OOP difference that a C++ programmer should keep in mind.

## Exit ticket

In two or three sentences, explain this claim: **“Python syntax such as `len(x)`, `print(x)`, and `x == y` is a conversation with an object’s protocol.”** Include one dunder method as evidence.

---

**Next arena:** inheritance, overriding methods, `super()`, and polymorphism. Bring your shield; multiple parent classes are eventually in the curriculum.
