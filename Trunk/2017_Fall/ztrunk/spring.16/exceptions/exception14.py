"""
There may be a setting where the code may "return" to another block 
and continue in that previous block based on some exception. If you 
need to do some house cleaning and force something to run (close
some files, release memory, etc.) then we can use a finally"
"""


def run_code1():
    print("1 + 1 = 2")
    
    
def run_code2():
    print("2 + 2 = 4")
    
def other_code():
    print("close files")


def test_run1():
    lst = [1,2,3]
    try:
        lst = lst + "hello"
    except TypeError:
        run_code2()
        return None   # The finally block is run before the method returns
    finally:
        other_code()
    
def test_run2():
    lst = [1,2,3]
    try:
        lst = lst + "hello"
    except TypeError:
        run_code2()
        return None   

    other_code()  # This doesn't get run if there's an exception.
    
    
test_run1()

test_run2()