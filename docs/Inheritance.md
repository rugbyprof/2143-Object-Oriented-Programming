# Inheritance

In object-oriented programming, inheritance enables new objects to take on the properties of existing objects. A class that is used as the basis for inheritance is called a superclass or base class. A class that inherits from a superclass is called a subclass or derived class. The terms parent class and child class are also acceptable terms to use respectively. A child inherits visible properties and methods from its parent while adding additional properties and methods of its own.

Subclasses and superclasses can be understood in terms of the is a relationship. A subclass is a more specific instance of a superclass. For example, an orange is a citrus fruit, which is a fruit. A shepherd is a dog, which is an animal. A clarinet is a woodwind instrument, which is a musical instrument. If the is a relationship does not exist between a subclass and superclass, you should not use inheritance. An orange is a fruit; so it is okay to write an Orange class that is a subclass of a Fruit class. As a contrast, a kitchen has a sink. It would not make sense to say a kitchen is a sink or that a sink is a kitchen. The has a relationship indicates composition (see Object-oriented programming concepts: Composition and aggregation) rather than inheritance.

Source [(1)](http://www.adobe.com/devnet/actionscript/learning/oop-concepts/inheritance.html)

The syntax for a derived class definition looks like this:
```python
class DerivedClassName(BaseClassName):
    <statement-1>
    .
    .
    .
    <statement-N>
```
The name BaseClassName must be defined in a scope containing the derived class definition. In place of a base class name, other arbitrary expressions are also allowed. This can be useful, for example, when the base class is defined in another module:
```python
class DerivedClassName(modname.BaseClassName):
```

## Multiple Inheritance

Python supports a limited form of multiple inheritance as well. A class definition with multiple base classes looks like this:
```python
class DerivedClassName(Base1, Base2, Base3):
    <statement-1>
    .
    .
    .
    <statement-N>
```
For old-style classes, the only rule is depth-first, left-to-right. Thus, if an attribute is not found in DerivedClassName, it is searched in Base1, then (recursively) in the base classes of Base1, and only if it is not found there, it is searched in Base2, and so on.

(To some people breadth first — searching Base2 and Base3 before the base classes of Base1 — looks more natural. However, this would require you to know whether a particular attribute of Base1 is actually defined in Base1 or in one of its base classes before you can figure out the consequences of a name conflict with an attribute of Base2. The depth-first rule makes no differences between direct and inherited attributes of Base1.)

For new-style classes, the method resolution order changes dynamically to support cooperative calls to super(). This approach is known in some other multiple-inheritance languages as call-next-method and is more powerful than the super call found in single-inheritance languages.

With new-style classes, dynamic ordering is necessary because all cases of multiple inheritance exhibit one or more diamond relationships (where at least one of the parent classes can be accessed through multiple paths from the bottommost class). For example, all new-style classes inherit from object, so any case of multiple inheritance provides more than one path to reach object. To keep the base classes from being accessed more than once, the dynamic algorithm linearizes the search order in a way that preserves the left-to-right ordering specified in each class, that calls each parent only once, and that is monotonic (meaning that a class can be subclassed without affecting the precedence order of its parents). Taken together, these properties make it possible to design reliable and extensible classes with multiple inheritance.

Source [(2)](https://docs.python.org/2/tutorial/classes.html#inheritance)


Sources:  
1. http://www.adobe.com/devnet/actionscript/learning/oop-concepts/inheritance.html  
2. https://docs.python.org/2/tutorial/classes.html#inheritance