"""
First example of handling an exception by not letting users append 
values to a list unless they are even integers.
"""

class EvenOnly(list):
    def append(self, integer):
        if not isinstance(integer, int):
            raise TypeError("Only integers can be added")
        if integer % 2:
            raise ValueError("Only even numbers can be added")
        super().append(integer)


e = EvenOnly()
e.append("a string")
e.append(3)
e.append(2)

"""
Traceback (most recent call last):
  File "ex.py", line 16, in <module>
    e.append("a string")
  File "ex.py", line 9, in append
    raise TypeError("Only integers can be added")
TypeError: Only integers can be added

With `e.append("a string")` commented out:

Traceback (most recent call last):
  File "ex.py", line 17, in <module>
    e.append(3)
  File "ex.py", line 11, in append
    raise ValueError("Only even numbers can be added")
ValueError: Only even numbers can be added
"""
