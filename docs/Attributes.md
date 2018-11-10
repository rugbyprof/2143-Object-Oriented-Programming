## Definition:
Data can be created anywhere, and used by any code at any time. In OOP, we want to restrict some data so that it can only be acted-upon by the Methods in the same Object. These restricted variables have a special name: Attributes.

Every Attribute is a Variable, with three special features:

1) The Class that creates the Object usually provides a default or starting value for each Attribute

2) Attributes can optionally be hidden from other code

3) Attributes can optionally be made visible to other code, but made uneditable (only the code (Methods) in the Attribute's    Object can edit the Attribute)

Source: [ [1] ]
## Examples
### Python:
A class attribute is an attribute of the class (circular, I know), rather than an attribute of an instance of a class.

Let’s use an example to illustrate the difference. Here, class_var is a class attribute, and i_var is an instance attribute:

```python
class MyClass(object):
    class_var = 1

    def __init__(self, i_var):
        self.i_var = i_var
```

Note that all instances of the class have access to class_var, and that it can also be accessed as a property of the class itself

Source: [ [2] ]

## C++
Here the attributes of _Class Box_ are made public meaning they can be directly accessed by the user as you can see in the example below.

```C++
class Box
{
   public:
      double length;   // Length of a box
      double breadth;  // Breadth of a box
      double height;   // Height of a box
};

int main( )
{
    // box 1 specification
   Box1.height = 5.0; 
   Box1.length = 6.0; 
   Box1.breadth = 7.0;
}
```
Source: [ [3] ]

Here is an example of a Private attribute that is being changed using a **Mutator** method within the class. Attributes that are made private can only be changed this way.

```C++
class Time
{
        private:
                double x;

        public:
              void  setx(double p);


};

// Functions of Time
void Time::setx(double p)
{
    x =p;
}
```
Source:[ [4] ]

Now, lets say you don't want to change the value of x, but you need its value. In this case you need an **Accessor** method to return the value of x because it is still not accessible directly. Here is the same class with an added accsessor method to return x. (written in-line)

```C++
class Time
{
        private:
                double x;

        public:
              void  setx(double p);
              double getx(){return x}

              
};

```
Source:[ [4] ] 

(With modification)

For more examples of Accessor and Mutator methods see the wiki page [Methods].

Sources:
   1. https://en.wikibooks.org/wiki/A-level_Computing/AQA/Paper_1/Fundamentals_of_programming/Object-oriented_programming
   2. https://www.toptal.com/python/python-class-attributes-an-overly-thorough-guide
   3. http://www.tutorialspoint.com/cplusplus/cpp_classes_objects.htm
   4. http://www.cplusplus.com/forum/beginner/30452/

[1]:https://en.wikibooks.org/wiki/A-level_Computing/AQA/Paper_1/Fundamentals_of_programming/Object-oriented_programming
[2]:https://www.toptal.com/python/python-class-attributes-an-overly-thorough-guide
[3]:http://www.tutorialspoint.com/cplusplus/cpp_classes_objects.htm
[4]:http://www.cplusplus.com/forum/beginner/30452/
[Methods]:https://github.com/rugbyprof/2143-ObjectOrientedProgramming/wiki/Methods