A method (or message) in object-oriented programming is a procedure associated with an object. An object is made up of data and behavior, which form the interface that an object presents to the outside world. Data is represented as properties of the object and behavior as methods. For example, a Window object would have methods such as open and close, while its state (whether it is opened or closed) would be a property. 

Source: [ [1] ]

Basically, a method is just a type of function that is defined in a class definition.
Here's a simple example of some methods.

```python
class BankAccount(object):
    def __init__(self):
        pass
    
    def deposit(self):
        pass
    
    def withdraw(self):
        pass
```
In this example, deposit(), withdraw(), and even \__init\__() are considered methods.

### Difference between functions and methods in python
A method differs from a function only in two aspects:

* it belongs to a class and it is defined within a class
* the first parameter in the definition of a method has to be a reference "self" to the instance of the class
* a method is called without this parameter "self"

Source: [ [2] ]

### Types of methods
There are three main types of methods: 
* Accessor methods that are used to read data values of an object. 
* Mutator methods that are used to modify the data of an object.
* Manager methods that are used to initialize and destroy objects of a class, e.g. constructors and destructors.

Source: [ [1] ]

Here's an example of an accessor method.
```python
class BankAccount(object):
    def getBalance(self):
        return self.balance
```
As you can see, getBalance() only retrieves the current balance and doesn't edit any data members.

Here's an example of a mutator method.
```python
class BankAccount(object):
    def deposit(self, amount):
        self.balance += amount
```
As you can see, deposit() is adding to the value of the balance, thus it is modifying(or mutating) a data member.

For examples of manager methods, see the wiki pages [Constructor] and [Destructor].

Sources:

1. https://en.wikipedia.org/wiki/Method_(computer_programming)
2. http://www.python-course.eu/object_oriented_programming.php

[1]: https://en.wikipedia.org/wiki/Method_(computer_programming)
[2]: http://www.python-course.eu/object_oriented_programming.php
[Constructor]: https://github.com/rugbyprof/2143-ObjectOrientedProgramming/wiki/Constructor
[Destructor]: https://github.com/rugbyprof/2143-ObjectOrientedProgramming/wiki/Destructor