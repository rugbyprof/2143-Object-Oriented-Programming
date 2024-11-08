## Program 2C - Knuckle Bones

#### Due: 11-18-2024 (Monday the 18<sup>th</sup>)

<img src="https://images2.imgbox.com/f8/8e/BA7Doxin_o.jpg">

### Next Program

|                                     AI player                                      |
| :--------------------------------------------------------------------------------: |
| <img src="https://reliefline.ca/wp-content/uploads/2023/10/dice.jpg" width="100">" |

## Overview

https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/

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

Implement an version of Knucklebones in which the Ncurses library is used to control the output to the console screen. Your output should use various colors, be organized, and utilize the screen as if it were a game window. Where by game window I mean all sides in a way that the console looks like a game visualizing everything necessary to ensure that game play looks animated or fun all while implementing the rules of knucklebones.

https://www.thegamer.com/cult-of-the-lamb-knucklebones-guide-dice-minigame-strategy-ratau-shrumy-klunko-bop-flinky/

### Specifics

- There are plenty of helper classes to give you a hand in implementing the knucklebones game.
- At a minimum will need to implement a `Player class` and a `Game class`.
- The big question is who is in charge of what? We have classes for every component ... pretty much. We really just need to organize the components so the outcome becomes a controlled set of actions (instructions) with a start ... some gameplay ... and an end. Yes I am over simplifying the issue but these are vital to every program.
- I've mentioned it in class many times. OOP can be a little gray. This project is a great example of how OOP can feel more like art than science! For a game like `Knucklebones`, there are a few ways to organize classes and responsibilities.
- Here’s a breakdown of a typical OOP structure with some alternatives. I intentionally did not include everything, but I wanted to give the class at least some standard ways of game / player interaction.

## Game Class

- The Game class is responsible for managing the overall flow of the game.
- It typically owns the components essential for controlling the game `state` (which in turn controls the `flow`).
- It can goes as far as controlling a players `turns` along managing ghe interactions with the `dice` and `grid`.

```cpp
class Game {
public:
   Game();

      // Main gameplay methods
      void start();
      void take_turn();
      bool check_win();

      // Game setup and utility methods
      void initialize_players(std::string player1_name, std::string player2_name);
      void roll_dice();

      // Optional UI-oriented methods
      void display_game_state();
      void end_game();

private:
   Dice dice; // Dice instance owned by Game, used each turn
   Grid grid; // Game-level grid instance for managing cells
   Player\* current_player;
   Player players[2]; // Array of players for a two-player game

   void switch_turn();

};
```

### Notes:

- **Ownership of Dice and Grid:**
  - Game owns the `dice` and `grid` objects because these are shared resources that shouldn’t belong to a single player.
  - Game manages access to them and coordinates interactions.
- **Player Management:**
  - The Game class keeps track of players and whose turn it is.
  - It might even handle the flow of turns and rolling the dice for each player.

## Player Class

- The Player class represents each player, holding their unique game state.
- This includes a personal name and score.
- It interacts with the `Grid` or `Dice` objects indirectly through Game.

```cpp
class Player {
public:
Player(std::string name);

    // Player actions
    void take_turn(Game& game);  // Player's turn with access to Game methods as needed
    void add_to_score(int points);

    // Accessors
    std::string get_name() const;
    int get_score() const;

private:
std::string name; // Player's name
int score; // Player's score
};
```

### Notes:

- **Turn Interactions:**
  - `take_turn` could be designed to interact with `Game` for rolling dice or using grid cells.
  - This keeps `Player` focused on player-specific actions while still allowing `Game` to enforce the rules.
- **Score Management:**
  - `add_to_score` lets the Player update their score directly.

---

## Alternatives and Flexibility

- **Alternative 1:**
  - Let Player Own Their Own Grid: In some designs, Player might own a Grid instance if each player has their own area to place dice.
  - If so, Player might contain Grid player_grid; and methods to interact with it independently.
- **Alternative 2:**
- Move Dice to Player: If each player has their own dice (or representation of rolled values), then `Dice` could be moved to `Player`, and each `Player` would roll their own dice each turn.
- But if `Dice` is a shared resource, keeping it in `Game` is more efficient.

### Dice and Grid Classes

Our existing `Dice` and `Grid` classes will remain mostly the same. They’re used by either `Game` (for shared resources) or `Player` (if individual instances are needed). Here are simple stubs just for clarity:

```cpp
class Dice {
   public:
      Dice();
      int roll(); // Randomly roll and return a value

   private:
      int current_value;
};

class Grid {
   public:
      Grid();

      // Methods to place dice and manage grid state
      bool place_dice(int row, int col, int value);
      int get_cell_value(int row, int col) const;

   private:
      int cells[3][3]; // Simplified for a 3x3 grid
};
```

### Summary of Game vs Player

• **Game Class:** Manages the flow, holds Dice and Grid for shared access, and switches player turns.
• **Player Class:** Represents individual players, optionally owns personal grids if needed.
• **Dice and Grid Classes:** Serve as utility classes, either shared in Game or individually managed by Player.

Remember to always think about reusability (but don't force it). For example that's why we made a dice class (earlier this semester) that allowed from 4 sides up to 20 sides, and as many as we wanted. That kind of class is reusable.

This division between Game and Player keeps responsibilities clear while offering flexibility for tweaks and additions. With this approach, we can make each component interact in a natural and OOP-compliant way, while also keeping our code maintainable.

## Other components

Using the bit of information above, decide where the other components might be best placed. Below is a list of hpp files as a reminder of what components we have to work with.

|  #  | Name                                 | Description                                    |
| :-: | :----------------------------------- | :--------------------------------------------- |
|  1  | [button_class.hpp](button_class.hpp) | Use to add a button to your game.              |
|  2  | [color_class.hpp](color_class.hpp)   | Use to easily make color pairs and use colors. |
|  3  | [dice_class.hpp](dice_class.hpp)     | Animate a cheesy dice square (rectangle).      |
|  4  | [game.cpp](game.cpp)                 | Example usage of helper classes.               |
|  5  | [grid_class.hpp](grid_class.hpp)     | Where you place dice values.                   |
|  6  | [input_class.hpp](input_class.hpp)   | Captures input from users like a txt box.      |
|  7  | [log.txt](log.txt)                   | Log file to help debug programs.               |
|  8  | [logger_class.hpp](logger_class.hpp) | Class to assist logging debug statements.      |

## Deliverables

- Create a folder called `P02C` and add a `README.md` to it.
- Place all of your code and any other documents or resources used inside your games folder.
- Upload this folder to your `Assignments` folder in Github.
- If you don't remember how to write a nice readme, go [HERE](../../Resources/02-Readmees/README.md)
