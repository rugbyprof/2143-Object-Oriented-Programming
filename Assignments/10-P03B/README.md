## Program 3B - BolNiverse Fight Club
#### Due: 11-15-2021 (Friday @ 12:00 p.m.)


## Overview
This assignment is being rolled back from our initial take on the `BolNiverse` Fight Club. In this version I will simplify things but still require the use of **dynamic runtime polymorphism**. Any `BolNiverse` defender currently fighting will be ruled by **Captain Base**, who uses his magical ability to "take over" other characters during a battle with the "attackers". So from now when you see **`Attacker`** you know they are the bad people and are attacking `BolNiverse` and when you see **`Defender`** they are the good people defending BolNiverse. Attackers are generated from a file. Defenders are created depending on how many attackers there are. An example input file can be seen below:

```
warrior 
wizard 
wizard
archer
warrior
dragonborn
elf 
elf
...
```

Wait you say! Where are the stats for each attacker? Lets talk about character generation. But first remember we need dice to help genrate our characters!

## Class Dice

Example Die class [HERE](dice.hpp)

|D4 | D6 | D8 | D10 | D12 | D20 |
|:----:|:----:|:----:|:----:|:----:|:----:|
|<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/4sided.png" width="50"> |<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/6sided.png" width="50"> |<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/8sided.png" width="50"> |<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/10sided.png" width="50"> | <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/12sided.png" width="50"> | <img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/20sided.png" width="50"> |
|4 sides | 6 sides | 8 sides | 10 sides | 12 sides | 20 sides |
|Values 1-4 | Values 1-6 |Values 1-8| Values 1-10| Values 1-12| Values 1-20|

Each weapon or character or anything that has stats, will have 1 or more of these die assigned to them. The following are some possible uses of the dice.

- 1.d.10 :
  - roll a 10 sided die and use the value rolled 
  - possible outcomes 1-10 
- 2.d.8:
  - roll two 8 sided die and add the results of both die together
  - possible outcomes 2-16
  - Increases odds of a decent roll
- a.2.d.12:
  - average of two 12 sided dice rolls
  - possible outcomes 1-12
  - if `double` data type used, then obviously a value such as 10.3 could happen 
  - Not as good as best of, but still improves chances of good die roll
- b.3.d.10:
  - best of three 10 sided die rolls
  - possible outcomes 1-10
  - Increases odds of a decent roll
- 2.d.6 + x:
  - Two 6 sided die rolls + some constant value
  - possible outcomes are x + (2-12)
  - Multiple dice increases odds of decent roll
  - Constant x places a minimum on the outcome



It has two classes `Die` and `Dice`. Dice uses 1-N instances of the Die class in order to simulate the rolling of multiple dice. You will need to modify the `Dice` class to allow someone to specify the type, the number, and possibly adding a constant so you can simulate a roll as described above. 

## Character Generation 

Each character will be generated as a descendant of `BaseFighter`. Base fighter has the following attributes:
- Name : string
- HP : Health points (random from 3 - 8)
- RR : Regeneration Rate (random from .15 - .75)
- PW : Primary Weapon = Fists and Feet
- ~~SW : Secondary Weapon = Fists and Feet~~

However a fighter also needs a weapon. So before we can complete a fighter base class, we need to create a weapon class.

### Class Weapon

Example Weapon class [HERE](weapon.hpp)

A weapon has stats of its own. These stats will be generated using a config file (discussed later or in class), but for now when assigning a weapon to a character, it needs to have its own base attack value and it shouldn't be exactly the same for every weapon of the same type. So below I am creating ranges of base attack values to give to each weapon type. I am pulling these out of thin air, so we may change these (as a class) over the next week or so.


- Fists & Feet have a base attack of:
  - 1.d.4 OR 1.d.6
- Sword 
  - 1.d.12 OR 2.d.6 OR 3.d.4
- Bow 
  - 1.d.8 OR 2.d.4 OR 1.d.10 
- ~~Dagger~~
- Magic Spell
  - 1.d.20 OR 2.d.10 OR 3.d.6 OR 5.d.4
- Magic Weapon
  - Add 1.d.4 OR 1.d.6 to primary weapon
- Fire Weapon
  -  Add 1.d.6 OR 1.d.8 to primary weapon


### BaseFighter subClasses

Example Fighter class [HERE](fighter.hpp)

- Base Character
  - Warrior: 
    - Uses a sword as a weapon
  - Wizard: 
    - Uses magic as a weapon
  - Archer:
    - Uses a bow as a weapon
  - Elf: 
    - Uses magic + a sword as their weapons
  - DragonBorn:
    - Uses magic + fire as a weapon


## Rules
There are a few other odd rules that I will list here:

- Attacking force can be any size from a few to thousands.
- Defending force can have 1 of each character type for every 100 attackers.
- Attacking force can heal only during battle.
- Defending force can heal at any time.
- Any character that reaches zero hit points expires and is removed from the game. 
- Defending force can swap out characters of the same type in the middle of any battle when it is their turn to attack. This will be used in place of an attack.

You will still have a base character that gets extended by different variations. Each variation will have slightly different abilities that will be explained more a little later. The attacking characters will have the following:

- `Hit Points` (life points) : How many points until expiration
- `Attack Strength` : Points damage against who they are fighting. Values similar to the following:
- `Recovery speed` : regains x number of hit points per round

All the attackers will be read from an input file into a queue of some sort. When an attacker has lost all of its hit points, it is removed from the queue. The game ends when either the attacker queue is empty, or the BolniVerse fighters queue is empty.
  
<!-- ### UML
- [UML Video on YouTube](https://www.youtube.com/embed/UI6lqHOVHic)
- [UML Resource](../../Resources/04-UML/README.md) -->


### Requirements

Write a program that creates the appropriate number of characters based on the input file, and proceeds to manage battles between attackers and defenders choosing the appropriate character to fight based on the above rules. You will use run time polymorphism to switch between attacking characters and defending characters. This means you should only have two pointers to manage battles. Attackers, defenders, and expired will be in separate queues based on status. When the attacking or defending queues become empty, the battle is over and the side with characters remaining wins.

You should printout running commentary to stdout describing in a minimal fashion what is happening in your battle. For example:

```
warrior 
wizard 
wizard
archer
warrior
dragonborn
elf 
elf
...
```

**Don't print out all of the  "running commentary" to be turned in. But you should only turn in a summary of what happened!**


### Deliverables

- Create a folder in your assignments folder called `P03B`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.
  - Make sure your banner is readable and does NOT have blank lines between every other row.

```
2143 
P03B
Name
```

- Print out your source code. Make sure it's **[commented](../../Resources/01-Comments/README.md)**.
- Print out your output file.
- Put your assignment on the lecture podium at the beginning of class.
- Staple everything in this order:
  - **1)** Banner (on top)
  - **2)** Source code (middle)
  - **3)** Output (bottom)
- Any hand writing on your assignment is reduction in 1 letter grade.
- Failure to follow instructions is a reduction in 1 letter grade.
- Unreadable banner is a reduction in 1 letter grade.
