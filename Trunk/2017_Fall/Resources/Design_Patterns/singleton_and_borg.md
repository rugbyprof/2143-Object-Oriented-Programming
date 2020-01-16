# Single Instance Patterns

## Unique Pattern

```python
#Unique Pattern
class Unique:
#Define some static variables here
    x = 1
    @classmethod
    def init(cls):
        #Define any computation performed when assigning to a "new" object
        return cls
```

## Singleton Pattern

```python
class Singleton:

    __single = None 

    def __init__(self):
        if not Singleton.__single:
            #Your definitions here
            self.x = 1 
        else:
            raise RuntimeError('A Singleton already exists') 

    @classmethod
    def getInstance(cls):
        if not cls.__single:
            cls.__single = Singleton()
        return cls.__single
```

## Borg Pattern

```python
class Borg:

    __monostate = None

    def __init__(self):
        if not Borg.__monostate:
            Borg.__monostate = self.__dict__
            #Your definitions here
            self.x = 1

        else:
            self.__dict__ = Borg.__monostate
```

### Test

```python
#SINGLETON
print "\nSINGLETON\n"
A = Singleton.getInstance()
B = Singleton.getInstance()

print "At first B.x = {} and A.x = {}".format(B.x,A.x)
A.x = 2
print "After A.x = 2"
print "Now both B.x = {} and A.x = {}\n".format(B.x,A.x)
print  "Are A and B the same object? Answer: {}".format(id(A)==id(B))


#BORG
print "\nBORG\n"
A = Borg()
B = Borg()

print "At first B.x = {} and A.x = {}".format(B.x,A.x)
A.x = 2
print "After A.x = 2"
print "Now both B.x = {} and A.x = {}\n".format(B.x,A.x)
print  "Are A and B the same object? Answer: {}".format(id(A)==id(B))


#UNIQUE
print "\nUNIQUE\n"
A = Unique.init()
B = Unique.init()

print "At first B.x = {} and A.x = {}".format(B.x,A.x)
A.x = 2
print "After A.x = 2"
print "Now both B.x = {} and A.x = {}\n".format(B.x,A.x)
print  "Are A and B the same object? Answer: {}".format(id(A)==id(B))
```

### Output

```
At first B.x = 1 and A.x = 1
After A.x = 2
Now both B.x = 2 and A.x = 2

Are A and B the same object? Answer: True

BORG

At first B.x = 1 and A.x = 1
After A.x = 2
Now both B.x = 2 and A.x = 2

Are A and B the same object? Answer: False

UNIQUE

At first B.x = 1 and A.x = 1
After A.x = 2
Now both B.x = 2 and A.x = 2

Are A and B the same object? Answer: True
```
