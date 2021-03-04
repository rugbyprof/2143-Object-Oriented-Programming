## Program 01 - Game: Game
#### Due: 2-23-2021 (Tuesday @ 9:30 a.m.)

### Overview:

Follow instructions for this first program without adding functionality or personalized touches for now. We will be organizing our code and applying some OOP techniques on subsequent assignments. So, keep it bare bones for now. 

Using the code snippets for help [here](../../Resources/09-SFML/README.md), and the [SFML documention](https://www.sfml-dev.org/learn.php) write a program (game) that does the following:

### Configurable
  - Configurable means that there is an ability to "change" or "customize" an item. 
  - In the context of this program, I want you to have an **overloaded constructor** that allows an object to be "configured" or "customized". 
  - In the context of the next program(s) you will implement the use of a configuration file, and command line parameters. I will explain both in class.

#### Player
  - Is a circle shape 
    - But could be another shape or sprite (later).
  - Size is configurable
  - Color is configurable
  - Starting location also configurable
    - However for this "game" player starts at middle left of screen. 
  - Moves up and down (1 direction only for now) using up and down arrows (additional keys can be set to do same thing).
    - A player can however possibly move other directions as well (in later installments).

#### Debris
  - Is a rectangle shape
    - But could be another shape or sprite (later).
  - Size is configurable
  - Color is configurable
  - Starting location also configurable
  - Moves them from right to left starting at a random `Y` location just off right side of screen.
  - The size should be random between some `min` and `max` value.
  - The speed should also be random set between some `min` and `max` value.
  - The frequency and speed should slowly increase over time. Enough that after ONE minute of play, it should be impossible 
  
#### Scoring
  - When a `Player` collides with a `Debris` item the score is negatively effected.
  - When a piece of `Debris` leaves game screen (on the left), score is positively effected.
  - We will add more logic to the game next time.

#### Text Output:
  - Score gets displayed somewhere on the screen (one of the corners).
  - Font is configurable.
  - Location is configurable.
  - Color is configurable.
  - Size is configurable.



### Deliverables

- Create a folder in your assignments folder called `P01`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.

```
2143 
P01
Name
```

- Print out your source code. Make sure it's **[commented](../../Resources/01-Comments/README.md)**.
- Take a screen shot of your program and place it behind the source code.
- Put your assignment on the front desk at the beginning of class.
- Staple everything in this order:
  - **1)** Banner (on top)
  - **2)** Source code (middle)
  - **3)** Screen Shot (bottom)
  

