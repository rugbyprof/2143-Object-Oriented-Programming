## Program 5 - Minesweeper
### Due: TBD

### Helper Code 
- https://repl.it/@rugbyprof/MineSweeper1

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
    - This method would randomly put bombs in MineSweeper cells. 
    - We would then calculate the neighbor numbers after we add the bombs.
  - Prints the layout to the console.
  - Below could be a minimal class definition:
  
```cpp
/**
*
*/
class MineCell{
private:
  sf::Sprite sprite;
  int NearbyBombs;
  bool Visited;
  bool isBomb;
public:
  MineCell(){
    NearbyBombs = 0;
    Visited = 0;
    isBomb = 0;
  }
  
  // method to set sprite
  // method to set NearbyBombs
  // method to set Visited
  // method to set isBomb
  // method to get NearbyBombs
  // method to get Visited
  // method to get isBomb  
};


class MineSweeper {
private:
  MineCell **World;
  int rows;
  int cols;
  bool onWorld(int r,int c); // private method to check if some cell is in bounds
  void calculateNeighbors(); // calculates NearbyBombs called after randomlyPopulate is called
public:
  void readFromFile(string file_name); // reads MineSweeper data from file and loads 2D array
  void randomlyPopulate(int num_bombs); // random loads MineSweeper with num_bombs.
  void printMineSweeper(); // print World data to console 
};
```
  
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

- It would be real easy to want to add SFML here, but lets hold off. There are plenty of methods we can still write and make sure we put ourself in a good position to make our lives easier. There are also some possible classes we could create. What is a class? A collection of data and methods that work on that data. A class is used to organize similar purposed methods together, like methods that all work on a timer! Timer class below:

NOTE: SFML provides clock functionality: https://www.sfml-dev.org/tutorials/2.5/system-time.php 
We can use whichever we want. 

```cpp
/**
* GameTimer
* Requires: #include <chrono>
* Purpose:
*     Package together like methods to create a game clock, or a clock to determine if mouse clicks are happening too fast, etc.
*/
class GameTimer{
private:
  std::chrono::high_resolution_clock::time_point startTime;   // chrono time type for a start timer
  std::chrono::high_resolution_clock::time_point endTime;     // chrono time type for a ending timer
  std::chrono::high_resolution_clock::time_point currentTime; // chrono time type for checking running time
  std::chrono::duration<double> timeSpan;
public:
  /**
  * Constructor initializes our timers.
  */
  GameTimer(){
    startTime = std::chrono::high_resolution_clock::now();
    endTime = std::chrono::high_resolution_clock::now();
    currentTime = std::chrono::high_resolution_clock::now();
    timeSpan = 0;
  }
  
  /**
  * Starts our timer
  * Params: none
  * Returns: void
  */
  void StartTimer(){
    startTime = std::chrono::high_resolution_clock::now();
  }
  
  /**
  * Stops our timer
  * Params: none
  * Returns: int - span (in seconds) from start to end
  */
  int StopTimer(){
    endTime = std::chrono::high_resolution_clock::now();
    timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
    return timeSpan;
  }
 
  /**
  * Grabs current running time without stopping our timer
  * Params: none
  * Returns: int - span (in seconds) from start to current
  */
  int TimeRunning(){
    currentTime = std::chrono::high_resolution_clock::now();
    timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime);
    return timeSpan;
  }
  
}
```


  
  
    - Mouse Click capture (SFML disregard)
    - Drawing sprites (SFML disregard)
    - Handling a mouse click (AHA!)
    


# NOT DONE



