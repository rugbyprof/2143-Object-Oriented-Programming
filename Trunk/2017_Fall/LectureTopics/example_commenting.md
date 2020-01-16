# Python Documentation Requirements 

This is how I want you to comment your code for class. Every program should have something similar
to this. It's not `pythonic` at all, but oh well. Python programmers have thier own way of doing things. 
I just created a format that shows clearly (to me) an overview of what your program does and requires (for
usage). Hopefully it will also force you to "think" a little bit about design before you actually start coding. 

### Program Comment Block
```python
"""
Program:
--------
    Program 2 - Binary heap implementation.

Description:
------------
    This would be a short description of your program and a general overview of what you did. 
    Should be about a paragraph, depending on the program.
    
Name: Joanna Culpepper
Date: 3 Feb 2016
"""
```

### Class Comment Block

```python
class SampleClass(object):
    """Summary of class here.

    Longer class information....
    Longer class information....

    Attributes:
        likes_spam: A boolean indicating if we like SPAM or not.
        eggs: An integer count of the eggs we have laid.
    """

    def __init__(self, likes_spam=False):
        """Inits SampleClass with blah."""
        self.likes_spam = likes_spam
        self.eggs = 0

    def public_method(self):
        """Performs operation blah."""
```

### Method Comment Block

```python

def fetch_bigtable_rows(big_table, keys, other_silly_variable=None):
    """Fetches rows from a Bigtable.

    Retrieves rows pertaining to the given keys from the Table instance
    represented by big_table.  Silly things may happen if
    other_silly_variable is not None.

    Args:
        big_table: An open Bigtable Table instance.
        keys: A sequence of strings representing the key of each table row
            to fetch.
        other_silly_variable: Another optional variable, that has a much
            longer name than the other args, and which does nothing.

    Returns:
        A dict mapping keys to the corresponding table row data
        fetched. Each row is represented as a tuple of strings. For
        example:

        {'Serak': ('Rigel VII', 'Preparer'),
         'Zim': ('Irk', 'Invader'),
         'Lrrr': ('Omicron Persei 8', 'Emperor')}

        If a key from the keys argument is missing from the dictionary,
        then that row was not found in the table.

    Raises:
        IOError: An error occurred accessing the bigtable.Table object.
    """
    pass
    
```
<sup>Source: https://google.github.io/styleguide/pyguide.html </sup>
