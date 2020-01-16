import random

some_exceptions = [ValueError, TypeError, IndexError, None]
raise Exception("some error")
try:
    choice = random.choice(some_exceptions)
    print(choice)
    print("raising {}".format(choice))
    # if choice:
    #     pass
    raise choice("An error")
except ValueError:
    print("Caught a ValueError")
except TypeError:
    print("Caught a TypeError")
except Exception as e:
    print("Caught some other error: %s" % ( e.__class__.__name__))
else:
    print("This code called if there is no exception")
finally:
    print("This cleanup code is always called")