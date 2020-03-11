## Object-Oriented Programming

### History: The Rise and Decline of Structured Programming

For many years (roughly 1970 to 1990), *structured programming* was the most common way to organize
a program. This is characterized by a functional-decomposition style - breaking the algorithms in to
every smaller functions. This technique was a great improvement over the ad hoc programming which
preceded it. However, as programs became larger, structured programming was not able control the
exponential increase in complexity.

#### The Problem - Complexity

Complexity measurements grow exponentially as the size of programs grow. One measurement is
*coupling*, or much different elements (modules, data structures) interact with each other. The
fewer the connections, the less complex a program is. Low coupling is highly desirable.

There have been several post-structured programming attempts to control complexity. One of these is
to use software *components* - preconstructed software "parts" to avoid programming. And when you
have to program, use *object-oriented programming* (OOP).

### Object-Oriented Programming (OOP)

Object-Oriented Programming groups related data and functions together in a *class*, generally
making data private and only some functions public. Restricting access decreases coupling and
increases cohesion. While it is not a panacea, it has proven to be very effective in reducing the
complexity increase with large programs. For small programs may be difficult to see the advantage of
OOP over, eg, structured programming because there is little complexity regardless of how it's
written. Many of the mechanics of OPP are easy to demonstrate; it is somewhat harder to create
small, convincing examples.

OOP is often said to incorporate three techniques: inheritance, encapsulation, and polymorphism. Of
these, you should first devote yourself to choosing the right classes (possibly difficult) and
getting the encapsulation right (fairly easy). Inheritance and polymorphism are not even present in
many programs, so you can ignore them at that start.

#### Encapsulation

*Encapsulation* is grouping data and functions together and keeping their implementation details
private. Greatly restricting access to functions and data reduces *coupling*, which increases the
ability to create large programs.

Classes also encourage *coherence*, which means that a given class does one thing. By increasing
coherence, a program becomes easier to understand, more simply organized, and this better
organization is reflected in a further reduction in coupling.

#### Inheritance

*Inheritance* means that a new class can be defined in terms of an existing class. There are three
common terminologies for the new class: the *derived* class, the *child* class, or the *subclass*.
The original class is the *base* class, the *parent* class, or the *superclass*. The new child class
inherits all capabilities of the parent class and adds its own fields and methods. Altho inheritance
is very important, especially in many libraries, is often not used in an application.

#### Polymorphism

*Polymorphism* is the ability of different functions to be invoked with the same name. There are two
forms.

*Static polymorphism* is the common case of *overriding* a function by providing additional
definitions with different numbers or types of parameters. The compiler matches the parameter list
to the appropriate function.

*Dynamic polymorphism* is much different and relies on parent classes to define *virtual functions*
which child classes may redefine. When this virtual member function is called for an object of the
parent class, the execution dynamically chooses the appropriate function to call - the parent
function if the object really is the parent type, or the child function if the object really is the
child type. This explanation is too brief to be useful without an example, but that will have to be
written latter.

<sub>Source: http://www.fredosaurus.com/</sub>