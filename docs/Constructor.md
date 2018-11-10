
###Constructors

A constructor is a method called in class objects. Constructors instantiate the object and initialize anything that is declared within this method. Every class needs a constructor, even if it is a default constructor.
Constructors can either accept parameters, or not. Parameters are not needed for it to be a constructor, but depending on the program, parameters may be needed. 

Source: [1](http://www.dummies.com/how-to/content/how-to-create-a-constructor-in-python.html)

```python
class Class_name(object):
     def __init__(self):
          pass
```
The above code is a simple class with a constructor that has no parameters.

```python
class Class_name(object):
     def __init__(self, itemName, itemNumber):
          pass
```
The above code is a simple class with a constructor that has parameters itemNumber and itemName.

Sources:

1. <http://www.dummies.com/how-to/content/how-to-create-a-constructor-in-python.html>
