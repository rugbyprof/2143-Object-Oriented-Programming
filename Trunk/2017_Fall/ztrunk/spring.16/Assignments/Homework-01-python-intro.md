# Homework 1 - Getting your python feet wet

### Requirements
- Add an `add` method to the simple fraction class below
- If you were to run the following code snippet:

```python
a = fraction(1,2)
b = fraction(4,5)
c = a + b
print(c)
```
it would print out:
```
1 3/10
```
it should not print out:

```
13/10
```

- This means we need to handle:
    - a `whole number` portion of a fraction.
    - ability to reduce 

### Deliverables

- A python file called `fraction_class.py` containing your added method(s).
- This file should be pushed to your github repo (I'll show you how on Thursday).
- Execution of the program should print something similar to the following:

```
1/2 + 3/4 = 1 1/4
```
- Prompting the user for input is not necessary (since not discussed) but not discouraged either
- File is due on github by ***Tuesday February 2<sup>nd</sup>*** by class time. 

## Starter Code

```python

class fraction(object):
    def __init__(self,n=None,d=None):
        self.numerator = n
        self.denominator = d
        
    def __str__(self):
        return "%s / %s" % (self.numerator , self.denominator)
        
    def numerator(self,n):
        self.numerator = n 
        
    def denominator(self,d):
        self.denominator = d
        
    def __mul__(self,rhs):
        x = self.numerator * rhs.numerator
        y = self.denominator * rhs.denominator
        return fraction(x,y)
   
if __name__ == '__main__':
    a = fraction(1,2)
    b = fraction(4,5)
    c = a * b
    print(c)
```
