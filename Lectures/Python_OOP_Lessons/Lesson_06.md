<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-06
name: oop-battle-arena
title: "Python’s Class Workshop: Class Methods, Static Methods, Decorators, and Dataclasses"
description: "Lesson 6 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 1
  day: 19
  year: 2027
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 6

# Python’s Class Workshop: Class Methods, Static Methods, Decorators, and Dataclasses

> **Arena premise:** not every useful action belongs to one fighter. Some actions belong to the entire fighter class; some are merely related helpers; some classes are mostly clean bundles of data. Python provides a tool for each, and none requires a ceremonial drum circle.

## Learning objectives

By the end of this lesson, you should be able to:

- Distinguish instance methods, class methods, and static methods.
- Use `@classmethod` and its `cls` parameter for class-wide behavior and alternate constructors.
- Use `@staticmethod` only for behavior that does not need instance or class state.
- Explain decorators as functions that transform or register other functions/classes.
- Create concise data-holding classes with `@dataclass`.
- Use dataclass defaults safely with `field(default_factory=...)`.
- Decide when a handwritten class is clearer than a dataclass.
- Read basic generated dataclass behavior such as `__init__`, `__repr__`, and `__eq__`.

## 1. Three kinds of methods

Lesson 1 introduced the usual **instance method**. Its first parameter is `self`, the current object.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def introduce(self):
        return f"{self.name} has {self.health} health."
```

Python also supports **class methods**, whose first parameter is conventionally `cls`, and **static methods**, which receive neither `self` nor `cls` automatically.

| Kind            | Decorator       | First automatic argument | Best use                                            |
| --------------- | --------------- | ------------------------ | --------------------------------------------------- |
| Instance method | none            | `self` (the instance)    | Reads/changes one object’s state                    |
| Class method    | `@classmethod`  | `cls` (the class)        | Reads/changes class state; alternate constructors   |
| Static method   | `@staticmethod` | none                     | Related utility that needs no object or class state |

The syntax looks similar, but the question is simple: **what information does the operation need?**

## 2. Class attributes and class methods

A class method can work with a class attribute shared by all instances.

```python
class Fighter:
    arena_name = "North Gate Arena"

    def __init__(self, name):
        self.name = name

    @classmethod
    def announce_arena(cls):
        return f"Welcome to {cls.arena_name}!"


print(Fighter.announce_arena())
aria = Fighter("Aria")
print(aria.announce_arena())  # Also works; cls is still Fighter
```

The method can be called through the class or an instance. In both forms above, `cls` receives `Fighter`. Calling it through the class is often clearer when the operation is truly class-wide.

Class methods become more interesting with inheritance:

```python
class Fighter:
    title = "Fighter"

    @classmethod
    def describe_class(cls):
        return f"This is the {cls.title} class."


class Wizard(Fighter):
    title = "Wizard"


print(Fighter.describe_class())  # This is the Fighter class.
print(Wizard.describe_class())   # This is the Wizard class.
```

Using `cls`, rather than spelling `Fighter.title`, lets the inherited method respond correctly for subclasses.

## 3. Alternate constructors with `@classmethod`

Python has one normal constructor call: `ClassName(...)`. A class method can provide a named alternate path for building an object from a different representation.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    @classmethod
    def from_record(cls, record):
        """Build a Fighter from a 'name,health' text record."""
        name, health_text = record.split(",")
        return cls(name.strip(), int(health_text))


aria = Fighter.from_record("Aria, 100")
print(aria.name)    # Aria
print(aria.health)  # 100
```

Why return `cls(...)` instead of `Fighter(...)`? Inherited class methods then build the class they were called on.

```python
class Wizard(Fighter):
    pass

milo = Wizard.from_record("Milo, 75")
print(type(milo))  # <class '__main__.Wizard'>
```

That behavior is called a **polymorphic constructor**. It is one of the most compelling reasons to use a class method rather than a separate parsing function.

### Validate external input

Text files, user input, and web data are imperfect. An alternate constructor should turn bad input into a clear error.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    @classmethod
    def from_record(cls, record):
        try:
            name, health_text = record.split(",")
            health = int(health_text)
        except (ValueError, AttributeError) as error:
            raise ValueError("record must look like 'name,health'") from error

        if not name.strip() or health < 0:
            raise ValueError("name must be non-empty and health non-negative")
        return cls(name.strip(), health)
```

## 4. Static methods: related helpers, no hidden receiver

A static method lives in a class namespace, but it does not receive an object or class automatically. Use one when the function is closely related to the class’s concept but does not need `self` or `cls`.

```python
class DamageRules:
    @staticmethod
    def is_valid(amount):
        return isinstance(amount, int) and amount >= 0

    @staticmethod
    def clamp(amount, maximum):
        return max(0, min(amount, maximum))


print(DamageRules.is_valid(12))   # True
print(DamageRules.clamp(150, 100))  # 100
```

It can be called through an instance, but that rarely helps:

```python
# DamageRules().is_valid(12)  # valid, but less clear
```

### Do you really need a static method?

Many static methods are simply ordinary module-level functions wearing a class jersey. If the helper has no special connection to the class, write a normal function. Put it in the class only when the association makes the API easier to discover.

```python
def roll_die(sides):
    """Return a random number from 1 through sides."""
    # This belongs naturally in a game utility module, not necessarily Fighter.
```

## 5. Decorating: functions that change functions

The `@decorator` syntax is a compact way to pass a function or class through another callable. You have already used decorators:

```python
@classmethod
def from_record(cls, record):
    ...
```

This is roughly equivalent to:

```python
def from_record(cls, record):
    ...

from_record = classmethod(from_record)
```

Decorators are not magic dust. They receive something, return something, and the returned object replaces the original name. `@property`, `@staticmethod`, `@classmethod`, `@dataclass`, and `@total_ordering` are all examples you have already encountered.

### A simple logging decorator

This example shows the basic shape. It is educational, not a license to decorate every line until the code resembles holiday lights.

```python
from functools import wraps


def announce_call(function):
    """Print a message before running function."""
    @wraps(function)
    def wrapper(*args, **kwargs):
        print(f"Calling {function.__name__}")
        return function(*args, **kwargs)
    return wrapper


@announce_call
def open_gate(name):
    return f"The gate opens for {name}."


print(open_gate("Aria"))
```

`*args` collects positional arguments; `**kwargs` collects named arguments. `@wraps` preserves useful metadata such as the original function’s name and docstring, which matters to `help()` and debuggers.

## 6. `@dataclass`: classes for structured data

Many classes primarily store data. The `dataclasses` module can generate common boilerplate such as `__init__`, `__repr__`, and value-based `__eq__`.

```python
from dataclasses import dataclass


@dataclass
class Coordinates:
    row: int
    column: int


tile = Coordinates(2, 4)
print(tile)                     # Coordinates(row=2, column=4)
print(tile == Coordinates(2, 4))  # True
```

Compare that with a handwritten version: you would normally write an initializer, representation, and equality method yourself. Dataclasses are excellent for small, mostly-data objects whose fields and equality rules are straightforward.

## 7. Defaults and the mutable-default trap, again

Dataclass fields can have defaults.

```python
from dataclasses import dataclass


@dataclass
class Potion:
    name: str
    healing: int = 20


basic = Potion("Red Potion")
strong = Potion("Golden Potion", 50)
print(basic)
print(strong)
```

Do **not** use a mutable list or dictionary literal as a per-instance default. Dataclasses protect you by rejecting this common mistake:

```python
# @dataclass
# class BrokenParty:
#     members: list[str] = []  # ValueError: mutable default is not allowed
```

Use `field(default_factory=...)` to create a fresh object for every instance.

```python
from dataclasses import dataclass, field


@dataclass
class Party:
    name: str
    members: list[str] = field(default_factory=list)


red = Party("Red Raptors")
blue = Party("Blue Basilisks")
red.members.append("Aria")

print(red.members)   # ['Aria']
print(blue.members)  # []
```

`list` is passed as a factory function. Python calls it for each new `Party`, creating a separate empty list.

## 8. Adding behavior to a dataclass

`@dataclass` saves boilerplate; it does not prevent ordinary methods, properties, validation, or inheritance.

```python
from dataclasses import dataclass


@dataclass
class Monster:
    name: str
    health: int

    def take_damage(self, amount: int) -> int:
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health = max(0, self.health - amount)
        return self.health

    @property
    def is_defeated(self) -> bool:
        return self.health == 0


slime = Monster("Slime", 12)
slime.take_damage(12)
print(slime.is_defeated)  # True
```

The generated initializer in this basic example does not validate annotations at runtime. If validation is needed at construction, use `__post_init__`.

## 9. Validation after generated initialization: `__post_init__`

After a dataclass-generated `__init__` assigns the fields, it calls `__post_init__` if you define one.

```python
from dataclasses import dataclass


@dataclass
class ArenaTicket:
    holder: str
    seat: int

    def __post_init__(self):
        if not self.holder.strip():
            raise ValueError("ticket holder cannot be empty")
        if not isinstance(self.seat, int) or self.seat < 1:
            raise ValueError("seat must be a positive integer")


ticket = ArenaTicket("Aria", 42)
print(ticket)
```

Use `__post_init__` to validate or calculate derived setup. Do not assume it turns a dataclass into an immutable object; fields can still be reassigned unless you choose `frozen=True`.

## 10. Frozen dataclasses: immutable value objects

For a value that should not change after creation, use `frozen=True`.

```python
from dataclasses import dataclass


@dataclass(frozen=True)
class MapTile:
    row: int
    column: int


tile = MapTile(2, 4)
print(tile)
# tile.row = 3  # dataclasses.FrozenInstanceError

visited = {MapTile(2, 4), MapTile(2, 4)}
print(len(visited))  # 1
```

Frozen dataclasses are useful for coordinates, configuration records, and other value objects. They are not truly unchangeable at every level: if a frozen class contains a mutable list, the list’s contents could still be changed. Favor immutable field types such as `tuple` when deep immutability matters.

## 11. Choosing the right tool

Use this guide as a starting point:

| Need                                                         | Good first choice                               |
| ------------------------------------------------------------ | ----------------------------------------------- |
| Operation needs one object’s state                           | Instance method                                 |
| Operation needs class-level state or should construct `cls`  | `@classmethod`                                  |
| Related helper needs neither `self` nor `cls`                | `@staticmethod` or a module-level function      |
| Mostly a simple collection of fields                         | `@dataclass`                                    |
| Simple data with independent mutable defaults                | `field(default_factory=...)`                    |
| Immutable record / dictionary or set member                  | `@dataclass(frozen=True)` with immutable fields |
| Complex invariants, custom initialization, many side effects | Handwritten class, possibly with properties     |

The best tool is the one that makes the responsibility obvious. A dataclass with seven hidden side effects is technically possible and spiritually suspicious.

## 12. Python and C++ comparisons

| Idea                     | Python                                           | C++ (rough comparison)                                             |
| ------------------------ | ------------------------------------------------ | ------------------------------------------------------------------ |
| Instance method receiver | explicit `self`                                  | implicit `this`                                                    |
| Class-wide method        | `@classmethod` receives `cls`                    | `static` member function (not identical; no dynamic `cls`)         |
| Helper with no receiver  | `@staticmethod` or free function                 | `static` member/free function                                      |
| Alternate constructor    | class method returning `cls(...)`                | overloaded constructors or factory function                        |
| Decorator                | callable transforms/wraps another callable/class | templates, attributes, wrappers, macros—no direct one-to-one match |
| Boilerplate data class   | `@dataclass` generates methods                   | structs/defaulted methods; libraries/macros may help               |
| Immutable record         | `@dataclass(frozen=True)`                        | `const` objects/members; design varies                             |

The comparison is approximate. In Python, a class method receives the actual class used for the call, which is why `cls(...)` naturally supports subclasses. C++ static member functions do not receive an equivalent runtime class object.

## 13. Common mistakes and repairs

1. **Using `self` inside a class method.** Use `cls`; no individual instance was supplied.

2. **Hard-coding the base class inside an alternate constructor.** Return `cls(...)`, not `Fighter(...)`, when subclasses should inherit the factory correctly.

3. **Making every utility a static method.** Use a module-level function when it is not meaningfully tied to the class.

4. **Forgetting `@wraps` in a decorator.** The decorated function can lose its name, docstring, and other useful metadata.

5. **Using `[]` as a dataclass default.** Use `field(default_factory=list)` so each instance receives its own list.

6. **Assuming annotations validate dataclass fields.** Use `__post_init__`, properties, or a custom initializer when runtime validation is required.

7. **Making a mutable dataclass hashable by accident.** Do not put objects that change their equality-relevant fields into a set or use them as dictionary keys.

8. **Choosing a dataclass for a class dominated by behavior.** A normal class may better tell the story.

## 14. Exercises

### Exercise A — A roster-wide count

Create a `Fighter` class with a class attribute `created_count`. Increment it each time an instance is created. Add a class method `count()` that returns the number of fighters created.

**Hint:** assign to `cls.created_count` inside a class method; assign to `type(self).created_count` or `Fighter.created_count` thoughtfully from an instance initializer.

### Exercise B — Alternate construction

Create a `Potion` class with `name` and `healing`. Add `Potion.from_label("Sunleaf:25")`. Validate the text format and return a proper instance.

### Exercise C — Static or standalone?

Classify each function, then explain your answer:

- `Fighter.from_record(text)`
- `DamageRules.clamp(amount, maximum)`
- `roll_die(sides)`
- `party.add_member(name)`

Choose from instance method, class method, static method, or module-level function.

### Exercise D — A safe dataclass

Create `@dataclass class Quest` with `title`, `reward_gold=0`, and `tags` as a list of strings. Use `default_factory` for tags and `__post_init__` to reject empty titles and negative rewards.

## 15. Mini-lab — The Summoning Ledger

Build a small system that combines the lesson’s tools.

Requirements:

- A frozen `@dataclass` named `SummonToken` with `creature` and `tier` fields.
- `SummonToken.from_code("wolf:2")` is a class-method alternate constructor with validation.
- A `SummoningCircle` normal class stores tokens in a private-ish `_tokens` list.
- `SummoningCircle.add(token)` accepts only `SummonToken` objects.
- `SummoningCircle.from_codes(codes)` builds a circle from an iterable of token-code strings.
- A static method or module helper validates a tier is from 1 through 5.
- `len(circle)` reports the number of stored tokens and `print(circle)` gives a readable summary.

### One possible solution

```python
from dataclasses import dataclass


@dataclass(frozen=True)
class SummonToken:
    creature: str
    tier: int

    def __post_init__(self):
        if not self.creature.strip():
            raise ValueError("creature cannot be empty")
        if not self.is_valid_tier(self.tier):
            raise ValueError("tier must be an integer from 1 through 5")

    @staticmethod
    def is_valid_tier(tier):
        return isinstance(tier, int) and 1 <= tier <= 5

    @classmethod
    def from_code(cls, code):
        try:
            creature, tier_text = code.split(":")
            return cls(creature.strip(), int(tier_text))
        except (ValueError, AttributeError) as error:
            raise ValueError("token code must look like 'creature:tier'") from error


class SummoningCircle:
    def __init__(self, tokens=()):
        self._tokens = []
        for token in tokens:
            self.add(token)

    @classmethod
    def from_codes(cls, codes):
        return cls(SummonToken.from_code(code) for code in codes)

    def add(self, token):
        if not isinstance(token, SummonToken):
            raise TypeError("token must be a SummonToken")
        self._tokens.append(token)

    def __len__(self):
        return len(self._tokens)

    def __str__(self):
        return f"SummoningCircle with {len(self)} token(s)"
```

Try it:

```python
circle = SummoningCircle.from_codes(["wolf:2", "phoenix:5"])
print(circle)       # SummoningCircle with 2 token(s)
print(len(circle))  # 2
```

Extensions:

- Add `__iter__` to iterate over tokens.
- Add a `by_tier(tier)` method that returns matching tokens as a tuple.
- Decide whether `is_valid_tier` belongs inside `SummonToken` or as a module-level function. Defend your choice.
- Use `help(SummonToken.from_code)` after writing docstrings for all public methods.

## 16. Review questions

1. Which method type receives `self`? Which receives `cls`? Which receives neither automatically?
2. Why should an alternate constructor normally return `cls(...)`?
3. When is a module-level function better than a static method?
4. What is a decorator doing conceptually?
5. Which methods does a basic dataclass generate by default?
6. Why is `field(default_factory=list)` necessary for a list field?
7. When does `__post_init__` run?
8. What is one limitation of `frozen=True` with nested mutable objects?

## Exit ticket

Choose one earlier Battle Arena class and propose one class method or alternate constructor that would genuinely improve its API. State what input it accepts and why it belongs on the class rather than as an instance method.

---

**Next arena:** modules, packages, imports, `__init__.py`, and `__main__`—because even the best class needs a sensible place to live.
