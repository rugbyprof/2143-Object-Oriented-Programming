<details>
<summary>readmees</summary>

```yaml
is_due: false
id: oop-battle-arena-lesson-07
name: oop-battle-arena
title: "Python’s Map Room: Modules, Packages, Imports, and __main__"
description: "Lesson 7 student handout for the OOP Battle Arena series."
category: Python / Object-Oriented Programming
date_due:
  month: 1
  day: 26
  year: 2027
  hour: 23
```

</details>

# OOP Battle Arena — Lesson 7

# Python’s Map Room: Modules, Packages, Imports, and `__main__`

> **Arena premise:** a one-file project is a cozy campfire. A growing project is a city. Modules and packages give every class, function, and test a sensible address—so nobody has to keep their sword in `final_final_really_final.py`.

## Learning objectives

By the end of this lesson, you should be able to:

- Define modules and packages and explain why projects use them.
- Import names using several forms and choose readable forms.
- Explain how `__name__` and the `if __name__ == "__main__":` guard work.
- Create and import from a simple package with `__init__.py`.
- Use absolute and relative imports in their appropriate contexts.
- Recognize and avoid circular imports and import-time side effects.
- Organize a small OOP project into focused files.
- Run a package module using `python -m`.

## 1. A module is a Python file

A **module** is usually a single `.py` file. It can contain functions, classes, constants, and module-level code.

Imagine a file named `fighters.py`:

```python
"""Fighter classes for the Battle Arena."""


class Fighter:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def take_damage(self, amount):
        self.health = max(0, self.health - amount)
```

Another file in the same folder can import it:

```python
import fighters

aria = fighters.Fighter("Aria", 100)
```

The name before the dot makes the source clear: `fighters.Fighter` came from the `fighters` module. This is a strong default when first organizing code.

## 2. Imports bind names

An `import` statement runs enough of another module to create it, then binds a name in the importing module. Different forms bind different names.

```python
import fighters
fighter = fighters.Fighter("Aria", 100)
```

```python
from fighters import Fighter
fighter = Fighter("Aria", 100)
```

```python
import fighters as arena_fighters
fighter = arena_fighters.Fighter("Aria", 100)
```

| Form                           | Name you use afterward       | Good use                                   |
| ------------------------------ | ---------------------------- | ------------------------------------------ |
| `import fighters`              | `fighters.Fighter`           | Clear origin; excellent default            |
| `from fighters import Fighter` | `Fighter`                    | A small number of central names            |
| `import fighters as af`        | `af.Fighter`                 | Avoiding a long or conflicting module name |
| `from fighters import *`       | unpredictable crowd of names | Usually avoid                              |

Avoid `from module import *`. Readers cannot easily tell where a name came from, and an import may overwrite another name already in the file. The arena has enough surprises already.

## 3. Importing functions, constants, and modules

Modules do not only hold classes.

```python
# rules.py
MAX_PARTY_SIZE = 4


def clamp(value, minimum, maximum):
    """Return value limited to the inclusive range."""
    return max(minimum, min(value, maximum))
```

```python
# game.py
from rules import MAX_PARTY_SIZE, clamp

health = clamp(120, 0, 100)
print(MAX_PARTY_SIZE)  # 4
print(health)          # 100
```

Use uppercase names for module-level constants by convention. Python does not prevent reassignment, but the capitalization warns readers: treat this as a shared setting, not ordinary temporary data.

## 4. A package is a directory of modules

A **package** organizes related modules in a directory. Traditionally, the directory contains `__init__.py`; in modern Python, namespace packages can work without it, but an explicit `__init__.py` is the clearest choice for beginner projects.

Here is a small project layout:

```text
battle_arena/
├── arena/
│   ├── __init__.py
│   ├── fighters.py
│   ├── items.py
│   ├── rules.py
│   └── game.py
└── run_arena.py
```

- `arena/` is the package.
- `fighters.py`, `items.py`, and `rules.py` are modules inside it.
- `__init__.py` marks/configures the package.
- `run_arena.py` is a top-level script that starts the program.

Inside `run_arena.py`, use an absolute import from the package:

```python
from arena.fighters import Fighter

aria = Fighter("Aria", 100)
```

The full import path is `arena.fighters.Fighter`.

## 5. What belongs in `__init__.py`?

`__init__.py` runs when Python imports the package. It may be empty, and often should start that way. It can also expose a small, convenient public package API.

```python
# arena/__init__.py
"""Tools for a small Battle Arena game."""

from .fighters import Fighter
from .items import Potion

__all__ = ["Fighter", "Potion"]
```

This allows:

```python
from arena import Fighter, Potion
```

The leading dot in `.fighters` means “from this package.” `__all__` states what should be exported when someone uses `from arena import *`; it does not make `import *` a preferred style, but it makes the package’s intended public names explicit.

Keep `__init__.py` light. Importing dozens of modules or running the game there can make a simple import slow, surprising, or circular.

## 6. Absolute imports and relative imports

**Absolute imports** start from the project’s package name:

```python
from arena.fighters import Fighter
from arena.items import Potion
```

**Relative imports** use dots to locate a module relative to the current package:

```python
# arena/game.py
from .fighters import Fighter
from .items import Potion
from .rules import clamp
```

```python
# arena/modes/tournament.py
from ..fighters import Fighter
```

One dot means the current package; two dots mean the parent package. Relative imports are useful *inside* a package because they remain correct if the top-level package is renamed. Absolute imports can be easier to search and understand in larger codebases.

### The direct-run trap

This command is likely to fail when `game.py` contains relative imports:

```text
python arena/game.py
```

Python does not know `game.py` is being used as part of its package in that form. Run it as a module from the project’s parent directory instead:

```text
python -m arena.game
```

The `-m` switch tells Python to locate and run a module by its import path. This is the usual solution, not a reason to scatter `sys.path` edits through your files.

## 7. `__name__`: imported or run directly?

Every module has a special `__name__` variable.

- When Python **imports** a file, `__name__` is its module name, such as `arena.game`.
- When Python **runs** a file/module as the program entry point, its `__name__` is `"__main__"`.

Use that distinction for demo code and command-line entry points:

```python
# arena/game.py
def main():
    """Run one short Battle Arena demonstration."""
    print("The arena gates open!")


if __name__ == "__main__":
    main()
```

Now these behave differently:

```text
python -m arena.game  # runs main()
```

```python
import arena.game     # defines main(), but does not run the demonstration
```

This **main guard** keeps imports quiet and reusable. A module should generally define tools when imported, not start a tournament, ask for keyboard input, or print a novel by surprise.

## 8. Package entry points with `__main__.py`

If a package contains a file named `__main__.py`, Python runs it when you use `python -m package_name`.

```text
battle_arena/
└── arena/
    ├── __init__.py
    ├── __main__.py
    ├── fighters.py
    └── game.py
```

```python
# arena/__main__.py
from .game import main

main()
```

From the parent directory, run:

```text
python -m arena
```

This gives the package a tidy command-line entry point. Keep `__main__.py` small; its job is usually to delegate to a `main()` function elsewhere.

## 9. Import-time behavior and caching

The first time Python imports a module in one running program, it executes the module’s top-level statements and stores the module in `sys.modules`. Later imports normally reuse the cached module rather than executing it again.

```python
# noisy.py
print("noisy.py was imported")
```

```python
import noisy  # prints once
import noisy  # usually does not print again in the same process
```

This is why import-time side effects are risky. Keep top-level module code to definitions, constants, and lightweight setup. Put actions in functions and call them explicitly.

Do not rely on import caching as an application feature; it is an implementation detail that can become confusing during tests, reloads, and interactive sessions.

## 10. Circular imports: when modules reach for each other

A **circular import** occurs when module A imports B while B imports A. Sometimes Python can finish the cycle, but often one module tries to access a name before the other has finished defining it.

```text
fighters.py  --> imports Potion from items.py
items.py     --> imports Fighter from fighters.py
```

This can produce an error like “cannot import name ... from partially initialized module.” The real problem is usually not Python being fussy; it is that responsibilities are tangled.

Better repairs:

1. Move shared data or functions into a third module, such as `rules.py` or `types.py` (avoid shadowing Python’s built-in `types` module in real projects).
2. Let one module depend on the other in one direction only.
3. Use a local import inside a function only when it truly breaks a dependency cycle and remains understandable.
4. Reconsider the design: perhaps two classes belong in the same module or communicate through a small interface.

Do not “fix” it by importing everything in every file. That produces a fog bank, not an architecture.

## 11. A practical Battle Arena package

Here is a small, runnable design. Create the files exactly as shown, then run `python -m arena` from the directory *containing* the `arena` folder.

```text
arena/
├── __init__.py
├── __main__.py
├── fighters.py
├── items.py
└── game.py
```

```python
# arena/fighters.py
class Fighter:
    """A combatant with a name and non-negative health."""

    def __init__(self, name, health):
        self.name = name
        self.health = max(0, health)

    def take_damage(self, amount):
        """Apply non-negative damage and return remaining health."""
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health = max(0, self.health - amount)
        return self.health

    def __str__(self):
        return f"{self.name}: {self.health} HP"
```

```python
# arena/items.py
class Potion:
    """A potion that restores a fixed amount of health."""

    def __init__(self, healing):
        self.healing = healing

    def use_on(self, fighter):
        """Restore health to fighter and return the new health value."""
        fighter.health += self.healing
        return fighter.health
```

```python
# arena/game.py
from .fighters import Fighter
from .items import Potion


def main():
    """Run one short arena scene."""
    aria = Fighter("Aria", 100)
    potion = Potion(20)

    aria.take_damage(35)
    print(aria)
    potion.use_on(aria)
    print(aria)
```

```python
# arena/__main__.py
from .game import main

main()
```

```python
# arena/__init__.py
"""The Battle Arena package."""

from .fighters import Fighter
from .items import Potion

__all__ = ["Fighter", "Potion"]
```

**Design note:** in this deliberately small example, `Potion.use_on()` changes `fighter.health` directly. In a larger project, `Fighter` may provide a validated `heal()` method (from Lesson 3) and the potion should call that public method instead. Package boundaries are a good reminder to respect each class’s API.

## 12. Finding modules: a gentle word about `sys.path`

When you run Python, it searches locations listed in `sys.path` to resolve imports. The current project location and installed packages are commonly included.

```python
import sys

for location in sys.path:
    print(location)
```

This explains why where you run `python` matters. Run a package from the directory that contains its top-level folder, or install the package properly when the project grows.

Avoid inserting arbitrary paths into `sys.path` inside application code as a first response to an import failure. First check:

- Is the folder/package layout correct?
- Are you running from the intended directory?
- Should you use `python -m package.module`?
- Did you accidentally give a file the same name as a standard library or installed module?

Files named `random.py`, `email.py`, or `dataclasses.py` can shadow Python’s real modules. Name your own modules clearly, such as `arena_rules.py`.

## 13. Python and C++ comparisons

| Idea                   | Python                                         | C++ (rough comparison)                    |
| ---------------------- | ---------------------------------------------- | ----------------------------------------- |
| One source unit        | module (`.py` file)                            | source/header translation units           |
| Group related code     | package (directory)                            | namespaces + directories/libraries        |
| Bring in a name        | `import` statement, runtime module loading     | `#include`, linking, `using` declarations |
| Entry point            | main guard / `__main__.py` / executable script | `int main()`                              |
| Public package surface | names exposed from modules/`__init__.py`       | headers and namespace API                 |
| Relative import        | `.module` / `..package`                        | no direct language equivalent             |
| Module caching         | `sys.modules` in one interpreter process       | different compilation/linking model       |

The analogy has limits: Python imports execute code at runtime, whereas C++ `#include` is preprocessor text inclusion followed by compilation. Think in terms of Python’s runtime module objects, not pasted source files.

## 14. Common mistakes and repairs

1. **Using `from module import *`.** Import explicit names or the module itself so origins stay visible.

2. **Running a package file directly when it contains relative imports.** Use `python -m package.module` from the parent directory.

3. **Putting the whole program in `__init__.py`.** Keep it for package setup and intentionally exposed names; use a `main()` entry point for actions.

4. **Printing, requesting input, or opening files at import time.** Put those actions behind a function and a main guard.

5. **Solving import errors by blindly editing `sys.path`.** Repair the layout, working directory, or import form first.

6. **Naming your module after a standard library module.** Avoid filenames such as `json.py`, `random.py`, or `typing.py`.

7. **Creating circular imports.** Move shared concepts to a third module or simplify responsibility boundaries.

8. **Making a package’s public API accidental.** Decide which names callers should import and document/expose those deliberately.

## 15. Exercises

### Exercise A — Split a script

Take a one-file arena program with a `Fighter` class and a `run_match()` function. Move the class to `fighters.py` and put `run_match()` in `game.py`. Choose an import form and explain why it is readable.

### Exercise B — Build a package

Create this folder layout:

```text
quest_tools/
├── __init__.py
├── tasks.py
└── rewards.py
```

Put a `Quest` class in `tasks.py` and a `GoldReward` class in `rewards.py`. Add a small `__init__.py` that lets a user write `from quest_tools import Quest, GoldReward`.

### Exercise C — Main guard experiment

Write a module that prints a message inside a `main()` function protected by a main guard. Run it directly, then import it from another file. What prints in each case, and why?

### Exercise D — Fix the circular import

`fighters.py` imports `Arena` from `arena.py`, and `arena.py` imports `Fighter` from `fighters.py`. Sketch a third module or a redesign that breaks the cycle. Which concepts should live where?

## 16. Mini-lab — Package the Battle Arena

Turn the following design into a real package named `battle_arena`:

```text
battle_arena/
├── __init__.py
├── __main__.py
├── combatants.py
├── equipment.py
└── match.py
```

Requirements:

- `combatants.py` defines a `Combatant` with `name`, `health`, `take_damage()`, and `is_defeated`.
- `equipment.py` defines a `HealingPotion` whose `use_on()` calls the combatant’s public healing behavior.
- `match.py` defines `run_demo()` and imports with relative imports.
- `__main__.py` calls `run_demo()` so `python -m battle_arena` works.
- `__init__.py` exposes only `Combatant` and `HealingPotion` as the convenient top-level public API.
- All modules must remain quiet when imported.

### One possible solution

```python
# battle_arena/combatants.py
class Combatant:
    """A fighter with bounded health."""

    def __init__(self, name, max_health):
        self.name = name
        self.max_health = max_health
        self.health = max_health

    def take_damage(self, amount):
        if amount < 0:
            raise ValueError("damage cannot be negative")
        self.health = max(0, self.health - amount)

    def heal(self, amount):
        if amount < 0:
            raise ValueError("healing cannot be negative")
        self.health = min(self.max_health, self.health + amount)

    @property
    def is_defeated(self):
        return self.health == 0
```

```python
# battle_arena/equipment.py
class HealingPotion:
    """A reusable example item that restores health."""

    def __init__(self, healing):
        self.healing = healing

    def use_on(self, combatant):
        """Heal combatant and return its current health."""
        combatant.heal(self.healing)
        return combatant.health
```

```python
# battle_arena/match.py
from .combatants import Combatant
from .equipment import HealingPotion


def run_demo():
    """Run one small Battle Arena scenario."""
    aria = Combatant("Aria", 100)
    potion = HealingPotion(20)

    aria.take_damage(35)
    print(f"After damage: {aria.health} HP")
    potion.use_on(aria)
    print(f"After potion: {aria.health} HP")
```

```python
# battle_arena/__init__.py
"""Public classes for the Battle Arena package."""

from .combatants import Combatant
from .equipment import HealingPotion

__all__ = ["Combatant", "HealingPotion"]
```

```python
# battle_arena/__main__.py
from .match import run_demo

run_demo()
```

From the directory containing `battle_arena`, run:

```text
python -m battle_arena
```

Extensions:

- Add an `enemies.py` module and decide which imports should point in which direction.
- Add a `rules.py` module for shared constants or helper functions.
- Add docstrings and use `help(battle_arena.Combatant)` from an interactive shell.
- Explain why `__main__.py` is better than placing `run_demo()` directly in `__init__.py`.

## 17. Review questions

1. What is the difference between a module and a package?
2. What names are bound by `import arena.fighters` versus `from arena.fighters import Fighter`?
3. Why is `from module import *` usually discouraged?
4. What does the main guard prevent when a module is imported?
5. When should you run `python -m package.module`?
6. What does `__init__.py` commonly do, and why should it stay light?
7. What causes a circular import problem?
8. Why can a file named `random.py` create confusing import errors?

## Exit ticket

Draw a four-file package for a small game feature. Label one package, two modules, and one `__main__.py` entry point. For each arrow between files, write the import path it would use.

---

**Final core arena:** modern Pythonic OOP—composition, abstract base classes, protocols, type hints, and choosing the simplest design that tells the truth.
