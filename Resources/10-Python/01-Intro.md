## Print

To print a string, just write:

```python
print "This line will be printed."
```

## Indentation
Python uses indentation for blocks, instead of curly braces. Both tabs and spaces are supported, but the standard indentation requires standard Python code to use four spaces. For example:

```python
x = 1
if x == 1:
    # indented four spaces
    print "x is 1."
```

## Variables and Types
Python is completely object oriented, and not "statically typed". You do not need to declare variables before using them, or declare their type. Every variable in Python is an object.

This tutorial will go over a few basic types of variables.

#### Numbers
Python supports two types of numbers - integers and floating point numbers. (It also supports complex numbers, which will not be explained in this tutorial).

To define an integer, use the following syntax:
```python
myint = 7
```

To define a floating point number, you may use one of the following notations:

```python
myfloat = 7.0
myfloat = float(7)
```

#### Strings
Strings are defined either with a single quote or a double quotes.

```python
mystring = 'hello'
mystring = "hello"
```

The difference between the two is that using double quotes makes it easy to include apostrophes (whereas these would terminate the string if using single quotes)

```python
mystring = "Don't worry about apostrophes"
```

There are additional variations on defining strings that make it easier to include things such as carriage returns, backslashes and Unicode characters. These are beyond the scope of this tutorial, but are covered in the Python documentation.

Simple operators can be executed on numbers and strings:

```python
#Adding Numbers
one = 1
two = 2
three = one + two

#Adding Strings = concatenation & overloading or polymorphism!
hello = "hello"
world = "world"
helloworld = hello + " " + world
```

Assignments can be done on more than one variable "simultaneously" on the same line like this

```python
a, b = 3, 4

```

Mixing operators between numbers and strings is not supported:

```python
# This will not work!
print one + two + hello
```

## Lists

Lists are very similar to arrays. They can contain any type of variable, and they can contain as many variables as you wish. Lists can also be iterated over in a very simple manner. Here is an example of how to build a list.

```python
mylist = []
mylist.append(1)
mylist.append(2)
mylist.append(3)
print(mylist[0]) # prints 1
print(mylist[1]) # prints 2
print(mylist[2]) # prints 3

# prints out 1,2,3
for x in mylist:
    print x
```

```python
L = ['yellow', 'red', 'blue', 'green', 'black']

print(L)
#prints: ['yellow', 'red', 'blue', 'green', 'black']
```

#### Accessing / Indexing

```python
print(L[0])
# prints 'yellow'
```

#### Slicing

```python
L[1:4]  #returns ['red', 'blue', 'green']
L[2:] 	#returns ['blue', 'green', 'black']
L[:2] 	#returns ['yellow', 'red']
L[-1]  	#returns 'black'
L[1:-1] #returns ['red', 'blue', 'green']
```

#### Length 
number of items in list

```python
len(L)  # returns 5
```

#### Sorting 

sorts the list

```python
sorted(L) # results in ['black', 'blue', 'green', 'red', 'yellow']
```

#### Append 

append to end of list

```python
L.append("pink")

print(L)
# prints ['black', 'blue', 'green', 'red', 'yellow', 'pink']
```

#### Insert

insert into list

```python
L.insert(0, "white")
print(L)
# prints ['white', 'black', 'blue', 'green', 'red', 'yellow', 'pink']
```

#### Extend

grow the list

```python
L.extend(L2)
```

#### Remove - remove first item in list with value "white"
```python
L.remove("white")

print(L)
returns: ['black', 'blue', 'green', 'red', 'yellow', 'pink']
```

#### Delete

Remove an item from a list given its index instead of its value

```python
del.L[0]

print(L)
# prints['blue', 'green', 'red', 'yellow', 'pink']
```

#### Pop

Remove last item in the list

```python
L.pop()  # returns 'pink'
```

Remove indexed value from list

```python
L.pop(1) # returns 'green'  
```

#### Reverse 

reversing the list

```python
L.reverse()
```

#### Count

Search list and return number of instances found

```python
L.count('red')
```

Keyword "in" - can be used to test if an item is in a list

```python
if 'red' in L:
    print("list contains", 'red')
```

For-in statement - makes it easy to loop over the items in a list

```python
for item in L:
    print item

L = ['red', 'blue', 'green']
for col in L:
    print col
```

## Basic Operators
This section explains how to use basic operators in Python.

#### Arithmetic Operators

Just as any other programming languages, the addition, subtraction, multiplication, and division operators can be used with numbers.
```python
number = 1 + 2 * 3 / 4.0
```

Try to predict what the answer will be. Does python follow order of operations?

Another operator available is the modulo (%) operator, which returns the integer remainder of the division. dividend % divisor = remainder.

```python
remainder = 11 % 3
```

Using two multiplication symbols makes a power relationship.

```python
squared = 7 ** 2
cubed = 2 ** 3
```

#### Using Operators with Strings
Python supports concatenating strings using the addition operator:

```python
helloworld = "hello" + " " + "world"
```

Python also supports multiplying strings to form a string with a repeating sequence:

```python
lotsofhellos = "hello" * 10
```

#### Using Operators with Lists

Lists can be joined with the addition operators:

```python
even_numbers = [2,4,6,8]
odd_numbers = [1,3,5,7]
all_numbers = odd_numbers + even_numbers
```

Just as in strings, Python supports forming new lists with a repeating sequence using the multiplication operator:

```python
print [1,2,3] * 3
```

## String Formatting

Python uses C-style string formatting to create new, formatted strings. The `%` operator is used to format a set of variables enclosed in a `tuple` (a fixed size list), together with a format string, which contains normal text together with "argument specifiers", special symbols like `%s` and `%d`.

Let's say you have a variable called "name" with your user name in it, and you would then like to print out a greeting to that user.

```python
# This prints out "Hello, John!"
name = "John"
print "Hello, %s!" % name
```

To use two or more argument specifiers, use a tuple (parentheses):

```python
# This prints out "John is 23 years old."
name = "John"
age = 23
print "%s is %d years old." % (name, age)
```

Any object which is not a string can be formatted using the %s operator as well. The string which returns from the "repr" method of that object is formatted as the string. For example:

```python
# This prints out: A list: [1, 2, 3]
mylist = [1,2,3]
print "A list: %s" % mylist
```
Here are some basic argument specifiers you should know:

```python
%s - String (or any object with a string representation, like numbers)
%d - Integers
%f - Floating point numbers
%.<number of digits>f - Floating point numbers with a fixed amount of digits to the right of the dot.
%x/%X - Integers in hex representation (lowercase/uppercase)
```

## Basic String Operations
Strings are bits of text. They can be defined as anything between quotes:

```python
astring = "Hello world!"
```
As you can see, the first thing you learned was printing a simple sentence. This sentence was stored by Python as a string. However, instead of immediately printing strings out, we will explore the various things you can do to them.

```python
print len(astring)
```
That prints out 12, because "Hello world!" is 12 characters long, including punctuation and spaces.

```python
print astring.index("o")
```

That prints out 4, because the location of the first occurrence of the letter "o" is 4 characters away from the first character. Notice how there are actually two o's in the phrase - this method only recognizes the first.

But why didn't it print out 5? Isn't "o" the fifth character in the string? To make things more simple, Python (and most other programming languages) start things at 0 instead of 1. So the index of "o" is 4.

```python
print astring.count("l")
```
For those of you using silly fonts, that is a lowercase L, not a number one. This counts the number of l's in the string. Therefore, it should print 3.

```python
print astring[3:7]
```
This prints a slice of the string, starting at index 3, and ending at index 6. But why 6 and not 7? Again, most programming languages do this - it makes doing math inside those brackets easier.

If you just have one number in the brackets, it will give you the single character at that index. If you leave out the first number but keep the colon, it will give you a slice from the start to the number you left in. If you leave out the second number, if will give you a slice from the first number to the end.

You can even put negative numbers inside the brackets. They are an easy way of starting at the end of the string instead of the beginning. This way, -3 means "3rd character from the end".

```python
print astring.upper()
print astring.lower()
```
These make a new string with all letters converted to uppercase and lowercase, respectively.

```python
print astring.startswith("Hello")
print astring.endswith("asdfasdfasdf")
```
This is used to determine whether the string starts with something or ends with something, respectively. The first one will print True, as the string starts with "Hello". The second one will print False, as the string certainly does not end with "asdfasdfasdf".

```python
afewwords = astring.split(" ")
```

## Conditions
Python uses boolean variables to evaluate conditions. The boolean values True and False are returned when an expression is compared or evaluated. For example:

```python
x = 2
print x == 2 # prints out True
print x == 3 # prints out False
print x < 3  # prints out True
```

Notice that variable assignment is done using a single equals operator "=", whereas comparison between two variables is done using the double equals operator "==". The "not equals" operator is marked as "!=".

#### Boolean operators

The "and" and "or" boolean operators allow building complex boolean expressions, for example:

```python
name = "John"
age = 23
if name == "John" and age == 23:
    print "Your name is John, and you are also 23 years old."

if name == "John" or name == "Rick":
    print "Your name is either John or Rick."
```

#### The "in" operator

The "in" operator could be used to check if a specified object exists within an `iterable` object container, such as a list:

```python
if name in ["John", "Rick"]:
    print "Your name is either John or Rick."
```

Python uses indentation to define code blocks, instead of brackets. The standard Python indentation is 4 spaces, although tabs and any other space size will work, as long as it is consistent. Notice that code blocks do not need any termination.

Here is an example for using Python's "if" statement using code blocks:

```python
if <statement is true>:
    <do something>
    ....
    ....
elif <another statement is true>: # else if
    <do something else>
    ....
    ....
else:
    <do another thing>
    ....
    ....
```

For example:

```python
x = 2
if x == 2:
    print "x equals two!"
else:
    print "x does not equal to two."
```

A statement is evaluated as true if one of the following is correct: 

1. The "True" boolean variable is given, or calculated using an expression, such as an arithmetic comparison. 
2. An object which is not considered "empty" is passed.

Here are some examples for objects which are considered as empty:
 
1. An empty string: "" 
2. An empty list: [] 
3. The number zero: 0 
4. The false boolean variable: False

#### The "is" operator

Unlike the double equals operator "==", the "is" operator does not match the values of the variables, but the instances themselves. For example:

```python
x = [1,2,3]
y = [1,2,3]
print x == y # Prints out True
print x is y # Prints out False
```

#### The "not" operator

Using "not" before a boolean expression inverts it:

```python
print not False # Prints out True
print (not False) == (False) # Prints out False
```

## Loops
There are two types of loops in Python, `for` and `while`.

#### The "for" loop
For loops iterate over a given sequence. Here is an example:

```python
primes = [2, 3, 5, 7]
for prime in primes:
    print prime
```

For loops can iterate over a sequence of numbers using the "range" and "xrange" functions. The difference between range and xrange is that the range function returns a new list with numbers of that specified range, whereas xrange returns an iterator, which is more efficient. (Python 3 uses the range function, which acts like xrange). Note that the xrange function is zero based.

```python
# Prints out the numbers 0,1,2,3,4
for x in xrange(5): # or range(5)
    print x

# Prints out 3,4,5
for x in xrange(3, 6): # or range(3, 6)
    print x

# Prints out 3,5,7
for x in xrange(3, 8, 2): # or range(3, 8, 2)
    print x
```

#### "while" loops

While loops repeat as long as a certain boolean condition is met. For example:

```python
# Prints out 0,1,2,3,4

count = 0
while count < 5:
    print count
    count += 1  # This is the same as count = count + 1
```

#### "break" and "continue" statements

break is used to exit a for loop or a while loop, whereas continue is used to skip the current block, and return to the "for" or "while" statement. A few examples:

```python
# Prints out 0,1,2,3,4

count = 0
while True:
    print count
    count += 1
    if count >= 5:
        break

# Prints out only odd numbers - 1,3,5,7,9
for x in xrange(10):
    # Check if x is even
    if x % 2 == 0:
        continue
    print x
```

## Dictionaries

A dictionary is a data type similar to arrays, but works with keys and values instead of indexes. Each value stored in a dictionary can be accessed using a key, which is any type of object (a string, a number, a list, etc.) instead of using its index to address it.

For example, a database of phone numbers could be stored using a dictionary like this:

```python
phonebook = {}
phonebook["John"] = 938477566
phonebook["Jack"] = 938377264
phonebook["Jill"] = 947662781
```

Alternatively, a dictionary can be initialized with the same values in the following notation:

```python
phonebook = {
    "John" : 938477566,
    "Jack" : 938377264,
    "Jill" : 947662781
}
```

#### Iterating over dictionaries
Dictionaries can be iterated over, just like a list. However, a dictionary, unlike a list, does not keep the order of the values stored in it. To iterate over key value pairs, use the following syntax:

```python
for name, number in phonebook.iteritems():
    print "Phone number of %s is %d" % (name, number)
```

```python
d = {'x': 1, 'y': 2, 'z': 3} 
list(d)
# prints ['y', 'x', 'z']

d.keys()
# prints ['y', 'x', 'z']
```

Another way

```python
d.items()
# prints [('y', 2), ('x', 1), ('z', 3)]
```

This gives you a list of tuples. When you loop over them like this, each tuple is unpacked into k and v automatically

```python
for k,v in d.items():
    print k, 'corresponds to', v
```

Using k and v as variable names when looping over a dict is quite common if the body of the loop is only a few lines. For more complicated loops it may be a good idea to use more descriptive names

```python
for letter, number in d.items():
    print letter, 'corresponds to', number
```

It's a good idea going forward to get into the habit of using format strings

```python
for letter, number in d.items():
    print '{0} corresponds to {1}'.format(letter, number)
```

#### Removing a value

To remove a specified index, use either one of the following notations:

```python
del phonebook["John"]
```
or:

```python
phonebook.pop("John")
```

Testing to see if a key exists, before trying to access it.

```python
d = dict()

for i in xrange(100):
    key = i % 10
    if key in d:
        d[key] += 1
    else:
        d[key] = 1
```

If you wanted a default, you can always use dict.get():

```python
d = dict()

for i in range(100):
    key = i % 10
    d[key] = d.get(key, 0) + 1
```

## Functions

#### What are Functions?
Functions are a convenient way to divide your code into useful blocks, allowing us to order our code, make it more readable, reuse it and save some time. Also functions are a key way to define interfaces so programmers can share their code.

How do you write functions in Python?
As we have seen on previous tutorials, Python makes use of blocks.

A block is an area of code of written in the format of:

```python
block_head: 
    1st block line 
    2nd block line 
    ...
```

Where a block line is more Python code (even another block), and the block head is of the following format: block_keyword block_name(argument1,argument2, ...) Block keywords you already know are "if", "for", and "while".

Functions in python are defined using the block keyword "def", followed with the function's name as the block's name. For example:

```python
def my_function():
    print "Hello From My Function!"
```

Functions may also receive arguments (variables passed from the caller to the function). For example:

```python
def my_function_with_args(username, greeting):
    print "Hello, %s , From My Function!, I wish you %s"%(username, greeting)
```

Functions may return a value to the caller, using the keyword: `return` . For example:

```python
def sum_two_numbers(a, b):
    return a + b
```
#### How do you call functions in Python?

Simply write the function's name followed by (), placing any required arguments within the brackets. For example, lets call the functions written above (in the previous example):

```python
# print a simple greeting 
my_function()

#prints - "Hello, John Doe, From My Function!, I wish you a great year!"
my_function_with_args("John Doe", "a great year!")

# after this line x will hold the value 3!
x = sum_two_numbers(1,2)
```

## Classes and Objects

Objects are an encapsulation of variables and functions into a single entity. Objects get their variables and functions from classes. Classes are essentially a template to create your objects.

A very basic class would look something like this:

```python
class MyClass:
    variable = "blah"

    def function(self):
        print "This is a message inside the class."
```

We'll explain why you have to include that "self" as a parameter a little bit later. First, to assign the above class(template) to an object you would do the following:

```python
myobjectx = MyClass()
```
Now the variable "myobjectx" holds an object of the class "MyClass" that contains the variable and the function defined within the class called "MyClass".

Accessing Object Variables
To access the variable inside of the newly created object "MyObject" you would do the following:

```python
myobjectx.variable
```
So for instance the below would output the string "blah":

```python
print myobjectx.variable
```
You can create multiple different objects that are of the same class(have the same variables and functions defined). However, each object contains independent copies of the variables defined in the class. For instance, if we were to define another object with the "MyClass" class and then change the string in the variable above:

```python
myobjecty = MyClass()
myobjecty.variable = "yackity"
```
Then print out both values:

```python
print myobjectx.variable   # This would print "blah".
print myobjecty.variable   # This would print "yackity".
```
#### Accessing Object Functions
To access a function inside of an object you use notation similar to accessing a variable:

```python
myobjectx.function()
```

The above would print out the message, "This is a message inside the class."



## Modules and Packages

Modules in Python are simply Python files with the *.py* extension, which implement a set of functions. Modules are imported from other modules using the import command.

To import a module, we use the import command. 

The first time a module is loaded into a running Python script, it is initialized by executing the code in the module once. If another module in your code imports the same module again, it will not be loaded twice but once only - so local variables inside the module act as a "singleton" - they are initialized only once.

If we want to import the module "urllib", which enables us to create read data from URLs, we simply import the module:

```python
# import the library
import urllib

# use it
urllib.urlopen(...)
```

#### Exploring built-in modules

Two very important functions come in handy when exploring modules in Python - the dir and help functions.

We can look for which functions are implemented in each module by using the dir function:

```python
>>> import urllib
>>> dir(urllib)
['ContentTooShortError', 'FancyURLopener', 'MAXFTPCACHE', 'URLopener', '__all__', '__builtins__', '__doc__', '__file__', '__name__', '__package__', '__version__', '_ftperrors', '_get_proxies', '_get_proxy_settings', '_have_ssl', '_hexdig', '_hextochr', '_hostprog', '_is_unicode', '_localhost', '_noheaders', '_nportprog', '_passwdprog', '_portprog', '_queryprog', '_safe_map', '_safe_quoters', '_tagprog', '_thishost', '_typeprog', '_urlopener', '_userprog', '_valueprog', 'addbase', 'addclosehook', 'addinfo', 'addinfourl', 'always_safe', 'basejoin', 'c', 'ftpcache', 'ftperrors', 'ftpwrapper', 'getproxies', 'getproxies_environment', 'getproxies_macosx_sysconf', 'i', 'localhost', 'main', 'noheaders', 'os', 'pathname2url', 'proxy_bypass', 'proxy_bypass_environment', 'proxy_bypass_macosx_sysconf', 'quote', 'quote_plus', 'reporthook', 'socket', 'splitattr', 'splithost', 'splitnport', 'splitpasswd', 'splitport', 'splitquery', 'splittag', 'splittype', 'splituser', 'splitvalue', 'ssl', 'string', 'sys', 'test', 'test1', 'thishost', 'time', 'toBytes', 'unquote', 'unquote_plus', 'unwrap', 'url2pathname', 'urlcleanup', 'urlencode', 'urlopen', 'urlretrieve']
```

When we find the function in the module we want to use, we can read about it more using the help function, inside the Python interpreter:

```python
help(urllib.urlopen)
```

#### Writing modules

Writing Python modules is very simple. To create a module of your own, simply create a new .py file with the module name, and then import it using the Python file name (without the .py extension) using the import command.

#### Writing packages

Packages are namespaces which contain multiple packages and modules themselves. They are simply directories, but with a twist.

Each package in Python is a directory which MUST contain a special file called `__init__.py`. This file can be empty, and it indicates that the directory it contains is a Python package, so it can be imported the same way a module can be imported.

If we create a directory called foo, which marks the package name, we can then create a module inside that package called bar. We also must not forget to add the `__init__.py` file inside the foo directory.

To use the module bar, we can import it in two ways:

```python
import foo.bar
```
or:

```python
from foo import bar
```
In the first method, we must use the foo prefix whenever we access the module bar. In the second method, we don't, because we import the module to our module's namespace.

## Generators

Generators are very easy to implement, but a bit difficult to understand.

Generators are used to create iterators, but with a different approach. Generators are simple functions which return an iterable set of items, one at a time, in a special way.

When an iteration over a set of item starts using the for statement, the generator is run. Once the generator's function code reaches a "yield" statement, the generator yields its execution back to the for loop, returning a new value from the set. The generator function can generate as many values (possibly infinite) as it wants, yielding each one in its turn.

Here is a simple example of a generator function which returns 7 random integers:

```python
import random

def lottery():
    # returns 6 numbers between 1 and 40
    for i in xrange(6):
        yield random.randint(1, 40)

    # returns a 7th number between 1 and 15
    yield random.randint(1,15)

for random_number in lottery():
    print "And the next number is... %d!" % random_number
```

This function decides how to generate the random numbers on its own, and executes the yield statements one at a time, pausing in between to yield execution back to the main for loop.

## List Comprehensions

List Comprehensions is a very powerful tool, which creates a new list based on another list, in a single, readable line.

For example, let's say we need to create a list of integers which specify the length of each word in a certain sentence, but only if the word is not the word "the".

```python
sentence = "the quick brown fox jumps over the lazy dog"
words = sentence.split()
word_lengths = []
for word in words:
    if word != "the":
        word_lengths.append(len(word))
```

Using a list comprehension, we could simplify this process to this notation:

```python
sentence = "the quick brown fox jumps over the lazy dog"
words = sentence.split()
word_lengths = [len(word) for word in words if word != "the"]
```

## Multiple Function Arguments

Every function in Python receives a predefined number of arguments, if declared normally, like this:

```python
def myfunction(first, second, third):
    # do something with the 3 variables
    ...
```

It is possible to declare functions which receive a variable number of arguments, using the following syntax:

```python
def foo(first, second, third, *therest):
    print "First: %s" % first
    print "Second: %s" % second
    print "Third: %s" % third
    print "And all the rest... %s" % list(therest)
```

The "therest" variable is a list of variables, which receives all arguments which were given to the "foo" function after the first 3 arguments. So calling foo(1,2,3,4,5) will print out:

```python
First: 1
Second: 2
Third: 3
And all the rest... [4, 5]
```

It is also possible to send functions arguments by keyword, so that the order of the argument does not matter, using the following syntax:

```python
def bar(first, second, third, **options):
    if options.get("action") == "sum":
        print "The sum is: %d" % (first + second + third)

    if options.get("number") == "first":
        return first

result = bar(1, 2, 3, action = "sum", number = "first")
print "Result: %d" % result
```

The following code yields the following output:

```python
The sum is: 6
Result: 1
```

The "bar" function receives 3 arguments. If an additional "action" argument is received, and it instructs on summing up the numbers, then the sum is printed out. Alternatively, the function also knows it must return the first argument, if a "return" argument is received which instructs it.

## Serialization
Python provides built-in JSON libraries to encode and decode JSON.

In Python 2.5, the simplejson module is used, whereas in Python 2.7, the json module is used. Since this interpreter uses Python 2.7, we'll be using json.

In order to use the json module, it must first be imported:

```python
import json
```

There are two basic formats for JSON data. Either in a string or the object datastructure. The object datastructure, in Python, consists of lists and dictionaries nested inside each other. The object datastructure allows one to use python methods (for lists and dictionaries) to add, list, search and remove elements from the datastructure. The String format is mainly used to pass the data into another program or load into a datastructure.

To load JSON back to a data structure, use the "loads" method. This method takes a string and turns it back into the json object datastructure:

```python
print json.loads(json_string)
```

To encode a data structure to JSON, use the "dumps" method. This method takes an object and returns a String:

```python
json_string = json.dumps([1, 2, 3, "a", "b", "c"])
```

Python supports a Python proprietary data serialization method called pickle (and a faster alternative called cPickle).

You can use it exactly the same way.

```python
import cPickle
pickled_string = cPickle.dumps([1, 2, 3, "a", "b", "c"])
print cPickle.loads(pickled_string)
```

## Sets

Sets are lists with no duplicate entries. Let's say you want to collect a list of words used in a paragraph:

```python
print set("my name is Eric and Eric is my name".split())
```

This will print out a list containing "my", "name", "is", "Eric", and finally "and". Since the rest of the sentence uses words which are already in the set, they are not inserted twice.

Sets are a powerful tool in Python since they have the ability to calculate differences and intersections between other sets. For example, say you have a list of participants in events A and B:

```python
a = set(["Jake", "John", "Eric"])
b = set(["John", "Jill"])
```

To find out which members attended both events, you may use the "intersection" method:

```python
>>> a.intersection(b)
set(['John'])
>>> b.intersection(a)
set(['John'])
```

To find out which members attended only one of the events, use the "symmetric_difference" method:

```python
>>> a.symmetric_difference(b)
set(['Jill', 'Jake', 'Eric'])
>>> b.symmetric_difference(a)
set(['Jill', 'Jake', 'Eric'])
```

To find out which members attended only one event and not the other, use the "difference" method:

```python
>>> a.difference(b)
set(['Jake', 'Eric'])
>>> b.difference(a)
set(['Jill'])
```

To receive a list of all participants, use the "union" method:

```python
>>> a.union(b)
set(['Jill', 'Jake', 'John', 'Eric'])
```

## Code Introspection

Code introspection is the ability to examine classes, functions and keywords to know what they are, what they do and what they know.

Python provides several functions and utilities for code introspection.

```python
help()
dir()
hasattr()
id()
type()
repr()
callable()
issubclass()
isinstance()
__doc__
__name__

```
Source: http://www.learnpython.org/
Source: http://www.pythonforbeginners.com/basics/python-list-manipulation
