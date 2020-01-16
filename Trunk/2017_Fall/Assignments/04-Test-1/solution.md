# 2143 OOP :: Test 1 
***Spring 17***
>
- Show up to class on time. 
- Bring a pencil, pens not allowed.
- Bring a blue book.
- Answer items in order in your bluebook (not on actual test).
- Do not start an answer if it may continue onto the next page. Think ahead.
- Write neatly, legibly, and indent code appropriately. 
- Failure to follow instructions will cost you a deduction of 1 letter grade.
- The bottom line is don't make me work to find or decipher your answers.
- There are 95 possible points. To make it an even 100, you can choose the question that you want to assign the additional 5 points to. You can turn a 10 point question into a 15 pointer, or a 20 pointer into a whopping 25! Choose wisely! 

-----

## Question 1:
***(20 Pts)***

Define the following terms:

- **A.** Polymorphism

>Generally, the ability to appear in many forms. A programming language's ability to process objects differently depending on their data type or class. More specifically, it is the ability of methods / functions to act differently based on the data types involved. One prime example is the overloading of operators. The operation will behave differently based on the data type involved. 

- **B.** Encapsulation

>Encapsulation boils down to hiding or limiting access to data or data manipulators in a class. Private methods and members vs Public methods and members.

- **C.** Inheritance vs Composition (define both, explain difference)

>Inheritance: Taking on the properties of existing object by using the existing objects definitions as the basis for its own class definition. 

```python

class someclass(otherclass):
    def __init__(self):
        super().__init__()
        # we now have access to all of 'otherclass's' "stuff" by inheriting from otherclass
        
```

>Composition: Aggregating objects together by making some objects attributes of other objects.

```python

class someclass(object):
    def __init__(self):
        other = otherclass()
        #we now have an instance of otherclass making it an attribute of this class.
        
```

>So Inheritence would "extend" a base obect gaining access to its methods and data members, while composition simply 
>would create instances of another object within its own class definition and use it in that way.

- **D.** Immutable vs Mutable 

>Objects whose value can change are said to be mutable; objects whose value is unchangeable once they are created are called immutable.
>Dictionaries and Lists are mutable, while Tuples are immutable.

-----

## Question 2:
***(10 Pts)***

***Given:***

```python
students = {
    'Bob' : { "grades": [98,99,99,90,91,88,89,87,81,70,72,71,77,75] , "year": "Sophomore"},
    'Sue' : { "grades": [92,99,91,88,84,87,86,82,70,74,71], "year": "Junior"},
    'Ann' : { "grades": [93,94,88,89,87,83,82,70,72,71,73,75], "year": "Sophomore"},
    'Bill' : { "grades": [96,99,95,88,82,87,86,70,72,71,77,71,75,75], "year": "Senior"},
    'Jon' : { "grades": [99,99,95,87,82,80,80,70,70,71,70,60,50,67], "year": "Freshman"}
}
```

Complete the function:

```python

def grade_avg(students):
"""
@Description:
    This function receives a dictionary as depicted above with between 1 and N students. The key is the students
    name and has an associated dictionary that lists 1 to N grades for that student along with their classification. 
@Returns: 
    This function should calculate the average score for each classification and return a dictionary with the same
    structure as: {'Freshman': 77, 'Senior': 81, 'Junior': 84, 'Sophomore': 83}
"""
  ans = {}
  for k,v in students.items():
    if not v['year'] in ans:
      ans[v['year']] = []
    ans[v['year']].extend(v['grades'])
    
  for k,v in ans.items():
    ans[k] = round(sum(v) / len(v),2)
    
  return ans
```

-----


## Question 3:
***(10 Pts)***

In this question I want to you leverage the power of unique keys to create a histogram of word occurences. Count the number of occurrences of words in a string using a dictionary as your container.  Assume there is a string called `words` that is space delimited and has NO punctuation. 

Complete the function:

```python

def unique_words(words):
"""
@Description:
    Count the number of occurrences of words in a string using a dictionary as your container.
    words = "the the and the and and and the boy boy the and boy boy and and and end"
@Returns: 
    A dictionary with the count for each unique word: {'the': 5,'and': 8,'boy': 4,'end': 1}
"""
  dict = {}
  for word in words.split():
    if not word in dict:
      dict[word] = 0
    dict[word] += 1
    
  return dict
```

-----

## Question 4:
***(10 Pts)***

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
  while len(L) > 2:
    pop(L.index(max(L)))
    pop(L.index(min(L)))
  if len(L) == 2:
    return (L[0]/L[1]) / 2
  else:
    return L[0]
```
-----

## Question 5:
***(15 Pts)***

Write a `fraction` class that overloads the `addition` and `multiplication` operators. Make sure you implement the `str` method so a fraction prints out correctly.

```python
  def gcd(self,x, y):
      while y != 0:
          (x, y) = (y, x % y)
      return x
      
  class Fraction(object):

      def __init__(self,n=1,d=1):
          self.num = n
          self.den = d
          self.__reduce()

      def __str__(self):
          return "%d / %d" % (self.num,self.den)

      def __reduce(self):
          thegcd = gcd(self.num,self.den)
          self.num /= thegcd
          self.den /= thegcd


      def __mul__(self,rhs):
          return Fraction(self.num * rhs.num,self.den*rhs.den)

      def __add__(self,rhs):
          den = self.den * rhs.den
          num = (self.num * rhs.den) + (rhs.num * self.den)
          if(num == den):
              return 1
          else:
              return Fraction(num,den)
```

-----

## Question 6:
***(10 Pts)***

```python
import random
def make_random_ints_no_dups(num, lower_bound, upper_bound):
"""
  - Generate a list containing num random ints between lower_bound and upper_bound. 
  - upper_bound is an open bound.
  - The result list cannot contain duplicates.
"""
  res = []
  for i in range(num):
    r = random.randint(lower_bound,upper_bound)
    while r in res:
      r = random.randint(lower_bound,upper_bound)
    res.append(r)
  return res
```

-----

## Question 7:
***(20 Pts)***

Create a new class called `SMS_store`. The class will manage SMS messages, similar to an inbox or outbox on a cellphone:

```python
message_box = SMS_store()
```

- This store can hold multiple SMS messages.
- Each message will be represented as a tuple: ***`(has_been_viewed, from_number, time_arrived, text_of_SMS)`***
- The object should provide these methods:

```python
class sms_store(object):

    def __init__(self):
      self.messages = []
      
    def add_new_arrival(from_number, time_arrived, text_of_SMS)
      """
      - Makes new SMS tuple, inserts it after other messages in the store. 
      - When creating this message, its has_been_viewed status is set False.
      """
      self.messages.append((False,from_number, time_arrived, text_of_SMS))

    def message_count()
      """
      - Returns the number of sms messages in my_inbox
      """
      return len(self.messages)
      
    def get_unread_indexes()
      """
      - Returns list of indexes of all not-yet-viewed SMS messages
      """
      L=[]
      i=0
      for m in self.messages:
        if not m[0]:
          L.append(i)
        i = i + 1
        
      return L
      
    def get_message(i)
      """
      - Return (from_number, time_arrived, text_of_sms) for message[i]
      - Also change its state to "has been viewed".
      - If there is no message at position i, return None
      """
      if i >= len(self.messages):
          return None
      else:
          old = self.message[i]
          new = (True,old[1],old[2],old[3])
          self.messages[i] = new
      return new
      
    def delete(i)
      """
      - Delete the message at index i
      """
      del self.messages[i]
      
    def clear()
      """
      - Delete all messages from inbox
      """
      self.messages = []
      
```



