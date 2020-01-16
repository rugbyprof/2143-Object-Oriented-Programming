## Test 1 Study Guide

#### Cheat Sheet
Everyone will get a copy of the [Python_Cheat_Sheet](./Python_Cheat_Sheet.md) along with thier exam, so don't panic about memorizing all things python. 

======
#### Python Container Types
Give a basic overview of each data type below. What kind of data could/would you store in each? Are each of them `mutable`? Give examples of each.
- lists
- dictionary's
- tuples

======
#### Definitions

Words are Defined [here](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/wiki/Definitions). 

- Attributes
- Class
- Constructor
- Data Member
- Encapsulation
- Immutable
- Information Hiding
- Inheritance
- Instance Variable
- Method
- Mutable

======
#### Looping over Lists

Given the following list: `[34,55,3,22,"hello","wassup",99,17.9,42]` provide more than one 
method for accessing each element (in this example, by access I mean print). 

https://gist.github.com/rugbyprof/2c5bf44a5d901d53e60b71defcdb725d

=====

#### Looping over Dictionaries

Given the following dictionary: {'a':'1','b':'2','c':'3','d':'4','e':'5','f':'6','g':'7'}

Loop over "it" and print out the key value pairs.

=====

#### Writing Functions

A clerk works in a store where the cost of each item is a positive integer number of dollars.
So, for example, something might cost $21, but nothing costs $9.99. In order to make change
a clerk has an unbounded number of bills in each of of the following denominations: $1, $2,
$5, $10, and $20. Write a procedure that takes two arguments, the cost of an item and the
amount paid, and prints how to make change using the smallest possible number of bills.

=====
#### Working With Lists

Write a procedure that takes a string of words separated by spaces (assume no punctuation
or capitalization), together with a ”target” word, and shows the position of the target word
in the string of words. 

For example, if the string is:
```
we dont need no education we dont need no thought control no we dont
```

and the target is the word `dont` then your procedure should return the list `1, 6, 13` because
`dont` appears at the `1st, 6th, and 13th` position in the string. Your procedure should return 
`False` if the target word doesn’t appear in the string.

=====
#### Choosing Correct Data Type

Create a data structure to hold data for a student. This structure would hold the following:
`string` first_name, `string` last_name, `int` id, `string` dob 

=====

#### Stats Function

Write a function that will return a `tuple` that contains the `average`, `maximum`, and the `minimum` number in a given list of integers.

=====

#### Stats Class

Now take that function with the logic you just created to solve the problem above and turn it into a class. Your class will be called `listStats` and have the following methods:

- setList()
- getMin()
- getAvg()
- getMax()

Here is some example usage of your class:

```python
l1 = [3,4,5,2,33,77,65,67,22,12,3,44,5,66,77]
l2 = [55,7,66,23,45,3,4,11,2,99,8,7,98,58,23]
s1 = listStats(l1)
print(s1.getAvg()) 
s1.setList(l2)
print(s1.getMax())
```
=====
#### String Output of a Class

Given the following class:

```python
class Point:
    """ Point class represents and manipulates x,y coords. """

    def __init__(self,x=0,y=0):
        """ Create a new point at the origin """
        self.x = x
        self.y = y
```

Write a `str` method to print out the string representation of the class. Example output:
```python
p1 = Point(3,5)
print(p1)
# prints: (x:3,y:5)
```

=====

#### Overloading an Operator

Given the following example of how to overload an operator:
```python
class Point:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y
    
    #Looks like an answer to another question!!! ;)
    def __str__(self):
        return "({0},{1})".format(self.x,self.y)
        # or
        # return "(%d , %d)" % (self.x,self.y)
    
    def __add__(self,other):
        x = self.x + other.x
        y = self.y + other.y
        return Point(x,y)
```
And it's usage:

```python
p1 = Point(2,3)
p2 = Point(-1,2)
print(p1 + p2)
# prints: (1,5)
```
Overload the `equal` operator to test for `point` equality.

======

#### Dictionary Class

Write a class called `wordDictonary` that represents an actual dictionary. Your class should contain the following methods:
- `loadDictionary` : 
    - reads a file that contains `word: definition` 
    - a word may occur more than once (same word alternate definition)
    - you should be able to hold all definitions
- `updateDictionary`:
    - a method that lets you add a word:definition to the class
- `findWord`:
    - this method receives a word, and returns all definitions that correspond to it. 
- `removeWord`:
    - this method lets you remove a word from the dictionary. 
    
    https://gist.github.com/rugbyprof/13efbdccb15acf023637522a6a15127d
    
======

### Median Trickery

- Complete the function using this algorithm: 
    - continually remove the largest and smallest values from the list and return either the last value (if there is only one left) or the average of the two last values (if there are two left).
    - Do not sort the list, and don't use any for loops in your solution.
    - Functions `max` and `min` may be helpful, as well as one or more list methods.

```python
def myMedian(L):
""" 
@Description: Return the median of the numbers in L.
@Params: L (list)
@Returns: median (int)
"""
	# Start with a copy of the list so we don’t modify the original.
	L = L[:]




