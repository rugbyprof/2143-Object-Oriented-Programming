---
title: UML Lesson Step 2 - Class Relationships
author: ChatGPT
date: 2024-11-24
tags:
  - UML
  - Class Diagram
  - Relationships
  - Knucklebones
  - Object-Oriented Design
description: Step 2 of a UML lesson using the Knucklebones game design, focusing on defining relationships between classes in the Class Diagram, including associations, aggregations, and compositions.
---

## Step 2: Defining Class Relationships

**Objective**

The goal of this step is to explore how the identified classes from Step 1 interact with each other, focusing on their relationships. We’ll refine the Class Diagram by adding associations, aggregations, and compositions to clearly define these interactions.

## Types of Relationships in UML

1. Association: A general connection between classes.
   - Example: Game is associated with Player (the game manages players).
2. Aggregation: A “whole-part” relationship where parts can exist independently of the whole.
   - Example: Game aggregates Player (players exist even outside a game).
3. Composition: A stronger “whole-part” relationship where parts cannot exist without the whole.
   - Example: Grid is composed of Cell objects (if Cell is its own class).
4. Dependency: A temporary relationship where one class uses another but does not maintain ownership.
   - Example: Player depends on Dice to roll during their turn.

## Relationships in Knucklebones

### 1. Game and Player

- **Type**: Aggregation
  - **Justification:** The game aggregates two players (or more in a variant).
- **Multiplicity**:
  - Game has a 1..2 relationship with Player (exactly two players in a standard game).

### 2. Game and Grid

- **Type**: Association
  - **Justification:** Game manages the shared Grid or coordinates interactions with individual player grids.
- **Multiplicity**:
  - If grids are shared: Game has a `1..1` relationship with Grid.
  - If grids are separate: Game has a `1..2` relationship with Grid.

### 2. Player and Grid

- **Type**: Composition
- **Justification**: Each player owns a grid, and the grid cannot exist independently of the player.
- **Multiplicity**:
  - Player has a `1..1` relationship with Grid.

### 3. Game and Dice

- \***\*Type:\*\*** Aggregation
- **Justification:** Game owns one or more dice used during gameplay, but dice can exist outside the game.
- **Multiplicity:**
  - Game has a `1..1..2` relationship with Dice (one or two dice for most games).

### 5. Grid and Cell (if Cell is a separate class)

- **Type:** Composition
- **Justification:** A grid is composed of cells, which cannot exist independently.
- **Multiplicity:**
  - Grid has a `1..9` relationship with Cell (a 3x3 grid contains 9 cells).

Updated Class Diagram (Textual Description)

1. Game:

- Aggregates Player and Dice.
- Associated with Grid.

2. Player:
   - Composed of Grid.
3. Grid:
   - Optionally composed of Cell.
4. Dice:
   - Independent but used by Game and Player.

### Diagram Enhancements

**Adding Relationships**

- Draw lines between related classes.
- Use arrows and multiplicities to define the type of relationship:
- Solid line: Association
- Solid diamond: Aggregation
- Filled diamond: Composition
- Annotate each relationship with a label if necessary (e.g., “rolls dice”).

### Example UML Class Diagram

Here’s a text description of what the diagram would look like:

```txt
+--------------------+        1      +-------------------+
|       Game         |----------------|      Player      |
|--------------------|   aggregates   |------------------|
| - players          |                | - name           |
| - grid             |                | - score          |
| - dice             |                | - grid           |
+--------------------+                +------------------+
        | 1                1..1              1..1
        |   associated with          composed of
        v
+-------------------+       1       +-------------------+
|       Grid        |----------------|       Cell       |
|-------------------|   composed of |-------------------|
| - cells[3][3]     |                | - value          |
|-------------------|                |-------------------|
```

## Practice Exercise

1. Add the appropriate relationships to your Class Diagram from Step 1.
   - Use a UML tool (e.g., draw.io) or sketch by hand.
1. Consider the following:
   - Should Dice be an aggregation or a dependency for Player?
   - What happens if Cell is not its own class?
1. Discuss as a group how these relationships impact reusability or scalability.

> In the next step, we’ll create Sequence Diagrams to represent interactions during specific scenarios, such as a player taking a turn or scoring dice on the grid. 🚀
>
> [Next Step: Sequence Diagrams](./Step-03.md)
