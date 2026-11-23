<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-05
name: oop-battle-arena
title: "Python’s Field Guide: Docstrings, help(), Introspection, and Clear APIs"
description: "Lesson 5 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 1
  day: 12
  year: 2027
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 5

# Python’s Field Guide: Docstrings, `help()`, Introspection, and Clear APIs

> **Arena premise:** code has two audiences: the computer that runs it and the human who meets it later. The computer is surprisingly forgiving. Future humans—often you—have standards.

## Learning objectives

By the end of this lesson, you should be able to:

- Write useful module, class, function, and method docstrings.
- Use `help()` and `.__doc__` to discover documentation at the prompt.
- Inspect objects with `type()`, `isinstance()`, `dir()`, `vars()`, and `__dict__`.
- Use `callable()`, `getattr()`, `hasattr()`, and `setattr()` with care.
- Read basic function annotations and signatures with `inspect`.
- Distinguish an object’s public API from implementation details.
- Design a small class whose behavior is understandable without reading every line.

## 1. Documentation is part of the interface

An **API** (application programming interface) is the set of names, arguments, return values, behaviors, and errors that other code is expected to use. For a small class, its API might be its constructor, public methods, public properties, and documented exceptions.

```python
class Fighter:
    """A combatant with a name and a non-negative health value.

    Args:
        name: Display name for the fighter.
        health: Starting health. Must be a non-negative integer.
    """

    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        """Reduce health by amount, stopping at zero.

        Args:
            amount: Non-negative integer damage.

        Returns:
            The fighter's remaining health.

        Raises:
            ValueError: If amount is negative.
        """
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health = max(0, self.health - amount)
        return self.health
```

The docstrings do not make the class work. They make its contract discoverable: callers learn what to supply, what to expect back, and what can go wrong.

## 2. What is a docstring?

A **docstring** is a string literal placed as the first statement in a module, class, function, or method body. Python stores it in the object’s `__doc__` attribute.

```python
"""Utilities for the OOP Battle Arena."""


class Potion:
    """A single-use item that restores health."""

    def drink(self):
        """Consume the potion and report its effect."""
        return "You recover 20 health."


print(Potion.__doc__)
print(Potion.drink.__doc__)
```

Comments beginning with `#` are for readers of the source code. Docstrings are attached to runtime objects, so tools and `help()` can display them. Both have a place; they are not rivals in a tiny punctuation war.

### A concise docstring style

Start with a one-sentence summary in imperative or descriptive voice. Add a blank line and details only when they help.

```python
def roll_damage(sides):
    """Return a random damage value from 1 through sides.

    Raises ValueError when sides is less than 1.
    """
    if sides < 1:
        raise ValueError("sides must be at least 1")
    # Implementation omitted for this example.
```

For a simple method whose name and behavior are obvious, a long docstring can add noise. Document the non-obvious: units, acceptable ranges, state changes, side effects, return values, exceptions, and special cases.

## 3. Ask Python for help

The built-in `help()` function asks Python’s documentation system to describe an object.

```python
help(Fighter)
help(Fighter.take_damage)
help(str)
help(list.append)
```

In an interactive Python shell, `help(Fighter)` displays its class docstring, methods, inherited information, and more. Type `q` to leave the interactive help viewer when it opens one.

You can also read the raw docstring:

```python
print(Fighter.__doc__)
print(Fighter.take_damage.__doc__)
```

`help()` is usually friendlier because it organizes the information. `.__doc__` is useful when you need the text programmatically or want a quick check.

## 4. Inspecting identity and relationships

Python objects can tell you a lot about themselves.

```python
class Knight:
    pass


class Paladin(Knight):
    pass


aria = Paladin()

print(type(aria))                 # <class '__main__.Paladin'>
print(isinstance(aria, Paladin))  # True
print(isinstance(aria, Knight))   # True
print(issubclass(Paladin, Knight))  # True
```

- `type(value)` returns an object’s class (or type).
- `isinstance(value, Class)` checks whether a value is an instance of that class or a subclass.
- `issubclass(Child, Parent)` checks an inheritance relationship between classes.

In everyday design, prefer behavior over unnecessary type checks. If a function only needs an object with `attack()`, calling `attack()` can be more flexible than demanding one exact class. Use inspection when the class relationship itself matters.

## 5. Explore available names with `dir()`

`dir(object)` returns a sorted list of names Python can find on an object.

```python
class Rune:
    rarity = "common"

    def __init__(self, label):
        self.label = label

    def activate(self):
        return f"{self.label} glows."


rune = Rune("ember")
print(dir(rune))
```

The result includes your names (`label`, `rarity`, `activate`) and many inherited dunder names. Use it to explore an unfamiliar object, then use `help()` or documentation to understand the candidates. `dir()` lists names; it does not guarantee what each name means or whether it is part of the promised public API.

To focus on non-dunder names while learning:

```python
publicish_names = [name for name in dir(rune) if not name.startswith("_")]
print(publicish_names)
```

This is a learning aid, not a perfect definition of public API. Some useful names begin with underscores, and some public framework APIs use special names on purpose.

## 6. Where attributes live: `vars()` and `__dict__`

For many ordinary objects, instance attributes are stored in a dictionary called `__dict__`.

```python
class Archer:
    guild = "Northwind"  # class attribute

    def __init__(self, name, arrows):
        self.name = name
        self.arrows = arrows


robin = Archer("Robin", 12)

print(robin.__dict__)   # {'name': 'Robin', 'arrows': 12}
print(Archer.__dict__)  # includes guild, __init__, and other class machinery
print(vars(robin))      # usually the same result as robin.__dict__
```

`vars(object)` is a convenient function that returns `object.__dict__` when it exists. Class attributes are not copied into each instance dictionary; Python finds them through attribute lookup.

Not every object has a `__dict__`. Built-in objects and classes using `__slots__` may store state differently. When in doubt, inspect cautiously rather than assuming every object is built from a visible dictionary.

## 7. Dynamic attribute helpers: powerful, not always necessary

Python supplies functions for working with attributes whose names are only known at runtime.

```python
class Scoreboard:
    def __init__(self):
        self.red = 0
        self.blue = 0


board = Scoreboard()
team = "red"

print(getattr(board, team))          # 0
setattr(board, team, 10)
print(getattr(board, "red"))        # 10
print(hasattr(board, "blue"))       # True
print(getattr(board, "gold", 0))    # 0: use a default if missing
```

- `getattr(object, name[, default])` retrieves an attribute by string name.
- `setattr(object, name, value)` assigns one by string name.
- `hasattr(object, name)` asks whether lookup succeeds.
- `delattr(object, name)` deletes an attribute by string name.

Use these when the name is genuinely dynamic—for example, a field selected from a safe configuration. For normal fixed names, `board.red` is clearer and easier for tools to analyze.

### Caution with `hasattr()`

`hasattr()` returns `False` when attribute lookup raises `AttributeError`. It can hide a bug if a property accidentally raises `AttributeError` inside its own logic. When correctness matters, consider explicitly using `getattr()` or handling the particular error where you understand the context.

Never pass untrusted arbitrary attribute names into `setattr()` without validating them. Otherwise a configuration file—or a mischievous goblin—could alter internal state you did not intend to expose.

## 8. Is it callable?

`callable(value)` checks whether an object can be called with parentheses. Functions, methods, and some objects return `True`.

```python
def cheer():
    return "For the arena!"


class Bell:
    def __call__(self):
        return "Ding! Round begins."


bell = Bell()
print(callable(cheer))  # True
print(callable(bell))   # True
print(callable("bell"))  # False
print(bell())           # Ding! Round begins.
```

`__call__` lets an instance behave like a function. It can be useful for objects that bundle configuration with an action, but ordinary named methods are often clearer for beginning designs.

## 9. Type annotations: useful clues, not runtime force fields

Annotations document intended types and help tools such as editors and static type checkers. Python does not automatically enforce most annotations at runtime.

```python
class Fighter:
    def __init__(self, name: str, health: int) -> None:
        self.name = name
        self.health = health

    def take_damage(self, amount: int) -> int:
        """Apply damage and return remaining health."""
        self.health = max(0, self.health - amount)
        return self.health
```

The annotation `name: str` means “this argument is intended to be a string.” The `-> int` means “this method is intended to return an integer.” This still runs:

```python
# Fighter(42, "many")  # Python permits it unless your code validates it.
```

Use validation when a program must reject bad values at runtime. Use annotations to make intent clear and enable better tool feedback. The two techniques cooperate well.

## 10. Inspecting signatures with `inspect`

The standard-library `inspect` module can reveal how a callable is defined. It is especially useful in a shell, a debugging session, or a documentation tool.

```python
import inspect


def heal(target: str, amount: int = 10) -> str:
    """Return a message describing healing."""
    return f"{target} heals {amount} HP."


print(inspect.signature(heal))
# (target: str, amount: int = 10) -> str

print(heal.__annotations__)
# {'target': <class 'str'>, 'amount': <class 'int'>, 'return': <class 'str'>}
```

Common inspection helpers include:

| Tool                      | Helpful question                                           |
| ------------------------- | ---------------------------------------------------------- |
| `inspect.signature(func)` | What arguments, defaults, and annotations does it declare? |
| `inspect.getdoc(obj)`     | What is its cleaned-up docstring?                          |
| `inspect.isclass(obj)`    | Is it a class?                                             |
| `inspect.ismethod(obj)`   | Is it a bound method?                                      |
| `inspect.getmembers(obj)` | What named members can it find?                            |

Introspection is excellent for exploration and tool building. Normal application code should not become a hall of mirrors just because it can inspect everything.

## 11. Public API versus implementation detail

Consider this class:

```python
class Inventory:
    """A collection of item names for one fighter."""

    def __init__(self):
        self._items = []

    def add(self, item):
        """Add a non-empty item name."""
        if not isinstance(item, str) or not item.strip():
            raise ValueError("item must be a non-empty string")
        self._items.append(item)

    def items(self):
        """Return a tuple snapshot of the stored items."""
        return tuple(self._items)
```

The intended public API is `add()` and `items()`. `_items` is an implementation detail. Returning a tuple lets callers examine items without accidentally changing the internal list:

```python
bag = Inventory()
bag.add("torch")
snapshot = bag.items()

# snapshot.append("rope")  # AttributeError: tuple has no append
print(snapshot)  # ('torch',)
```

This does not make the object invincible—someone can still reach for `bag._items`—but it communicates the contract and helps prevent ordinary accidents.

## 12. Designing an understandable class

Before writing a class, answer these questions:

1. **What responsibility does it own?** Keep it narrow enough to explain in one sentence.
2. **What inputs are valid?** Specify types, ranges, or required states.
3. **What public actions should callers use?** Prefer a small, coherent set of names.
4. **What does each action return or change?** State this in docstrings when it is not obvious.
5. **What can fail?** Raise useful built-in exceptions with clear messages.
6. **What details can change later?** Keep those behind underscore names or public methods/properties.

Names are documentation too. `take_damage(amount)` is more informative than `do_thing(x)`. The name cannot explain every rule, but it should at least point readers toward the right spellbook.

## 13. Python and C++ comparisons

| Idea                  | Python                           | C++ (rough comparison)                                |
| --------------------- | -------------------------------- | ----------------------------------------------------- |
| Built-in help         | `help(object)` and docstrings    | documentation tools / headers / IDE help              |
| Runtime documentation | `object.__doc__`                 | comments are generally not runtime data               |
| Discover members      | `dir()`, `vars()`, `inspect`     | reflection is limited; IDEs/header files often lead   |
| Runtime type          | `type(x)`, `isinstance()`        | `typeid`, RTTI, templates, compile-time types         |
| Dynamic lookup        | `getattr()` / `setattr()`        | usually not ordinary language-level behavior          |
| Type annotations      | optional, tool-facing by default | types are part of declarations and compile-time rules |

Python makes runtime discovery unusually accessible. That is great for interactive learning, debuggers, and frameworks. It is not a license to replace clear design with clever reflection.

## 14. Common mistakes and repairs

1. **Writing a comment where a docstring belongs.** Use a docstring for a class, function, or method’s contract; use comments to explain local implementation choices.

2. **Restating the method name without useful detail.** `"""Take damage."""` adds little. Explain range, clamping, return value, or errors when relevant.

3. **Documenting behavior that the code does not actually provide.** Treat documentation as a promise; update it with the code.

4. **Treating `dir()` as the official API list.** It includes inherited and internal implementation names.

5. **Using `setattr()` when a normal assignment is clearer.** Dynamic lookup should solve a real dynamic-name problem.

6. **Assuming annotations validate automatically.** Add explicit checks when bad input must be rejected at runtime.

7. **Returning internal mutable lists directly.** Return a tuple/copy or provide controlled operations when callers should not mutate internal state.

8. **Using introspection to avoid learning an API.** Inspecting is a wonderful first step; reading the docs and writing a small experiment completes the job.

## 15. Exercises

### Exercise A — Document a spell

Write a `Spell` class with `name`, `mana_cost`, and `cast(caster)`. Add a class docstring and a method docstring that explain valid mana cost, what `cast()` returns, and at least one failure condition.

### Exercise B — Explore a built-in

In a Python shell, run these and write one sentence about what each reveals:

```python
help(dict.get)
dir("arena")
type([])
vars(your_own_object)
```

Why might `vars([])` fail while `vars(your_own_object)` works?

### Exercise C — Dynamic scoreboard

Use `getattr()` and `setattr()` to add points to either a `red` or `blue` attribute based on a string supplied by the program. Validate the string against an allowed set before changing anything.

**Hint:** do not let arbitrary strings become attribute names.

### Exercise D — Annotations and validation

Annotate a function `award_gold(player: str, amount: int) -> str`. Then add runtime validation that rejects a negative `amount`. What job do the annotation and validation each perform?

## 16. Mini-lab — The Discoverable Artifact Registry

Build an `ArtifactRegistry` class designed for someone else to use.

Requirements:

- A class docstring describes its purpose and the artifact-name rule.
- `register(name, rarity)` validates both non-empty strings and rejects duplicate names.
- `find(name)` returns a rarity or raises `KeyError` with a useful message.
- `names` is a read-only property returning a sorted tuple of artifact names.
- `__len__` returns the number of registered artifacts.
- `__repr__` helps a developer inspect the registry.
- Every public method/property has a docstring.

### One possible solution

```python
class ArtifactRegistry:
    """Store uniquely named arena artifacts and their rarity labels.

    Artifact names and rarity labels must be non-empty strings.
    """

    def __init__(self):
        """Create an empty registry."""
        self._artifacts = {}

    def register(self, name: str, rarity: str) -> None:
        """Register one unique artifact name with its rarity.

        Raises:
            ValueError: If either argument is empty or name is already registered.
        """
        if not isinstance(name, str) or not name.strip():
            raise ValueError("name must be a non-empty string")
        if not isinstance(rarity, str) or not rarity.strip():
            raise ValueError("rarity must be a non-empty string")
        if name in self._artifacts:
            raise ValueError(f"artifact already registered: {name!r}")
        self._artifacts[name] = rarity

    def find(self, name: str) -> str:
        """Return the rarity for name.

        Raises KeyError when name is absent from the registry.
        """
        try:
            return self._artifacts[name]
        except KeyError:
            raise KeyError(f"unknown artifact: {name!r}") from None

    @property
    def names(self) -> tuple[str, ...]:
        """Return artifact names as an alphabetically sorted tuple."""
        return tuple(sorted(self._artifacts))

    def __len__(self) -> int:
        """Return the number of registered artifacts."""
        return len(self._artifacts)

    def __repr__(self) -> str:
        """Return a developer-oriented representation."""
        return f"ArtifactRegistry({self._artifacts!r})"
```

Try it:

```python
registry = ArtifactRegistry()
registry.register("Sunstone", "rare")
registry.register("Ember Key", "uncommon")

print(registry.names)         # ('Ember Key', 'Sunstone')
print(registry.find("Sunstone"))  # rare
print(len(registry))          # 2
help(ArtifactRegistry.register)
```

Extensions:

- Add `remove(name)` and document whether it raises an error for unknown names.
- Add `__contains__` so `"Sunstone" in registry` works.
- Write a short doctest-style example in the class docstring (optional preview of a testing tool).
- Use `inspect.signature(ArtifactRegistry.register)` to inspect your own API.

## 17. Review questions

1. What makes a string literal a docstring rather than an ordinary string?
2. What is the difference between `help(obj)` and `obj.__doc__`?
3. What can `dir(obj)` tell you, and what can it not promise?
4. How do `vars(obj)` and `obj.__dict__` relate?
5. When is `getattr()` more appropriate than direct attribute access?
6. Why should type annotations and runtime validation often be used together?
7. What does it mean for `_items` to be an implementation detail?
8. Name two qualities of a clear public API.

## Exit ticket

Choose one class from an earlier lesson. Write a two- or three-sentence class docstring for it that states its responsibility, the most important invariant, and one public operation a caller can use.

---

**Next arena:** `@classmethod`, `@staticmethod`, decorators, `@dataclass`, and alternate constructors—because not every useful behavior needs an instance as its first argument.
