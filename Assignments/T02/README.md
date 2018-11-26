## Test 2 Study Guide

```cpp

class Rectangle{
    float width;
    float height;
};
```

Consider the class above. Write an appropriate default constructor setting `width` and `height` to zero and an overloaded constructor that would allow the `width` and `height` to be set by the user when an instance of `Rectangle` was created.

------

Add the appropriate code to the `Rectangle` class that would allow a `Rectangle` to be printed like so:

```cpp
Rectangle R1(3.4,5.8);

cout<<R1<<endl;

// Would print: {w:3.4,h:5.8}
```

------

Write a code snippet that would allow two Rectangles to be added together like so:

```cpp

Rectangle R1(3.6,5.0);
Rectangle R2(2.4,7.0);

R1 = R1 + R2;

cout<<R1<<endl;

// Would print: {w:6.0,h:12.0}
```

-----

Add a property to the `Rectangle` class that would keep track of how many rectangles have been created during the life of your program. 

----

The previous question would add 1 to some value every time a `Rectangle` was instantiated keeping a total count of "created" `Rectangles`. What if I wanted to decrement that number each time a `Rectangle` was destroyed?

-----

Write a copy constructor for the rectangle class and overload the assignment operator.

-----

Write two versions of a hierarchy of point, line, and polygon classes one using inheritance and one using composition.  

Which makes more logical sense? 

Which do you think you would use more often: inheritance vs composition?

-----


- https://repl.it/@rugbyprof/ObeseListLovers
- https://repl.it/@rugbyprof/overloadingoperatorslist
- https://repl.it/@rugbyprof/classconstructors
- https://repl.it/@rugbyprof/listcopyconstructor
- https://repl.it/@rugbyprof/staticobjectcounter
- https://repl.it/@rugbyprof/listcopyconstructor
- https://repl.it/@rugbyprof/overloadingoperatorslist
