## Porgram 1 - Stack Upgrade
#### Due: 09-15-2020 (Thursday @ 9:30 a.m.)


### Overview

In [Lecture 2](../../Lectures/02-L02/array_based_stack.cpp) we wrote an array based stack, but didn't implement any checks for popping an empty stack, or overflowing our array data structure. If we wrote a list based implementation we wouldn't have to worry about it getting full, but we chose array so that's an issue. 

This is a pretty simple assignment in which you need to fix the existing `Stack` class and add the following functionality:

### Empty Stack

- If a `Pop` method is called when the stack is empty, simply print: "Error: Stack empty!" and return a `-1`.
- We have to return some integer because our method is defined as such, so lets use `-1` for now. I will show you a better technique for achieving this in a much cleaner manner. 

### Full Stack

- This one is a little tougher to implement. Because we are not simply going to print "Error: Stack full!". We are going to **resize** the stack!
- When a user (you) try's to push onto a full stack, you will do the following:
  - Allocate new memory double the size of the original array.
  - Copy each stack value over to the new array.
  - Point the array pointer `S` to the new array.
  - Delete the old array.

- Likewise, when the user starts popping items off the stack, and the stack gets below half full, we need to reduce the size of the stack by half.
- Be careful since a brand new stack is already below half full! So you only want to reduce a stacks size after it has been doubled at least once.


### Input File

- The input file will have between `1 - N` commands where `N` will be no bigger than `100000`. 
- The file is formatted like:

```txt
push x
pop
```
- Where **pushes** have a value to push 
- And **pops** do not

## Output

### Screen Output

- You should print your name and assignment data as the first part of your output:
```txt
Name: Latesha Smith
Program: P01
Date: 15 Sep 2020

```

- Every time your stack resizes you should print out the action and the stack size.
- For example `+` sign implies growing and `-` implies shrinking:
  
```txt
+ : 10 -> 20
+ : 20 -> 40
+ : 40 -> 80
- : 80 -> 40
.
.
.
etc.
```

### File Output

- Create an output file that contains the following:
  - Stack starting size
  - Largest stack size
  - Ending stack size

```txt
Name: Latesha Smith
Program: P01
Date: 15 Sep 2020

Start size: 10
Max size: 655360
Ending size: 10240
```


### Deliverables

- Rename the original file from [L03](../../Lectures/03-L03/resize_array.cpp) to `main.cpp`
- Create a folder in your `Assignments` folder called `p01`.
- Place your commented `main.cpp` file into this `p01` folder.
- Place all input files and output files created and or used in this folder as well 
- Create a banner with **P01** as part of the title (see [HERE](../../Resources/03-Banner/README.md))
- Bring a print out of your **code** and and **output file** to class.
- Banner is stapled with your code so its the top and only visible page. Basically a cover sheet.
- Put your code on the front desk at the beginning of class. Example below:
  
```txt
Banner
Code
Output File
```
- If your papers are not there at the beginning of class they are late. Sorry.