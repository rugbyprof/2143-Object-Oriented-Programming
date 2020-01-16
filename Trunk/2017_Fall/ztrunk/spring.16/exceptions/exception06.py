"""
The problem with the previous example is that it will catch any type of exception.
What if we were writing some code that could raise both a TypeError and a ZeroDivisionError? 
We might want to catch the ZeroDivisionError, but let the TypeError propagate to the console. 
"""

def funny_division(anumber):
       try:
           return 100 / anumber
       except ZeroDivisionError:
           return "Silly wabbit, you can't divide by zero!"

print(funny_division(0))#
print(funny_division(50.0))
print(funny_division("hello"))
