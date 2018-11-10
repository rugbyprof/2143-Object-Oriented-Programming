Source: [ [1] ]

A user-defined prototype for an object that defines a set of attributes that characterize any object of the class. The attributes are data members (class variables and instance variables) and methods, accessed via dot notation.

Source: [ [2] ]

##C++

Classes are an expanded concept of data structures: like data structures, they can contain data members, but they can also contain functions as members.

An object is an instantiation of a class. In terms of variables, a class would be the type, and an object would be the variable.

Classes are defined using either keyword class or keyword struct, with the following syntax:


    class class_name {
      access_specifier_1:
        member1;
      access_specifier_2:
        member2;
      ...
    } object_names;


Where class_name is a valid identifier for the class, object_names is an optional list of names for objects of this class. The body of the declaration can contain members, which can either be data or function declarations, and optionally access specifiers.

Classes have the same format as plain data structures, except that they can also include functions and have these new things called access specifiers. An access specifier is one of the following three keywords: private, public or protected. These specifiers modify the access rights for the members that follow them:

  * Private members of a class are accessible only from within other members of the same class (or from their "friends").
  
  * Protected members are accessible from other members of the same class (or from their "friends"), but also from 
    members of their derived classes.
  
  * Finally, public members are accessible from anywhere where the object is visible.*  

By default, all members of a class declared with the class keyword have private access for all its members. Therefore, any member that is declared before any other access specifier has private access automatically. For example: 


    1 class Rectangle {
    2     int width, height;
    3   public:
    4     void set_values (int,int);
    5     int area (void);
    6 } rect;


Declares a class (i.e., a type) called Rectangle and an object (i.e., a variable) of this class, called rect. This class contains four members: two data members of type int (member width and member height) with private access (because private is the default access level) and two member functions with public access: the functions set_values and area, of which for now we have only included their declaration, but not their definition.

Notice the difference between the class name and the object name: In the previous example, Rectangle was the class name (i.e., the type), whereas rect was an object of type Rectangle. It is the same relationship int and a have in the following declaration:


    int a;
  

Where int is the type name (the class) and a is the variable name (the object). 

After the declarations of Rectangle and rect, any of the public members of object rect can be accessed as if they were normal functions or normal variables, by simply inserting a dot (.) between object name and member name. This follows the same syntax as accessing the members of plain data structures. For example: 


    1 rect.set_values (3,4);
    2 myarea = rect.area(); 


The only members of rect that cannot be accessed from outside the class are width and height, since they have private access and they can only be referred to from within other members of that same class.

Here is the complete example of class Rectangle:


    1 // classes example
    2 #include <iostream>
    3 using namespace std;
    4
    5 class Rectangle {
    6    int width, height;
    7  public:
    8    void set_values (int,int);
    9    int area() {return width*height;}
    10 };
    11
    12 void Rectangle::set_values (int x, int y) {
    13   width = x;
    14   height = y;
    15 }
    16
    17 int main () {
    18   Rectangle rect;
    19   rect.set_values (3,4);
    20   cout << "area: " << rect.area();
    21   return 0;
    22 }

Source: [ [3] ]
##Python:

The simplest form of class definition looks like this:


    class ClassName:
        <statement-1>
        .
        .
        .
        <statement-N>

Class objects support two kinds of operations: attribute references and instantiation.

Attribute references use the standard syntax used for all attribute references in Python: obj.name. Valid attribute names are all the names that were in the class’s namespace when the class object was created. So, if the class definition looked like this:


    class MyClass:
        """A simple example class"""
        i = 12345
        def f(self):
            return 'hello world'


Then MyClass.i and MyClass.f are valid attribute references, returning an integer and a function object, respectively. Class attributes can also be assigned to, so you can change the value of MyClass.i by assignment. __doc__ is also a valid attribute, returning the docstring belonging to the class: "A simple example class".

Class instantiation uses function notation. Just pretend that the class object is a parameterless function that returns a new instance of the class. For example (assuming the above class):


    x = MyClass()


Creates a new instance of the class and assigns this object to the local variable x.

The instantiation operation (“calling” a class object) creates an empty object. Many classes like to create objects with instances customized to a specific initial state. Therefore a class may define a special method named __init__(), like this:


    def __init__(self):
        self.data = []


When a class defines an __init__() method, class instantiation automatically invokes __init__() for the newly-created class instance. So in this example, a new, initialized instance can be obtained by:


    x = MyClass()


Of course, the __init__() method may have arguments for greater flexibility. In that case, arguments given to the class instantiation operator are passed on to __init__(). For example,


    >>>>>> class Complex:
    ...     def __init__(self, realpart, imagpart):
    ...         self.r = realpart
    ...         self.i = imagpart
    ...
    >>> x = Complex(3.0, -4.5)
    >>> x.r, x.i
    (3.0, -4.5)




##Sources:

  1. http://www.tutorialspoint.com/python/python_classes_objects.htm
  2. http://www.cplusplus.com/doc/tutorial/classes/ 
  3. https://docs.python.org/2/tutorial/classes.html

  [1]:http://www.tutorialspoint.com/python/python_classes_objects.htm
  [2]:http://www.cplusplus.com/doc/tutorial/classes/ 
  [3]:https://docs.python.org/2/tutorial/classes.html
