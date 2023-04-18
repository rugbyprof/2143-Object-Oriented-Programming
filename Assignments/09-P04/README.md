## Program 4 - Roll them Bones!

#### Due: 04-24-2023 (Monday @ 5:00 p.m.)

YES ... I KNOW THE DUE DATE IS MONDAY! Shut it...[^1].

![](../graphics/polyhedral_dice2.png)

### Helper Files

|  #  | Name                               | Description                                    |
| :-: | :--------------------------------- | :--------------------------------------------- |
|  1  | [dice.cpp](dice.hpp)               | [Example die/dice class](dice.hpp)             |
|  2  | [dice_tester.cpp](dice_tester.hpp) | [It tests the die/dice class](dice_tester.hpp) |

### Overview

The opening salvo we will be taking in the solving of the D&D battle royale program (and learning Python) is to convert the above two files into Python. Since `D&D` characters need to roll for many different things, we need to have a dice class handy. Could it be a simple function? Sure. But this dice class will do so much more! Most of it is implemented, but some is up to you.

The dice_tester file is just what it sounds like: a usage example for the dice class. In python you can combine both files into one with any issue. Look below:

#### Easy testing syntax

I will discuss more in class.

```python

class Die:
    # implement everything here
    pass

if __name__ == '__main__':
    # test your class here in the same file!
    pass

```

### Requirements

- Implement the `Die` and `Dice` classes in Python, using the c++ code as a template.
- Implement the `max` and `avg` roll methods that are not implemented as of yet.
- Place your implementation in a file called: `Dice.py`
- Use the `__str__` method as a replacement for overloading ostream for both the `Die` and `Dice` classes.
- Use the `__name__ == '__main__'`: syntax and write tests to ensure both your classes work inside the `Dice.py` file.
- Create a `main.py` file and import your classes, to also ensure they work :)

#### main.py

```python
from dice import Dice

# run the same tests or different ones...
```

### Deliverables

- Create a folder in your assignments folder called `P04`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.

```
2143
P04
Name
```

- Include your python file(s) inside the `P04` folder: `Dice.py` and `main.py`

---

[^1]: But shut it in a really nice way :)
