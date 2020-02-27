## OOP: Copy Constructors

### When copies of objects are made

A *copy constructor* is called whenever a new variable is created from an object. This happens in
the following cases (but not in assignment).

  - A variable is declared which is *initialized from another object*, eg,
    
    ``` fragment
    Person q("Mickey"); // constructor is used to build q.
    Person r(p);        // copy constructor is used to build r.
    Person p = q;       // copy constructor is used to initialize in declaration.
    p = q;              // Assignment operator, no constructor or copy constructor.
    ```

  - A value parameter is initialized from its corresponding argument.
    
    ``` fragment
    f(p);               // copy constructor initializes formal value parameter.
    ```

  - An object is returned by a function.

C++ calls a *copy constructor* to make a copy of an object in each of the above cases. If there is
no copy constructor defined for the class, C++ uses the default copy constructor which copies each
field, ie, makes a *shallow copy*.

### Don't write a copy constructor if shallow copies are ok

If the object has no pointers to dynamically allocated memory, a shallow copy is probably
sufficient. Therefore the default copy constructor, default assignment operator, and default
destructor are ok and you don't need to write your own.

### If you need a copy constructor, you also need a destructor and `operator=`

If you need a copy constructor, it's because you need something like a deep copy, or some other
management of resources. Thus is is almost certain that you will need a destructor and override the
assignment operator.

### Copy constructor syntax

The copy constructor takes a reference to a `const` parameter. It is `const` to guarantee that the
copy constructor doesn't change it, and it is a reference because a value parameter would require
making a copy, which would invoke the copy constructor, which would make a copy of its parameter,
which would invoke the copy constructor, which ...

Here is an example of a copy constructor for the `Point` class, which doesn't really need one because
the default copy constructor's action of copying fields would work fine, but it shows how it works.

```cpp

//=== file Point.h =============================================
class Point {
    public:
        //. . .
        Point(const Point& p);   // copy constructor
        //. . .
//=== file Point.cpp ==========================================
// . . .

Point::Point(const Point& p) {
    x = p.x;
    y = p.y;
}

//. . .
//=== file my_program.cpp ====================================
//. . .

Point p;            // calls default constructor
Point s = p;        // calls copy constructor.
p = s;              // assignment, not copy constructor.

```

### Difference between copy constructor and assignment

A copy constructor is used to initialize a *newly declared* variable from an existing variable. This
makes a deep copy like assignment, but it is somewhat simpler:

1.  There is no need to test to see if it is being initialized from itself.
2.  There is no need to clean up (eg, delete) an existing value (there is none).
3.  A reference to itself is not returned.


<sub>Fred Swartz: http://www.fredosaurus.com/</sub>
