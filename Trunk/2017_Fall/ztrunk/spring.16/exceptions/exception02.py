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