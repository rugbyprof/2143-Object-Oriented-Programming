---
title: UML Lesson Step 3 - Sequence Diagrams
author: ChatGPT
date: 2024-11-24
tags:
  - UML
  - Sequence Diagram
  - Knucklebones
  - Object-Oriented Design
description: Step 3 of a UML lesson using the Knucklebones game design, focusing on creating sequence diagrams to model interactions during key game scenarios such as taking turns and scoring.
---

## Step 3: Sequence Diagrams

**Objective**

This step focuses on modeling interactions between objects during specific game scenarios using Sequence Diagrams. These diagrams help students understand how objects collaborate by showing the order of method calls and interactions over time.

## Key Scenarios for Knucklebones

1. A Player Takes a Turn:
   - The player rolls a dice, chooses a column to place it in, and updates the grid.
   - Scoring is recalculated after the placement.
2. Scoring Dice on the Grid:
   - The game checks for multipliers and calculates the total score for the player.
   - If the new dice matches an opponent’s dice in the same column, the opponent’s dice are removed.

### How to Create Sequence Diagrams

- Actors: Identify who or what initiates the sequence (e.g., Player, Game).
- Objects: Determine the objects involved in the interaction (e.g., Dice, Grid).
- Messages: Show the methods or actions being invoked during the interaction.
- Lifelines: Represent the duration of each object’s participation in the scenario.

### Scenario 1: Player Takes a Turn

**Textual Description**

1. The player rolls a dice.
2. The dice value is displayed.
3. The player chooses a column on their grid to place the dice.
4. The grid updates with the new value.
5. The game recalculates the player’s score.

**Sequence Diagram Explanation**

    - Actors:
    - Player
    - Objects:
    - Game, Dice, Grid
    - Messages:

1. Player calls roll() on Dice.
2. Dice generates a value and sends it back to Player.
3. Player calls placeDice() on their Grid.
4. Grid updates the internal state.
5. Grid notifies Game to recalculate the score.
6. Game updates the player’s score.

## Diagram Placement

**Student Exercise - Insert Image Here:**

Create an image of a basic Sequence Diagram showing the lifelines of Player, Dice, Grid, and Game. Highlight method calls (roll(), placeDice(), updateScore()).

### Scenario 2: Scoring Dice on the Grid

**Textual Description**

1. A player places a dice on their grid.
2. The grid checks for any matching values in the same column.
3. If a match is found, the opponent’s dice are removed.
4. The grid recalculates the column score using multipliers.
5. The game updates the player’s total score.

**Sequence Diagram Explanation**

    - Actors:
    - Player
    - Objects:
    - Game, Grid, Opponent
    - Messages:

1. Player calls placeDice() on their Grid.
2. Grid checks for matching values (checkMatch()).
3. If a match exists, Grid calls removeDice() on the Opponent’s Grid.
4. Grid recalculates the column score (calculateColumnScore()).
5. Grid notifies Game to update the player’s total score.

### Diagram Placement

**Student Exercise - Insert Image Here:**

Visualize a Sequence Diagram with interactions between Player, Grid, Opponent, and Game. Highlight the conditional logic for matching and removing opponent dice. (to replace txt output below)

**Sequence Diagram Example (Textual)**

Below is a textual representation of a Sequence Diagram for Scenario 1: Player Takes a Turn:

```txt
Player        Dice          Grid         Game
   |            |             |             |
   | roll()     |             |             |
   |----------->|             |             |
   | value()    |             |             |
   |<-----------|             |             |
   | placeDice()|             |             |
   |------------------------->|             |
   |             updateScore()|             |
   |---------------------------->-----------|
   |             updateState() |            |
   |<--------------------------|            |
```

## Practice Exercise

1. Sketch the Diagrams:
   - Have students draw Sequence Diagrams for the two scenarios above using tools like:
   - Lucidchart
   - draw.io
   - Or simple pen and paper.
2. Extend the Scenarios:
   - Ask students to create a Sequence Diagram for additional interactions, such as:
   - Player rolling a dice and matching it with an opponent’s dice.
   - Game determining the winner at the end of play.
3. Critical Thinking Questions:
   - What happens if the player rolls a dice but no valid placement exists?
   - How could error handling (e.g., invalid input) be shown in the diagram?

> In the next step, we’ll create State Diagrams to represent changes in the game or player state during gameplay. These diagrams will highlight transitions like “Player Taking Turn” → “Dice Placed” → “Score Updated.”
>
> [Next Step: State Diagrams](./Step-04.md) 🚀
