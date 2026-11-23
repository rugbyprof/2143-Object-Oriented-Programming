<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-04
name: oop-battle-arena
title: "Python’s Secret Handshakes: Dunder Protocols, Operators, and Iteration"
description: "Lesson 4 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 1
  day: 5
  year: 2027
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 4

# Python’s Secret Handshakes: Dunder Protocols, Operators, and Iteration

> **Arena premise:** Python’s built-in syntax is not reserved for built-in types. Teach an object the right protocol, and it can be printed, compared, measured, indexed, iterated, or combined—without wearing a fake `list` mustache.

## Learning objectives

By the end of this lesson, you should be able to:

- Explain a protocol as a behavior Python recognizes through special methods.
- Implement helpful `__repr__` and `__str__` methods.
- Define value equality with `__eq__` and understand `NotImplemented`.
- Implement ordering deliberately with `functools.total_ordering`.
- Overload selected operators with methods such as `__add__`.
- Make objects work with `len()`, `in`, indexing, loops, and `bool()`.
- Describe when `__hash__` matters and avoid unsafe mutable keys.
- Choose protocols that clarify an object’s meaning rather than create novelty confusion.

## 1. What is a protocol?

A **protocol** is a set of operations Python knows how to perform. Special methods—usually called **dunder methods** because of their double underscores—let your objects participate in those operations.

| Familiar syntax | Protocol method Python may call |
| --------------- | ------------------------------- |
| `print(x)`      | `x.__str__()`                   |
| `repr(x)`       | `x.__repr__()`                  |
| `x == y`        | `x.__eq__(y)`                   |
| `x < y`         | `x.__lt__(y)`                   |
| `x + y`         | `x.__add__(y)`                  |
| `len(x)`        | `x.__len__()`                   |
| `item in x`     | `x.__contains__(item)`          |
| `x[index]`      | `x.__getitem__(index)`          |
| `for item in x` | `x.__iter__()`                  |
| `bool(x)`       | `x.__bool__()` or `x.__len__()` |

Usually, write the left-hand syntax. `len(backpack)` expresses intention better than `backpack.__len__()`, and Python gets to apply the protocol consistently.

## 2. Representing objects: `__repr__` and `__str__`

These methods appeared in Lesson 1; they are worth revisiting because they are your fastest debugging allies.

```python
class Spell:
    def __init__(self, name, power):
        self.name = name
        self.power = power

    def __repr__(self):
        return f"Spell(name={self.name!r}, power={self.power!r})"

    def __str__(self):
        return f"{self.name} [{self.power} power]"


firebolt = Spell("Firebolt", 9)
print(firebolt)       # Firebolt [9 power]
print(repr(firebolt)) # Spell(name='Firebolt', power=9)
print([firebolt])     # [Spell(name='Firebolt', power=9)]
```

Use `__str__` for friendly output and `__repr__` for precise developer-facing output. If `__str__` is absent, Python falls back to `__repr__`. A useful `__repr__` means a list of 40 objects does not become 40 opaque memory addresses—an underrated quality-of-life feature.

## 3. Value equality with `__eq__`

Two objects can be different objects but represent the same value. By default, separately created instances generally compare unequal. Define `__eq__` when your class has a meaningful value-based identity.

```python
class Position:
    def __init__(self, row, column):
        self.row = row
        self.column = column

    def __repr__(self):
        return f"Position({self.row!r}, {self.column!r})"

    def __eq__(self, other):
        if not isinstance(other, Position):
            return NotImplemented
        return self.row == other.row and self.column == other.column


print(Position(2, 4) == Position(2, 4))  # True
print(Position(2, 4) == Position(4, 2))  # False
print(Position(2, 4) == (2, 4))          # False
```

### Why return `NotImplemented`?

`NotImplemented` is a special singleton, not the same thing as `NotImplementedError`. Returning it tells Python, “I do not know how to compare with that type.” Python can then try the reflected operation or use its normal fallback behavior.

Do **not** write this:

```python
# Wrong for an unsupported type:
# return False
```

Returning `False` claims the comparison was understood and is false. Returning `NotImplemented` is more cooperative and produces better behavior when another class understands the comparison.

## 4. Equality and hashing: the important contract

Sets and dictionary keys use hashes. If you define value-based `__eq__`, Python normally makes instances unhashable unless you explicitly provide a compatible `__hash__`.

```python
class Badge:
    def __init__(self, code):
        self.code = code

    def __eq__(self, other):
        if not isinstance(other, Badge):
            return NotImplemented
        return self.code == other.code


# badges = {Badge("A-1")}  # TypeError: unhashable type: 'Badge'
```

That restriction protects you. The key rule is:

> If `a == b`, then `hash(a)` must equal `hash(b)`.

Only create `__hash__` for objects whose equality-relevant data will not change while they are used as keys or set members.

```python
class ImmutableBadge:
    def __init__(self, code):
        self.code = code

    def __eq__(self, other):
        if not isinstance(other, ImmutableBadge):
            return NotImplemented
        return self.code == other.code

    def __hash__(self):
        return hash(self.code)


print(ImmutableBadge("A-1") == ImmutableBadge("A-1"))  # True
print(len({ImmutableBadge("A-1"), ImmutableBadge("A-1")}))  # 1
```

In real code, `@dataclass(frozen=True)` is often a more convenient way to make a small immutable value object; that arrives in a later lesson. Do not hash a mutable `Fighter` whose health can change. It would be a key that changes its own lock.

## 5. Ordering objects

`__lt__` means “less than.” It lets you sort objects and use comparisons such as `<`. Here, lower initiative acts first.

```python
from functools import total_ordering


@total_ordering
class Turn:
    def __init__(self, fighter, initiative):
        self.fighter = fighter
        self.initiative = initiative

    def __repr__(self):
        return f"Turn({self.fighter!r}, {self.initiative!r})"

    def __eq__(self, other):
        if not isinstance(other, Turn):
            return NotImplemented
        return self.initiative == other.initiative

    def __lt__(self, other):
        if not isinstance(other, Turn):
            return NotImplemented
        return self.initiative < other.initiative


turns = [Turn("Aria", 14), Turn("Milo", 8), Turn("Zed", 11)]
print(sorted(turns))
```

`@total_ordering` fills in the remaining comparison methods (`<=`, `>`, `>=`) when you supply `__eq__` and one ordering method. Import it from `functools` as shown.

Only make objects orderable when there is a clear, stable ordering. Is one fighter “less than” another? Not generally. A scheduled turn with an initiative number is a much clearer answer.

## 6. Operator overloading: give symbols an honest meaning

An operator method can make a domain operation concise. For example, adding two loot piles can combine their gold values.

```python
class Loot:
    def __init__(self, gold):
        self.gold = gold

    def __repr__(self):
        return f"Loot(gold={self.gold})"

    def __add__(self, other):
        if not isinstance(other, Loot):
            return NotImplemented
        return Loot(self.gold + other.gold)


reward = Loot(12) + Loot(8)
print(reward)  # Loot(gold=20)
```

`__add__` should return a **new** value here rather than secretly changing either original pile. That resembles how integers behave.

There are many operator hooks, including `__sub__`, `__mul__`, `__truediv__`, and `__matmul__`. Implement only operations that a reader can predict. `fighter + dragon` is not automatically expressive just because Python permits it.

### Reflected and in-place operators

If Python evaluates `3 + object`, it may look for `object.__radd__(3)`. `__iadd__` supports `+=` when mutation makes sense. You do not need them for most beginner classes.

```python
class HitPoints:
    def __init__(self, amount):
        self.amount = amount

    def __add__(self, bonus):
        if not isinstance(bonus, int):
            return NotImplemented
        return HitPoints(self.amount + bonus)

    def __radd__(self, bonus):
        return self + bonus


print(5 + HitPoints(20))  # A HitPoints object with amount 25
```

For that final line to print pleasantly, add `__repr__` or inspect `.amount`. The example’s point is direction: `__add__` handles `object + value`; `__radd__` handles `value + object`.

## 7. Container behavior: length, membership, and indexing

Let’s build a useful inventory wrapper.

```python
class Inventory:
    def __init__(self, items=()):
        self._items = list(items)

    def __repr__(self):
        return f"Inventory({self._items!r})"

    def __len__(self):
        return len(self._items)

    def __contains__(self, item):
        return item in self._items

    def __getitem__(self, index):
        return self._items[index]


bag = Inventory(["rope", "torch", "apple"])
print(len(bag))       # 3
print("torch" in bag)  # True
print(bag[0])         # rope
print(bag[1:])        # ['torch', 'apple']; slices work because the list handles them
```

`__getitem__` receives the bracket contents. It may be an integer, a `slice`, or another valid key for your object. Delegating to a list gives normal list indexing behavior, including useful `IndexError` messages.

## 8. Iteration: making `for` loops work

The cleanest implementation of `__iter__` delegates to an existing iterable.

```python
class Party:
    def __init__(self, members=()):
        self._members = list(members)

    def __iter__(self):
        return iter(self._members)


party = Party(["Aria", "Milo", "Zed"])
for member in party:
    print(member)
```

`iter(self._members)` returns a list iterator. Your `Party` does not need to reinvent the iterator protocol merely to pass names along.

You can also use a generator with `yield`:

```python
class Party:
    def __init__(self, members=()):
        self._members = list(members)

    def __iter__(self):
        for member in self._members:
            yield member.upper()


print(list(Party(["Aria", "Milo"])))  # ['ARIA', 'MILO']
```

Use the second form only when your class adds meaningful iteration behavior. If it merely owns a list, direct delegation is shorter and clearer.

## 9. Truthiness: `__bool__` and `__len__`

Every object can appear in an `if` condition. By default, an instance is truthy. Define `__bool__` for an explicit truth concept, such as whether a fighter is still active.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def __bool__(self):
        return self.health > 0


aria = Fighter("Aria", 0)
if not aria:
    print("Aria is defeated.")
```

If `__bool__` is absent, Python consults `__len__`: objects with length zero are falsey. An `Inventory` with `__len__` is therefore falsey when empty without needing an additional method.

Be conservative with custom truthiness. `if fighter:` should be obvious to a reader; surprising meanings create “works technically” code that nobody wants to maintain.

## 10. Python and C++ comparisons

| Idea                    | Python                      | C++ (rough comparison)                       |
| ----------------------- | --------------------------- | -------------------------------------------- |
| Friendly representation | `__str__`, `__repr__`       | typically `operator<<` or a display function |
| Equality                | `__eq__`                    | `operator==`                                 |
| Ordering                | `__lt__`, etc.              | `operator<`, etc.                            |
| Addition                | `__add__`                   | `operator+`                                  |
| Size                    | `__len__` used by `len(x)`  | commonly `.size()` / `.length()`             |
| Iteration               | `__iter__`, `__next__`      | iterator `begin()`/`end()` conventions       |
| Hashing                 | `__hash__` for dict/set use | hash specialization / hash functor           |

The broad idea is familiar: both languages let user-defined types participate in operations. Python centralizes those behaviors in named protocols and often supplies built-in functions (`len`, `iter`, `repr`) rather than member-method syntax.

## 11. Common mistakes and repairs

1. **Calling dunders directly in normal code.** Prefer `len(bag)`, `item in bag`, and `str(spell)`; call the dunder directly only when debugging or teaching the protocol.

2. **Returning `False` instead of `NotImplemented` for an unsupported operand type.** Returning `NotImplemented` allows Python to try the other operand’s method.

3. **Defining value equality for mutable objects and then hashing them.** Do not use changing equality data as a dictionary-key hash basis.

4. **Making every object sortable.** Define ordering only when there is an honest, unambiguous basis.

5. **Overloading an operator with a surprising meaning.** `+` should feel addition-like to the reader.

6. **Returning something other than an integer from `__len__`.** `__len__` must return a non-negative integer.

7. **Reimplementing a list badly.** Delegate to a real list, tuple, dictionary, or iterator when that gives the behavior you want.

8. **Exposing internal mutable collections unnecessarily.** Consider whether iteration or safe methods communicate intent better than handing out the actual list.

## 12. Exercises

### Exercise A — Equal coordinates

Create a `Tile` class with `row` and `column`. Implement `__repr__` and `__eq__` so two tiles with the same coordinates compare equal. Compare a `Tile` with a tuple and confirm your class handles the unsupported type safely.

**Hint:** return `NotImplemented` when `other` is not a `Tile`.

### Exercise B — Sort the turn order

Create a `CombatTurn` class that stores a `name` and an `initiative`. Implement enough methods to sort a list of turns by initiative. You may use `@total_ordering`.

**Hint:** define both `__eq__` and `__lt__`.

### Exercise C — A sensible `+`

Create a `Gold` class where `Gold(7) + Gold(5)` returns `Gold(12)`. Add a `__repr__` so you can inspect the result. What should happen for `Gold(7) + 5`? Choose and implement a consistent answer.

### Exercise D — Browse the armory

Create an `Armory` class around a list of strings. Make it support `len(armory)`, `weapon in armory`, `armory[0]`, and `for weapon in armory`.

## 13. Mini-lab — The Quest Log Collection

Create a `QuestLog` that behaves like a small collection of quest names while protecting its internal list.

Requirements:

- Start from any iterable of quest names, defaulting to none.
- `add(quest)` adds a non-empty string or raises a helpful error.
- `len(log)` returns the number of quests.
- `quest in log` tests membership.
- `log[index]` supports ordinary indexing and slices.
- `for quest in log` iterates in order.
- `repr(log)` is useful in the debugger.
- `bool(log)` is false when no quests are present. You may get this automatically from `__len__`.

### One possible solution

```python
class QuestLog:
    def __init__(self, quests=()):
        self._quests = []
        for quest in quests:
            self.add(quest)

    def add(self, quest):
        if not isinstance(quest, str):
            raise TypeError("a quest must be a string")
        if not quest.strip():
            raise ValueError("a quest cannot be empty")
        self._quests.append(quest)

    def __repr__(self):
        return f"QuestLog({self._quests!r})"

    def __len__(self):
        return len(self._quests)

    def __contains__(self, quest):
        return quest in self._quests

    def __getitem__(self, index):
        return self._quests[index]

    def __iter__(self):
        return iter(self._quests)
```

Try it:

```python
log = QuestLog(["Find the map", "Cross the marsh"])
log.add("Meet the archivist")

print(log)                 # QuestLog([...]) because __str__ is absent
print(len(log))            # 3
print("Find the map" in log)  # True
print(log[1:])             # ['Cross the marsh', 'Meet the archivist']
print(list(log))
print(bool(log))           # True
```

Extensions:

- Add `remove(quest)` with a clear behavior when the quest is absent.
- Add `__reversed__` so `reversed(log)` gives newest-to-oldest order.
- Add a separate `CompletedQuestLog` subtype only if it truly needs distinct behavior; otherwise consider an ordinary status field.
- Decide whether two logs should be value-equal. If so, discuss whether they should be hashable.

## 14. Review questions

1. What does it mean for a class to support a protocol?
2. Why is `NotImplemented` a better result than `False` for an unsupported `__eq__` comparison?
3. What hashing rule must hold for equal objects?
4. Why should mutable fighters generally not be dictionary keys based on their health and name?
5. Which dunder makes `len(x)` work? Which makes `x[index]` work?
6. What two ways can an object influence its truthiness?
7. When would `@total_ordering` be useful?
8. Give one example of an operator overload that would confuse readers.

## Exit ticket

In two or three sentences, explain why a `QuestLog` that supports `len`, `in`, indexing, and iteration can be easier to use than a class with methods named `get_count`, `has_quest`, `get_quest`, and `get_all_quests`. Name at least two dunder methods that make the natural syntax possible.

---

**Next arena:** documentation, `help()`, introspection, and APIs that future humans can actually understand.
