## Basic inheritance

- A **superclass**, or parent class, is a class that is being inherited from. 
- A **subclass** is a class that is inheriting from a **superclass**. 
- In this case, the superclass is object, and MySubClass is the subclass. 
- A subclass is also said to be **derived** from its parent class or that the subclass **extends** the parent.


```python
 class Contact:
       all_contacts = []
       def __init__(self, name, email):
           self.name = name
           self.email = email
           Contact.all_contacts.append(self)
           
```

```python
   class Supplier(Contact):
       def order(self, order):
           print("If this were a real system we would send "
                   "{} order to {}".format(order, self.name))
                   
```

```
>>> c = Contact("Some Body", "somebody@example.net")
>>> s = Supplier("Sup Plier", "supplier@example.net")
>>> print(c.name, c.email, s.name, s.email)
>>> c.all_contacts
>>> c.order("Ineed pliers")
>>> s.order("I need pliers")
>>>
```

## Extending built-ins

- Extending the built in `list` type

```python
class ContactList(list):
    def search(self, name):
        '''Return all contacts that contain the search value
        in their name.'''
        matching_contacts = []
        for contact in self:
            if name in contact.name:
                matching_contacts.append(contact)
        return matching_contacts
        
class Contact:
    all_contacts = ContactList()
    def __init__(self, name, email):
        self.name = name
        self.email = email
        self.all_contacts.append(self)
        
```

```
>>> c1 = Contact("John A", "johna@example.net")
>>> c2 = Contact("John B", "johnb@example.net")
>>> c3 = Contact("Jenna C", "jennac@example.net")
>>> [c.name for c in Contact.all_contacts.search('John')]
>>> [] == list()
```

Extending the built in `dict` type
```python
class LongNameDict(dict):
    def longest_key(self):
          longest = None
           for key in self:
               if not longest or len(key) > len(longest):
                   longest = key
           return longest
```

```
>>> longkeys = LongNameDict()
>>> longkeys['hello'] = 1
>>> longkeys['longest yet'] = 5
>>> longkeys['hello2'] = 'world'
>>> longkeys.longest_key()
```

## Overriding and super

- **Overriding** is altering or replacing a method of the superclass with a new method (with the same name) in the subclass.

```python

class Friend(Contact):
    def __init__(self, name, email, phone):
        self.name = name
        self.email = email
        self.phone = phon
        
```

- Using the **super** function

```python
 class Friend(Contact):
       def __init__(self, name, email, phone):
           super().__init__(name, email)
           self.phone = phone   
           
```

## Multiple inheritance

>`As a rule of thumb, if you think you need multiple inheritance, you're probably wrong, but if you know you need it, you're probably right.`

- A **mixin** is generally a superclass that is not meant to exist on its own, but is meant to be inherited by some other class to provide extra functionality.

```python
class MailSender:
    def send_mail(self, message):
        print("Sending mail to " + self.email)
        # Add e-mail logic here
        
```

```python
class EmailableContact(Contact, MailSender):
	pass
```

```
>>> e = EmailableContact("John Smith", "jsmith@example.net")
>>> Contact.all_contacts
[<__main__.EmailableContact object at 0xb7205fac>]
>>> e.send_mail("Hello, test e-mail here")
Sending mail to jsmith@example.net
```


```python
class AddressHolder:
       def __init__(self, street, city, state, code):
           self.street = street
           self.city = city
           self.state = state
           self.code = code 
           
```

## The Diamond Problem

![](https://s3.amazonaws.com/f.cl.ly/items/1u2o3C1u1j3Z3l0g2o24/Screen%20Shot%202016-02-04%20at%2010.16.49%20AM.png)


```python
class Friend(Contact, AddressHolder):
       def __init__(self, name, email, phone,
               street, city, state, code):
           Contact.__init__(self, name, email)
           AddressHolder.__init__(
               self, street, city, state, code)
           self.phone = phone
           
```

![](https://s3.amazonaws.com/f.cl.ly/items/2y0O3H062Y3z3m401l47/Screen%20Shot%202016-02-04%20at%2010.17.49%20AM.png)

```python
class BaseClass:
       num_base_calls = 0
       def call_me(self):
           print("Calling method on Base Class")
           self.num_base_calls += 1
           
class LeftSubclass(BaseClass):
    num_left_calls = 0
    def call_me(self):
        BaseClass.call_me(self)
        print("Calling method on Left Subclass")
        self.num_left_calls += 1
        
class RightSubclass(BaseClass):
    num_right_calls = 0
    def call_me(self):
        BaseClass.call_me(self)
        print("Calling method on Right Subclass")
        self.num_right_calls += 1
        
class Subclass(LeftSubclass, RightSubclass):
    num_sub_calls = 0
    def call_me(self):
        LeftSubclass.call_me(self) 
        RightSubclass.call_me(self) 
        print("Calling method on Subclass") 
        self.num_sub_calls += 1  
        
```


```python

class BaseClass:
    num_base_calls = 0
    def call_me(self):
        print("Calling method on Base Class")
        self.num_base_calls += 1
class LeftSubclass(BaseClass):
    num_left_calls = 0
    def call_me(self):
        super().call_me()
        print("Calling method on Left Subclass")
        self.num_left_calls += 1
class RightSubclass(BaseClass):
    num_right_calls = 0
    def call_me(self):
        super().call_me()
        print("Calling method on Right Subclass")
        self.num_right_calls += 1
class Subclass(LeftSubclass, RightSubclass):
    num_sub_calls = 0
    def call_me(self):
        super().call_me()
        print("Calling method on Subclass")
        self.num_sub_calls += 1

```

## Different sets of arguments

```python
Contact.__init__(self, name, email)
AddressHolder.__init__(self, street, city, state, code)
```

```python
class Contact:
    all_contacts = []
    
    def __init__(self, name='', email='', **kwargs): 
        super().__init__(**kwargs)
        self.name = name
        self.email = email 
        self.all_contacts.append(self)
        
class AddressHolder:
    def __init__(self, street='', city='', state='', code='', **kwargs):
        super().__init__(**kwargs)
        self.street = street
        self.city = city
        self.state = state
        self.code = code
        
class Friend(Contact, AddressHolder):
    def __init__(self, phone='', **kwargs): 
    super().__init__(**kwargs) 
    self.phone = phone
    
```

> If you aren't familiar with the `**kwargs` syntax, it basically collects any keyword arguments passed into the method that were not explicitly listed in the parameter list. These arguments are stored in a dictionary named kwargs (we can call the variable whatever we like, but convention suggests kw, or kwargs). When we call a different method (for example: `super().__init__)` with a `**kwargs` syntax, it unpacks the dictionary and passes the results to the method as normal keyword arguments. 

Not complete ....

- http://www.programiz.com/python-programming/namespace
- http://www.python-course.eu/python3_multiple_inheritance.php
