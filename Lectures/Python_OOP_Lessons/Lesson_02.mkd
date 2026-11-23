<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-02
name: oop-battle-arena
title: "Python Inheritance Arena: Reuse, Overrides, super(), and Polymorphism"
description: "Lesson 2 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 12
  day: 22
  year: 2026
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 2

# Python Inheritance Arena: Reuse, Overrides, `super()`, and Polymorphism

> **Arena premise:** Lesson 1 gave every fighter a class. This lesson gives classes family trees. Used well, inheritance avoids repetition; used recklessly, it creates a family reunion nobody can debug.

## Learning objectives

By the end of this lesson, you should be able to:

- Describe the “is-a” relationship that makes inheritance appropriate.
- Define a subclass and recognize what it inherits.
- Override an inherited method intentionally.
- Use `super()` to preserve and extend parent-class behavior.
- Explain runtime polymorphism and duck typing.
- Use `isinstance()` and `issubclass()` appropriately.
- Recognize when composition is a better design than inheritance.
- Read basic multiple-inheritance and MRO output without panic.

## 1. Why inherit?

Suppose every arena fighter has a name, health, and a way to introduce itself. Rather than retyping that state for every kind of fighter, make a general base class and more specific subclasses.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def introduce(self):
        return f"I am {self.name}, with {self.health} health."


class Knight(Fighter):
    pass


class Wizard(Fighter):
    pass


knight = Knight("Aria", 120)
wizard = Wizard("Milo", 75)

print(knight.introduce())
print(wizard.name)
```

`Knight(Fighter)` means **Knight is a kind of Fighter**. The subclass inherits accessible attributes and methods from its parent (also called a base class or superclass). `pass` means “the class body is intentionally empty for now.”

Inheritance models an **is-a** relationship:

- A `Knight` **is a** `Fighter`.
- A `Wizard` **is a** `Fighter`.
- A `Fighter` is *not necessarily* a `Sword`. A fighter *has a* sword. That distinction matters later.

## 2. Adding subclass-specific state

Subclasses can add their own attributes and methods. To reuse the parent’s initialization, call `super().__init__(...)`.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health


class Wizard(Fighter):
    def __init__(self, name, health, mana):
        super().__init__(name, health)
        self.mana = mana

    def cast_spell(self):
        if self.mana < 10:
            return f"{self.name} needs more mana."
        self.mana -= 10
        return f"{self.name} casts a spell!"


milo = Wizard("Milo", 75, 30)
print(milo.health)        # 75, initialized by Fighter
print(milo.cast_spell())  # Milo casts a spell!
print(milo.mana)          # 20
```

`super()` gives access to the next appropriate implementation in the inheritance chain. In this simple case, that is `Fighter`. Calling the parent initializer prevents duplicated setup and makes future changes less error-prone.

### A common mistake: skipping parent initialization

```python
class BrokenWizard(Fighter):
    def __init__(self, name, health, mana):
        self.mana = mana
        # Forgot: super().__init__(name, health)

broken = BrokenWizard("Milo", 75, 30)
# print(broken.name)  # AttributeError: name was never set
```

You *can* manually assign `self.name` and `self.health`, but `super()` makes the relationship explicit and keeps shared initialization in one place.

## 3. Overriding: same method name, specialized behavior

A subclass can replace an inherited method by defining a method with the same name. This is called **overriding**.

```python
class Fighter:
    def attack(self):
        return f"{self.name} attacks with a basic strike."


class Knight(Fighter):
    def attack(self):
        return f"{self.name} charges with a lance!"


class Wizard(Fighter):
    def attack(self):
        return f"{self.name} launches an arcane bolt!"
```

Python chooses the version that belongs to the actual object at runtime:

```python
fighters = [Knight("Aria", 120), Wizard("Milo", 75)]

for fighter in fighters:
    print(fighter.attack())

# Aria charges with a lance!
# Milo launches an arcane bolt!
```

That is **polymorphism**: one operation (`attack()`) works through the same interface while each object supplies behavior suited to its type.

## 4. Extending an inherited method with `super()`

Overriding does not mean you must discard the parent behavior. Call `super().method_name()` when you want to add onto it.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)
        return self.health


class ShieldKnight(Fighter):
    def __init__(self, name, health, shield):
        super().__init__(name, health)
        self.shield = shield

    def take_damage(self, amount):
        absorbed = min(self.shield, amount)
        self.shield -= absorbed
        remaining = amount - absorbed
        super().take_damage(remaining)
        return self.health


aria = ShieldKnight("Aria", 120, shield=15)
aria.take_damage(20)
print(aria.shield)  # 0
print(aria.health)  # 115
```

First, the shield absorbs 15 damage. The subclass then delegates the remaining 5 to the base method, which applies the ordinary health rule. Each class owns the part of the work it understands.

## 5. Inheritance and constructors

If a subclass does **not** define `__init__`, it inherits the parent’s initializer unchanged.

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

class Archer(Fighter):
    pass

robin = Archer("Robin", 90)  # Uses Fighter.__init__
```

If it defines its own `__init__`, it is responsible for calling `super().__init__()` when parent initialization is needed. A subclass may pass different arguments, add more attributes, or validate its special data first.

## 6. Checking class relationships

Use `isinstance(object, Class)` to ask whether an object is an instance of a class **or one of its subclasses**. Use `issubclass(Child, Parent)` to ask about classes.

```python
aria = ShieldKnight("Aria", 120, 15)

print(isinstance(aria, ShieldKnight))  # True
print(isinstance(aria, Fighter))       # True
print(issubclass(ShieldKnight, Fighter))  # True
print(issubclass(Fighter, ShieldKnight))  # False
```

For most behavior, prefer calling the method you need instead of checking exact types. If code needs something that can `attack()`, let objects demonstrate that ability. This is the beginning of Python’s “duck typing” style: if it quacks correctly, the program often does not need to inspect its family tree.

## 7. Duck typing: behavior before ancestry

The function below never asks whether its input is a `Fighter`. It only requires an object with an `attack()` method.

```python
class TrainingDummy:
    def attack(self):
        return "The dummy bravely remains still."


def announce_attack(combatant):
    print(combatant.attack())


announce_attack(Knight("Aria", 120))
announce_attack(TrainingDummy())
```

This can make programs flexible. It also means a missing method becomes an error at the point of use, so clear interfaces and tests are valuable.

## 8. Python and C++ comparisons

| Idea                          | Python                                       | C++ (rough comparison)                                                       |
| ----------------------------- | -------------------------------------------- | ---------------------------------------------------------------------------- |
| Inherit                       | `class Wizard(Fighter):`                     | `class Wizard : public Fighter { ... };`                                     |
| Parent initialization         | `super().__init__(...)`                      | base constructor in the initializer list                                     |
| Override                      | define same method name                      | usually define a `virtual` method in base, then override                     |
| Dynamic dispatch              | normal instance methods dispatch dynamically | requires `virtual` for polymorphic dispatch through base pointers/references |
| “Private” inheritance concern | not an ordinary Python category              | access modes include `public`, `protected`, `private` inheritance            |
| Interface checking            | often duck typing; sometimes `isinstance()`  | static type/interface checks are more common                                 |

Python does not require a `virtual` keyword. When you call an instance method, Python generally resolves the method based on the object’s actual class. That convenience is powerful; it also means naming consistency matters.

## 9. Multiple inheritance and the MRO: a cautious preview

Python allows a class to inherit from more than one parent. The **method resolution order** (MRO) is the sequence Python uses to look for methods and attributes.

```python
class Flyer:
    def move(self):
        return "flies"


class Swimmer:
    def move(self):
        return "swims"


class Dragon(Flyer, Swimmer):
    pass


draco = Dragon()
print(draco.move())        # flies
print(Dragon.mro())        # [Dragon, Flyer, Swimmer, object]
```

Because `Flyer` appears first, its `move` is found first. Multiple inheritance is sometimes useful for small, cooperative behaviors, but it can create difficult-to-follow designs. For now, read the MRO, use `super()` rather than hard-coding parent names in cooperative hierarchies, and do not summon a diamond-shaped hierarchy before lunch.

## 10. Inheritance or composition?

Use **inheritance** when a specialized thing genuinely *is a* more general thing. Use **composition** when one object *has a* helper or part.

```python
class Weapon:
    def __init__(self, name, damage):
        self.name = name
        self.damage = damage


class Fighter:
    def __init__(self, name, weapon):
        self.name = name
        self.weapon = weapon  # Fighter has a Weapon.

    def attack(self):
        return f"{self.name} attacks with {self.weapon.name}!"


spear = Weapon("Ash Spear", 12)
aria = Fighter("Aria", spear)
print(aria.attack())
```

Do **not** make `Fighter` inherit from `Weapon`; a fighter is not a subtype of weapon. Composition keeps unrelated responsibilities separate and often makes code easier to change.

## 11. Common mistakes and repairs

1. **Using inheritance only to reuse a few lines.** First ask whether the subtype truly satisfies an “is-a” relationship. Otherwise favor composition or a helper function.

2. **Overriding `__init__` and forgetting `super().__init__`.** Parent attributes will not exist unless you initialize them yourself.

3. **Calling a parent class by name unnecessarily.** Prefer `super()` in ordinary inheritance; it cooperates correctly with later subclassing and MRO.

4. **Changing a method’s meaning incompatibly.** If every `Fighter.attack()` returns a useful description, a subclass should not suddenly return a random list. Polymorphism relies on predictable contracts.

5. **Using `type(x) is Fighter` when subclasses should count.** Prefer `isinstance(x, Fighter)`.

6. **Checking types where behavior is enough.** If all you need is `.attack()`, accept an object that can attack.

7. **Building deep inheritance trees too soon.** Three parent classes and a prophecy are not automatically good architecture.

## 12. Exercises

### Exercise A — Specialized attack

Create a `Fighter` class with a `name` and an `attack()` method. Create `Rogue` and `Healer` subclasses that override `attack()` with different messages. Store one object of each class in a list and loop over the list to call `attack()`.

**Hint:** the loop should not need `if isinstance(...)` branches.

### Exercise B — Extend, do not replace

Create a `Fighter.take_damage(amount)` method. Then make an `ArmoredFighter` subclass with an `armor` value. Damage should reduce armor first and then call the parent method with the remaining damage.

**Hint:** calculate `remaining = max(0, amount - self.armor)` carefully; remember to update the armor.

### Exercise C — Is-a or has-a?

For each pair, decide whether inheritance or composition fits better and give one sentence of reasoning:

- `Wizard` and `Fighter`
- `Fighter` and `Inventory`
- `Arena` and `Fighter`
- `FireWizard` and `Wizard`

### Exercise D — Read the MRO

Create `class Amphibious(Swimmer, Walker):`. Give both parent classes a `move()` method. Predict the result of `Amphibious().move()`, then check `Amphibious.mro()`.

## 13. Mini-lab — The Arena Tournament

Build a small tournament that demonstrates polymorphism.

Requirements:

- `Fighter` stores `name` and `health`, and has `take_damage(amount)`.
- `Knight` has `armor` and reduces incoming damage before the base health rule runs.
- `Wizard` has `mana`; its `attack()` spends mana when possible and otherwise returns a weaker message.
- A `run_round(attacker, defender)` function calls `attacker.attack()` and then applies an amount of damage to the defender. It should work for either subclass without checking its exact type.

One reasonable starting solution:

```python
class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)
        return self.health

    def attack(self):
        return f"{self.name} strikes", 5


class Knight(Fighter):
    def __init__(self, name, health, armor):
        super().__init__(name, health)
        self.armor = armor

    def take_damage(self, amount):
        blocked = min(self.armor, amount)
        remaining = amount - blocked
        return super().take_damage(remaining)

    def attack(self):
        return f"{self.name} swings a sword", 8


class Wizard(Fighter):
    def __init__(self, name, health, mana):
        super().__init__(name, health)
        self.mana = mana

    def attack(self):
        if self.mana >= 5:
            self.mana -= 5
            return f"{self.name} casts a fire bolt", 10
        return f"{self.name} uses a staff", 3


def run_round(attacker, defender):
    message, damage = attacker.attack()
    defender.take_damage(damage)
    print(message)
    print(f"{defender.name} has {defender.health} health left.")


aria = Knight("Aria", 40, armor=3)
milo = Wizard("Milo", 30, mana=10)
run_round(milo, aria)
run_round(aria, milo)
```

Extensions:

- Add `is_defeated()` to `Fighter`.
- Give `Knight` armor that wears down each time it blocks damage.
- Add `__str__` methods so a scoreboard can print each fighter.
- Create an unrelated `TrainingDummy` that still works with `run_round` because it supplies the needed methods.

## 14. Review questions

1. What relationship does inheritance model?
2. What does `super().__init__()` accomplish in a subclass initializer?
3. What is method overriding?
4. How does polymorphism let one loop call `attack()` on different classes?
5. When should `isinstance(x, Parent)` be preferred to `type(x) is Parent`?
6. Why might composition be better than inheritance for a fighter and a weapon?
7. What does the method resolution order tell Python?
8. How does Python’s method dispatch differ from C++ virtual dispatch?

## Exit ticket

In two or three sentences, explain the difference between **overriding** and **extending** a method. Include one use of `super()` in your explanation.

---

**Next arena:** encapsulation, properties, validation, and the difference between “private” conventions and actual force fields.
