
Programs are very fragile. It would be nice if code always returned a valid result, but sometimes a valid result can’t be calculated. It’s not possible to divide by zero, or to access the eighth item in a five-item list, for example.

In the old days, the only way around this was to rigorously check the inputs for every function to make sure they made sense. Typically functions had special return values to indicate an error condition; for example, they could return a negative number to indicate that a positive value couldn’t be calculated. Different numbers might be different errors occurred. Any code that called this function would have to explicitly check for an error condition and act accordingly. A lot of code didn’t bother to do this, and programs simply crashed.

Not so in the object-oriented world! 

There are many different exception classes available and you can easily define more of your own. The one thing they all have in common is that they derive from a built-in class called ```BaseException ```. 

[Source 1]

## **Example of Common Exceptions**

**IndexError:**

```python
first = [1, 2, 3]
print(first[3])
Traceback (most recent call last): 
	File “<stdin>”, line 1, in <module>
IndexError: list index out of range
```

**ZeroDivisionError:**

```python
x = 5 / 0
Traceback (most recent call last): 
	File “<stdin>”, line 1, in <module>
ZeroDivisionError: int division or modulo by zero
```

This page ([Built-in Exceptions](https://docs.python.org/2/library/exceptions.html)) lists the built-in exceptions and their meanings.

Sometimes these exceptions are indicators of something wrong in our program, but they also occur in legitimate situations. A ```ZeroDivisionError ``` doesn’t always mean we received invalid input, just different input. There user may have entered a zero by mistakes, or on purpose, or it may represent a legitimate value such as an empty bank account or the age of a newborn child. 

In Python, the words “error” and “exception” are used almost interchangeably. Errors are sometimes considered more dire than exceptions, but they are dealt with in exactly the same way. 

[Source 1]

## **Syntax Errors**

Syntax errors, also known as parsing errors, are perhaps the most common kind of complaint you get while you are still learning Python:

```python 
while True print 'Hello world’
File "<stdin>", line 1, in <module>
	while True print 'Hello world'
                   ^
SyntaxError: invalid syntax
```

The parser repeats the offending line and displays a little ‘arrow’ pointing at the earliest point in the line where the error was detected. The error is caused by (or at least detected at) the token preceding the arrow: in the example, the error is detected at the keyword ```print ```, since a colon (':') is missing before it. File name and line number are printed so you know where to look in case the input came from a script.

[Source 2]

## **Exceptions**

Even if a statement or expression is syntactically correct, it may cause an error when an attempt is made to execute it. Errors detected during execution are called exceptions and are not unconditionally fatal: you will soon learn how to handle them in Python programs. Most exceptions are not handled by programs, however, and result in error messages as shown here:

```python
4 + spam*3
Traceback (most recent call last):
 	File "<stdin>", line 1, in <module>
NameError: name 'spam' is not defined

'2' + 2
Traceback (most recent call last):
	File "<stdin>", line 1, in <module>
TypeError: cannot concatenate 'str' and 'int' objects
```
The last line of the error message indicates what happened. Exceptions come in different types, and the type is printed as part of the message: the types in the example are ```ZeroDivisionError```, ```NameError``` and ```TypeError```. The string printed as the exception type is the name of the built-in exception that occurred. This is true for all built-in exceptions, but need not be true for user-defined exceptions (although it is a useful convention). Standard exception names are built-in identifiers (not reserved keywords).

The rest of the line provides detail based on the type of exception and what caused it.

The preceding part of the error message shows the context where the exception happened, in the form of a stack traceback. In general it contains a stack traceback listing source lines; however, it will not display lines read from standard input.

[Source 2]

## **Handling Exceptions**

It is possible to write programs that handle selected exceptions. Look at the following example, which asks the user for input until a valid integer has been entered, but allows the user to interrupt the program (using Control-C or whatever the operating system supports); note that a user-generated interruption is signaled by raising the ```KeyboardInterrupt``` exception.

```python
while True:
	try:
		x = int(raw_input("Please enter a number: "))
		break
	except ValueError:
		print "Oops!  That was no valid number.  Try again..."
```
The ```try``` statement works as follows.

* 	First, the try clause (the statement(s) between the ```try``` and ```except```keywords) is executed.
* 	If no exception occurs, the _except clause_ is skipped and execution of the ```try``` statement is finished.
* 	If an exception occurs during execution of the try clause, the rest of the clause is skipped. Then if its type matches the exception named after the ```except``` keyword, the except clause is executed, and then execution continues after the ```try``` statement.
* 	If an exception occurs which does not match the exception named in the except clause, it is passed on to outer ```try``` statements; if no handler is found, it is an _unhandled exception_ and execution stops with a message as shown above.

A ```try``` statement may have more than one except clause, to specify handlers for different exceptions. At most one handler will be executed. Handlers only handle exceptions that occur in the corresponding try clause, not in other handlers of the same ```try``` statement. An except clause may name multiple exceptions as a parenthesized tuple, for example:

```python
except (RuntimeError, TypeError, NameError):
	pass
```

The last except clause may omit the exception name(s), to serve as a wildcard. Use this with extreme caution, since it is easy to mask a real programming error in this way! It can also be used to print an error message and then re-raise the exception (allowing a caller to handle the exception as well):

```python
import sys

try:
    f = open('myfile.txt')
    s = f.readline()
    i = int(s.strip())
except IOError as e:
    print "I/O error({0}): {1}".format(e.errno, e.strerror)
except ValueError:
    print "Could not convert data to an integer."
except:
    print "Unexpected error:", sys.exc_info()[0]
    raise
```

The ```try``` ... ```except``` statement has an optional _else clause_, which, when present, must follow all except clauses. It is useful for code that must be executed if the try clause does not raise an exception. For example:

```python
for arg in sys.argv[1:]:
    try:
        f = open(arg, 'r')
    except IOError:
        print 'cannot open', arg
    else:
        print arg, 'has', len(f.readlines()), 'lines'
        f.close()
```

The use of the ```else``` clause is better than adding additional code to the ```try``` clause because it avoids accidentally catching an exception that wasn’t raised by the code being protected by the ```try``` ... ```except``` statement.

[Source 2]

## **Raising Exceptions**

The ```raise``` statement allows the programmer to force a specified exception to occur. For example:

```python
raise NameError('HiThere')
Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
NameError: HiThere
```

The sole argument to ```raise``` indicates the exception to be raised. This must be either an exception instance or an exception class (a class that derives from ```Exception```).

If you need to determine whether an exception was raised but don’t intend to handle it, a simpler form of the ```raise``` statement allows you to re-raise the exception:

```python
try:
     raise NameError('HiThere')
except NameError:
     print 'An exception flew by!'
     raise

An exception flew by!
Traceback (most recent call last):
     File "<stdin>", line 2, in <module>
NameError: HiThere
```

[Source 2]


## **User-defined Exceptions**

Often, when we want to raise an exception, we find that none of the built-in exceptions are quite what we need. Luckily, it's very easy to define new exceptions of our own. The name of the class is usually designed to communicate what went wrong, and we can provide arbitrary arguments in the initializer to add additional information.

All we have to do is inherit from the ```Exception``` class. We don't even have to ass any content to the class! We can, of course, extend ```BaseException``` directly, but then it will not be caught by generic ```except Exception``` clauses.

Here's a simple exception we might use in a banking application:

```python
class InvalidWithdrawal(Exception):
     pass

raise InvalidWithdrawal ("You don't have $50 in your account")
```

The last line illustrates how to raise the newly defined exception. The ```Exception __init__``` method is designed to accept any arguments and store them as a tuple in an attribute named ```args```. This makes exceptions easier to define without needing to override ```__init__```.

In this example, the default __init__() of Exception has been overridden. The new behavior simply creates the value attribute. This replaces the default behavior of creating the args attribute.

```python
class MyError(Exception):
     def __init__(self, value):
         self.value = value
     def __str__(self):
         return repr(self.value)

try:
     raise MyError(2*2)
except MyError as e:
     print 'My exception occurred, value:', e.value

My exception occurred, value: 4

raise MyError('oops!')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
__main__.MyError: 'oops!'
```

[Source 1] [Source 2]

## **Finally Clause**

The ```try``` statement has another optional clause which is intended to define clean-up actions that must be executed under all circumstances. For example:

```python
try:
     raise KeyboardInterrupt
finally:
     print 'Goodbye, world!'

Goodbye, world!

KeyboardInterrupt
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
```

A _finally clause_ is always executed before leaving the ```try``` statement, whether an exception has occurred or not. When an exception has occurred in the ```try``` clause and has not been handled by an ```except``` clause (or it has occurred in a ```except``` or ```else``` clause), it is re-raised after the ```finally``` clause has been executed. The ```finally``` clause is also executed “on the way out” when any other clause of the ```try``` statement is left via a ```break```, ```continue``` or ```return statement```. A more complicated example (having ```except``` and ```finally``` clauses in the same ```try``` statement works as of Python 2.5):

```python
def divide(x, y):
     try:
         result = x / y
     except ZeroDivisionError:
         print "division by zero!"
     else:
         print "result is", result
     finally:
         print "executing finally clause"

>>> divide(2, 1)
result is 2
executing finally clause
>>> divide(2, 0)
division by zero!
executing finally clause
>>> divide("2", "1")
executing finally clause
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "<stdin>", line 3, in divide
TypeError: unsupported operand type(s) for /: 'str' and 'str'
```

As you can see, the ```finally``` clause is executed in any event. The ```TypeError``` raised by dividing two strings is not handled by the ```except``` clause and therefore re-raised after the ```finally``` clause has been executed.

In real world applications, the ```finally``` clause is useful for releasing external resources (such as files or network connections), regardless of whether the use of the resource was successful.

[Source 2]

## **Sources**

1. Phillips, D. (2010). Python 3 Object Oriented Programing. Birmingham, UK: Packt Publishing Ltd.
2. https://docs.python.org/2/tutorial/errors.html