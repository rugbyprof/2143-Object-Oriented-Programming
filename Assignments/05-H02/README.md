## Homework 2 - Poker Game Design
#### Due: 02-04-2020 (Tuesday @ 11:00 a.m.)

### Overview

When designing classes with the OOP mindset, you should follow a few principles to keep you out of trouble. I will list a few to help you when designing your poker game. 

#### Dry (Don't Repeat Yourself)

- Don't write duplicate code.
- A class should do its own thing. If two classes are doing the same thing, to the same data, maybe it should be its own class entirely.
- Similarly, if you have a block of code in more than two places consider making it a separate method.
  
#### Single Responsibility Principle (SRP)

- A class should be written to handle **one** defined thing, and handle it well. 
- The definition of "one" is the question here.
- Think along the lines of `decoupling`. For example when **ClassA** depends heavily on **ClassB**, the chances of **ClassA** being affected when **ClassB** is changed are high. We don't want this to happen.


#### Favor Composition over Inheritance

- We haven't discussed inheritance yet, but still here are a couple of points to think about.
- To favor composition over inheritance is a design principle that gives the design higher flexibility. 
- It is more natural to build classes out of various separate components rather than trying to find commonality between them in order to create an inheritance hierarchy.

### Poker Classes 

 We want to create a set of classes to implement a poker game. But I want you to along the lines of: "Can my classes be used for other games as well?" The only class that should end up highly coupled with the game "poker" is a `poker` class! Even a `game` class shouldn't think "poker only". 

 Here are a list of classes we might want to implement. We don't have to be limited to just these.

 - Possible Classes:
   - Card
   - Deck
   - Hand
   - Player
   - Game
   - Poker

#### Card

A truly abstract card would not have a suit and rank (those are playing cards and we may want magic cards :) ), but this is an issue we will tackle later.

- A card should know its value (some value not necessarily related to suit and rank).
- A card (for poker) should know its suit and rank.
- A card should know how to print itself.
- A card should know how to be compared to other cards (`<`, `>`, `==`, `!=`).

#### Deck

Again, if we don't think of playing cards, a deck should just be able to hold any type of card(s). Its ok for now to stick with "poker" like thinking, just keep in mind for future a more "generic" approach.

- A deck is composed of 1 - N cards.
- A deck can deal a card.
- A deck can shuffle cards.
- A deck can get a card back and place it in the deck.
- A deck can run out of cards.

----

Using `Card` and `Deck` as examples, come up with functionality (using similar wording) for the classes below. 

#### Hand

#### Player

#### Game

#### Poker


### Deliverables

- Create a folder called `H02` in your `Assignments` folder. 
- Add a `README.md` file in your `H02` folder with all of your class designs listed in an orderly fashion.
- Your document should be written in markdown.
- Bring a print out of your readme to class on the due date.
- There is an extension called `Markdown PDF` that will convert markdown files to PDF's to assist in printing.
- Don't forget your banner (cover page).

```
H02
2143
LASTNAME
```