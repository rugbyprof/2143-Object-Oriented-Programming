# Test 1 Study Guide
***Test Date: 23 Feb 2017***

- I will provide a python cheatsheet for the exam. Syntax should not be an issue. [HERE](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/Resources/python_cheatsheet.md) is the sheet.
- Show up to class on time. 
- Bring a pencil, pens not allowed.
- Bring a blue book.
- Questions on the actual test could be exact copies of the question below, more likely they will be closely related in scope. In the case of lists and dictionaries be ready for varying types of organizations. (e.g. Lists of dictionaries of lists, or Dictionaries of lists of dictionaries, etc.). You get the picture. 

## Definitions:

These are the basic terms that you should be familiar with. More will come later.

- Polymorphism
- Encapsulation
- Inheritance vs Composition
- Immutable vs Mutable 



## Dictionaries

#### Traversing Dictionaries

You should be comfortable with traversing arbitrary data structures. Below you are given a Dictionary of Dictionarys of Lists.

***Given:***

```python
grades = {
    'Bob' : { "A": [98,99,99,90,91], "B" : [88,89,87,81], "C" : [70,72,71,77,75]},
    'Sue' : { "A": [92,99,91], "B" : [88,84,87,86,82], "C" : [70,74,71]},
    'Ann' : { "A": [93,94], "B" : [88,89,87,83,82], "C" : [70,72,71,73,75]},
    'Bill' : { "A": [96,99,95], "B" : [88,82,87,86], "C" : [70,72,71,77,71,75,75]}
}
```
Print out the number of occurences of A's, B's and C's for each student. The `len` function will help here.
Also remember one method of looping through dictionaries uses the `.items()` method so we can assign the returned
tuple to a key,value combo.

```
Bob: A's = 5 , B's = 4 , C's = 5
Bob: A's = 3,  B's = 5 , C's = 3
Bob: A's = 2 , B's = 5 , C's = 5
Bob: A's = 3 , B's = 4 , C's = 7
```

#### Counting Occurences

In this question I want to you leverage the power of unique keys to create a histogram of word occurences. Count the number of occurrences of words in a string using a dictionary as your container. The code we discussed in class is [HERE](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/ClassLectures/day3b.py).  Assume there is a string
called `words` that is space delimited and has NO punctuation. 

***Given:***
```python
words = "the the and the and and and the boy boy the and boy boy and and and end"
```

***Result:***
```python
{'the': 5,'and': 8,'boy': 4,'end': 1 }
```

## Python Lists / Functions

Given a list of unkown / unsorted integer values find the median value. There is a little trick to this, as we won't be using a sorted list of values which would simply require this:

```python
def median(L):
    L = sorted(L)
    return L[len(L)/2)]
```
In fact python HAS a `median` function :) However, we will use our own algorithm:
    - Continue looping until there is 1 or 2 values left in your list
    - Do not use a `for` loop.
    - On each iteration, continually remove the largest and smallest values from the list
    - If there is only 1 value left, return it. 
    - If there are 2 values left, return the average of the two.

```python
def myMedian(L):
""" 
@Description: Return the median of the numbers in L.
@Params: L (list)
@Returns: median (int)
"""










```
-----

## Classes

This was discussed in class [HERE](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/ClassLectures/day3a.py). 

#### Fraction Class
Be able to write a fraction class and overload the `addition` and `multiplication` operators. I will provide a GCD method. Make sure you implement the `str` method so a fraction prints out correctly.

-----

I used this topic in my 1063 class this semester, and seem to use it quite a bit. But RGB values and color classes are easy to understand but still useful as an example. So I will keep using it.

#### Color Class

- Create a class called "rgbColor" that will store the red, green, and blue values for a color pixel.
- This class has one method called "color" that returns a `tuple` like the following: `(128,200,34)`
- If no color is passed in assign each of the color channels to 0. 
- Add a __str__ method to print out the color class so it looks like: "(red: redVal, green: greenVal, blue: blueVal)"
- Here is some usage:

```python

c1 = Color((255,0,0))
print(c1.red)
#prints: 255
print(c1.r)
#again prints: 255

c1.blue = 128
print(c1)
#prints: (red: 255, green: 0, blue: 128)
print(c1.b)
prints: 128
```

-----

#### Operator Overloading
Overload the assignment operator so we can do the following:

```
c1 = (32,100,255)
print(c1)
#prints: (red: 32, green: 100, blue: 255)

```

Overload the addition operator so that we can add two colors. Adding colors is a pretty wierd experience, so we will create our own addition method. Basically we will average each color. 

For example:

```python

c1 = (255,255,255)
c2 = (0,0,0)
c3 = c1 + c2

print(c3)
#prints: (128,128,128)
```

-----

#### Grayscale Class

So what is gray scale? Its where you take the 3 individual parts of a color and using those values you calculate a single value that will be assigned to each of the 3 components, making it some shade of gray.
 
For example here is red: `(0,255,0)` and here is the gray scale equivalent: `(85,85,85)` (using the average method from below).

Your `GrayScaler` class is serious about its grayscalin` powers and has three methods to turn a color into its monochromatic equivalent:
- lightness
- average
- luminosity
- custom

**Lightness**

The lightness method averages the most prominent and least prominent colors: `(max(R, G, B) + min(R, G, B)) / 2`.

**Average**

The average method simply averages the values: `(R + G + B) / 3`.

**Luminosity**

This method also averages the values, but it forms a weighted average to account for human perception. We’re more sensitive to green than other colors, so green is weighted most heavily. The formula for luminosity is `0.21 * R + 0.72 * G + 0.07 * B`

**Custom**

This method allows the user to pass in three floats to act as the weights in your formula: `w1 * R + w2 * G + w3 * B`

Here is some example usage to help you determine how to design your class:

```python

c1 = Color(255,0,0)
grayish = GrayScaler(c1)
gray1 = grayish.Average()
gray2 = grayish.Custom(.33,.44,.23)


grayish2 = GrayScaler() # defaults to black in the class if no color provided
grayish2.SetColor(255,192,203)
gray3 = grayish2.Luminosity()
```

Determine whether you would inherit from `Color`? Or use composition.

```python
"""
@Description: Gets an RGB color represented as a tuple, and converts it to a 
				gray scale equivalent based on chosen method.
@Methods:
    Lightness - as described above
    Average - as described above
    Luminosity - as described above
    Custom - as described above
    SetColor - Lets user change the color originally passed in.
"""
class GrayScaler(Object):













```
