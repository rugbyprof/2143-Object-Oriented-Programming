## Program 4 - Roll them Bones!

#### Due: 04-24-2023 (Monday @ 5:00 p.m.)

YES ... I KNOW THE DUE DATE IS MONDAY! Shut it...[^1].

![](../graphics/polyhedral_weapons.png)

### Helper Files

|  #  | Name                               | Description                                    |
| :-: | :--------------------------------- | :--------------------------------------------- |
|  1  | [dice.cpp](dice.hpp)               | [Example die/dice class](dice.hpp)             |
|  2  | [dice_tester.cpp](dice_tester.hpp) | [It tests the die/dice class](dice_tester.hpp) |

### Overview

The opening salvo we will be taking in the solving of the D&D battle royale program (and learning Python) is to convert the above two files into Python. Since `D&D` characters need to roll for many different things, we need to have a dice class handy. Could it be a simple function? Sure. But this dice class will do so much more! Most of it is implemented, but some is up to you.

The dice_tester file is just what it sounds like: a usage example for the dice class. In python you can combine both files into one without any issues. We have discussed the `__name__=='__main__'` concept alreay, but this program will put it to actual use. For those who have forgotten: The if `__name__=='__main__'` is a common concept used in Python programming to ensure that certain parts of a Python module are only executed when the module is run directly as the main program, and not when it is imported by another module.

**Filename:** dice.py

```python

class Die:
    # implement everything here
    pass

class Dice:
    pass

if __name__ == '__main__':
    """This code gets executed if you run this file directly: python dice.py
       It does not get executed if you import this file
       So do lots of testing below!
    """
    D1 = Dice('5.d.20')
    D2 = Dice('4.d.8')

```

**Filename:** main.py

All the tests in `dice.py` do not get run when you import the class(s)
into another file. However, the local `__main__` block will run if you call
this file like: `python main.py`

```python
from dice import Die
from dice import Dice

if __name__ == '__main__':

    d6 = Die(6)
    d4_8 = Dice('4.d.8')


```

### Requirements

- Implement the `Die` and `Dice` classes in Python, using the c++ code as a template.
- Implement the `max` and `avg` roll methods that are not implemented as of yet.
- Place both of your class implementations in a file called: `Dice.py`
- Use the `__str__` method as a replacement for overloading ostream for both the `Die` and `Dice` classes.
- Use the `__name__ == '__main__'`: syntax and write tests to ensure both of your classes work inside the `Dice.py` file.
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
