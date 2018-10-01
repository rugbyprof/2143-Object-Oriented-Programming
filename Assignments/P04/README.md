# Game of Life Requirements

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
 
