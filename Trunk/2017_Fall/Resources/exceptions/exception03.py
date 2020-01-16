"""
When an exception is raised, it appears to stop program execution immediately. 
Any lines that were supposed to happen after the exception are not executed, and, unless the exception is dealt with, the program will exit with an error message. 
"""


"""
Second print never executes
"""
def no_return():
    print("I am about to raise an exception") 
    raise Exception("This is always raised") 
    print("This line will never execute") 
    return "I won't be returned"
    
no_return()