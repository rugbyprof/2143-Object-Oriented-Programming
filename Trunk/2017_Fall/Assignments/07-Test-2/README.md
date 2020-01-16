Test 2 Study Guide
==================

## Q1

Read the following: [Inheritance](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/blob/master/ztrunk/fall.16/inheritence_explanation.md)

Also, go look at this: https://inst.eecs.berkeley.edu/~cs61a/fa14/lab/lab06/


## Q2

- ***class:***
    - A user-defined type. A class definition creates a new class object.
- ***class object:***
    - An object that contains information about a user-defined type. The class object can be used to create instances of the type.
- ***instance:***
    - An object that belongs to a class.
- ***attribute:***
    - One of the named values associated with an object. Also referred to as instance variables.
- ***method:***
    - A function that is defined inside a class definition and is invoked on instances of that class.
- ***object diagram:***
    - A diagram that shows objects, their attributes, and the values of the attributes.
- ***subject:***
    - The object a method is invoked on.
- ***constructor:***
    - A special method always named __init__ that handles initializing the values of attributes in an object, and any other setup required when a new instance is created.
- ***magic methods:***
    - Method names that begin and end with __; they are implicitly and automatically invoked by the Python interpreter.
- ***object-oriented language:***
    - A language that provides features, such as user-defined classes and method syntax, that facilitate object-oriented programming.
- ***object-oriented programming:***
    - A style of programming in which data and the operations that manipulate it are organized into classes and methods. Also referred to as OOP.
- ***embedded (object) (aka composition):***
    - An object that is stored as an attribute of another object.
- ***HAS-A relationship:***
    - The relationship between two classes where instances of one class contain references to instances of the other.
- ***IS-A relationship:***
    - The relationship between a child class and its parent class.
- ***inheritance:***
    - The ability to define a new class that is a modified version of a previously defined class.
- ***parent class:***
    - The class from which a child class inherits.
- ***child class:***
    - A new class created by inheriting from an existing class; also called a “subclass.”
- ***shallow copy:***
    - To copy the contents of an object, including any references to embedded objects; implemented by the copy function in the copy module.
- ***deep copy:***
    - To copy the contents of an object as well as any embedded objects, and any objects embedded in them, and so on; implemented by the deepcopy function in the copy module.
- ***class attribute:***
    - An attribute associated with a class object. Class attributes are defined inside a class definition but outside any method.


## Q3

### Candy Class

Create a set of classes that represent the following:

- A bag/box of candy
- A case of the above
- Inventory of our candy

Determine whether to use inheritence or composition as the relationship between classes. Use the information given below to guide your class creation:

- ***Candy Class*** 
    - Attributes
        - key
        - name of candy
        - bag or box
        - num items per bag or box
        - cost per item
        - cost per bag or box
    - Methods
        - ?
- ***Case Class***
    - Attributes
        - weight
        - number of bags or boxes
        - cost per case as a discount percentage (e.g. .22)
    - Methods
        - ?
- ***Inventory Class***
    - Attributes
        - uses a dictionary to track items or cases of items
    - Methods:
        - `AddItem(int key,string name,float price,int amount)`
            - adds an item(s) to your inventory
            - returns None
        - `SellItem(int key,int amount)`
            - sells (subtracts) a amount of items from inventory.
            - returns cost of selling that many item(s).
        
## Q4

Create a `point class`, `line class`, and a `rectangle class`. 

- A point is a tuple of two integers: `(3,6)`
    - Add a move point method that receives: *dx*,*dy* which are the amounts of change to apply to the point. Example: *(-2,2)* would turn the point *(3,6)* into *(1,8)*.
- A line consists of two points: `(3,6),(7,8)`
    - Add a length method that returns the length of a line.
- A rectangle consists of two points as well, the upper right, and the lower left.
    - Add an area and perimeter method 

## Q5

Given an email class to represent an email: 
```python
class Email(object):
	def __init__(self, msg, subj, sender, receiver):
		self.message = msg
		self.subject = subj
		self.sender = sender 	#email address
		self.receiver = receiver #email address
```

- Write a class called "EmailLogger" that will keep track of all emails sent and received by each user. 
- Do you need to extend the Email class? Or use composition.
- Create 2 containers: `emails_sent` and `emails_received` that would let you obtain a list of emails when you pass in an email address.
- The method `get_sent_by` would receive an email address as input and return a list of emails sent by that user.
- The method `get_received_by` would receive an email address as input and return a list of emails received by that user. 

Usage:
```
Logger = EmailLogger()

Email1 = Email("fake message 1","fake subject 1","joe@yahoo.com","sue@gmail.com")
Logger.add(Email1)

Email2 = Email("fake message 2","fake subject 2","bill@yahoo.com","sue@gmail.com")
Logger.add(Email2)

Email3 = Email("fake message 3","fake subject 3","bill@yahoo.com","joe@yahoo.com")
Logger.add(Email3)

Email4 = Email("fake message 4","fake subject 4","jon@hotmail.com","sue@gmail.com")
Logger.add(Email4)


list1 = Logger.get_sent_by("bill@yahoo.com")
# list1 = [Email2,Email3]

list2 = Logger.get_received_by("sue@gmail.com")
# list2 = [Email1,Email2,Email4]
```

Your answer should be a complete class that would fulfill the usage example above.

## Q6
Write a function called `pigify` that turns a string of words into piglatin.
- 'y' is a vowel if it is not the first letter of a word 
- If word begins with a vowel, append 'hay'
- If word starts with 'q', assume followed by 'u'; move 'qu' to the end, and append 'ay'
- If word begins with a consonant, move all consonants up to first vowel to end and add 'ay'
- Precondition: input contains only (lowercase) letters

```python
def pigify(w):
""" Returns: copy of w converted to Pig Latin
"""
 
 
 
 
 
 ```

## Q7
Write a function that receives a list of integers along with an `A` and a `B`. Replace all the `A's` in the list with whatever value `B` is.

- Example: replace([1,2,3,1], 1, 4) = [4,2,3,4].
- Precondition: All values in the list, and A,B will be integers.

```python
def replace(thelist,a,b):
 """Returns: A COPY of thelist with all occurrences of a replaced by b.
 """
 
 
 
 
 ```
