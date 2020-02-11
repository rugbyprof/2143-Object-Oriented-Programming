## Homework 4 - Poker Game Design
#### Due: 02-18-2020 (Tuesday @ 11:00 a.m.)

### Overview

This lesson is a lot like the last poker assignment except we will be formalizing your poker game designs using `class design` methods. Below is a video from lucidcharts that explains it very well. Better than I could :) 

[![Class Diagram Video](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_vid_250.png)](https://www.youtube.com/embed/UI6lqHOVHic) 

You can use lucidcharts to do your diagrams, or you can use [https://draw.io](draw.io) to make your diagrams. Lucidchart is free to some extent, but it makes you create an account where  [https://draw.io](draw.io) does not. 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step1" width="250">

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step2" width="250">

### Poker Classes 

Below is a set of poker classes as I see them, convert them to Class Diagrams 

#### Requirements / Attributes

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

#### Hand

- A hand is composed of 1 - N cards 
- A hand can add card(s)
- A hand can remove card(s)
- A hand can order cards
- A hand can shuffle cards
- A hand can display (print) its cards
- A hand can calculate its value 
- A hand can be compared to other hands

----

#### Player

- A player has a unique identifier 
- A player has a bank of units (money)  (Bank could be its own class)
- A player can add to its bank
- A player can remove from its bank
- A player has a `hand`

----

#### Poker Game

- A game is composed of 2-N players
- A game keeps track of a score for each player
- A game determines if someone has won the game
- A game can be started
- A game can be terminated
- A game can print a current summary of game (who has what score, who is in what place)

----



### Example Document

You would replace the example lables with the poker game labels:

```
### Person

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.person" width="200">

### Street

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.street" width="200">

### Student

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.student" width="200">

### Professor

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.professor" width="200">

### Diagram

<img src="draw.io.wholething" width="400">
```
Would result in:

### Person

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.person.png" width="150">

### Street

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.street.png" width="150">

### Student

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.student.png" width="150">

### Professor

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.professor.png" width="150">

### Diagram

<img src="draw.io.wholething.png" width="400">


### Deliverables

- Create a folder called `H04` in your `Assignments` folder. 
- Add a `README.md` file in your `H04` folder with all of your class designs listed in an orderly fashion.
- Your document should be written in markdown. 
- Don't forget to include your Name and essentials at the top of the document.
- No hand written anything will be graded.
- Bring a print out of your readme to class on the due date.
- There is an extension called `Markdown PDF` that will convert markdown files to PDF's to assist in printing.
- If your not using VSCode then you can replace `github` with `gitprint` in the url of your readme and print it that way.
- Don't forget your banner (cover page).

```
H04
2143
LASTNAME
```
