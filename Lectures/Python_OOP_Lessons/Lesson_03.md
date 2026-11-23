<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-03
name: oop-battle-arena
title: "Python’s Guarded Gate: Encapsulation, Properties, and Validation"
description: "Lesson 3 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 12
  day: 29
  year: 2026
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 3

# Python’s Guarded Gate: Encapsulation, Properties, and Validation

> **Arena premise:** a fighter’s health should not mysteriously become `"banana"`, and an inventory should not contain negative swords. This lesson teaches an object to protect its own rules—politely, because Python favors cooperation over padlocks.

## Learning objectives

By the end of this lesson, you should be able to:

- Explain encapsulation as bundling data with the rules that protect it.
- Recognize Python’s public, single-underscore, and double-underscore naming conventions.
- Use `@property` to expose attribute-like access with validation.
- Write a getter, setter, and deleter when each is appropriate.
- Avoid accidental infinite recursion in property methods.
- Use properties to preserve a class’s interface while changing its implementation.
- Compare Python’s approach with C++ access control.

## 1. What is encapsulation?

**Encapsulation** means keeping related data and behavior together and giving the object responsibility for maintaining its own valid state. It is not merely “hide every variable.” It is about making misuse harder and correct use clear.

Imagine a fighter with health. If any code can freely assign any value, an accidental bug can create impossible states:

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

aria = Fighter("Aria", 100)
aria.health = -900
aria.health = "very healthy"
```

Python allows this, but your program probably should not. A class can provide a controlled gateway for changing health.

## 2. Python does not use C++-style access modifiers

Python has no `public`, `protected`, or `private` keywords for ordinary attributes. Instead, it uses naming conventions and a feature called name mangling.

| Name style | Meaning by convention                                         | Example                    |
| ---------- | ------------------------------------------------------------- | -------------------------- |
| `health`   | Public API: other code may use it.                            | `fighter.health`           |
| `_health`  | Internal implementation detail: “please do not use directly.” | `fighter._health`          |
| `__health` | Name-mangled to reduce accidental access/collision.           | `fighter._Fighter__health` |
| `__init__` | Special Python protocol name; do not invent your own dunders. | `Fighter.__init__`         |

A leading underscore is a social boundary, not a security system. It says: “This works, but it is not a promise to outside code.” Most tools also treat underscore names as internal when deciding what to import or display.

## 3. The simplest useful convention: one underscore

Store internal data under an underscore name, then expose a public property. This lets users write natural attribute syntax while the class enforces rules.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health  # Calls the property setter below.

    @property
    def health(self):
        """Current health, always a non-negative integer."""
        return self._health

    @health.setter
    def health(self, value):
        if not isinstance(value, int):
            raise TypeError("health must be an integer")
        if value < 0:
            raise ValueError("health cannot be negative")
        self._health = value


aria = Fighter("Aria", 100)
print(aria.health)  # 100
aria.health = 80    # Calls the setter
```

`@property` turns the `health` method into an attribute-like **getter**. `@health.setter` adds the assignment behavior. Outside code uses `aria.health`, not `aria.get_health()` and `aria.set_health(80)`.

Try invalid values:

```python
# aria.health = -1       # ValueError
# aria.health = "full"   # TypeError
```

The errors are not punishment. They identify a broken assumption where it happens, instead of allowing broken data to wander the arena until it causes a more mysterious failure later.

## 4. Properties preserve a clean interface

Suppose your first version stores health directly:

```python
class EarlyFighter:
    def __init__(self, health):
        self.health = health
```

Later, you discover that values need checking. Replacing `health` with a property keeps client code unchanged:

```python
fighter.health = 80
print(fighter.health)
```

The public interface remains `health`; only its implementation changes from direct storage to controlled access. That is a major benefit of properties: they offer flexibility without making every caller rewrite its code.

## 5. The recursion trap

Inside a property getter or setter, do **not** assign to or return the public property itself. That just calls the property again forever.

```python
class BrokenFighter:
    @property
    def health(self):
        return self.health  # Calls health again: recursion!

    @health.setter
    def health(self, value):
        self.health = value  # Calls the setter again: recursion!
```

Use a distinct backing attribute such as `_health`:

```python
class SafeFighter:
    @property
    def health(self):
        return self._health

    @health.setter
    def health(self, value):
        self._health = value
```

The underscore is doing organizational work: it separates the public gateway (`health`) from the stored value (`_health`).

## 6. Put behavior near the state it changes

Validation is not only for assignment. Methods can express meaningful game actions and protect rules in one place.

```python
class Fighter:
    def __init__(self, name, max_health):
        self.name = name
        self.max_health = max_health
        self.health = max_health

    @property
    def health(self):
        return self._health

    @health.setter
    def health(self, value):
        if not isinstance(value, int):
            raise TypeError("health must be an integer")
        self._health = max(0, min(value, self.max_health))

    def take_damage(self, amount):
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health -= amount

    def heal(self, amount):
        if amount < 0:
            raise ValueError("healing cannot be negative")
        self.health += amount


aria = Fighter("Aria", 100)
aria.take_damage(30)
aria.heal(500)
print(aria.health)  # 100, capped at max_health
```

Notice that `take_damage` and `heal` use `self.health`, so they automatically pass through the setter. The object’s health rule lives in one authoritative place.

## 7. Read-only properties and calculated attributes

Not every property needs a setter. A **read-only property** is useful when a value is calculated from other data.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    @property
    def is_defeated(self):
        return self.health == 0


aria = Fighter("Aria", 0)
print(aria.is_defeated)  # True
# aria.is_defeated = False  # AttributeError: no setter exists
```

`is_defeated` looks like data because it is an attribute-like fact, even though it is computed each time. Do not add a setter: whether a fighter is defeated should follow from health, not be independently assigned by a confused wizard.

Another example uses two stored attributes:

```python
class Weapon:
    def __init__(self, base_damage, bonus_damage):
        self.base_damage = base_damage
        self.bonus_damage = bonus_damage

    @property
    def damage(self):
        return self.base_damage + self.bonus_damage

blade = Weapon(8, 3)
print(blade.damage)  # 11
```

## 8. Setters should have clear rules

Ask two questions before writing a setter:

1. **What values are valid?** For health, perhaps integers from 0 through `max_health`.
2. **Should invalid input be rejected or adjusted?** `raise ValueError` rejects it; `max()`/`min()` clamps it into range.

Both approaches can be reasonable. Choose one intentionally and document it.

```python
class StrictLevel:
    @property
    def level(self):
        return self._level

    @level.setter
    def level(self, value):
        if not isinstance(value, int) or not 1 <= value <= 20:
            raise ValueError("level must be an integer from 1 to 20")
        self._level = value
```

Clamping is friendlier for a game-health bar. Rejecting is often better when an out-of-range value indicates a programming mistake. The design should make failures understandable, not merely loud.

## 9. The property deleter: rare, but real

You can define a response for `del object.attribute` with `@attribute.deleter`. Use it only when deletion has a meaningful domain interpretation.

```python
class ArenaEntry:
    def __init__(self, fighter_name):
        self._fighter_name = fighter_name

    @property
    def fighter_name(self):
        return self._fighter_name

    @fighter_name.deleter
    def fighter_name(self):
        raise AttributeError("An arena entry must always have a fighter name")


entry = ArenaEntry("Aria")
# del entry.fighter_name  # AttributeError
```

Most properties need only a getter, or a getter plus setter. A deleter is not a requirement to check off on a quest log.

## 10. Double underscores and name mangling

An attribute named `__secret` inside a class is rewritten by Python to include the class name. This is called **name mangling**.

```python
class Vault:
    def __init__(self):
        self.__code = "moon-owl"

    def verify(self, attempt):
        return attempt == self.__code


vault = Vault()
print(vault.verify("moon-owl"))  # True
# print(vault.__code)             # AttributeError
print(vault._Vault__code)         # moon-owl (possible, but discouraged)
```

Name mangling is useful mainly to avoid accidental name clashes in subclasses. It is **not** security: a determined caller can still use the mangled name. Prefer `_name` for ordinary internal details. Reserve `__name` for cases where you specifically want collision avoidance.

Avoid inventing names like `__battle_magic__`; names with double underscores on both sides are reserved for Python’s special protocols unless documented otherwise.

## 11. `property()` without decorator syntax

The decorator form is standard and easiest to read, but this older equivalent reveals what `@property` creates.

```python
class Banner:
    def get_title(self):
        return self._title

    def set_title(self, value):
        if not value:
            raise ValueError("title cannot be empty")
        self._title = value

    title = property(get_title, set_title)
```

In modern Python, prefer the decorator form because it groups the getter and setter under one readable attribute name. You may still encounter `property(getter, setter)` in older code.

## 12. Python and C++ comparisons

| Idea                       | Python                                       | C++ (rough comparison)                              |
| -------------------------- | -------------------------------------------- | --------------------------------------------------- |
| Public data                | ordinary attribute, e.g. `health`            | public member or getter                             |
| Internal convention        | `_health` signals “internal”                 | often `protected` or `private`                      |
| Private-like name          | `__health` is name-mangled, not inaccessible | `private` has compiler-enforced access restrictions |
| Getter/setter syntax       | `@property` preserves `obj.health` syntax    | commonly `getHealth()` / `setHealth()` methods      |
| Validation                 | property setter or domain method             | setter/member function, often with access control   |
| Read-only calculated value | getter-only property                         | `const` member function / getter                    |

Python chooses a trust-based style: conventions communicate intent, while properties provide controlled behavior when an attribute needs rules. C++ access modifiers are stronger boundaries enforced at compile time.

## 13. Common mistakes and repairs

1. **Treating underscores as security.** `_health` is a convention; `__health` is mangling. Neither protects secrets from code that can run in your process.

2. **Using a getter/setter for every field automatically.** Start with a plain public attribute when there is no invariant to protect. Add a property when behavior or validation earns its keep.

3. **Writing recursive property code.** Store data in `_health`, not `health`, inside the `health` property.

4. **Validating in some methods but not others.** Put a single rule in a property setter or one dedicated validation method.

5. **Making a derived fact writable.** `is_defeated` should be calculated from health, not set independently.

6. **Using `assert` for public input validation.** Assertions can be disabled and are best for internal programmer assumptions. Raise `TypeError` or `ValueError` for invalid public arguments.

7. **Returning a misleading value after a rejected update.** Either reject invalid values clearly or clamp them consistently; document the chosen rule.

## 14. Exercises

### Exercise A — A validated mana pool

Create a `Mage` class with `name`, `max_mana`, and a `mana` property. Mana must be an integer from 0 through `max_mana`. Decide whether out-of-range assignments should raise an error or clamp, then test your choice.

**Hint:** initialize `max_mana` before assigning `self.mana`.

### Exercise B — A read-only status

Add a read-only `can_cast` property to `Mage`. It should be `True` only when mana is at least 10. Why would a setter for `can_cast` be misleading?

### Exercise C — Fix the recursion

Repair this class so it stores and returns a temperature correctly:

```python
class BrokenPotion:
    @property
    def temperature(self):
        return self.temperature

    @temperature.setter
    def temperature(self, value):
        self.temperature = value
```

### Exercise D — Conventions investigation

Create an object with `public`, `_internal`, and `__mangled` instance attributes. Print its `__dict__`. Which keys do you see? Why is the double-underscore name different?

## 15. Mini-lab — The Safe Character Sheet

Build a `CharacterSheet` class with these rules:

- It has a public `name`.
- It accepts `max_health` only as a positive integer.
- Its `health` property always stays from 0 through `max_health`.
- `take_damage(amount)` and `heal(amount)` reject negative amounts.
- Its `is_defeated` property is read-only.
- `__str__` returns a useful one-line status.

Use this test:

```python
aria = CharacterSheet("Aria", 100)
aria.take_damage(35)
print(aria)              # Aria: 65/100 HP
print(aria.is_defeated)  # False
aria.heal(500)
print(aria)              # Aria: 100/100 HP
```

### One possible solution

```python
class CharacterSheet:
    def __init__(self, name, max_health):
        if not isinstance(max_health, int) or max_health <= 0:
            raise ValueError("max_health must be a positive integer")
        self.name = name
        self.max_health = max_health
        self.health = max_health

    @property
    def health(self):
        return self._health

    @health.setter
    def health(self, value):
        if not isinstance(value, int):
            raise TypeError("health must be an integer")
        self._health = max(0, min(value, self.max_health))

    @property
    def is_defeated(self):
        return self.health == 0

    def take_damage(self, amount):
        if not isinstance(amount, int) or amount < 0:
            raise ValueError("damage must be a non-negative integer")
        self.health -= amount

    def heal(self, amount):
        if not isinstance(amount, int) or amount < 0:
            raise ValueError("healing must be a non-negative integer")
        self.health += amount

    def __str__(self):
        return f"{self.name}: {self.health}/{self.max_health} HP"
```

Extensions:

- Add a validated `level` property from 1 through 20.
- Make `heal()` return the amount actually restored, after the maximum-health cap.
- Add a private-ish `_log` list of changes and a read-only property that returns a copy of it.
- Discuss why returning a copy is safer than returning the actual internal list.

## 16. Review questions

1. What problem does encapsulation try to solve?
2. What does a single leading underscore communicate in Python?
3. Is `__name` truly private? Explain name mangling precisely.
4. Why does a property use `_health` internally rather than `health`?
5. When is a getter-only property a better design than a writable attribute?
6. What is one advantage of adding a property after code already uses a public attribute?
7. When should a program raise an error rather than clamp a value?
8. How does Python’s access-control philosophy differ from C++’s?

## Exit ticket

In two or three sentences, explain why `fighter.health` can be a better interface than `fighter.get_health()` and `fighter.set_health(value)` in Python. Include the role of `@property` and one rule it can enforce.

---

**Next arena:** dunder protocols in depth—equality, ordering, arithmetic, containers, and iteration. Your objects are about to learn new moves.
