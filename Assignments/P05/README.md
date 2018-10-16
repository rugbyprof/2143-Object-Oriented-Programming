## Program 5 - Minesweeper
### Due: TBD



### Incremental Programming

- Start small
- Compile frequently
- Use functions / methods whenever possible
  - If something is needed more than once, it should be in a function. The `onWorld` function from last program is a prime example. 
  - If something is needed and needs quite a few lines of code to solve, making `main` harder to read: function. Reading in a file to some data structure is a good example.
 

### Rules
- https://zyxyvy.wordpress.com/2012/08/11/the-rules-of-minesweeper/

### SFML Help
- https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php
- https://www.sfml-dev.org/tutorials/2.5/window-events.php

## How I Would Approach the Problem

### Part 1

- Ignore any SFML logic initially
- Create a class / struct that:
  - Defines a MineSweeper cell with:
    - Its state (covered, a number, a bomb, flag, etc)
    - Neighboring bombs (int)
    - Uncovered (boolean)
    - ??
    - We can add more if we find a need.
- Create a class that:
  - Reads in a MineSweeper layout from a file.
  - Randomly generates a MineSweeper layout.
  - Prints the layout to the console.
  
### Part 2

- We now should have a class that holds a MineSweeper game, but has ZERO game logic.
- We are still not at the point where we should incorporate SFML.
- But what are we missing? Lets look at the rules <sup>[source](https://zyxyvy.wordpress.com/2012/08/11/the-rules-of-minesweeper/)</sup>:
    - The game of minesweeper begins upon the opening of the first square the player clicks open, which starts the timer.
    - The grid of mines for a board is pre-generated before the start of the game. The first square clicked never contains a mine. If it did contain a mine in the board pre-generation, the mine is moved to the upper-left hand corner of the board, and if that was a mine, the next square over to the right, and so on.
    - When a square is successfully opened without containing a mine, it shows a number. The number indicates the number of mines that exist in the eight squares touching the square the number was in.
    - If the number would have been a 0, the number 0 is not shown, and all squares touching that square are opened as well.
    - When a square is right-clicked, a flag appears over the square. Right-clicking is intended for marking a square as a mine. Right-click again to remove the flag. Each time a square is flagged, the number of “mines left” display is decremented.
    - The number of mines in a board is pre-determined. A Beginner board has 10 mines on an 8-by-8 board, an Intermediate board has 40 mines on a 16-by-16 board, and an Expert board has 99 mines on a 16-by-30 board. 
- From the rules I see we need a couple of things to keep track of:
    - A timer that displays seconds played.
    - Total Bombs in the game.
    - Marked bombs (if succesfully `if (marked_bombs_count == total_bombs){you win}`).
    - Mines left (for display purposes. `total-bombs - flags = bombs_left`).
    - A game finished check (all bombs successfully marked).
    
### Part 3 
    
    - Mouse Click capture (SFML disregard)
    - Drawing sprites (SFML disregard)
    - Handling a mouse click (AHA!)
    






