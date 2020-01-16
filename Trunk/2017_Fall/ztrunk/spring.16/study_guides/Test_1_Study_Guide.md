
##Question 1:

Consider this program:
```python
L = [4, 10, 8]
x = L.sort()
L.append(20)
L2 = L[1:]
```

Fill in the Python Shell output after this program has executed.
```
>>> x

```

```
>>> L


```


```
>>> id(L) == id(L2)


```

##Question 2:

See the phone pad below:

![](https://s3.amazonaws.com/f.cl.ly/items/2O371F2t1U422A3m340S/225px-telephone-keypad.jpg)

Write a function called `alphaToNumeric` that receives an 'alphanumeric' phone number and returns a numeric (9 digit) phone number. For example: XH0EZQI70A = 9403974702. You can solve this anyway you want. If the input to the function is not 9 characters/digits return `None`. The list below is a hint at one way to approach the problem.



```python
alpha = ['ABC', 'DEF', 'GHI', 'JKL', 'MNO', 'PQRS', 'TUV', 'WXYZ']

```

##Question 2a:

Would the previous function solution have been better with a dictionary? Explain.

##Question 3:

Write a function called `guessAnswer` that will guess the correct answer and return the number of guesses that were necessary. This function receives 3 values: 
- `low`: lowest value that answer could be (inclusive)
- `high`: highest value that answer could be (inclusive)
- `answer`: the correct answer

Your function should find the answer in less than O(N) time. Meaning you shouldn't loop from low -> high testing every value. 

##Question 3a

Try turning your `guessAnswer` function into a class that actually runs a game. 

##Question 4a:

#### Airplane & Flight Class

- Develop two classes to keep track of airplanes and flights.
- Here is the header and docstring for class Airplane.

```python
class Airplane:
"""
Information about a particular airplane including the model, the serial
number, the number of seats, and the number of miles travelled.
"""
```


####Constructor

Complete the `__init__` method for our Airplane class:

```python
def __init__(self, plane_model, serial_num, num_seats, miles_travelled):
""" 
@Description:
	Record the airplane's model plane_model, serial number serial_num, the
	number of seats, and the distance travelled miles_travelled.
@params: 
	plane_model (string) - type of plane (e.g. Boing 747)
	serial_num (int) - 
	num_seats (int) - 
	miles_travelled (float) - total number of miles plane has travelled.
@Returns: None
"""












```

Here is some usage and its output:

```python
airplane = Airplane('Boeing 747', '19643', 366, 45267.7)

print(airplane.model)
# Prints: 'Boeing 747'
print(airplane.serial)
# Prints: '19643'
print(airplane.seats)
# Prints: 366
print(airplane.miles)
# Prints: 45267.7
```

##Question 4b:

#### \_\_str__ Method

Write a `__str__` method for  class Airplane that returns strings of this form: 'Airplane(Boeing 747, 19643, 366, 45267.7)'



#### Adding a Method to Airplane Class

- Below is a description for method `log_trip` in our class `Airplane`. 
- Write the body of the method.
- Add an example that creates an Airplane object, logs a trip of 1000.0 miles, and shows that
those miles have been logged. 

```python
def log_trip(self, num_miles):
""" 
@Description: Adds n miles to the planes total miles flown where n > 0
@Param: num_miles (float) - number of miles to add to the total
@Returns: None
"""










```

Example Here:
```
















```

##Question 4c:

#### Overloading an Operator

Write an `__eq__` method in class `Airplane` that compares two Airplane objects to see if they are equal.

Consider two Airplanes equal if they have the same serial number. 



##Question 4d:

#### Class Flight

```python
""" 
@Description: Information about an airplane flight. 

"""
class Flight:

    def __init__(self, plane):
    """ 
    @Description: Create a Flight with an empty passenger list on airplane plane.
    @Param: plane (Airplane) - the airplane in which to keep track of flight information.
    @Returns: None
"""










```

Example Usage:
```python
a = Airplane('Boeing 747', '19643', 366, 45267.7)
f = Flight(a)
print(f.airplane)
# Print: 'Airplane(Boeing 747, 19643, 366, 45267.7)'
print(f.passengers)
#Prints: []
```

##Question 4e:

#### Add Method to Flight Class

Complete method add in class Flight.

```python
def add(self, passenger):
""" 
@Description: If there are still seats available on this flight, add passenger to the
passenger list. 
@Params: passenger (string) - passenger name
@Returns: (bool) True iff passenger is added to this flight.













```

Example Usage:
```python
a = Airplane('Cessna 150E', '9378', 1, 824.8)
f = Flight(a)
print(f.add('Myrto'))
#Prints: True
print(f.add('Jen'))
#Prints: False
```

-- 

##Question 5:
#### Dictionary Class

Write a class called `wordDictonary` that represents an actual dictionary. Your class should contain the following methods:
- `loadDictionary` : 
    - reads a file that contains `word: definition` 
    - a word may occur more than once (same word alternate definition)
    - you should be able to hold all definitions
- `updateDictionary`:
    - a method that lets you add a word:definition to the class
- `findWord`:
    - this method receives a word, and returns all definitions that correspond to it. 
- `removeWord`:
    - this method lets you remove a word from the dictionary. 
    
##Question 6:

### Median Trickery

- Complete the function using this algorithm: 
    - continually remove the largest and smallest values from the list and return either the last value (if there is only one left) or the average of the two last values (if there are two left).
    - Do not sort the list, and don't use any for loops in your solution.
    - Functions `max` and `min` may be helpful, as well as one or more list methods.

```python
def myMedian(L):
""" 
@Description: Return the median of the numbers in L.
@Params: L (list)
@Returns: median (int)
"""
	# Start with a copy of the list so we don’t modify the original.
	L = L[:]









```
##Question 7:

### Coffee Class 
A coffee shop lets customers purchase coffee with pre-loaded electronic cards. They can reload their cards
by specifying an amount of money to be added. Each card is also programmed with a default dollar amount
that gets reloaded when the purchaser does not specify an amount.

#### Defining the class
- Write the constructor with the appropriate data members needed to keep track of 
    - defualt reload amount
    - current amount on the card
- Write the reload method that allows the user to reload the card with a specified amount.
- Write the default reload method that will reload the card with the default amount.
- Write the buy_coffee method, which has a parameter indicating the amount paid.
    - If the card has enough money to cover the purchase, the amount is deducted.
    - If the card does not have enough money to cover the purchase, the balance is unchanged. 
    - Return True iff the card had enough money to cover the purchase.

There may some additional things you need to add to your class depending on the user stories (the way
the class is used) below.

#### Using the class
- Create a card for Karen with an initial balance of $100 and a default reload value of $50.
    - e.g.(card_for_karen = Card("Karen", 100, 50))
- Have Karen buy 25 coffees at a cost of $2.50 each.
- Create a card for Sven with an initial balance of $50 and a
    - default reload value of $20.
- Have Sven buy a fancy coffee at a cost of $5.
- Reload Karen’s card with her default reload value.
- Have Sven put an additional $5.75 on his card.
- Print the owner and balance of both cards.


##Question 8:
#### Unique Dictionary

Use a dictionary to help you create a list of unique values. Lets say I asked you to create a list of _`N`_ integers where _`0 <= N <= 99999`_ and any value of _`N`_ occurs only once within the list. You cannot use the `in` operator to check and see if the value is already in the list. You also can't use sets like so: `myNums = list(set(myNums))`. So, use a dicionary to help keep your items unique. 

##Question 9:

#### Password File

You decide to save all your passwords in files, one password per file. You then decide you want to update your 6-character MWSU Portal password, but you don’t remember which of your password files you saved it in. Luckily, this is the only 6-character password you have so you decide to write a function to find the password and change it.
Your code runs, but the function’s body contains four bugs which will result in the function execution not matching its docstring description. In the space provided, rewrite the buggy lines with the bugs fixed. Do not add or remove any lines.

```python
def change_password(files_list, new_password):
    """ (list of str, str) -> str
    Preconditions:
    (1) files_list is not empty.
    (2) Each file in files_list contains one single-line password.
    (3) All files in files_list contain passwords of different lengths.
    (4) Your 6-character password is guaranteed to be in one of these files.
    In the appropriate file from files_list, replace your 6-character password
    with new_password, and return your old password.
    """
```

**Code**

If you think a given line contains a bug, rewrite it. Otherwise leave it blank.

```python
found = True
for filename in files_list[:-1]:
    passwd_file = open(filename, 'r')
    first_line = passwd_file.read()
    password = first_line.strip("2")
    if password == 6:
        passwd_file.close()
        passwd_file = open(filename, 'w')
        passwd_file.write(new_password)
        found = True
    passwd_file.close()
    if found:  # This is correct. Do not modify.
        return password
```

##Question 10:
#### Simple Encryption

Two friends like to send messages to each other, but they don’t want anyone else to read the messages. To keep the messages private, they change each letter in the original message to a different letter of the alphabet (by adding an integer value to it). For every letter, they both know which letter will be substituted for it, which is called an encoding. The message will contain only lowercase letters. It will not contain whitespace, digits, or punctuation. 

The receiver of a secret message doesn’t want to convert it back to the original message by hand. Instead, that person asks you to write a function to do it. In other words, were creating a shift cipher where if the "shift" was 4, then:

`A = E, B = F, ... Y = C, Z = D`

Define a function that given a secret message and the encoding used, returns the original message. 

Example:
```python
"""
@Params:
    message (string) : The encrypted message. Example: SST ERH TCXLSR EVI EAIWSQI
    shift (int): The shift amount. Example 4
@Returns:
    (string) decrypted message
"""
def Decrypt(message,shift):



```
##Question 11:

#### List practice

- What are the two ways to add something to a list? How are they different?
- What are the two ways to remove something from a list? How are they different?
- What is the difference between a list and a tuple?
- In the Python shell, do the following:
    - Define a variable named states that is an empty list
    - Add Iowa to the list
    - Now add Nebraska to the end of the list
    - Define a variable states2 that is initialized with New York, Vermont, and New Hampshire
    - Add Maine to the beginning of the list
    - Add Massachusetts so that it is the third state in the list
    - Add Pennsylvania to the list so that it appears before New York. Do this as if you DO NOT KNOW where New York is in the list
        - HINT: See what `states2.index(“New York”)` does. What can you conclude about what `listname.index(item)` does?
    - Remove the 5th state from the list and print that state’s name

##Question 12:

#### Grayscale Class

Create a class called `GrayScaler` that will convert an rgb value to grayscale by some chosen method. Your class should expect an rgb value that will be represented as a `tuple` looking something like this `(128,45,100)` where the values in order are red,green,blue and must be between 0-255 inclusive. So `(0,0,0)` and `(255,255,255)` are ok and are black and white respectively. 

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
class GrayScaler(object):




















```

##Question 13a:

Here is the header and two methods for class Restaurant. 
```python
class Restaurant:
    """ 
    Information about a particular restaurant including its name,
    price range, the types of cuisines it serves, and reviews.

	@Description:
		Records the restaurant's name, price range, and types of cuisines. 
		It will also hold multiple reviews for the restaurant.
		There are initially no reviews of this restaurant.
	@Params:
	    name 			(string) - name of restaurant
	    price_range 	(string) - how expensive in dollar signs from 1-5 '$'
	    cuisine_list  (list) - list of types of food served
	"""
    def __init__(self, name, price_range, cuisine_list):









```

**Example Usage:**
```
    >>> rest = Restaurant('Dumplings R Us', '$$', ['Chinese', 'Japanese'])
    >>> rest.name
    'Dumplings R Us'
    >>> rest.price_range
    '$$'
    >>> rest.cuisine_list
    ['Chinese', 'Japanese']
    >>> rest.reviews
    []
    """
```
##Question 13b:
    
Assuming you implemented the restaurant class properly, now make a class to hold a review.

```python
"""
@Description:
    Creates a review that will contain the following information:
    Author (string) - name of person who wrote the review
    Rating (string) - 1-5 stars as a rating system
    Recommends (bool) - Would recommend this restaurant
"""










```

**Example Usage:**
```
rest = Restaurant('Mexican Grill', '$$$', ['Mexican'])
Print(rest.reviews)
Output: []

review = Review('Susur Lee', '*****', True)
rest.add_review(review)


# Notice that by printing the first review we get a formatted statement!
# Thats a __str__ method being implemented for the review class.
Print(rest.reviews[0])
Output: 'Susur Lee gives a **** star rating and recommends you do eat there'

```

##Question 13c:

Implement the `__str__` method for the review class.

```















```





##Question 13d:
Complete method recommended_percentage in class Restaurant:

```python
"""
@Description:
    This method returns a percentage based on the number of stars in your restaurant. 
    1 star = 10% tip and 5 star = 50% tip. So it will return a recommended tip based on the bill total
    and the number of stars.
@Param:
    total (float) - bill total
@Returns:
    tip (float)
"""
def recommended_percentage(self,total):










```
