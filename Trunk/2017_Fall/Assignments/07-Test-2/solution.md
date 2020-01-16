 

***1)*** Place the appropriate letter in the space next to its corresponding definition. 

<> | Word | Ans | Definition
------- | ------- | ------- | -------
A. | Attribute: | E | A user-defined type. A class definition creates a new class object.
B. | Child Class: | D | An object that contains information about a user-defined type. The class object can be used to create instances of the type.
C. | Class Attribute: | K | An object that belongs to a class.
D. | Class Object: | A | One of the named values associated with an object. Also referred to as instance variables.
E. | Class: | N | A function that is defined inside a class definition and is invoked on instances of that class
F. | Constructor: | O | A diagram that shows objects, their attributes, and the values of the attributes.
G. | Deep Copy: | T | The object a method is invoked on.
H. | Composition: | F | A special method always named init that handles initializing the values of attributes in an object, and any other setup required when a new instance is created.
I. | Has-A Relationship: | M | Method names that begin and end with __; they are implicitly and automatically invoked by the Python interpreter.
J. | Inheritance: | P | A language that provides features, such as user-defined classes and method syntax, that facilitate object-oriented programming.
K. | Instance: | Q | A style of programming in which data and the operations that manipulate it are organized into classes and methods. 
L. | Is-A Relationship: | H | An object that is stored as an attribute of another object.
M. | Magic Methods: | I | The relationship between two classes where instances of one class contain references to instances of the other.
N. | Method: | L | The relationship between a child class and its parent class.
O. | Object Diagram: | J | The ability to define a new class that is a modified version of a previously defined class.
P. | Object-Oriented Language: | R | The class from which a child class inherits.
Q. | Object-Oriented Programming: | B | A new class created by inheriting from an existing class; also called a “subclass.”
R. | Parent Class: | S | To copy the contents of an object, including any references to embedded objects; implemented by the copy function in the copy module.
S. | Shallow Copy: | G | To copy the contents of an object as well as any embedded objects, and any objects embedded in them, and so on; implemented by the deepcopy function in the copy module.
T. | Subject: | C | An attribute associated with a class object. Class attributes are defined inside a class definition but outside any method.

***2)*** Create a point class, line class, and a rectangle class.
- •	A point is a tuple of two integers: (3,6)
    - o	Add a move point method that receives: dx,dy which are the amounts of change to apply to the point. Example: (-2,2) would turn the point (3,6) into (1,8).
    - o	Overload the addition operater to add two points together:
        - (4, 4) +  (1, 2)  = ( 5, 6 )
- •	A line consists of two points: (3,6),(7,8)
    - o	Add a length method that returns the length of a line.
- •	A rectangle consists of two points as well, the upper right, and the lower left.
    - o	Add an area and perimeter method
    - o	Overload the addition operator to add rectangles A and B. This method would take min and max of all the points in A and B, and create a single rectangle that encompasses both A and B.

#### Answer:
```python
class Point(object):
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y
        
    def move(self,dx,dy):
        self.x += dx
        self.y += dy
        
    def __str__(self):
        return "(%d , %d)" % (self.x,self.y)
        
    def __add__(self,rhs):
        return Point(self.x + rhs.x,self.y + rhs.y )
    
class Line(object):
    def __init__(self,p1=None,p2=None):
        if p1 == None:
            self.p1 = Point(0,0)
        else:
            self.p1 = p1
            
        if p2 == None:
            self.p2 = Point(0,0)
        else:
            self.p2 = p2
    
    def __str__(self):
        return "[%s , %s]" % (self.p1,self.p2)
    
    def length(self):
        return math.sqrt((self.p1.x - self.p2.x)**2 + (self.p1.y - self.p2.y)**2)
        
class Rectangle(object):
    def __init__(self,ul=None,lr=None):
        self.ul = ul
        self.lr = lr
        l1 = Line(Point(self.ul.x,self.ul.y),Point(self.lr.x,self.ul.y))
        l2 = Line(Point(self.lr.x,self.lr.y),Point(self.lr.x,self.ul.y))
        self.w = l1.length()
        self.h = l2.length()
        
    def __add__(self,rhs):
        min_x = min([self.ul.x,self.lr.x,rhs.ul.x,rhs.lr.x])
        max_x = max([self.ul.x,self.lr.x,rhs.ul.x,rhs.lr.x])
        min_y = min([self.ul.y,self.lr.y,rhs.ul.y,rhs.lr.y])
        max_y = max([self.ul.y,self.lr.y,rhs.ul.y,rhs.lr.y])
        return Rectangle(Point(min_x,max_y),Point(max_x,min_y))
    
    def area(self):
        return self.w * self.h
        
    def perimeter(self):
        return self.w*2 + self.h*2 
```


 
***3)*** Given an email class to represent an email: 
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

#### Answer:
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
 
 


***4)*** Write a function called pigify that turns a string of words into piglatin.
- 'y' is a vowel if it is not the first letter of a word
- If word begins with a vowel, append 'hay'
- If word starts with 'q', assume followed by 'u'; move 'qu' to the end, and append 'ay'
- If word begins with a consonant, move all consonants up to first vowel to end and add 'ay'
- Precondition: input contains only (lowercase) letters

#### Answer:
```python
def pigify(w): 
""" Returns: copy of w converted to Pig Latin 
"""
def pigify(w):
  vowels = ['a','e','i','o','u']
  words = w.split()
  new = ""
  for w in words:
    if w[0] in vowels:
      w = w +'hay'
    elif w[0] == 'q':
      w = w[2:] +'quay'
    else:
      i = 0
      while i < len(w):
        if w[i] in vowels + ['y'] and i > 0:
          break
        i += 1
      w = w[i:]+w[:i]+'ay'
    new += w 
    new += " "
  return new

print(pigify("hello this is your quirky doctor calling you to say bye yes we do"))
```
>Prints: `ellohay isthay ishay ouryay irkyquay octorday allingcay ouyay `

***5)*** Write a function that receives a list of integers along with an A and a B. Replace all the A's in the list with whatever value B is.
- Example: replace([1,2,3,1], 1, 4) = [4,2,3,4].
- Precondition: All values in the list, and A,B will be integers.

#### Answer:
```python
def replace(thelist,a,b):  
"""Returns: A COPY of the list with all occurrences of a replaced by b.  
"""
copy = thelist[:]
for i in range(len(copy)):
    if copy[i] == a:
        copy[i] = b
return copy
```
