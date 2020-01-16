"""
Passing arguments to an exception
"""

try:
    raise ValueError("This is an argument","banana")
except ValueError as e:
    print("The exception arguments were", e.args[1]) 