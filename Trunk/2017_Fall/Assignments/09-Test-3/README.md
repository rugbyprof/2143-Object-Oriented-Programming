## Take Home Portion of Exam

- Create a digital document containing the answers to the following questions.
- Your document should be organized and easy to read. Any code included (which is the whole exam :) ) should be commented.
- Turn your document in to my office on Wednesday May 10<sup>th</sup> by 10:00 a.m.
- By turning in this document, you are guaranteeing the CS department that you worked alone.
- Along with your digital document, you need to turn in a signed academic honesty sheet (found in this directory).

***Question 1***

- Once upon a time, on a way through the old wild west a man was given directions to go from one point to another. The directions were  **"NORTH", "SOUTH", "WEST", "EAST"**.  Clearly ***`"NORTH"`*** and ***`"SOUTH"`*** are opposite, ***`"WEST"`*** and ***`"EAST"`*** too. 

- Going to one direction and coming back the opposite  direction is a needless effort. 
- Since this is the wild west, with dreadfull weather and not much water, it's important  to save yourself some energy, otherwise you might die of thirst!
- The directions given to the man are, for example, the following:

**`["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"]`**

- You can immediatly see that going ***`"NORTH"`*** and then ***`"SOUTH"`*** is not reasonable, better stay to the same place! 
- So the task is to  give to the man a simplified version of the plan. A better plan in this case is simply:

**`["WEST"]`**

- In `["NORTH", "SOUTH", "EAST", "WEST"]`, the direction "NORTH" + "SOUTH" is going north and coming back right away. 
- What a waste of  time! Better to do nothing.
- The path becomes `["EAST", "WEST"]`, now "EAST" and "WEST" annihilate each other, therefore, the final result is **`[]`**.

- In ***`["NORTH", "EAST", "WEST", "SOUTH", "WEST", "WEST"]`*** , ***`"NORTH"`*** and ***`"SOUTH"`*** are not directly opposite but they become directly opposite after the reduction of ***`"EAST"`***  and ***`"WEST"`*** so the whole path is reducible to ***`["WEST", "WEST"]`*** .

#### Task

- Write a function ***dirReduc*** which will take an array of strings and returns an array of strings with the needless directions  removed (W<->E or S<->N side by side).

#### Examples

```python
dirReduc(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"]) => ["WEST"]
dirReduc(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH"]) => []
```
>Note
***-*** All paths can't be made simpler. The path `["NORTH", "WEST", "SOUTH", "EAST"]` is not reducible. 
***-*** "NORTH" and "WEST", "WEST" and "SOUTH", "SOUTH" and "EAST" are not directly opposite of each other and can't become such. 
***-*** Hence the result path is itself : `["NORTH", "WEST", "SOUTH", "EAST"]`.

-----

***Question 2***
The new "Avengers" movie has just been released! There are a lot of people at the cinema box office 
standing in a huge line. Each of them has a single ***`100`*** ,  ***`50`*** , or ***`25`*** ,  dollars bill.  

- A "Avengers" ticket  costs ***`25`*** dollars.
- Vasya is currently working as a clerk. He wants to sell a ticket to every single person in this line.
- Can Vasya sell a ticket to each person and give the change if he initially has no money and sells the 
tickets strictly in the order people follow in the line?
- Return **YES**, if Vasya can sell a ticket to each person and give the change. Otherwise return **NO**.

#### Examples:

```python
tickets([25, 25, 50]) # => YES 
tickets([25, 100]) # => NO. Vasya will not have enough money to give change to 100 dollars
```

-----

***Question 3***

Here is a `Point` class. 

```python
class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y

    def __str__(self):
        return "[%d,%d]" % (self.x, self.y) 

class Shape(object):
    def __init(self,p1,p2):
        self.p1 = p1
        self.p2 = p2
    
    def area(self):
        pass
```

- Write a `Square` class that that inherits from `Shape`.
- Write a `Rectangle` class that inherits from `Shape`. 
- Write a `Cube` class that inherits from `Square`. 



### Example Usage:
```python
w = 4
h = 6
s1 = Square(w)
r1 = Rectangle(w,h)
c1 = Cube(w)
print(s1.area())
print(r1.area())
print(c1.area())
print(s1.perimeter())
print(c1.surfaceArea())
```
-----

***Question 4***

Counting Duplicate Letters

Write a function that will return the count of distinct case-insensitive alphabetic characters and numeric digits that occur more than once in the input string. The input string can be assumed to contain only alphanumeric characters, including digits, uppercase and lowercase alphabets.

Example

- "abcde" -> 0 # no characters repeats more than once
- "aabbcde" -> 2 # 'a' and 'b'
- "aabbcdeB" -> 2 # 'a' and 'b'
- "indivisibility" -> 1 # 'i'
- "Indivisibilities" -> 2 # 'i' and 's'
- "aa11" -> 2 # 'a' and '1'

-----

***Question 5***

Your task is to find the first element of an array that is not consecutive and return it (if it exists).

E.g. If we have an array `[1,2,3,4,6,7,8]` then 1 then 2 then 3 then 4 are all consecutive but 6 is not, so that's the first non consecutive number.

If the whole array is consecutive then return **`None`**

The array will always have at least 2 elements and all the elements will be numbers. The numbers will also all be unique and in ascending order. The numbers could be positive or negetive and the first non-consecutive could be either too!

-----

***Question 6***

Given: 
```python
class Person(object):

    def __init__(self, firstname, lastname):
        self.firstname = firstname
        self.lastname = lastname

    def get_name(self):
        return '%s %s' % (self.firstname, self.lastname)
```

- Write a class to represent a `Parent` and a `Child` using either inheritance or composition.
- The `Parent` class should have a method that adds a "child" to a list. So a parent can have multiple children.
- The `Child` class should have an attribite that specifies whom it's parent is. 

-----

***Question 7***

Your going to write a simplified version of a roulette game. No worries ... right ?!?!

![](http://cdn-blog-assets.bigfishgames.com/uploads/2013/11/6-1-American-Roulette-1024x463.png)

**Roulette Wheel Class**

- Write a class to represent a roulette wheel. Looking at the image above should give you some ideas about what needs to be represented. 
- Colors used are: 
    - 0 and 00  - Green, 
    - 1 thru 10 and 19 thru 28, evens are black and odds are red
    - 11 thru 18, and 26 thru 36, odds are black and evens are red.
- Use an appropriate data structure to represent the values and colors on the wheel.
- A single method `spin` is needed, and it will return a dictionary with the following information:
    - **`{'number':8,'color':'black'}`**
    - **`{'number':19,'color':'red'}`**

**Roulette Table Class**
- The table may or may not have an instance of a roulette wheel. You make the correct decision. 
- The table needs to be able to support a certain bets.
- Supporting = provide the appropriate payouts for a specific bet:

|Bet name	| Winning spaces   	| Payout |
|--------------| ----------------------	| -------- |	
|  0              |     0                      	|   35-1  |	
|  00              |     00                  	|   35-1  |	
|  1-36              |     any number   |   35-1  |	
|  Row            |    0,00   |   17-1 |	
|  Split           |  Any two adjoining #'s     |   17-1 |	
|  Corner           |  Any four adjoining #'s     |   8-1 |	
|  Red/Black             |       |   1-1 |	
|  Even/Odd             |       |   1-1 |	
|  1st Column            |    1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34   |   2-1 |	
|  2nd Column            |    2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35   |   2-1 |	
|  3rd Column            |     3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36  |   2-1 |	
|  1st Dozen            |     1 through 12  |   2-1 |	
|  2nd Dozen            |    13 through 24   |   2-1 |	
|  3rd Dozen            |    25 through 36   |   2-1 |	

<sub>More here: https://en.wikipedia.org/wiki/Roulette </sub>

**Player Class**

This class should contain the following attributes:

| attribute            | desription | 
|----------------------|-------------------------------------|
| name                 | Players name                        |
| total_bank           | Total amount of money for betting   |
| current_bet_amount   | Current bet placed amount           |
| current_bet          | What player is betting on           | 

**Game Class**

This should encompass all of the above classes either through composition, or inheritance. Your call.
What needs to be turned in ??

- Class design with appropriate data members (attributes) with implementation of methods not necessary. 
- This means, I'm not totally interested in how you use `random` to spin the roulette wheel, I'm really interested in how you will define the "wheel"  or the "table" or a "player" from a data structure standpoint. 

### Example:

```python

class RoulettWheel(object):
    def __init__(self):
        """
        Tell me what, why, where ...
        """
        wheel = []     # or dictionary or ???
        # anything else needed ?? 
        
    def spin(self):
        """
        Describe what, why, where ...   
        """
        pass
```

- Ultimately, your not totally expected to make a roulette game, but you are expected to design a class structure that could easily be turned into a game.


