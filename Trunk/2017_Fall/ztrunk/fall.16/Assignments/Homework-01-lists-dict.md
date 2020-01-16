## LIST AND DICTIONARIES
Due: September 19<sup>th</sup> by class time.

What to turn in:
- A python document with all your functions and answers from below.
- Use comments where and when needed to explain your answers.
- A comment block at the top should look like this:

```python
"""
Name: Your Name
Email: your.email@somewhere.com
Assignment: Homework 1 - Lists and Dictionaries
Due: 19 Sep @ 1:00 p.m.
"""

```

- Make sure you clearly mark each answer appropriately: A, B, C, D ... J
- Additionally, create a folder called `Assignments` in your github repo.
- Place a copy of your document in this folder and call it `homework-01.py`
- Push your new folder and document to github.

## 1 Lists

A list is an ordered collection of values. You can have a list of integers, a list of strings, or even a mix of any types of values you want; this means that the list need not be homoge- nous. You can add and remove items to and from a list them by calling list methods, and you can access elements through the index notation. Let's look at an example:

```python
fantasy_team = []
fantasy_team.append("frank gore")
print(fantasy_team)
# Prints: ['frank gore']

fantasy_team.append("calvin johnson") 
print(fantasy_team[1])
# Prints: calvin johnson

fantasy_team.remove("calvin johnson") 
fantasy_team[0] = "aaron rodgers"
print(fantasy_team)
# Prints: ['aaron rodgers']
```

Lists can be created using square braces, and likewise, their elements can be accessed via square braces. Just like tuples, lists are zero-indexed. Let's try out some basics.

#### 1.1 Basics
---
**`A:`** What would Python print?

```python
a = [1, 5, 4, 2, 3] 
print(a[0], a[-1])
# Prints: ??

a[4] = a[2] + a[-2]
Print(a)
# Prints: ??

print(len(a))
# Prints: ??

print(4 in a)
# Prints: ??

a[1] = [a[1], a[0]]
print(a)
# Prints: ??

```

#### 1.2 List methods

---

In addition to the indexing operator, lists have many mutating methods, some examples of which are listed here:
 
1. `append(el)` → Adds `el` to the end of the list
2. `index(el)` → Returns the index of `el` if it occurs in the list, otherwise errors. 
3. `insert(i, el)` → Insert `el` at index `i`
4. `remove(el)` → Removes the first occurrence of `el` in list, otherwise errors
5. `sort()` → Sorts elements of list in place

List methods are called via 'dot notation', as in:

```python
fruits = ['apple', 'pineapple']
fruits.append('banana')
```

**`B:`** Write a function that removes all instances of an element from a list.

```python
def remove_all(el, lst):
"""Removes all instances of el from lst. 
Given: x = [3, 1, 2, 1, 5, 1, 1, 7]
Usage: remove_all(1, x)
Would result in: [3, 2, 5, 7]
"""
   pass





```
 
**`C:`** Write a function that takes in two values, x and y, and a list, and adds as many y's to
the end of the list as there are x's. Do not use the built-in function count.

```python
def add_this_many(x, y, lst):
""" Adds y to the end of lst the number of times x occurs in lst. 
Given: lst = [1, 2, 4, 2, 1]
Usage: add_this_many(1, 5, lst)
Results in: [1, 2, 4, 2, 1, 5, 5]
"""
    pass



```

#### 1.3 Slicing
---

Like tuples, lists also support slicing notation, allowing you to retrieve multiple elements of a list at once. Slicing a list returns a new list. Slicing has the following syntax:

```python 
lst[start:end:interval]
```

where start, end, and interval are integers. The slice includes the element at start and every interval elements up to but not including the element at end. It is legal to omit one or more of start, end, and incr; they default to 0, `len(lst)`, and 1, respectively. Start and end can be negative, meaning you count from the end.

```python
a = [0, 1, 2, 3, 4, 5, 6]
print(a[1:4])
# Prints: [1, 2, 3]
print(a[1:6:2])
# Prints: [1, 3, 5]
a[:4] # equivalent to a[0:4]
# Prints: [0, 1, 2, 3]
a[3:] # equivalent to a[3:len(a)]
# Prints: [3, 4, 5, 6]
a[1:4:] # equivalent to a[1:4:1] or a[1:4] 
# Prints: [1, 2, 3]
a[-1:]
# Prints: [6]
```

**`D:`**  What would Python print?

```python
a = [3, 1, 4, 2, 5, 3]
print(a[:4])
# Prints: ??

print(a)
# Prints: ??

print(a[1::2])
# Prints: ??

print(a[:])
# Prints: ??

print(a[4:2])
# Prints: ??

print(a[1:-2])
# Prints: ??

print(a[::-1])
# Prints: ??
```


#### 1.4 For loops

---

There are two main methods of looping through lists.

- `for el in lst` → loops through the elements in lst
- `for i in range(len(lst))` → loops through the valid, positive indices of lst

If you do not need indices, looping over elements is usually more clear. Let's try this out.

**`E:`**  Let's reverse Python lists in place, meaning mutate the passed in list itself, instead of returning a new list.
We didn't discuss this in class directly, so feel free to use google. Why is the "in place" solution preferred?

```python
def reverse(lst):
""" Reverses lst in place. 
Given: x = [3, 2, 4, 5, 1] 
Usage: reverse(x)
Results: [1, 5, 4, 2, 3]
"""
    pass





```

**`F.`** Write a function that rotates the elements of a list to the right by `k`. Elements should not ”fall off”; they should wrap around the beginning of the list. `rotate` should return a new list. To make a list of `n` `0's`,you can do this: `[0] * n`

```python
def rotate(lst, k):
""" Return a new list, with the same elements of lst, rotated to the right k.
Given: x = [1, 2, 3, 4, 5]
Usage: rotate(x, 3)
Results: [3, 4, 5, 1, 2]
"""
    pass





```


## 2 Dictionaries

Recall that dictionaries are data structures that map keys to values. Dictionaries are usually unordered (unlike real-world dictionaries) – in other words, the key-value pairs are not arranged in the dictionary in any particular order. Let's look at an example:

```python
superbowls = {'joe montana': 4, 'tom brady':3, 'joe flacco': 0}
print(superbowls['tom brady'])
# Prints: 3

superbowls['peyton manning'] = 1
print(superbowls)
# Prints: {'peyton manning': 1, 'tom brady': 3, 'joe flacco': 0, 'joe montana': 4}

superbowls['joe flacco'] = 1
print(superbowls)
# Prints:{'peyton manning': 1, 'tom brady': 3, 'joe flacco': 1, 'joe montana': 4}
```

Dictionaries are indexed with similar syntax as sequences, only they use keys, which can be any immutable value, not just numbers. Dictionaries themselves are mutable; we can add, remove, and change entries after creation. There is only one value per key, however, in a dictionary (we call this _injective_ or one-to-one).

**`H:`**  Continuing from above, what would Python print?

```python
print('colin kaepernick' in superbowls)
#Prints: ??

print(len(superbowls))
#Prints: ??

print(superbowls['peyton manning'] == superbowls['joe montana'])
#Prints: ??

superbowls[('eli manning', 'giants')] = 2
print(superbowls)
#Prints: ??

superbowls[3] = 'cat'
print(superbowls)
#Prints: ??


superbowls[('eli manning', 'giants')] =  superbowls['joe montana'] + superbowls['peyton manning']
print(superbowls)
#Prints: ??

superbowls[['steelers', '49ers']] = 11
print(superbowls)
#Prints: ??


```

Dictionaries in general can be arbitrarily deep, meaning their values can be dictionaries themselves. Let's get practice traversing these deep structures. To do so, we'll need to know a couple more things about dictionaries.
To iterate over a dictionary's keys:

`for k in d.keys(): ...`

and to remove an entry:

`del dictionary[key]`


**`I:`**  Given a dictionary replace all occurrences of x as the value with y.

```python
def replace_all(d, x, y):
"""Replaces all values of x with y. 
Given: d = {1: {2:3, 3:4}, 2:{4:4, 5:3}} 
Usage: replace_all(d,3,1)
Results: {1: {2: 1, 3: 4}, 2: {4: 4, 5: 1}} 
"""
    pass







```

**`J:`**  Given a (non-nested) dictionary delete all occurences of a value. You cannot delete items in a dictionary as you are iterating through it (google :) ).

 ```python
def rm(d, x):
"""Removes all pairs with value x. 
Given:  d = {1:2, 2:3, 3:2, 4:3}
Usage:  rm(d,2)
Results: {2:3, 4:3}
"""
    pass 







```
