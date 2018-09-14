## Program 1 - Array Vector Class
#### Due: September 14<sup>th</sup> by Classtime

## Overview

- Write a class the will emulate (partially) a C++ vector. 
- Here is a good overview of a c++ vector: https://www.geeksforgeeks.org/vector-in-cpp-stl/
- What does this mean? Well lets compare the two:
    - `Arrays` allow us to store like items in contiguous memory locations.
    - `Vectors` do as well.
    - `Arrays` have a fixed size. Array of size 10, cannot store 11 items.
    - `Vectors` will grow to accommodate the new item.
    - `Arrays` use an integer index to access locations (slots or cells) in the array.
    - `Vectors` do as well, but they also have methods (`push`,`pop`) to add items (really `push_back` and `pop_back`). 
- Vectors do many other things (see above link) but we are only going to implement the basics for your first program. 

## Requirements

- Write a C++ class that (loosely) implements the functionality of a C++ vector using an array as your storage container.
- Your vector will only need to store integers at this time (we will fix that later).
- It must be variable size:
    - Initially, your array container should be sized at whatever size you see fit. However, allocating too much memory is a waste and you will lose points.
    - If an item is pushed onto a full array, you will automatically resize the array to `1.5` times its current size, to accommodate the new item.
    - If your array container becomes .40 full, you will shrink your container to half its size (unless your at the original allocated size).
        - For example, if you start off with a container of 25, you may go up to 37, 55, 82 , etc., but it's size will never go below 25.
- It must have `push_back` and `pop_back` implemented which adds an item to the end of the array and removes an item from the end of the array respectively.
    -  What would pushing or popping from the front of the array require?
-  Some other methods that might be helpful:
    -  void print(); // public
    -  int size(); // public
    -  double percentFull(); // private

## Starter Code

- [main.cpp](./main.cpp)
- [myVector.cpp](./myVector.cpp)
- [myVector.h](./myVector.h)

## Testing your code

- Write a program that creates an implementation of your vector class and runs the following tests on it:
    - Create instance of `myvector` of size 10 and immediately attempt to `pop_back` (remove from empty vector). 
        - Removing from an empty vector should return `false`.
    - Insert the values 13,31,73 into your vector. Print it out.
    - Insert 10000 items into your vector. Print the size of your vector.
    - Remove 9998 items from your vector. Print the size of your vector.
    - Print out your vector.

### Checklist

(NOT TOTALLY COMPLETE)

| #       | Item                                                                | Value           | Earned |
| :------ | :------------------------------------------------------------------ | --------------: | ------ |
| ***1*** | ***General***                                                       | **pass / fail** |        |
| -       | Github repository exists                                            |                 |        |
| -       | `assignments` folder exists in Repo                                 |                 |        |
| -       | `P01` folder exists in `assignments`                                |                 |        |
| -       | Your Code is commented.                                             |                 |        |
|         |                                                                     |                 |        |
| ***2*** | ***Files***                                                         | **0**           |        |
| -       | Class definition called `myvector.h` correctly created.             | -               |        |
| -       | Class implementation called `myvector.cpp` contains implementation. | -               |        |
| -       | `main.cpp` contains tests to show requirements were met.            | -               |        |
|         |                                                                     |                 |        |
| ***3*** | ***Class Container***                                               | **0**           |        |
| -       | Used an array as the container for the vector                       | -               |        |
| -       | Container grew at the appropriate time.                             | -               |        |
| -       | Container shrank at the appropriate time.                           | -               |        |
|         |                                                                     |                 |        |
| ***4*** | ***Class Methods***                                                 | **0**           |        |
| -       | pushBack method exists and works correctly                          | -               |        |
| -       | popBack method exists and works correctly                           | -               |        |
| -       |                                                                     | -               |        |
|         |                                                                     |                 |        |
| ***5*** | ***Tests***                                                         | **0**           |        |
| -       | Popping off empty vector doesnt crash .                              | -               |        |
| -       | Vector grows appropriately                                           | -               |        |
|         | Vector shrinks appropriately                                        | -               |         |                
|         | Output shows that program works appropriately.                       |                 |        |
|         |                                                                     |                 |        |
|         | Total:                                                              | **100**         |        |
