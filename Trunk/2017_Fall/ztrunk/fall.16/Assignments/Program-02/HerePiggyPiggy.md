


# Program 2 - Gaming Strategy Simulation
- Part 1 Due: 24<sup>th</sup> Oct by Classtime.
- Part 2 Due: 31<sup>st</sup> Oct by Classtime.
- Part 3 Due: 7<sup>th</sup> Oct by Classtime.

## Program Overview

This is a three part project:

- Part 1: Make a minor adjustment to the game play, get familiar with code base.
- Part 2: Add two strategy methods
- Part 3: Run a simulation to determine best strategies.

You are going to determine the best strategy for playing the dice game pig. By simulating thousands of rounds of games, we can see which strategy would maximize a players odds for winning. The basic game class has been written, and what you need to do is create a player class that will represent a player, thier score, and thier strategy. Below is a basic explanation of the game "pig" that we have been discussing in class.


### Pig

The game was introduced by John Scarne, a magician and game developer, in 1945 and it has since been played with a wide range of variants to the original concept. Over the years, there have been a number of commercial productions of Pig, with titles like Skunk and Pig Dice, as well as the most current version, Pass the Pig. It has also served as a fun and useful tool for math teachers who are trying to convey probability concepts to young students and for computer science instructors, as well.

### How to Play Basic Pig

Pig requires at least two players and it can, conceivably, be played by as many people as you have available. The only things that you’ll need to have are a standard, six-sided die, a piece of paper and something to write with.

Every time that a player rolls in Pig, they have to make a decision about their next move that could cost them the win. If they have rolled any number from a 2 to a 6, they are free to collect points that are equal to the face value of their roll and they can roll again, or they can decide to take the points and hold, handing the die over to the next player. If the player makes the call to decide to roll again and a 1 comes up, the points that they had from their initial roll are taken away, their turn is over, and their score for that round is a zero. For as long as they don’t roll a 1 though, the player can continue to throw the dice and to accumulate points. The players take turns this way until one of them reaches 100 points and is declared the winner.

In an example, if a player’s first three rolls come up as a 4, a 2, and a 3, and they opt to hold, they will receive nine points for that turn, because 4 + 2 + 3 = 9. If they decided to continue rolling and their fourth throw yielded a 1 on the die however, those nine points would be wiped out and their score for that round would be a zero.

<sup>Source: http://dicegames.org/pig/</sup>

## Model vs Simulation 

A computer model is the algorithms and equations used to capture the behavior of the system being modeled. By contrast, computer simulation is the actual running of the program that contains these equations or algorithms. Simulation, therefore, is the process of running a model. Thus one would not "build a simulation"; instead, one would "build a model", and then either "run the model" or equivalently "run a simulation".

<sup>Source: https://en.wikipedia.org/wiki/Computer_simulation</sup>

## Game Play Styles (Strategies)

- Strategies
    - Target Score
    - Target Rolls
    - Sprint to Finish
    - Mimic Opponent
    - Situational
    - Combination

### Target Score

This simply picks a target score for each turn. For example the value 20 seemed to work well in our simple experiments in class. We could adjust this score up or down to see there is any improvement in outcome.

### Target Rolls

The player will roll a "target" number of times every time unless a skunk value occurs. Again, we could adjust this target up or down to see there is any improvement in outcome.

### Sprint To Finish

This strategy could be employed with one of the above strategies (Target Score, Target Rolls), with the addition of the "sprint". If the player comes within _**X**_ points of finishing the game, they will continue to roll until they encounter a skunk, or finish. 

> Note: The implementation of this could be a little fuzzy. For example lets define our "sprint" threshold as 72. If our current score is 55, and in our current turn we achieve the "sprint" score, do we keep going? If we skunk out we go back to 55. OR if we have 55 do we employ our current strategy (no matter if we get to 72 or not) then the NEXT turn if we are 72 or greater we can sprint to the end. 

### Mimic Opponent

Count your oppenents rolls, or avg points per turn, and copy their actions. This may take a few turns to figure out, so an initial strategy may need to be employed. 

### Situational

We decided that this strategy would be "conservative" if they were ahead of their opponent, or "aggressive" if they were behind their opponent. This could get a little hard if we are playing with more than one opponent. 

### Combination

This will incorporate a combination of 2 or more of the above strategies.

## Part 1 Deliverables
Part 1 Due: 24<sup>th</sup> Oct by Classtime.
- Create a folder called _**program\_2**_ in your **_assignments_** folder. (If I haven't previously instructed you to create an assignments folder, please do).
- Create a file called _**game\_part1.py**_ within _**program\_2**_ that is a copy of the given file [game_starter.py](./game_starter.py)
- Make necessary changes so that game play is correct:
    - Currently the player does not stop rolling immediately after reaching the target score.
    - Adjust the player class so that the player knows the target score and stop immediately after reaching it.
- In addition to changing the game play, add a statement that will print the following:
    - "{Playername} has just reached {Target Score} points and is stopping."

## Part 2 Deliverables
Part 1 Due: 31<sup>st</sup> Oct by Classtime.
- Create a file called _**game\_part2.py**_ within _**program\_2**_ that is a copy of your corrected version of the following: [game_starter.py](./game_starter.py) (Basically a copy of your _**game\_part1.py**_)
- Complete the method `Sprint_To_Finish` . This method should be invoked when the player gets close enough to the final score in order to feel like they can achieve the  score if they keep rolling. Currently, the strategy is `Random`. I would do something like below to choose which strategy to roll with:

```python

        # New code to choose strategy 
        # This block will apply the sprint to finish when the player
        # is within %80 of the final score.
        if self.TotalScore / self.TargetScore >= .8:
            self.Strategy = 'SprintToFinish'
            
        # Same if/else statements to call strategy method
        if self.Strategy == 'Random':
            Score,NumRolls = self.RandomRoll()
        elif self.Strategy == 'Aggressive':
            pass
        elif self.Strategy == 'Cautious':
            pass
        elif self.Strategy == 'Robust':
            pass
        elif self.Strategy == 'CopyCat':
            pass
        elif self.Strategy == 'SprintToFinish':
            self.SprintToFinish()
```

- Complete the `Aggressive` and `Cautious` methods. Remember the "Random" method rolled the die between 1 and 7 times randomly (unless they rolled a 1).  The average score for a single roll of a die is **3.5** and if we use the **20** points as a goal, thats **5.7** rolls. I'm not sure what is aggressive or cautious but it probably should be based on these values, where aggressive would be 2-3 rolls above the average 6 rolls, and the cautious would be 2-3 below.  

## Part 3 Deliverables

- TBD


 
