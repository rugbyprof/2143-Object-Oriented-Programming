## Program 2B - Knuckle Bones

### TBD

## Overview

The game KnuckleBones, as featured in **"Cult of the Lamb"**, is a simple dice game that is played between two players on a 3x3 grid. The goal is to place dice on the grid and score more points than your opponent by following a few key rules. Here's a brief breakdown of the rules:

### Basic Rules of KnuckleBones:

1. **Two Players**: The game is played between two players, each with their own 3x3 grid.
2. **Dice Rolling**: Each turn, a player rolls a six-sided die.
3. **Placing Dice**: The player then places the die in one of the three columns on their grid.
   - A player can place a die in any of the three columns, and dice stack vertically in each column (similar to a 3-column Tetris grid).
4. **Scoring Rules**:
   - The player's score is the sum of the dice in each column.
   - **Multiplication Bonus**: If a player places multiple dice with the same value in the same column, their values are **multiplied together** (e.g., two dice showing a 3 in a column would be worth 3 × 3 = 9 points).
5. **Opponent's Dice Removal**: If a player places a die in a column that matches one of their opponent's dice in the same column, the opponent's matching die is **removed** from their grid.
6. **End of Game**: The game ends when all 9 spaces in both players' grids are filled. The player with the **highest score** wins.

### Assignment:

Implement an version of Knucklebones in which the Ncurses library is used to control the output to the console screen. Your output should use various colors, be organized, and utilize the screen as if it were a game window. Where by game window I mean all sides in a way that the console looks like a game visualizing everything necessary to visualize game play while implementing the rules of knucklebones.

# NOT DONE

<!--
### Design Steps

1. **Define the 3x3 Grid for Each Player**:
   - Use a 2D array (3x3) for each player to represent the grid where dice will be placed.
2. **Dice Rolling**:
   - Simulate the rolling of a six-sided die using a random number generator.
3. **Dice Placement**:
   - Allow the player to select a column to place the die.
   - Stack the dice in the column and apply the multiplication rule if the dice match.
4. **Opponent's Dice Removal**:
   - If the placed die matches the value of an opponent's die in the same column, remove the opponent's die from the grid.
5. **Scoring**:
   - Calculate each player's score based on the sum of the dice in each column, applying the multiplication rule for matching dice.
6. **Game End**:
   - The game ends when both grids are full, and the program should declare the winner based on the total score.

### Example of Basic Code Structure (Python):

Here’s a simplified outline to get you started:

```python
import random

def roll_die():
    return random.randint(1, 6)

def print_grid(grid):
    for row in grid:
        print(row)

def place_die(grid, die, column):
    for row in range(2, -1, -1):  # Place the die in the first available spot in the column
        if grid[row][column] == 0:
            grid[row][column] = die
            break

def calculate_score(grid):
    score = 0
    for col in range(3):
        col_values = [grid[row][col] for row in range(3) if grid[row][col] != 0]
        if len(col_values) > 1 and len(set(col_values)) == 1:  # Multiplication bonus
            score += col_values[0] * len(col_values)
        else:
            score += sum(col_values)
    return score

def knucklebones_game():
    player1_grid = [[0 for _ in range(3)] for _ in range(3)]
    player2_grid = [[0 for _ in range(3)] for _ in range(3)]

    current_player = 1

    while True:
        if current_player == 1:
            die = roll_die()
            print(f"Player 1 rolls: {die}")
            col = int(input("Choose a column to place your die (0, 1, 2): "))
            place_die(player1_grid, die, col)
            current_player = 2
        else:
            die = roll_die()
            print(f"Player 2 rolls: {die}")
            col = int(input("Choose a column to place your die (0, 1, 2): "))
            place_die(player2_grid, die, col)
            current_player = 1

        print("Player 1 Grid:")
        print_grid(player1_grid)
        print("Player 2 Grid:")
        print_grid(player2_grid)

        # Scoring logic and game end condition goes here (when all slots are filled)
        if all(all(cell != 0 for cell in row) for row in player1_grid + player2_grid):
            print("Game Over!")
            p1_score = calculate_score(player1_grid)
            p2_score = calculate_score(player2_grid)
            print(f"Player 1 Score: {p1_score}")
            print(f"Player 2 Score: {p2_score}")
            if p1_score > p2_score:
                print("Player 1 Wins!")
            elif p1_score < p2_score:
                print("Player 2 Wins!")
            else:
                print("It's a tie!")
            break

knucklebones_game()
```

### Additional Features for Advanced Students:

- Add a graphical user interface (GUI) using a library like `Tkinter` or `pygame`.
- Include AI to play against a computer opponent.
- Implement a more complex scoring system or variation of the game’s rules.

This game is simple but involves important concepts like **random number generation**, **arrays**, **conditional logic**, and **loops**, making it a great programming exercise. Let me know if you need further refinement for the assignment! -->
