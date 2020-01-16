"""
We can even catch two or more different exceptions and handle them with the same code. 
Here's an example that raises three different types of exceptions. 
It handles TypeError and ZeroDivisionError with the same exception handler, but it may also raise a ValueError if you supply the number 13:
"""


def funny_division2(anumber):
       try:
           if anumber == 13:
               raise ValueError("13 is an unlucky number")
           return 100 / anumber
       except (ZeroDivisionError, TypeError):
           return "Enter a number other than zero"

"""
Enter a number other than zero
2.0
Enter a number other than zero
"""
