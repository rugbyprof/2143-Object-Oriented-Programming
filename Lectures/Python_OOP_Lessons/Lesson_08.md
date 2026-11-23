<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-08
name: oop-battle-arena
title: "Pythonic OOP Design: Composition, Abstract Classes, Protocols, and Type Hints"
description: "Lesson 8 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 2
  day: 2
  year: 2027
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 8

# Pythonic OOP Design: Composition, Abstract Classes, Protocols, and Type Hints

> **Arena premise:** you now know many OOP tools. The final boss is not memorizing more syntax; it is choosing the design that tells the truth about the problem, stays easy to change, and does not require a 14-level inheritance tree to add a backpack.

## Learning objectives

By the end of this lesson, you should be able to:

- Choose composition or inheritance using “has-a” and “is-a” reasoning.
- Define an abstract base class (ABC) with `abc.ABC` and `@abstractmethod`.
- Explain nominal typing versus structural typing (protocols / duck typing).
- Write basic type hints for variables, functions, classes, collections, and optional values.
- Define a `typing.Protocol` to describe required behavior without requiring inheritance.
- Use `@runtime_checkable` cautiously when a runtime protocol check is necessary.
- Apply small design principles: single responsibility, clear boundaries, and dependency injection.
- Refactor a tangle of conditionals toward simple, polymorphic objects.

## 1. Design begins with relationships

The first question is not “which feature can I use?” Ask what relationship is true.

- **Inheritance:** `Wizard` **is a** `Fighter`.
- **Composition:** `Fighter` **has an** `Inventory`.
- **Collaboration:** `Match` **uses** objects that can attack and take damage.

```python
class Inventory:
    def __init__(self):
        self._items = []

    def add(self, item):
        self._items.append(item)


class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health
        self.inventory = Inventory()  # A Fighter has an Inventory.
```

This is **composition**: build a larger object from smaller, focused objects. `Fighter` delegates inventory work to an `Inventory` rather than pretending a fighter *is* an inventory.

## 2. Favor composition when behavior varies independently

Consider attack styles. You could create a subclass for every combination:

```text
SwordKnight, BowKnight, FireWizard, IceWizard, FireBowKnight, ...
```

The arena’s class registry would soon require a second arena. Instead, give a fighter an object responsible for attacking.

```python
class SwordAttack:
    def perform(self, attacker, defender):
        defender.take_damage(8)
        return f"{attacker.name} strikes with a sword."


class FireAttack:
    def perform(self, attacker, defender):
        defender.take_damage(12)
        return f"{attacker.name} casts a fire bolt."


class Fighter:
    def __init__(self, name, health, attack_style):
        self.name = name
        self.health = health
        self.attack_style = attack_style

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)

    def attack(self, defender):
        return self.attack_style.perform(self, defender)


aria = Fighter("Aria", 100, SwordAttack())
milo = Fighter("Milo", 75, FireAttack())
print(aria.attack(milo))
```

Now the attack strategy can change at runtime:

```python
aria.attack_style = FireAttack()
```

This pattern is sometimes called **strategy**. The important lesson is not the pattern’s name. It is the separation: a fighter owns fighter state; an attack style owns attack behavior.

## 3. Inheritance still has an important role

Inheritance is useful when a subtype can stand in wherever its parent type is expected, without breaking the parent’s promises.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)


class ShieldKnight(Fighter):
    def __init__(self, name, health, shield):
        super().__init__(name, health)
        self.shield = shield

    def take_damage(self, amount):
        blocked = min(self.shield, amount)
        self.shield -= blocked
        super().take_damage(amount - blocked)
```

A `ShieldKnight` still has a name, health, and `take_damage()` behavior. It extends the ordinary fighter rule in a way callers can accept. That is a good “is-a” relationship.

### A useful design check

Ask: “Could I replace a `Fighter` with this subclass and still meet the caller’s expectations?” If not, inheritance may be lying. For example, a `PacifistFighter` that raises an error whenever `attack()` is called may not fit code that expects all fighters to attack.

## 4. Abstract base classes: promise an interface

An **abstract base class** (ABC) expresses a common interface and prevents direct instantiation until required methods are supplied. Use the `abc` module from Python’s standard library.

```python
from abc import ABC, abstractmethod


class AttackStyle(ABC):
    """Base interface for an attack behavior."""

    @abstractmethod
    def perform(self, attacker, defender):
        """Apply this attack and return a description."""
        raise NotImplementedError


class SwordAttack(AttackStyle):
    def perform(self, attacker, defender):
        defender.take_damage(8)
        return f"{attacker.name} strikes with a sword."


# style = AttackStyle()  # TypeError: abstract method perform is missing
style = SwordAttack()
```

`@abstractmethod` marks a method subclasses must implement before Python permits instantiation. The body can raise `NotImplementedError`, use `pass`, or even contain shared code; the decorator is what makes it abstract.

### ABCs are contracts, not automatic correctness proof

This subclass technically satisfies the ABC but may still be unhelpful:

```python
class ConfusingAttack(AttackStyle):
    def perform(self, attacker, defender):
        return ["maybe", 42]
```

Python verifies that the method exists, not that it returns a sensible description or changes the defender appropriately. Clear docs, tests, and type hints still matter.

## 5. Duck typing and structural typing

Python often cares about what an object **can do**, not what class it inherits from. This is duck typing: if an object supplies the behavior, it can participate.

```python
class TrainingDummy:
    def take_damage(self, amount):
        print(f"The dummy absorbs {amount} damage.")


def practice_strike(target):
    target.take_damage(5)


practice_strike(TrainingDummy())
```

`TrainingDummy` does not inherit from `Fighter`, yet it works because it has the needed method.

**Structural typing** is the type-hint version of this idea. Instead of requiring a parent class, define the required shape using a `Protocol`.

```python
from typing import Protocol


class Damageable(Protocol):
    def take_damage(self, amount: int) -> None:
        """Accept non-negative damage."""
        ...


def practice_strike(target: Damageable) -> None:
    target.take_damage(5)
```

A type checker can accept any object with a compatible `take_damage` method, whether or not it inherits from `Damageable`. Unlike an ABC, a class does not need to name `Damageable` in its parent list.

## 6. Protocols versus abstract base classes

Both can describe expected behavior, but they serve different purposes.

| Question                                    | Abstract base class                      | `typing.Protocol`                                      |
| ------------------------------------------- | ---------------------------------------- | ------------------------------------------------------ |
| Must implementation inherit/opt in?         | Usually yes                              | No; matching shape is enough                           |
| Main audience                               | Runtime design and shared base behavior  | Static type checkers and flexible interfaces           |
| Can provide ordinary shared implementation? | Yes                                      | It can, but keep protocol members interface-focused    |
| Does it block incomplete instantiation?     | Yes, with `@abstractmethod`              | No; a protocol is not runtime enforcement by default   |
| Best when                                   | You own a real family of related classes | You want to accept capabilities from unrelated objects |

Use an ABC when you own a family whose members genuinely share a conceptual base and perhaps some implementation. Use a protocol when a function needs a small capability, such as “can take damage” or “can be saved,” regardless of ancestry.

## 7. Runtime-checkable protocols: a limited tool

Normally, this is not allowed:

```python
# isinstance(target, Damageable)  # TypeError by default
```

Add `@runtime_checkable` if you need a shallow runtime check:

```python
from typing import Protocol, runtime_checkable


@runtime_checkable
class Damageable(Protocol):
    def take_damage(self, amount: int) -> None:
        ...


class TrainingDummy:
    def take_damage(self, amount):
        print(f"Dummy absorbs {amount} damage.")


print(isinstance(TrainingDummy(), Damageable))  # True
```

This checks attribute presence, not detailed method signatures, type annotations, or behavior. A class with a badly implemented `take_damage` could still pass. Prefer calling the operation and relying on tests/type checking unless a runtime check has a real purpose.

## 8. Type hints: a shared vocabulary

Type hints document intent and allow type checkers (such as mypy, pyright, or an editor) to find mismatches before the program runs. They are usually optional at runtime.

```python
def heal(current: int, maximum: int, amount: int) -> int:
    """Return a health value after bounded healing."""
    return min(maximum, current + amount)


name: str = "Aria"
party: list[str] = ["Aria", "Milo"]
scores: dict[str, int] = {"red": 10, "blue": 8}
```

Use the built-in generic forms in current Python:

```python
members: list[str]
loot_by_name: dict[str, int]
coordinates: tuple[int, int]
```

For a value that may be absent, use `X | None` (Python 3.10+) or `Optional[X]` for older code:

```python
def find_fighter(name: str) -> Fighter | None:
    """Return a matching fighter, or None when no match exists."""
    # Search implementation omitted.
    return None
```

When a result can be `None`, callers must handle that possibility:

```python
target = find_fighter("Aria")
if target is not None:
    target.take_damage(5)
```

Do not write `if target:` when an existing object might be falsey (for example, a fighter with a custom `__bool__`). `is not None` expresses the specific question.

## 9. Type aliases and expressive signatures

Names can make complex types readable. A **type alias** gives a meaningful label to an existing type.

```python
from typing import TypeAlias

Health: TypeAlias = int
Damage: TypeAlias = int
CombatLog: TypeAlias = list[str]


def apply_damage(current: Health, amount: Damage) -> Health:
    return max(0, current - amount)
```

At runtime, these aliases are still just `int` and `list[str]` descriptions. Their benefit is communication: a reader sees which integers represent health versus damage.

You can also express a callable requirement without making a full protocol:

```python
from collections.abc import Callable

DamageRule = Callable[[int, int], int]


def resolve_damage(base: int, armor: int, rule: DamageRule) -> int:
    return rule(base, armor)
```

For a multi-method object capability, a protocol is often clearer than a complicated `Callable` type.

## 10. Dependency injection: pass in collaborators

Hard-coding collaborators makes classes difficult to change and test. **Dependency injection** simply means receiving a needed collaborator as an argument rather than constructing it secretly inside the class.

```python
class Match:
    def __init__(self, damage_rule):
        self.damage_rule = damage_rule

    def resolve_hit(self, base_damage, armor):
        return self.damage_rule(base_damage, armor)


def standard_damage(base_damage, armor):
    return max(0, base_damage - armor)


match = Match(standard_damage)
print(match.resolve_hit(10, 3))  # 7
```

The match does not need to know every damage-rule variation. Tests can pass a simple predictable function; a different game mode can pass another rule. This is composition in action.

With type hints:

```python
from collections.abc import Callable

DamageRule = Callable[[int, int], int]


class Match:
    def __init__(self, damage_rule: DamageRule):
        self.damage_rule = damage_rule
```

## 11. Refactoring conditionals toward polymorphism

This code works, but it grows a new branch for every attack kind:

```python
def damage_for(kind, base_damage):
    if kind == "sword":
        return base_damage
    if kind == "fire":
        return base_damage + 4
    if kind == "ice":
        return base_damage + 2
    raise ValueError(f"unknown attack kind: {kind}")
```

When each branch represents a behavior that keeps growing, objects can isolate those rules:

```python
from abc import ABC, abstractmethod


class AttackModifier(ABC):
    @abstractmethod
    def damage(self, base_damage: int) -> int:
        """Return modified damage."""


class SwordModifier(AttackModifier):
    def damage(self, base_damage: int) -> int:
        return base_damage


class FireModifier(AttackModifier):
    def damage(self, base_damage: int) -> int:
        return base_damage + 4


class IceModifier(AttackModifier):
    def damage(self, base_damage: int) -> int:
        return base_damage + 2
```

Now client code calls `modifier.damage(base_damage)` without knowing which subtype it received. Do not replace every `if` statement with a class hierarchy; two stable branches may be simpler than five files. Refactor when behavior is growing, independently varying, or difficult to test in its current shape.

## 12. Three practical design principles

### Keep one responsibility in one place

An `Inventory` stores items. A `DamageRule` calculates damage. A `Match` coordinates a round. A class that stores data, formats a user interface, saves files, and emails a dragon is asking for a vacation.

### Depend on small capabilities

If a function only needs `take_damage(amount)`, type it as a small protocol or document that capability. Do not demand a giant `Fighter` object with 30 unrelated methods.

### Prefer explicit collaboration to hidden global state

Pass a random-number generator, rules object, or logger into the place that uses it when flexibility/testing matter. Global variables make dependencies invisible and cross-arena chaos more likely.

These are guidelines, not ceremonial laws. Small scripts can be simple. Add structure when it reduces confusion.

## 13. Python and C++ comparisons

| Idea                    | Python                                    | C++ (rough comparison)                                                 |
| ----------------------- | ----------------------------------------- | ---------------------------------------------------------------------- |
| Composition             | object holds collaborator objects         | members/owned objects/pointers/references                              |
| Abstract base           | `ABC` + `@abstractmethod`                 | abstract class with pure virtual functions                             |
| Interface by capability | duck typing / `Protocol`                  | templates, concepts, interfaces/pure virtual bases depending on design |
| Type hints              | optional, tool-oriented annotations       | types are enforced in declarations at compile time                     |
| Runtime protocol check  | limited `@runtime_checkable` `isinstance` | varies; usually explicit inheritance/RTTI/concepts at compile time     |
| Dependency injection    | pass collaborators/functions/objects      | pass dependencies through constructors/parameters                      |

Python’s protocols fit its dynamic style: a class can satisfy a needed shape without announcing that relationship ahead of time. C++ templates and concepts have related goals, but their compile-time model is very different.

## 14. Common mistakes and repairs

1. **Inheriting merely to reuse code.** Check whether the child genuinely is a kind of parent. If not, use composition or a helper.

2. **Creating a subclass for every feature combination.** Put independent variations—weapon, movement, damage rule—into composed collaborators.

3. **Using an ABC when a two-method protocol is enough.** An ABC couples implementations to a family; a protocol can keep a small consumer flexible.

4. **Assuming a runtime-checkable protocol validates signatures.** It checks shallow attribute presence, not semantic correctness.

5. **Treating hints as runtime validation.** Hints help tools; validate untrusted input separately.

6. **Annotating everything with `Any`.** `Any` turns off useful checking. Use a real type, union, protocol, or generic collection when you know the expected shape.

7. **Building a pattern before the problem earns it.** A small function or plain class is often the best first design.

8. **Hard-coding a dependency that should vary.** Pass it in if tests, modes, or callers need a different collaborator.

## 15. Exercises

### Exercise A — Is-a or has-a?

For each pair, choose inheritance, composition, or neither. Explain your reasoning in one sentence.

- `Rogue` and `Fighter`
- `Fighter` and `Inventory`
- `Match` and `DamageRule`
- `MapTile` and `Coordinates`
- `HealingPotion` and `Fighter`

### Exercise B — Abstract attack styles

Create an `AttackStyle` ABC with abstract `perform(attacker, defender)`. Implement `SwordAttack` and `PoisonAttack`. What happens if you attempt to instantiate `AttackStyle` itself?

### Exercise C — A protocol for targets

Write a `Damageable` protocol with `take_damage(amount: int) -> None`. Annotate a `cast_fireball(target)` function using it. Create a `TrainingDummy` that does not inherit from the protocol but works with the function.

### Exercise D — Type the inventory

Add type hints to this design:

```python
class Inventory:
    def __init__(self, items):
        self.items = items

    def add(self, item):
        self.items.append(item)

    def count(self):
        return len(self.items)
```

Assume items are strings. Then decide whether callers should access `.items` directly or receive a tuple snapshot instead.

## 16. Mini-lab — The Pluggable Arena

Build a mini arena that uses composition and a protocol rather than a giant inheritance tree.

Requirements:

- Define a `Damageable` protocol requiring `take_damage(amount: int) -> None`.
- Define a `DamageRule` type alias for a callable accepting `(base_damage, armor)` and returning damage.
- Create a `Combatant` class with `name`, `health`, `armor`, and `take_damage()`.
- Create at least two damage-rule functions, such as `standard_damage` and `piercing_damage`.
- Create a `Match` that receives a `DamageRule` in its initializer and uses it in `strike(attacker_name, defender, base_damage)`.
- Demonstrate that an unrelated `TrainingDummy` can serve as the defender if it implements `take_damage()`.

### One possible solution

```python
from collections.abc import Callable
from typing import Protocol


class Damageable(Protocol):
    """An object that can receive a non-negative amount of damage."""

    def take_damage(self, amount: int) -> None:
        ...


DamageRule = Callable[[int, int], int]


def standard_damage(base_damage: int, armor: int) -> int:
    """Reduce damage by armor, never below zero."""
    return max(0, base_damage - armor)


def piercing_damage(base_damage: int, armor: int) -> int:
    """Ignore half of the defender's armor."""
    return max(0, base_damage - armor // 2)


class Combatant:
    def __init__(self, name: str, health: int, armor: int = 0):
        self.name = name
        self.health = health
        self.armor = armor

    def take_damage(self, amount: int) -> None:
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health = max(0, self.health - amount)

    def __str__(self) -> str:
        return f"{self.name}: {self.health} HP"


class TrainingDummy:
    def __init__(self) -> None:
        self.total_damage = 0

    def take_damage(self, amount: int) -> None:
        self.total_damage += amount


class Match:
    def __init__(self, damage_rule: DamageRule):
        self.damage_rule = damage_rule

    def strike(
        self,
        attacker_name: str,
        defender: Damageable,
        base_damage: int,
        armor: int = 0,
    ) -> int:
        damage = self.damage_rule(base_damage, armor)
        defender.take_damage(damage)
        print(f"{attacker_name} deals {damage} damage.")
        return damage


aria = Combatant("Aria", 100)
milo = Combatant("Milo", 80, armor=6)
standard_match = Match(standard_damage)
piercing_match = Match(piercing_damage)

standard_match.strike(aria.name, milo, base_damage=15, armor=milo.armor)
piercing_match.strike(aria.name, milo, base_damage=15, armor=milo.armor)

dummy = TrainingDummy()
standard_match.strike(aria.name, dummy, base_damage=10)
print(dummy.total_damage)  # 10
```

Extensions:

- Replace the two damage functions with objects that share an ABC. Which version do you prefer, and why?
- Add a `CriticalHitRule` wrapper that doubles damage only when a passed-in random value meets a threshold. Inject the random-value source for predictable tests.
- Add `@runtime_checkable` to `Damageable`, then demonstrate why `isinstance(dummy, Damageable)` cannot prove that `take_damage` is correct.
- Add a protocol for objects with a `name` property and remove the separate `attacker_name` argument.

## 17. Review questions

1. What is the difference between “is-a” and “has-a” design reasoning?
2. What does `@abstractmethod` prevent?
3. How does a protocol differ from an abstract base class?
4. Why is a runtime-checkable protocol not full runtime type validation?
5. What does `X | None` communicate in a return annotation?
6. Why can dependency injection make a class easier to test?
7. When might a pair of `if` statements be better than a class hierarchy?
8. What is one danger of annotating a broad value as `Any`?

## Exit ticket

Choose one class hierarchy from a game or an earlier lesson. Identify one behavior that could vary independently, then explain in two or three sentences how composition or a protocol could make that behavior easier to change.

---

**Core series complete.** Your next challenge is a capstone: combine the lessons into a small, well-packaged Battle Arena game with tests, documentation, and a design you can defend.
