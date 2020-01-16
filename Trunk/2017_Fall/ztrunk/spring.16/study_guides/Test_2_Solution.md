1. Use pencil to answer all questions
2. Do not cram too many answers on a sheet of paper.
- Draw a line between each answer.
- Write neatly and legibly.
- Place your name on all pages turned in.
- Your test should be in ascending order when turned in. 
- Failure to comply with these instructions WILL result in a loss of 1 letter grade.

##Question 1:

Given a list: L = [2,46,9,12,32,43,77,9,7,1]

The following code will print out the values of L.

```python
for i in L:
	print(i)
```

Complete the same task using `range` and `len`.

### Answer:

```python
L = [4,3,55,6,5,44,3,4,3,55,66,77]

for i in range(len(L)):
    print(L[i])
```


## Question 2

### Color Class

- Create a class called "Color" that will store a tuple of (r,g,b). 
- The constructor should accept 3 parameters, red,green,blue.
- Those three values should be stored in a single data member (a tuple) called color.
- Add a __str__ method to print out the color class so it looks like: "(red: redVal, green: greenVal, blue: blueVal)"
- Here is some usage:

```python

purple = color(160,32,240)
print(purple)
# prints:
(red: 160 , green: 32 , blue: 240)

```

Your answer should contain a complete class that would fulfill the usage example.

### Answer:
```python
class color(object):
    def __init__(self,r,g,b):
        self.color = (r,g,b)
    
    def __str__(self):
        c = self.color
        return "(red: %d , green: %d , blue: %d)" % (c[0],c[1],c[2])
        
```

## Question 3

Overload the addition operator so that we can add two colors. Adding colors is a pretty weird experience, so we will create our own fake method of addition. For each color component, add them together and take the minimum of the added value or 255. 

For example:

- c1 = color(160,32,240)
- c2 = color(178,34,34)

- Add the   reds and take the minimum of 160 + 178 or 255 (ans: 255)
- Add the greens and take the minimum of  32 +  34 or 255 (ans: 66)
- Add the  blues and take the minimum of 240 +  34 or 255 (ans: 255)

```python
c1 = color(160,32,240)
c2 = color(178,34,34)
c3 = c1 + c2
print(c3)
#prints: (red:255 , green:66, blue:255)
```

Your answer should only contain the method to overload the addition operator (as if it was written within the color class from question 1).

### Answer:
```python
def __add__(self,rhs):
    c1 = self.color
    c2 = rhs.color
    return color(min(c1[0]+c2[0],255),min(c1[1]+c2[1],255),min(c1[2]+c2[2],255))

c1 = color(160,32,240)
c2 = color(178,34,34)
c3 = c1 + c2
print(c3)
```
### Notes:
A lot of you returned `(r,g,b)` which is NOT a type `color`, it's a primitive data type: `tuple` which if you tried to add it to another color, would fail. From the usage, you should have figured out that `c3` needed to be of type `color`.


## Question 4

The "grayscale" value for a color is when you take the 3 individual parts of a color (r,g,b) and convert those values to a single value that will be assigned to each of the 3 components, making it some shade of gray.
 
For example here is red: `(0,255,0)` and here is the gray scale equivalent: `(85,85,85)` (using the average method from below).

Your `GrayScaler` class is not too serious about its grayscalin` powers and only implements two methods to turn a color into its monochromatic equivalent:
- ***average***
    - The average method simply averages the values: `(R + G + B) / 3`.
- ***custom***
    - This method allows the user to pass in three floats to act as the weights in your formula: `w1 * R + w2 * G + w3 * B`

- Write a complete python class called `GrayScaler` meeting the requirements from above.
- Your `GrayScaler` class should not change the color that it was orignally created with. 
- Both the `average` and the `custom` methods should simply return a new `color` instance with the calculated grayscale values.
 
 
Here is some example usage to help you determine how to design your class:

```python

myColor = (160,32,240)
grayish = GrayScaler(myColor)
gray1 = grayish.Average()
gray2 = grayish.Custom(.30,.50,.20)
print(gray1)
#prints: (red:144 , green:144, blue:144)

print(gray2)
#prints (red:112 , green:112, blue:112)

```

### Answer:
```python
# Don't inherit from color ... write your own string method.

class GrayScaler1(object):
    def __init__(self,c):
        self.color = c
        
    def average(self):
     	c = self.color
        avg = (c[0]+c[1]+c[2]) / 3
        return color(avg,avg,avg)
        
    def custom(self,w1,w2,w3):
        c = self.color
        w = (c[0]*w1 + c[1] * w2 + c[2] * w3)
        return color(w,w,w)
        
    def __str__(self):
        c = self.color
        return "(red: %d , green: %d , blue: %d)" % (c[0],c[1],c[2])

myColor = (160,32,240)
gray = GrayScaler(myColor)
print(gray)
avg = gray.average()
print(avg)
cust = gray.custom(.2,.5,.3)
print(cust)

# Inheriting from color doesn't give us a lot to "extend" aside from the "__str__" method. But
# it doesn't hurt much and may be useful if the color class were to add some functionality.

class GrayScaler2(color):
    def __init__(self,c):
        self.color = c

    def average(self):
        c = self.color
        avg = (c[0]+c[1]+c[2]) / 3
        return color(avg,avg,avg)

    def custom(self,w1,w2,w3):
        c = self.color
        w = (c[0]*w1 + c[1] * w2 + c[2] * w3)
        return color(w,w,w)
        
        
myColor = (160,32,240)
gray = GrayScaler(myColor)
print(gray)
avg = gray.average()
print(avg)
cust = gray.custom(.2,.5,.3)
print(cust)
```

### Notes:

- I messed up on the line `myColor = (160,32,240)`. It should have read `myColor = color(160,32,240)`, but since it didn't I altered the answer to match ... well the question. 
- A lot of you ignored the fact that a `tuple` was passed in (see usage) and instead you assumed r,g,b (three values). You need to pay attention to detail. 


## Question 5

Given the "Pet" class below. Write a "Dog" class extending the Pet class. 


```python
class Pet(object):

    def __init__(self, name, species):
        self.name = name
        self.species = species

    def getName(self):
        return self.name

    def getSpecies(self):
        return self.species

    def __str__(self):
        return "< %s is a %s >" % (self.name, self.species)
        
```

Your "Dog" class should add an additional method:
```
def makesSound(self):
	return "Bark"
```

Here is some usage:

```python
myDog = Dog("Fido")
print(myDog)
#prints < Fido is a Dog >
```

Your answer should contain a complete class with the appropriate code to extend the "Pet" class.

### Answer:
```python
class Pet(object):

    def __init__(self, name, species):
        self.name = name
        self.species = species

    def getName(self):
        return self.name

    def getSpecies(self):
        return self.species

    def __str__(self):
        return "< %s is a %s >" % (self.name, self.species)

class Dog(Pet):
	def __init__(self,name):
		super().__init__(name,"Dog")
	
	def makesSound(self):
		return "Bark"
		
myDog = Dog("Fido")
print(myDog)
print(myDog.makesSound())
```

## question 6

Given the following snippet (as a reminder of how to open files):

```python
# Get a filename from user
filename = input("Enter a file name: ")

#open the file for reading
f = open(filename, "r")

```

- Write a function that would safely test to see if a file exists. 
- Your function would receive a filename, then attempt to open the file. 
- If it can open the file, then immediately close the file and return true. 
- If you can't open the file return false. 
- Hint:
	- Don't overthink, not looking for anything fancy.
    - You will need a `try ... except`
    - You don't have to use one of the exception types (like file exists error). 

Your answer is a function that returns true or false.

### Answer:
```python
def exists(filename):
	try:
		f = open(filename,"r")
		f.close()
		return True
	except:
		return False
```

## Question 7

Describe to me a situation in which a `finally` clause would come in handy. We know that a finally clause will execute no matter what, but when is that good? Example code would be nice.

Your answer is a short explanation with example code to back up your answer.


### Answer:

```python
def can_open(name):
    result = {}
    try:
         file = open(name, 'w')
         result = {'message':"File opened",'success':True}
    except IOError:
         result = {'message':"File failed to open",'success':False}
    else:
         file.close()
    finally:
        return result

print(can_open("temp3.txt"))
```


## Question 8

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

### Answer:
```python

class Email(object):
	def __init__(self, msg, subj, sender, receiver):
		self.message = msg
		self.subject = subj
		self.sender = sender 	#email address
		self.receiver = receiver #email address

# Using a dictionary		
class EmailLogger(object):
	def __init__(self):
		self.emails_sent = {}
		self.emails_received = {}
		
	def add(self,email):
		if not email.sender in self.emails_sent:
			self.emails_sent[email.sender] = []
		self.emails_sent[email.sender].append(email)
		
		if not email.receiver in self.emails_received:
			self.emails_received[email.receiver] = []
		self.emails_received[email.receiver].append(email)		
			
	def get_sent_by(self,sender):
		return self.emails_sent[sender]
		
	def get_received_by(self,receiver):
		return self.emails_received[receiver]

# Using a list
class EmailLogger(object):
    def __init__(self):
        self.emails = []

    def add(self,email):
        self.emails.append(email)

    def get_sent_by(self,sender):
        temp = []
        for e in self.emails:
            if e.sender == sender:
                temp.append(e)
        return temp

    def get_received_by(self,receiver):
        temp = []
        for e in self.emails:
            if e.receiver == receiver:
                temp.append(e)
        return temp
		
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
print(list1)
# list1 = [Email2,Email3]

list2 = Logger.get_received_by("sue@gmail.com")
print(list2)
# list2 = [Email1,Email2,Email4]
```
### Notes:

- Remember a list is similar to an array, so you have access to each element via some index, but you don't have direct access to each email based on some key (like in a dictionary).
- Below are two dictionarys that hold all the emails sent / received using email as a key:

```python
emails_sent['joe@yahoo.com'] =   [('fake message 1' , 'fake subject 1' , 'joe@yahoo.com' , 'sue@gmail.com')]
emails_sent['bill@yahoo.com'] =  [('fake message 2' , 'fake subject 2 ', 'bill@yahoo.com ', 'sue@gmail.com'),
				  ('fake message 3 ', 'fake subject 3' , 'bill@yahoo.com' , 'joe@yahoo.com')]
emails_sent['jon@hotmail.com'] = [('fake message 4' , 'fake subject 4' , 'jon@hotmail.com' , 'sue@gmail.com')]

emails_received['sue@gmail.com'] = [('fake message 1' , 'fake subject 1' , 'joe@yahoo.com' , 'sue@gmail.com'),
				    ('fake message 2' , 'fake subject 2' , 'bill@yahoo.com ', 'sue@gmail.com'),
				    ('fake message 4' , 'fake subject 4' , 'jon@hotmail.com' , 'sue@gmail.com')]
emails_received['joe@yahoo.com'] = [('fake message 3' , 'fake subject 3' , 'bill@yahoo.com' , 'joe@yahoo.com')]				
```

- So if I print `emails_sent['bill@yahoo.com']` I get a list of each email bill sent.
- What about a list? Well theres no reason to split emails "sent" vs "received" becuase a list doesn't provide key access, it's simply a collection that uses a numerical index to access locations. Python does provide methods to "find" items in a list, but they still require a traversal and are O(n) access time, where as  a dictionary has O(1) access time.

```python
emails_sent = [ ('fake message 1' , 'fake subject 1' , 'joe@yahoo.com' , 'sue@gmail.com'),
		('fake message 2' , 'fake subject 2' , 'bill@yahoo.com' , 'sue@gmail.com'),
		('fake message 3' , 'fake subject 3' , 'bill@yahoo.com' , 'joe@yahoo.com'),
                ('fake message 4' , 'fake subject 4' , 'jon@hotmail.com' , 'sue@gmail.com')]
```
- So to find any emails sent by `bill` I would need to "find" the emails that matched 'bill@yahoo.com'. 
- Both methods work, and each has merit. 
