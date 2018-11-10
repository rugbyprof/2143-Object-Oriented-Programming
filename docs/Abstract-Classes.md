#Abstract Classes

### Definition:

In programming languages, an abstract class is a generic class (or type of object) used as a basis for creating specific objects that conform to its protocol, or the set of operations it supports. Abstract classes are not instantiated directly.
Abstract classes are useful when creating hierarchies of classes that model reality because they make it possible to specify an invariant level of functionality in some methods, but leave the implementation of other methods until a specific implementation of that class (a derived class) is needed.

###Explanation:

 Classes that are derived from abstract classes are called derived classes. When this principle is applied many times in succession, it results in a hierarchy of classes. In this context, abstract classes are at the root of this hierarchy, and is used to enforce methods that need to be overridden in the derived classes, thus avoiding potential run time errors. 
 
An abstract class has at least one abstract method. An abstract method will not have any code in the base class; the code will be added in its derived classes. The abstract method in the derived class should be implemented with the same access modifier, number and type of argument, and with the same return type as that of the base class. Objects of abstract class type cannot be created, because the code to instantiate an object of the abstract class type will result in a compilation error.


###Example:
```python
    defining Abstract Base Classes (ABCs) is a metaclass
    class Foo:
    def __getitem__(self, index):
        ...
    def __len__(self):
        ...
    def get_iterator(self):
        return iter(self)

    class MyIterable(metaclass=ABCMeta):

    @abstractmethod
    def __iter__(self):
        while False:
            yield None

    def get_iterator(self):
        return self.__iter__()

    @classmethod
    def __subclasshook__(cls, C):
        if cls is MyIterable:
            if any("__iter__" in B.__dict__ for B in C.__mro__):
                return True
        return NotImplemented

    MyIterable.register(Foo)
```
The ABC MyIterable defines the standard iterable method, __iter__(), as an abstract method. The implementation given here can still be called from subclasses. The get_iterator() method is also part of the MyIterable abstract base class, but it does not have to be overridden in non-abstract derived classes.

The __subclasshook__() class method defined here says that any class that has an __iter__() method in its __dict__ (or in that of one of its base classes, accessed via the __mro__ list) is considered a MyIterable too.

Finally, the last line makes Foo a virtual subclass of MyIterable, even though it does not define an __iter__() method (it uses the old-style iterable protocol, defined in terms of __len__() and __getitem__()). Note that this will not make get_iterator available as a method of Foo, so it is provided separately.

###Sources:

<https://www.techopedia.com/definition/17408/abstract-class>

<https://docs.python.org/3/library/abc.html>