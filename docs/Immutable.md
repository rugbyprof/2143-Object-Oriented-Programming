An object’s type determines the operations that the object supports (e.g., “does it have a length?”) and also defines the possible values for objects of that type. The type() function returns an object’s type (which is an object itself). The value of some objects can change. Objects whose value can change are said to be mutable; objects whose value is unchangeable once they are created are called immutable. (The value of an immutable container object that contains a reference to a mutable object can change when the latter’s value is changed; however the container is still considered immutable, because the collection of objects it contains cannot be changed. So, immutability is not strictly the same as having an unchangeable value, it is more subtle.) An object’s mutability is determined by its type; for instance, numbers, strings and tuples are immutable, while dictionaries and lists are mutable.

Source: [ [1] ]


### Mutable Class (monkey patching)

Here’s a simple class that doesn’t do much of anything:

```python
class Mutable(object):
    """
    A mutable class
    """
 
    #---------------------------------------
    def __init__(self):
        """Constructor"""
        pass
```

Now let’s create an instance of this class and see if we can add an attribute:

```
>>> mut_obj = Mutable()
>>> mut_obj.monkey = "tamarin"
>>> mut_obj.monkey
'tamarin'
```

This class does allow us to add attributes to it at run time. Now that we know how to do some simple monkey patching, let’s try to block that behavior.

### Immutable Class

One of the examples I was reading about immutable classes mentioned that you could create one by replacing a class’s `__dict__` with `__slots__`. Let’s see how that looks:

```python
class Immutable(object):
    """
    An immutable class
    """
    __slots__ = ["one", "two", "three"]
 
    #----------------------------------------------------------------------
    def __init__(self, one, two, three):
        """Constructor"""
        super(Immutable, self).__setattr__("one", one)
        super(Immutable, self).__setattr__("two", two)
        super(Immutable, self).__setattr__("three", three)
 
    #----------------------------------------------------------------------
    def __setattr__(self, name, value):
        """"""
        msg = "'%s' has no attribute %s" % (self.__class__,name)
        raise AttributeError(msg)
```

Now we just need to create an instance of this class to see if we can monkey patch it:

```
>>> i = Immutable(1, 2, 3)
>>> i.four = 4
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "temp.py", line 18, in __setattr__
    raise AttributeError(msg)
AttributeError: '<class '__main__.Immutable'>' has no attribute four
```
In this case, the class does not allow us to monkey patch the instance. Instead, we receive an AttibuteError. Let’s try to change one of the attributes:

```
>>> i = Immutable(1, 2, 3)
>>> i.one = 2
Traceback (most recent call last):
  File "c:\Users\mdriscoll\Desktop\rep-fonts\immutable\immute_slots.py", line 1, in <module>
    ########################################################################
  File "c:\Users\mdriscoll\Desktop\rep-fonts\immutable\immute_slots.py", line 33, in __setattr__
    raise AttributeError(msg)
AttributeError: '<class '__main__.Immutable'>' has no attribute one
```

This is because we have overridden the `__setattr__` method. You could just override the method and not do anything at all if you wanted. This would stop the traceback from happening, but also prevent the value from being changed. If you like to be explicit with what is going on, raising an error is probably the way to go.

If you do any reading about slots, you will quickly find that using slots in this manner is discouraged. Why? Because slots were created primarily as a memory optimization (it reduces attribute access time).

Source: [ [2] ]

Another article can be found here: https://codehabitude.com/2013/12/24/python-objects-mutable-vs-immutable/


### Immutable Objects in Java
1. Immutable objects are thread-safe so you will not have any synchronization issues.
1. Immutable objects are good Map keys and Set elements, since these typically do not change once created.
1. Immutability makes it easier to write, use and reason about the code (class invariant is established once and then unchanged)
1. Immutability makes it easier to parallelize your program as there are no conflicts among objects.
1. The internal state of your program will be consistent even if you have exceptions.
1. References to immutable objects can be cached as they are not going to change.

Source: [ [3] ]

Sources:

1. https://docs.python.org/2/reference/datamodel.html
2. http://www.blog.pythonlibrary.org/2014/01/17/how-to-create-immutable-classes-in-python/
3. https://www.linkedin.com/pulse/20140528113353-16837833-6-benefits-of-programming-with-immutable-objects-in-java

[1]: https://docs.python.org/2/reference/datamodel.html
[2]: http://www.blog.pythonlibrary.org/2014/01/17/how-to-create-immutable-classes-in-python/
[3]: https://www.linkedin.com/pulse/20140528113353-16837833-6-benefits-of-programming-with-immutable-objects-in-java