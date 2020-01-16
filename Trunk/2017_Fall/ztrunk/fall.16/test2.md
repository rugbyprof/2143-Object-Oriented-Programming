Test 2 - OOP 
==========

#### Question 1:  Color Class
- Create a class called "Color" that will store values for an RGB color. RGB stands for red, green, and blue.
- Add a __str__ method to print out the color class so it looks like: "(R: redVal, G: greenVal, N: blueVal)"
- The user can initialize their color in a few different ways.
- Here is some usage:

```python

c1 = Color((255,0,0))
print(c1)
# prints: (R: 255, G: 0, B: 0)

c2 = Color(255,255,0)
print(c2)
# prints: (R: 255, G: 255, B: 0)

c3 = Color()
print(c3)
#prints: (red: 0, green: 0, blue: 0)
```

The following may help you create your color constructor:

```
>>> A = 255
>>> type(A)
<type 'int'>
>>> A is int
False
>>> type(A) is int
True
>>> B = (255,255,255)
>>> type(B)
<type 'tuple'>
>>> type(B) is tuple
True
```



----

#### Question 2:  Polymorphism

Overload the addition operator so that we can add two colors. Adding colors is not an exact science, so we will create our own addition method.  Add each of the values together, then modulo the result by 255. 

For example:

```python

c1 = Color(100,128,110) # 100 + 64 = 164
c2 = Color(64,162,64)   # 128 + 162 = 35
                        # 110 + 64 = 174
c3 = c1 + c2

print(c3)
#prints: (R: 164,G: 35,B: 174)
```

----

#### Question 3:  Gray Scale Class

This class will ***extend*** the color class.

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

myColor = (255,0,0)
grayish = GrayScaler(myColor)
gray1 = grayish.Average()
gray2 = grayish.Custom(.33,.44,.23)


grayish2 = GrayScaler() # defaults to black in the class if no color provided
grayish2.SetColor(255,192,203)
gray3 = grayish2.Luminosity()
```

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
class GrayScaler(Color):













```

----

#### Question 4:  Student Class

 Write a class to represent a student at school. The class needs to keep track of the following items:

- First Name (e.g Sue Ann)
- Last Name (e.g. Smith)
- Id Number (e.g. 123456789)
- Courses taken with grades (e.g. courseId : CMPS 2143, hours : 3, grade : 4) 

> Note: (A=4, B=3, C=2, D=1, F=0)

An example list of course may be:

> courseId: CMPS 2143, hours : 3, grade : 4 
> courseId: ENGL 1113, hours : 3, grade : 3 
> courseId: MATH 1604, hours : 4, grade:  3
> courseId: POLS 1333, hours : 3, grade : 2
> courseId: EXPH 1102, hours : 2, grade : 4 


Your class will need to calculate a students Grade Point Average. A GPA is the total number of hours taken divided into total grade points earned. So an 'A' in a 3 hour class = 12 grade points (`4*3=12`). Getting a 'C' in a 4 hour course only gives you 8 grade points (`2 * 4 = 8`)

| Hours  | * |  Grade   | = |  Grade Points   |
|:------:|---|:--------:|---|:-------------:|
|  3 | * | 4 | = | 12  |
|  3 | * | 3 | = |  9  |
|  4 | * | 3 | = | 12  |
|  3 | * | 2 | = | 6  |
|  2 | * | 4 | = | 8  |
| **15** |    |   |   | **47** | 

GPA = 47 / 15 = **3.13**

Example Usage:

```python
s1 = Student("Sue" , "Smith" , "123456789")
s1.addCourse("CMPS 2143", 3, 4) 
s1.addCourse("MATH 1604" , 4, 3)
s1.addCourse("ENGL 1113", 3, 3)
grade = s1.getGrade("MATH 1604")
print(grade)
# prints: B
gpa = s1.calcGPA()
print(gpa)
# prints: 3.66

```

#### Question 5:  Binary Search

**A)** Run a binary search on the following values looking for key=37. Show the index values for `first` `mid` and `last` at each iteration.


| 0 | 1 | 2 | 3 | 4	| 5 | 6 | 7	| 8 | 9 | 10| 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 3 | 5| 7 | 11	| 13 | 17 | 19	| 23| 29| 31 | 37 | 41 | 43 | 47 | 53 | 59 |


**B)** What is the worst case search time for binary search on an unordered list?


#### Question 6:  Frequency Analysis

Write a class called `FreqAnalysis` that will do a word frequency analysis on a book. You can assume that the book has had all punctuation removed. Your class should count the number of unique words and be able to return the **n**<sup>th</sup> most frequent word. 

**Given**:

> The function `getGutenberg('moby_dick.txt')` will magically return a list of words from the book Moby Dick without punctuation.

Using your new magical function, and the usage below, complete the creation of our frequency analysis class.

```python
freq = FreqAnalysis('moby_dick.txt')
most = freq.getnth(3)
print(most)
# ('and', 6434)

x = freq.occurs('barwait')
print(x)
# 1 

x = print(freq.totalWords()
print(x)
# 20211

```

<sup>Note: class functions don't print, unless that is their sole purpose.</sup>

----

#### Question 7:  Traversing Data Structures

Given: 

```
grades = {
    'Bob' : { "A": [98,99,99,90,91], "B" : [88,89,87,81], "C" : [70,72,71,77,75]},
    'Sue' : { "A": [92,99,91], "B" : [88,84,87,86,82], "C" : [70,74,71]},
    'Ann' : { "A": [93,94], "B" : [88,89,87,83,82], "C" : [70,72,71,73,75]},
    'Bill' : { "A": [96,99,95], "B" : [88,82,87,86], "C" : [70,72,71,77,71,75,75]}
}
```

Print out the name, and count of each grade type for each student:

```
Bob: A's = 5 , B's = 4 , C's = 5
Bob: A's = 3, B's = 5 , C's = 3
Bob: A's = 2 , B's = 5 , C's = 5
Bob: A's = 3 , B's = 4 , C's = 7
```

