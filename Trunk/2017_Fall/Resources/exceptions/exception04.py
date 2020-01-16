"""
Won't even return to a function that it was called from...
"""

def no_return():
    print("I am about to raise an exception") 
    raise Exception("This is always raised") 
    print("This line will never execute") 
    return "I won't be returned"
    
    
def call_exceptor():
    print("call_exceptor starts here...") 
    no_return()
    print("an exception was raised...") 
    print("...so these lines don't run")



call_exceptor()

"""
call_exceptor starts here...
I am about to raise an exception
Traceback (most recent call last):
  File "ex.py", line 16, in <module>
    call_exceptor()
  File "ex.py", line 10, in call_exceptor
    no_return()
  File "ex.py", line 3, in no_return
    raise Exception("This is always raised")
Exception: This is always raised
"""
