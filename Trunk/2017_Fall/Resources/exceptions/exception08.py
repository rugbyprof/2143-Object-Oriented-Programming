"""
What if we want to catch different exceptions and do different things with them? 
Or maybe we want to do something with an exception and then allow it to continue 
to bubble up to the parent function, as if it had never been caught? 
"""

def funny_division3(anumber):
       try:
           if anumber == 13:
               ValueError("13 is an unlucky number")
           return 100 / anumber
       except ZeroDivisionError:
           return "Enter a number other than zero"
       except TypeError:
           return "Enter a numerical value"
       except ValueError:
           print("No, No, not 13!")
           raise 
           
for val in (0, "hello", 50.0, 13):
    print("Testing {}:".format(val), end=" ")
    print(funny_division3(val))

"""
Testing 0: Enter a number other than zero
Testing hello: Enter a numerical value
Testing 50.0: 2.0
Testing 13: 7.6923076923076925
""
