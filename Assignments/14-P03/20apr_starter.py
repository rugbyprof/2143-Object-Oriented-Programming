#!/usr/bin/env python3

"""
Another intro to python lecture...

"""

import pygame

# example function / code block
def myprint(x,y):
    '''This method adds two things together and prints them out. 
    '''
    print (x+y)

# general stuff 
# varables and data types
age = 21

print(f"Bobs age = {age}")

# data types dont matter (don't have to declare)
x = 10
y = 90

myprint(x,y)

x = "hello "
y = "world"

myprint(x,y)

x = str(99.9)
y = " apples"

myprint(x,y)

# Data structures

# 1) lists 2) dictionary 3) tuples

L = [1,2,3,"hello", 44.5,[5,6,7,8],{"apples":56}]   # mutable (like an array but holds anything together)

# square matrix 3x3
M = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
]

array = [0,1,2,3,4,5,6,7,8,9]

for i in range(len(M)):
    for j in range(len(M[i])):
        print(M[i][j])

print(L)

print(L[5][3])

for item in L:
    print(item)

print("=================")

D = {
    "apples":99,
    "pears":67,
    "bananas":120,
    0:"fruit"
    }   # mutable  (like json or key value pairs)

print(D)
print(D[0])
print(D['pears'])


for key,value in D.items():
    #print(item,D[item])
    print(f"key:{key},value:{value}")

print("=================")

T = (3,4,5)   # immutable (used sets and such)

x,y,z = T

print(T)
print(T[0])
print(f"x:{x},y:{y},z:{z}")


print("=================")









