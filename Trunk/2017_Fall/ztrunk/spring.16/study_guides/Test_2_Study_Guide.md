##Question 1:

### Color Class

- Create a class called "Color" that will store a tuple of (r,g,b). 
- The tuple should be stored in a data member called color.
- The components of the color tuple should be stored in data members: red, green, blue as well 
- Add a __str__ method to print out the color class so it looks like: "(red: redVal, green: greenVal, blue: blueVal)"
- Here is some usage:

```python

c1 = Color((255,0,0))
print(c1.red)
#prints: 255

c1.blue = 255
print(c1)
#prints: (red: 255, green: 0, blue: 255)

c1.color = (0,0,0)
print(c1)
#prints: (red: 0, green: 0, blue: 0)

```

##Question 2:

Overload the addition operator so that we can add two colors. Adding colors is a pretty wierd experience, so we will create our own addition method. Basically we will average each color. 

For example:

```python

c1 = (255,255,255)
c2 = (0,0,0)
c3 = c1 + c2

print(c3)
#prints: (128,128,128)
```

##Question 3:

### Grayscale Class

This class will ***extend*** the color class.

So what is gray scale? Its where you take the 3 individual parts of a color and using those values you calculate a single value that will be assigned to each of the 3 components, making it some shade of gray.
 
For example here is red: `(0,255,0)` and here is the gray scale equivalent: `(85,85,85)` (using the average method from below).

Your `GrayScaler` class is serious about its grayscalin` powers and has three methods to turn a color into its monochromatic equivalent:
- lightness
- average
- luminosity
- custom

**Lightness**

The lightness method averages the most prominent and least prominent colors: `(max(R, G, B) + min(R, G, B)) / 2`.

**Average**

The average method simply averages the values: `(R + G + B) / 3`.

**Luminosity**

This method also averages the values, but it forms a weighted average to account for human perception. We’re more sensitive to green than other colors, so green is weighted most heavily. The formula for luminosity is `0.21 * R + 0.72 * G + 0.07 * B`

**Custom**

This method allows the user to pass in three floats to act as the weights in your formula: `w1 * R + w2 * G + w3 * B`

Here is some example usage to help you determine how to design your class:

```python

myColor = (255,0,0)
grayish = GrayScaler(myColor)
gray1 = grayish.Average()
gray2 = grayish.Custom(.33,.44,.23)


grayish2 = GrayScaler() # defaults to black in the class if no color provided
grayish2.SetColor(255,192,203)
gray3 = grayish2.Luminosity()
```

```python
"""
@Description: Gets an RGB color represented as a tuple, and converts it to a 
				gray scale equivalent based on chosen method.
@Methods:
    Lightness - as described above
    Average - as described above
    Luminosity - as described above
    Custom - as described above
    SetColor - Lets user change the color originally passed in.
"""
class GrayScaler(Color):













```
##Question 4:

Python does not always explicitly run the constructor of a parent class. How would we do this? And how can we pass parameters back to our parent class? Look at the code below, run it, then alter it to give an example of running a parents constructor and passing back parameters. You can make whatever alterations you want to get your point across.

```python
class A(object):

    def __init__(self):
        print("Constructor A was called")

class B(A):

    def __init__(self):
        print("Constructor B was called")

class C(B):

    def __init__(self):
        print("Constructor C was called")
        
x = C()
#What happens? Anything printed?
```


##Question 5:

Create a point class, line class, and a rectangle class. 
- A point is a tuple of two integers: (3,6)
- A line consists of two points: (3,6),(7,8)
	- Add a length method 
- A rectangle consists of two points as well, the upper right, and the lower left.
	- Add an area and perimeter method








## Question 6:

Remember exceptions? Looking at the example below answer a couple of questions:
- What kind of exception is this? 
- Does it have to specify the exception type?

```python
def no_return():
	print("I am about to raise an exception") 
	raise Exception("This is always raised") 
	print("This line will never execute") 
	return "I won't be returned"
```


## Question 7:

Look at the method below and fix it by adding a `try ... except` clause ensuring that:
- We don't divide by zero
- a and b are both integers

```python
def ratio(a,b):
	return a / b

```

## Question 8:

Describe to me a situation in which a `finally` clause would come in handy. We know that a finally clause will execute no matter what, but when is that good? Example code would be nice.


## Question 9:

This group of questions will all deal with a store that sells office supplies. Your going to extend the item class to create an inventory class, and then add some error handling. Obviously, we are over simplifying this for brevity.

### Part A:

Given the following class defining an office supply `item`:

```python

class item(object):
    def __init__(self,key,name,cost,amount):
        self.key = key				# Unique key for a candy
        self.name = name			# Name of candy
        self.cost = cost			# Cost per box or bag
        self.amount = amount			# Number in stock
        
C = item(3,"scissors",4.99,10)
    	
```

Add a __str__ method to print out the item so that `C` above would print out (notice the 3.99):

```
(id:3 , name:scissors , cost:4.99 , amount:10)
```

### Part B:

Create a class that either extends the `item` class OR uses composition to create the `inventory` class. Explain your method of choice.

- Call your class `inventory`.
- Use a dictionary to keep track of your office items.
- Minimum methods:
    - `AddItem(int key,string name,float price,int amount) `
        - adds an item(s) to your inventory
        - returns None
    - `SellItem(int key,int amount)` 
        - sells (subtracts) a `amount` of items from inventory. 
        - returns cost of selling that many item(s).

```python
a = item(1,"paper pad",3.99)
b = item(2,"tape",1.99)
c = item(3,"scissors",4.99)

print(a)
print(b)
print(c)

i = inventory()

i.addItem(a,35)
i.addItem(b,20)
i.addItem(c,35)

print(i.sellItem(2,4))

print(i)

# I implemented a string method for my inventory class (look below the output)
print(i)
```

Output:

```
(key:1 , name:paper pad , cost:3.99)
(key:2 , name:tape , cost:1.99)
(key:3 , name:scissors , cost:4.99)
7.96
35 (key:1 , name:paper pad , cost:3.99)
16 (key:2 , name:tape , cost:1.99)
35 (key:3 , name:scissors , cost:4.99)
```

Example string function for inventory class:

```python
    def __str__(self):
        val = ''
        for i in self.dict:
            val += str(self.dict[i])
            val += "\n"
            
        return val
```

### Part C

Add some exception checking to your inventory class to handle if a user tries to purchase more items than there is in inventory.

Bonus: Write your exception as it's own class (as described starting on page 108 in your text).


### Part D

Lets say I wanted to define a new type called a "case". A `case` of `items` holds multiples of the same type. It would (in addition to the attributes in `item`) keep track of:

- weight of case (in whatever system you wish lbs, kg, etc)
- discount (cost per case as a percent discount of the original price, like .22) 
    - The cost for a case of 'paper pads' that holds 48 would be 48 * 3.99 * .22
- amount per case (count of items in a case)

Create a class that either extends the `item` class OR uses composition to create the `case` class. Explain your method of choice.



## Question 10:

Modify the Account class from lecture so that it has a new attribute, transactions, that is a list keeping track of any transactions performed.

```python
class Account(object):
    """
    A bank account that allows deposits and withdrawals.
    """

    interest = 0.02

    def __init__(self, account_holder):
        self.balance = 0
        self.holder = account_holder

    def deposit(self, amount):
        """Increase the account balance by amount and return the
        new balance.
        """
        
        self.balance = self.balance + amount
        return self.balance

    def withdraw(self, amount):
        """Decrease the account balance by amount and return the
        new balance.
        """
        
        if amount > self.balance:
            return 'Insufficient funds'
        self.balance = self.balance - amount
        return self.balance
```

Some Account usage:

```python
eric_account = Account('Eric')
eric_account.deposit(1000000)   # depositing my paycheck for the week

print(eric_account.transactions)
# Prints: [('deposit', 1000000)]

eric_account.withdraw(100)      # buying dinner

print(eric_account.transactions)
# Prints: [('deposit', 1000000), ('withdraw', 100)]
```

## Question 11:

We'd like to be able to cash checks, so let's add a `deposit_check` method to our CheckingAccount class. It will take a `Check` object as an argument, and check to see if the `payable_to` attribute matches the CheckingAccount's holder. If so, it marks the Check as deposited, and adds the amount specified to the CheckingAccount's total.

Write an appropriate Check class, and add the `deposit_check` method to the CheckingAccount class. 
Use inheritance whenever possible.

```python
class CheckingAccount(Account):
    """A bank account that charges for withdrawals.

    >>> check = Check("Steven", 42)  # 42 dollars, payable to Steven
    >>> steven_account = CheckingAccount("Steven")
    >>> eric_account = CheckingAccount("Eric")
    >>> eric_account.deposit_check(check)  # trying to steal steven’s money
    The police have been notified.
    >>> eric_account.balance
    0
    >>> check.deposited
    False
    >>> steven_account.balance
    0
    >>> steven_account.deposit_check(check)
    42
    >>> check.deposited
    True
    >>> steven_account.deposit_check(check)  # can't cash check twice
    The police have been notified.
    """
    withdraw_fee = 1
    interest = 0.01

    def withdraw(self, amount):
        return Account.withdraw(self, amount + self.withdraw_fee)


class Check(object):
    "*** YOUR CODE HERE ***"
    
    
    
```

## Question 12:

```python
class Person(object):

    def __init__(self, name, age):
        self.name = name
        self.age = age

    def is_old(self):
        return self.age > 40

        
person = Person('G. H. Hardy', 70)  
print person.is_old() # Prints True
```

Write a `Student` class that extends the `Person` class and add a method: `is_honor_student` that would print `True` if the students gpa is greater than 3.0

```python
student = Student('G. H. Hardy', 70, 4.0)
print student.is_old()	# prints True
print student.is_honor_student()	# prints True
```

