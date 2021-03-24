## Lecture 04 - Constructors
#### Jan 26th

### Files

| Num | File                                         | description |
| --- | -------------------------------------------- | ----------- |
| 1   | [01_shallow.cpp](01_shallow.cpp)             | see below   |
| 2   | [02_deep.cpp](02_deep.cpp)                   | see below   |
| 3   | [03_string_concat.cpp](03_string_concat.cpp) | see below   |


### General
- We covered constructors (again):
  - Default
  - Parameterized
  - Copy Constructor
- We overloaded the assignment operator
- We overloaded addition operator

### Descriptions

- [01_shallow.cpp](01_shallow.cpp) 
  - Example of a simple point object that doesn't need a copy constructor since there is no dynamically allocated memory. 
  - We did overload the addition operator which was necessary, but we could still use the assignment operator (=) to create a brand new object with the result of adding two "points" together. Remember, the assignment operator when used for the "instantiation" (creation) of a new "instance" will invoke a copy constructor whether you wrote one or not. 
  - Play with the code by commenting and un-commenting the copy constructor along with its prototype in the class definition.

- [02_deep.cpp](01_shallow.cpp) 
  - Example of a generic array object that needs a copy constructor since there is dynamically allocated memory (array). 
  -  Overloaded the (+) sign to "concatenate" arrays and not add each of the values together. We decided this in class for really no reason.
  -  I would encourage you to change it to add each array element together (beware of arrays that are different sizes). 

- [03_string_concat.cpp](03_string_concat.cpp) 
  - Addition is already overloaded for the string object!
