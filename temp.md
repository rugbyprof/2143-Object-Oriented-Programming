# P02 - Poker

### Diya Patel

## Description

This project implements a simplified command-line **Poker game** using C++. The program creates a standard 52-card deck, shuffles the cards, deals hands to the players, and determines the contents of each player's hand.

The project demonstrates several object-oriented programming concepts, including:

- Classes and objects
- Encapsulation
- Composition
- Constructors
- Vectors and other STL containers
- Enumerations
- Randomization
- Basic card-hand algorithms

A card is internally represented using an integer value from `0-51`. The card's suit and rank can be calculated using integer division and modulo:

```cpp
suit = card / 13;
rank = card % 13;
```

The program uses `Card`, `Deck`, and `Hand` classes to organize the game.

## Class Structure

```text
Poker Game
│
├── Card
│   ├── value
│   ├── getRank()
│   ├── getSuit()
│   └── toString()
│
├── Deck
│   ├── vector<Card>
│   ├── shuffle()
│   └── deal()
│
└── Hand
    ├── vector<Card>
    ├── addCard()
    ├── show()
    └── evaluate()
```

A `Deck` contains `Card` objects, and a `Hand` also contains `Card` objects. This demonstrates **composition** because a deck *has cards* and a hand *has cards*.

## Files

| # | File | Description |
| :---: | --- | --- |
| 1 | `main.cpp` | Main driver that creates the deck, deals cards, and runs the game. |
| 2 | `Card.hpp` | Declaration of the `Card` class. |
| 3 | `Card.cpp` | Implementation of the `Card` class. |
| 4 | `Deck.hpp` | Declaration of the `Deck` class. |
| 5 | `Deck.cpp` | Creates, stores, shuffles, and deals cards. |
| 6 | `Hand.hpp` | Declaration of the `Hand` class. |
| 7 | `Hand.cpp` | Stores and evaluates a player's poker hand. |

## Building the Program

The program can be compiled using `g++`:

```bash
g++ main.cpp Card.cpp Deck.cpp Hand.cpp -o poker
```

Then run:

```bash
./poker
```

## Example Output

```text
Creating deck...
Shuffling deck...

Player 1:
Ace of Spades
Ace of Hearts
Ten of Clubs
Seven of Diamonds
Three of Hearts

Player 2:
King of Hearts
Queen of Hearts
Jack of Hearts
Four of Clubs
Two of Spades

Player 1: One Pair
Player 2: High Card

Winner: Player 1
```

## Instructions

1. Create a standard 52-card deck.
2. Shuffle the deck before dealing.
3. Deal five cards to each player.
4. Display each player's hand.
5. Determine the type of poker hand held by each player.
6. Compare the hands and determine the winner.

At minimum, the program should recognize:

- High Card
- One Pair
- Two Pair
- Three of a Kind
- Straight
- Flush
- Full House
- Four of a Kind
- Straight Flush

## Example Usage

```bash
./poker
```

Optional command-line parameters may be used to specify the number of players:

```bash
./poker 4
```

Example:

```text
$ ./poker 3

Players: 3
Cards per player: 5

Shuffling...

Player 1:  AS  7H  7C  4D  2S
Player 2:  KH  QH  JC  10D  3C
Player 3:  9S  9D  9H  5C  2D

Player 1: One Pair
Player 2: High Card
Player 3: Three of a Kind

Winner: Player 3
```

## Notes

The program does not need to simulate betting, chips, blinds, folding, or multiple betting rounds. The primary goal of the project is to use a familiar card game to practice **class design, composition, STL containers, and object interaction**.

The basic relationship between the classes should remain simple:

```text
Deck ───── has many ─────► Card

Hand ───── has many ─────► Card
```