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
- Create a class that:
  - Reads in a MineSweeper layout from a file.
  - Randomly generates a MineSweeper layout.
  - Prints the layout to the console.
  
### Part 2
