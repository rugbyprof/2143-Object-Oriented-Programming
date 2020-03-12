## Playing Cards - Game of WAR!
#### Due:  03-24-2020 (Teusday @ 12:30 p.m.)

## Game of War!

- The goal is to be the first player to win all 52 cards

#### THE DEAL

- The deck is divided evenly, with each player receiving 26 cards, dealt one at a time, face down. 

#### THE PLAY

- Each player turns up a card at the same time and the player with the higher card takes both cards and puts them, face down, on the bottom of his/her stack.

If the cards are the same rank, it is **War**. 

### WAR

- Each player places 3 cards face down and the fourth card face up. 
- The player with the higher cards takes both piles (8 cards). 
- If the turned-up cards are again the same rank, each player repeats the WAR by each placing 3 more cards face down and a fourth face up. Winner keeps ALL the cards played. 

### HOW TO KEEP SCORE

- The game ends when one player has won all the cards.


Using your new `GameCard` class, create a `WarGame` class that uses all of the functionality of our Card, Deck, and Hand class to implement the game of war. 

- Your game shouldn't get all wrapped in in player names and the such, for now simply use "player 1" and "player 2" or randomly assign names to them.
- Your output should look like:

**Game Start**
```
  Cards:26    Cards:26
┌──────────┐┌──────────┐
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
│░░░░░░░░░░││░░░░░░░░░░│
└──────────┘└──────────┘
  Player 1   Player 2
```

**First Deal A**
```
 Cards: 26    Cards: 26
┌──────────┐┌──────────┐
│{8}       ││{A}       │
│          ││          │
│          ││          │
│    {8}   ││    {A}   │
│          ││          │
│          ││          │
│       {8}││      {A} │
└──────────┘└──────────┘
 Player 1     Player 2
```

**First Deal B**
```
 Cards: 26    Cards: 26
┌──────────┐┌──────────┐
│{8}       ││{A}       │
│          ││          │
│          ││          │
│    {8}   ││    {A}   │
│          ││          │
│          ││          │
│       {8}││      {A} │
└──────────┘└──────────┘
 Player 1     Player 2
               Winner!
```

**Second Deal**
```
 Cards: 25    Cards: 27
┌──────────┐┌──────────┐
│{3}       ││{8}       │
│          ││          │
│          ││          │
│    {3}   ││    {8}   │
│          ││          │
│          ││          │
│       {3}││      {8} │
└──────────┘└──────────┘
 Player 1     Player 2
              
```
- You can print winner, or change the winner color, whatever looks good.
- Notice the card counts above each player. Thats important.

**WAR??**

- You decide how it should look, but it should be recognizable and clear to see whats happening.

- Keep clearing the screen, and repeating until one of the players has won all cards.

- I will add more details with a round of questions on Thursday the 12th.

### Deliverables

- Add a folder to Assignments called `P01`.
- Put your edited source code in this folder. 
- Your game driver should be in `main.cpp`.
- Include any `.h` or `.cpp` or `.hpp` files you used.
- Make sure you [COMMENT](../../Resources/01-Comments/README.md) your code!
- Bring a printed copy of your code to class on Teusday after spring break.
- Don't forget your [BANNER](../../Resources/02-Banner/README.md) (cover page).

```
P01
2143
LASTNAME
```


