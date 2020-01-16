"""
Exceptions aren't exceptional
"""

def divide_with_exception(number, divisor):
    try:
        print("{} / {} = {}".format(number, divisor, number / divisor * 1.0))
    except ZeroDivisionError:
        print("You can't divide by zero")
           
def divide_with_if(number, divisor):
    if divisor == 0:
        print("You can't divide by zero")
    else:
        print("{} / {} = {}".format(number, divisor, number / divisor * 1.0))
        
        
"""
- Can avoid errors with if statements
- Don't do this, use built in classes:
    - you might not test for all cases (e.g. -1 in an index) and exceptions do
"""