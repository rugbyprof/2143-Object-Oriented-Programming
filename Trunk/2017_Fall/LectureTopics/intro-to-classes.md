# Introduction to Object-Oriented Programming
<sup>Source: https://www.udacity.com/wiki/classes</sup>

## The Basics

### Overview

A **Class** is just an organized collection of variables and functions. Classes are defined similarly to functions, with the following syntax:

```python
class MyClass(object):

    i = 123

    def say_hello(self):
        return 'Hi there!'
```
To use a class, you can create a representation of that class, called an **instance** or **object**, and assign it to a variable. For example:

```python
a = MyClass()
```

You can then call on the functions and variables defined within the class:

```python
>>> print a.i
123

>>> print a.say_hello()
"Hi there!"
```

The syntax we use to define a class can vary by preference. For example, we could have defined `MyClass`:

```python
class MyClass(object):

    def prepare(self):
        self.i = 123

    def say_hello(self):
        return 'Hi there!'
```

The `self` variable represents the object itself, and we use it inside procedures to refer to other functions and variables that are defined within the **scope** of our class. When we talk about a variable's scope, we're talking about the region in a program in which we can access that variable. For example, suppose we had the basic program:

```python
x = 2
y = 3
def add_nums():
    x = 5
    y = 6
    return x + y

print add_nums()
```

Before we reach the definition of `add_nums`, two variables `x` and `y` have been defined in the **global** scope. Furthermore, our add_nums procedure has created a second scope, and this scope is local to the function. Right now our environment looks like this:

![](https://lh3.googleusercontent.com/oWHIHNw-gelKiYuFu-cCtIbl286dEJvWiH3jsh57WF3Pt7mQz5GTnDE4zLNloeN667VU5e8TwAULXxqfZVey)

When executing a piece of code, Python _prefers_ to choose variables within its local scope. If it can't find the variable it's looking for, then it moves up to its enclosing environment, and repeats this process until the variable is either found, or a NameError Exception is thrown. So, when we call `print add_nums()` in the above snippet of code, the return value is `11`. However, if we call `add_nums` in the following snippet of code:

```python
x = 2
y = 3
def add_nums():
    y = 6
    return x + y

print add_nums()
```

the result will be `8`.

The idea of scope applies to Classes as well. Calling `self.some_variable` or `self.some_function` tells Python to look only inside the scope of the class for the respective variable or function. This helps to differentiate between those functions and variables that are defined outside of our class, or even defined within those functions that are _in_ the scope of our class. Going back to our `MyClass` code, here are some examples of how scope affects the behavior of our programs:

```python
def say_hi():
    return 'hi!'

i = 789

class MyClass(object):

    i = 5

    def prepare(self):
        i = 10
        self.i = 123
        print i

    def say_hi(self):
        return 'Hi there!'

    def say_something(self):
        print say_hi()

    def say_something_else(self):
        print self.say_hi()
```

```
>>> print say_hi()
hi!

>>> print i
789

>>> a = MyClass()

>>> a.say_something()
hi!

>>> a.say_something_else()
Hi there!

>>> print a.i
5

>>> a.prepare()
10

>>> print i
789

>>> print a.i
123
```

To recap, calling `self.variable` or `self.function` is a reference to those functions and variables that are local to our class, and ignores those functions and variables that are defined either outside of our class or even within a function that belongs to our class.

Also, note that all procedures that are defined in a class must be given at least this one parameter as a means of referring to the class itself. The class instance is automatically passed in as an argument when the function is called.

(The source code in this section is modified from the [Python documentation of Classes](http://docs.python.org/tutorial/classes.html).)

### Instantiation

The instantiation operation ("calling" a class object) creates an empty object. Many classes like to create objects with instances customized to a specific initial state. We mimicked this behavior with our `prepare` function, but Python has a special built-in method named `__init__()`, which evaluates when the object is created, to handle this type of object initialization:

```python
class MyClass(object):

    def __init__(self):
        self.i = 123

a = MyClass()

>>> print a.i
123
```
### Inheritance

Now, say we want to create two classes that are very similar in functionality, but not completely identical. For example, we want one class that can 'say hi' and that stores an integer in the variable 'i', but we want another class that can do all of those same things, as well as 'say hello'. To accomplish this, we can use the idea of **Inheritance** in object-oriented programming. Inheritance describes the process of setting up multiple classes where one or more of these classes **inherits** the functionality of another, base class. To write out our example in code:

```python
class MyClass(object):

    def __init__(self):
        self.i = 123

    def say_hi(self):
        return 'Hi there!'

class MyBetterClass(MyClass):

    def say_hello(self):
        return 'Hello!'

a = MyBetterClass()

>>> print a.say_hello()
Hello!

>>> print a.say_hi()
Hi there!

>>> print a.i
123
```

Note the syntax we used to tell our class `MyBetterClass` to inherit from `MyClass`:

```python
class MyBetterClass(MyClass):
    ...
```

When defining a class, placing the name of another class in parentheses next to the name of the class you are defining indicates that you want your class to inherit all of the functions and variables defined in the base class.

### When, Where, and Why

As you may have seen in either CS 101: Introduction to Computer Science/, or one of the other Udacity CS courses, when programs are written they typically try to model real word objects. For example, below is a candid photograph of my good friend Maryo during one of his infamous journeys through the wilderness.

![](https://lh3.googleusercontent.com/APo-IzYrPfHjyfo56S-l6ZXtS0yRREHGILwt8jmCBZUr2VJjhxecpdBEQK1gwu4xtVDpfp7ucRMfvu2tuw)

Right away we can list some of the different objects in the picture:

- Maryo
- Tree
- Monster
- Block

One way to model this world is to create a class for each of these objects, and we can use our imaginations to identify some of the properties and attributes the objects might have.

For example, perhaps our Maryo object can 'talk', has position coordinates, and a state of being either 'alive' or 'dead':

```python
class Maryo(object):
    #position coordinates
    x = 50
    y = 0

    #properties
    alive = True

    #actions
    def say_hi(self):
        if self.alive:
            print "It's me! Maryo!"
        else:
            print "This Maryo disappeared"

    def poof(self):
        self.alive = False
```

Our Tree object can 'grow', has position coordinates, and a state of being either 'alive' or 'dead':

```python
class Tree(object):
    #position coordinates
    x = 60
    y = 0

    #properties
    alive = True

    size = 3

    #actions
    def grow(self):
        if self.alive:
            self.size += 1
            print 'Grew to be %s meters tall' % self.size
        else:
            print 'This tree disappeared'

    def poof(self):
        self.alive = False
```

And our monster object can 'eat', has position coordinates, and a state of being 'alive' or 'dead'.

```python
class Monster(object):
    #position coordinates
    x = 85
    y = 10

    #properties
    alive = True

    size = 5

    #actions
    def eat(self):
        if self.alive:
            self.size += 5
            print 'Yum!'
        else:
            print 'This monster disappeared'

    def poof(self):
        self.alive = False
```

Nice! So now we have a basic programatic model of our world. But, we have to note that many of our objects share similar properties and attributes, such as position coordinates, state, and the unfortunate ability to 'poof'. Perhaps our model would benefit from simplicity if our objects **inherited** these properties and attributes from a base `character` model:

```python
class Character(object):

    def __init__(self, x, y, size = None):
        self.x = x
        self.y = y
        self.size = size
        self.alive = True

    def poof(self):
        self.alive = False
        print 'Poof!'

class Maryo(Character):

    def say_hi(self):
        if self.alive:
            print "It's me! Maryo!"
        else:
            print "This Maryo disappeared"

class Tree(Character):

    def grow(self):
        if self.alive:
            self.size += 1
            print 'Grew to be %s meters tall!' % self.size
        else:
            print 'This tree disappeared'

class Monster(Character):

    def eat(self):
        if self.alive:
            self.size += 5
            print 'Yum!'
        else:
            print 'This monster disappeared'
```

So for each class that we write to represent an object, if that class inherits from Character, then we only have to focus on defining the properties and attributes specific to that object, and all of the basic properties and attributes will inherently be included.

Example of how our world works:

```
>>> m, t, o = Maryo(50, 0), Tree(60, 0, 3), Monster(85, 10, 5)

>>> print t.size
3

>>> t.grow()
Grew to be 4 meters tall!

>>> print t.size
4

>>> print o.size
5

>>> o.eat()
Yum!

>>> print o.size
10

>>> print m.x, m.y
50 0

>>> m.say_hi()
Its me! Maryo!

>>> m.poof()
Poof!

>>> m.say_hi()
This Maryo disappeared

>>> print m.alive
False
```

Congratulations! You should now understand enough about object-oriented programming to get through Udacity's Intermediate level Computer Sciences courses, CS253, CS258, and CS262. However, we encourage you to continue reading the follow up Advanced section, Making A Game, below to see a more flushed out example of how and when to use objected-oriented programming. The source code for this text-based game is available to download at the bottom of this page, and is also posted on the Wiki for students, like you to collaborate and expand upon. Make a better game!

## The Advanced

### Making A Game

Suppose we want to make a game. To do so, we need various types of characters. Regardless of the type of game we're developing, different characters will likely have many similar properties, and will likely do many similar things (even though each character has its own differences). In order to avoid writing similar code for different characters, we can make a multi-purpose class to organize our code. Let's say our game involves characters that can move around, attack each other, obtain items that do various things, and use those items. We'll leave it up to you to come up with the details, and the purpose for this game.

The first step is to come up with all of the attributes of a character that every characters will have. One attribute is location. If our game is 2D, this will be composed of an x and y coordinate. If it's 3D, it will also include a z coordinate. Let's stick to a 2D platformer game, where our characters can move left and right. (In the future, we can support jumping and climbing to change a character's y coordinate, but we'll keep things simple for now.) We also want our characters to have hit points (HP), a number representing the life of the character---if the character gets attacked, its hit points go down. We also want a list of items that the character might have obtained. A real game will be much more complicated, but that should be enough for us.

```python
class Character(object):
    def __init__(self, x, y, hp):
        self.x = x
        self.y = y
        self.hp = hp
        self.items = []
```

Now we need to come up with things that our character can do. We've already described a few things. Let's define our character's motion first. We'll say our character can move one unit to the left or right.

```python
class Character(object):
    def __init__(self, x, y, hp):
        self.x = x
        self.y = y
        self.hp = hp
        self.items = []

    def move_left(self):
        self.x -= 1

    def move_right(self):
        self.x += 1
```

Now let's see our class in action:

```
>>>Alice = Character(0, 0, 100)

>>> Alice.move_right()

>>> Alice.move_right()

>>> Alice.x
2

>>> Alice.y
0

>>> Alice.hp
100
```

Now let's define attacking. We'll only let our character attack if there is another character adjacent to it at the same height. For now we'll just say attacking reduces a character's HP by 10.

```python
class Character(object):
    ...

    # the character can only attack an enemy (another instance of Character) if it is one square
    # away.
    def attack(self, enemy):
        if abs(enemy.x - self.x) == 1 and (enemy.y == self.y):
            enemy.hp -= 10
```

Let's see some action!

```python
# We're going to start Bob at (3, 0) since we moved Alice to (2,0) and he needs to be adjacent
# to attack.
>>> Bob = Character(3, 0, 100)

>>> Bob.attack(Alice)

>> Bob.hp
100

>>> Alice.hp
90

>>> Alice.attack(Bob)

>>> Bob.hp
90

>>> Alice.hp
90
```

I wonder who's going to win!

Now we notice several flaws in our game. Our character should not be able to move into a space with another character. Furthermore, we probably want other objects at different locations. Therefore, we probably want to know when a location is occupied, and when a character moves into a location we can mark it as occupied. To do this, we can use a list that represents our world map. Since that doesn't have much to do with object-oriented programming, we won't worry about that now.

However, now that we want various entities occupying locations, maybe we should have an Entity object. What do different entities have in common? Well an entity can be anything from a character to an object to a building. Really all they have in common is that they occupy a certain location. (Suppose we have a world map called world that's a 2-dimensional list that keeps track of what object is in each location. If there is no object in a given location, then we set the location to contain None.)

```python
class Entity(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        world[x][y] = self

    def remove(self):
        world[self.x][self.y] = None
```

Now we want to modify our character class to be an entity. We do this using inheritance. Since a character is an entity, but it's more specific than an entity, we will make Character a subclass of Entity, or say the Character class inherits from Entity. Here's how we do this:

```python
class Character(Entity):
    def __init__(self, x, y, hp):
        Entity.__init__(self, x, y)
        self.hp = hp
        self.items = []

    def move_left(self):
        self.x -= 1

    def move_right(self):
        self.x += 1

    def attack(self, enemy):
        if abs(enemy.x - self.x) == 1 and (enemy.y == self.y):
            enemy.hp -= 10
```

Now if we want to remove our character, we simply call Entity's remove method:

```python
Bob.remove()
```

Now suppose we want some wizards and some archers in our game. Since wizards and archers are characters, we can have them be subclasses of Character. We'll let our wizard cast a spell that can make enemies disappear! Here we go!

```python
class Wizard(Character):
    def __init__(self, x, y, hp):
        Character.__init__(self, x, y, hp)

    def cast_spell(self, enemy):
        if abs(enemy.x - self.x) == 1 and (enemy.y == self.y):
            enemy.remove()
```

We'll let our archer attack any enemy within a distance of 5.

```python
class Archer(Character):
    def __init__(self, x, y, hp):
        Character.__init__(self, x, y, hp)

    def range_attack(self, enemy):
        if abs(enemy.x - self.x) <= 5 and (enemy.y == self.y):
            enemy.hp -= 5
```

Now notice, we have this notion of enemy. But we don't define what an enemy is. Any character can be an enemy. So can we define a class called Enemy that inherits from Character? Another improvement we can make is, have a function that calculates the distance between two entities, so we don't need to repeat code like this:

```python
if abs(enemy.x - self.x) <= 5 and (enemy.y == self.y):
```

We'll let you improve upon this simple example, and feel free to post modifications of our code here! Hopefully, you now see how useful classes can be in reducing the amount of code you need to write, and making your code a lot more organized.

