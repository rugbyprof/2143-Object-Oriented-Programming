# Game of Life 
#### Due: TBD

## Overview

The Game of Life was invented by John Conway (as you might have gathered).  It consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply.  The "game" is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input from humans. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are directly horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbors dies, as if caused by under-population.
2. Any live cell with more than three live neighbors dies, as if by overcrowding.
3. Any live cell with two or three live neighbors lives on to the next generation.
4. Any dead cell with exactly three live neighbors becomes a live cell.

Your implementation will not be an infinite two-dimensional orthogonal grid of square cells, but a finite dynamically allocated 2-dimensional array of `golCell`'s (game of life cells).  A `golCell` contains:

- isAlive (bool [true,false])
- neighborCount (int # of neighbors)

In class we discussed how to get from our current state to the next state by adding two matrices together, however we are going to use a different method to go from one generation to the next. 

- If you look below, the far left is the current "state" of the game, where the two values are: `isAlive` and `neighborCount` respectively. 
- You can traverse the game board and count each cells neighbors storing its neighbor-count within the cell. 
- Once each cell has its neighbors counted, you can apply the rules (killing 2 and spawning 2 in this example) and also reset the neighbor counts to zero.


|  State | Calculate Transition | Apply Transition | 
|:---------------------:|:---------------------:|:---------------------:|
| <img src="https://d3vv6lp55qjaqc.cloudfront.net/items/3q2C2c2d2H1n1W1L1426/Image%202018-10-02%20at%206.43.39%20PM.png" width="250"> | <img src="https://d3vv6lp55qjaqc.cloudfront.net/items/022V2T3i2p2V2p0v3a3u/Image%202018-10-02%20at%206.44.26%20PM.png" width="250"> | <img src="https://cl.ly/f106f3413fb2/Image%2525202018-10-02%252520at%2525206.55.48%252520PM.png" width="250"> |


### Initializing the Game

How do we start our zero person game? We need to have an initial state (generation 0) for our game to be played. We are going to do this by reading in a file that will be formatted like below and named “gen_zero.txt”. The first two numbers are rows and columns respectively.

```
 8 10
 0000000000
 0000000100
 0000011000
 0000110000
 0000100000
 0001000000
 0000000000
 0000000000
```


## Data Elements

### Data Structures

### golCell

```cpp
struct golCell {
  bool isAlive;
  int neighborCount;
};
```

### gameBoard

```cpp

  golCell** gameBoard;

  gameBoard = new golCell* [rows];
  
  // get memory for each row
  for (int i = 0; i < rows; i++)
      gameBoard[i] = new golCell [cols];

```



### Data Elements
|   Member         |     Description   |
|:---------------|:--------------------|
| int FrameCount  | Total times game loop did loop |
| int FrameRate   | Allow user to slow down animation |
| int Rows        | Number of rows in world |
| int Cols        |  Number of cols in world | 
| golCell** gameBoard  | 2D game world of `golCell`s |
  

## Methods

| Type |   Method         |     Description   |
|:-----|:----------|:--------------------|
| Primary |    |      |
| | printWorld  | Prints world to game window |
| | goNextGen        | Transitions from current to next generation |
| Helper |    |      |
| | countNeighbors   | Counts the neighbors for a given cell |
| | onWorld       | determines if a cell is within the matrix| 

