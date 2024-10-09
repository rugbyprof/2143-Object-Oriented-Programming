## Program 2B - Class Design

#### Due: 10-11-2024 (Friday)

## Basic Rules of KnuckleBones:

1. **Two Players**: The game is played between two players, each with their own 3x3 grid.
2. **Dice Rolling**: Each turn, a player rolls a six-sided die.
3. **Placing Dice**: The player then places the die in one of the three columns on their grid.
   - A player can place a die in any of the three columns, and dice stack vertically in each column (similar to a 3-column Tetris grid).
4. **Scoring Rules**:
   - The player's score is the sum of the dice in each column.
   - **Multiplication Bonus**: If a player places multiple dice with the same value in the same column, their values are **multiplied together** (e.g., two dice showing a 3 in a column would be worth 3 × 3 = 9 points).
5. **Opponent's Dice Removal**: If a player places a die in a column that matches one of their opponent's dice in the same column, the opponent's matching die is **removed** from their grid.
6. **End of Game**: The game ends when all 9 spaces in both players' grids are filled. The player with the **highest score** wins.

## Assignment: Class Design for "Knucklebones" Game

### Objective:
Design a set of classes for a digital version of the game **Knucklebones**. The goal of this assignment is to organize your ideas and determine the relationships between different components of the game, such as players, dice, and the game itself. You will also decide when to use **composition** and **inheritance**, keeping in mind the "IS-A" rule we discussed in class.

This is the **initial design phase**, where you’ll think through the actions, data, and organization for each class, breaking them down into **bulleted lists**. There is no need to create formal UML diagrams at this stage.

### Steps:

1. **Class Organization**:
   For each class, create a **bulleted list** that outlines:
   - The **data** that each class will store (attributes).
   - The **actions** or methods each class will have.
   - Any **relationships** to other classes (e.g., one class might use another, or inherit from another).

2. **Inheritance vs. Composition**:
   In your design, explain where you would use **inheritance** and where you would use **composition**. 
   - Inheritance: Use when a class **IS-A** type of another class.
   - Composition: Use when a class **HAS-A** relationship with another class.

   Examples:
   - **Inheritance**: Knucklebones **IS-A** Game.
   - **Composition**: A Player **HAS-A** Dice or a Knucklebones game **HAS-A** Player.

3. **Suggested Class Template**:
   Here are some suggested classes to help guide your design. You are welcome to expand on this, combine classes, or add others as you see fit:

   - **Dice Class**: 
     - Data: `sides`, `current_value`
     - Actions: `roll()`, `get_value()`
     - Relationships: Dice will be used by the Player to roll during the game.
   
   - **Player Class**:
     - Data: `name`, `score`, `dice_set`, `player_stats`
     - Actions: `roll_dice()`, `get_score()`, `update_score()`
     - Relationships: Each player has a set of dice and participates in the game.
   
   - **Game Class**:
     - Data: `players`, `rules`, `current_round`
     - Actions: `start_game()`, `end_game()`, `get_winner()`
     - Relationships: The Game class controls the players and their actions.

   - **Knucklebones Class**:
     - Data: `board`, `knucklebones_specific_rules`
     - Actions: `start_round()`, `end_round()`, `calculate_winner()`
     - Relationships: Inherits from Game, as Knucklebones **is a** game with specific rules and conditions.

4. **Keywords and Feature List**:
   Below are some **keywords** that we brainstormed in class. Categorize them into three labels: **necessary**, **possible**, or **wishful**, based on your design. Feel free to add more items that you think could be part of your Knucklebones game design:

   - chat
   - coins
   - first name
   - high score
   - last name
   - leaderboard
   - levels
   - messaging
   - player stats
   - score
   - streak
   - team stats
   - teams
   - userid
   - winner

   Add **any other features** you think would be valuable or interesting to include in your version of the game. Consider whether they are necessary for a basic version or features you might add if you had more time and resources.


### Example of Class Design Outline:

**Player Class**:
- **Data**:
  - `name`
  - `score`
  - `dice_set`: Array of Dice objects
  - `player_stats`
  
- **Actions**:
  - `roll_dice()`: Roll the dice for the player.
  - `get_score()`: Retrieve the current score.
  - `update_score(points)`: Update the player’s score after each roll.

- **Relationships**:
  - A Player **HAS-A** Dice (composition).
  - A Player **IS-A** participant in the game.

### Submission:
- Provide your **bulleted lists** for each class.
- Label the keywords with **necessary**, **possible**, or **wishful**.
- Explain where you are using **inheritance** and **composition** in your class design.

## Deliverables

- Create a folder called `P02B` and add a `README.md` to it.
- Place your class design inside the readme. 
- Upload this folder to your `Assignments` folder in Github.