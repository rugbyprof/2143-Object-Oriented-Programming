## Program 3B - BolNiverse Fight Club
#### Due: 11-12-2021 (Friday @ 12:00 p.m.)


### Overview
This assignment is being rolled back from our initial take on the BolNiverse Fight Club. In this version I will simplify things, but still require the use of dynamic runtime polymorphism. An input file will choose who "battles". The input file will challenge a particular type of character, you must use that type of character to "battle". Whichever side goes to zero hit points first loses and that character is removed from the game. There are a few other odd rules that I will list here:

- Attacking force can be any size from a few to thousands.
- Defending force can have 1 of each character type for every 100 attackers.
- Attacking force can heal only during battle.
- Defending force can heal at any time.
- Any character that reaches zero hit points expires and is removed from the game. 
- Defending force can swap out characters of the same type in the middle of any battle when it is their turn to attack. This will be used in place of an attack.

You will still have a base character that gets extended by different variations. Each variation will have slightly different abilities that will be explained more a little later. The attacking characters will have the following:

- `Hit Points` (life points) : How many points until expiration
- `Attack Strength` : Points damage against who they are fighting. Values similar to the following:
  - d10 = roll a 10 sided die and use that value
  - 2d8 = roll 2 8 sided die and add them together
  - b3d10 = best of 3 10 sided die rolls
  - 2d6+x = 2 6 sided die rolls + some constant value
- `Recovery speed` : regains x number of hit points per round

All the attackers will be read from an input file into a queue of some sort. When an attacker has lost all of its hit points, it is removed from the queue. The game ends when either the attacker queue is empty, or the BolniVerse fighters queue is empty.
  
<!-- ### UML
- [UML Video on YouTube](https://www.youtube.com/embed/UI6lqHOVHic)
- [UML Resource](../../Resources/04-UML/README.md) -->

### Input File

The input file will contain one attacker per line with the same data as described above, but also with the type of class they are attacking. 

challengeClass hitPoints AttackStrength recoverySpeed

```
warrior 13 d10 1
wizard 11 2d6 2
...
```


### Classes

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
- Weapon
  - Sword d10
  - Bow d8
  - Magic 2d6
  - Fire 2d6
- ~~Shield~~
  - ~~physical~~
  - ~~magical~~
- Dice
  - sides


### Requirements

Write a program that creates the appropriate number of characters based on the input file, and proceeds to manage battles between attackers and defenders choosing the appropriate character to fight based on the above rules. You will use run time polymorphism to switch between attacking characters and defending characters. This means you should only have two pointers to manage battles. Attackers, defenders, and expired will be in separate queues based on status. When the attacking or defending queues become empty, the battle is over and the side with characters remaining wins.

You should printout running commentary to stdout describing in a minimal fashion what is happening in your battle. For example:

```
Attacker challenges warrior
Attacker: 12hp Warrior 15hp
Warrior strikes and takes 5 hp
Attacker: 7hp Warrior 15hp
Attacker strikes and misses
Attacker: 7hp Warrior 15hp
...
```


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
