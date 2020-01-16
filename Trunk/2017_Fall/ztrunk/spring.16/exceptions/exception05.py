"""
 We handle exceptions by wrapping any code that might throw one (whether it is exception code itself, or a call to 
 any function or method that may have an exception raised inside it) inside a try...except clause.
 
 Catches ANY type of exception
 """
def no_return():
    print("I am about to raise an exception") 
    try:
        x = 1 / 0
    except:
        print("I caught an exception and divided by zero")
    print("This line will never execute") 
    return "I won't be returned"
    

print("executed after the exception")

print(no_return())
