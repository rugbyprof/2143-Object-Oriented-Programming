# NOT DONE
# Game of Life 

## Overview

The Game of Life was invented by John Conway (as you might have gathered).  It consists of a collection of cells which, based on a few mathematical rules, can live, die or multiply.  The "game" is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input from humans. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are directly horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
2. Any live cell with more than three live neighbors dies, as if by overcrowding.
3. Any live cell with two or three live neighbors lives on to the next generation.
4. Any dead cell with exactly three live neighbors becomes a live cell.

Below is an example of the first 3 generations from the following initial configuration (green = life).

|  Example Generations |
|:---------------------:|
| <img src="https://cl.ly/eaa827597c4a/Image%2525202018-10-02%252520at%2525204.48.28%252520PM.png" width="500"> |



Your implementation will not be an infinite two-dimensional orthogonal grid of square cells, but a finite 2-dimensional array of `golCell`(s) (game of life cells).  A `golCell` contains


## Data Elements

### Main Data Structure

- `CurrentState`
  - 2D array of int's where 1 = alive

-`NextState` (transition)
  - 2D array of integers to store (-1,0,1)
    - -1 = death
    - 0 = no action
    - 1 = life
- A transition means adding `CurrentState` => `NextState`

### Helper Elements
  - int FrameCount
  - int FrameRate
  - int Rows
  - int Cols 
  - sf::RenderWindow window (not sure what were gonna do?)
  

## Methods

  - PrintGeneration
    - simply prints to std out
  - ApplyRules
    - Reset `nextGeneration`
    - Some 2D array (`nextGeneration` gets the values -1,0,1 base on the `currentGenerations` state.
  - NextGeneration
    - Add `nextGeneration` to `currentGeneration`
  - OnWorld
    - Determines if a cell is on the world
    - return (i >= 0 && i < height && j >= 0 && j < width)
  - Alive or Dead?
    - create a function that adds all neighboring cells and return the sum.
 
