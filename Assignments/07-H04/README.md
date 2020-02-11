## Homework 4 - Poker Game Design
#### Due: 02-18-2020 (Tuesday @ 11:00 a.m.)

### Overview



<iframe width="560" height="315" src="https://www.youtube.com/embed/UI6lqHOVHic" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step1" width="250">

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step2" width="250">

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

#### Requirements / Attributes

When writing "requirements" for our classes (and were are following a very **loose** design process) you should think in the following terms:  The ***\<thing\>*** should provide ***\<something\>*** so we can do ***\<this\>***. They don't ALL of to fit this exactly, but each "requirement" or "attribute" should at least have a ***\<subject\>*** => ***\<verb\>*** approach.

**Example:**

- A **card** (the \<**thing**\>) should know its **value** (the <**something**\>) so it can be **compared** (the \<**this**\>) to other cards.
- A deck (the \<thing\>) is composed of 1 - N cards. 
  - This is more of a relationship between card and deck so it doesn't necessarily fit the ***\<thing\>*** ***\<something\>*** ***\<this\>*** approach. 
- We could force it, but it's not necessary.
  - A deck (the \<thing\>) is composed of 1 - N cards (the <something\>) so it can provide a set of cards for a game (the \<this\>). Seems **forced** and reduncant.

#### Card

A truly abstract card would not have a suit and rank (those are playing cards and we may want magic cards :) ), but this is an issue we will tackle later.

- A card should know its value (some value not necessarily related to suit and rank) so it can be compared to other cards.
- A card (for poker) should know its suit and rank so it can be compared to other cards.
- A card should know how to print itself.
- A card should know how to be compared to other cards (`<`, `>`, `==`, `!=`) so we can quantify scores.

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
