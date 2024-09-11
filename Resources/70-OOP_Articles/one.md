

<img src ='./images/1*6rqSrrz_Q5m80KZM9XbqRg.jpeg' width=300>


## The Rise and Fall of Object Oriented Programming

Original Article: https://medium.com/machine-words/the-rise-and-fall-of-object-oriented-programming-d67078f970e2

<img src ='./images/2*BVH6Hf_V03dmMllfRl_L2g.jpeg' width=60>


Author: Talin
Nov 20, 2018 

No, object-oriented programming (OOP) is not dead. But it is significantly less ubiquitous than it
used to be.

I remember back in the 90s there were a lot of textbooks and computer science courses on
introductions to object-oriented programming. It was “the thing”, the next wave. If you didn’t
program in that style, you were a bad programmer, or at least sadly behind the curve.

Back then, CS students were taught OOP in a very strict and dogmatic way. Not only were
practitioners encouraged to structure their applications in the form of objects and classes, they
were even supposed to think about the *problem space* in terms of objects and classes as well. This
practice was known as “Object-Oriented Analysis and Design”.

However, as the years went by, people started to realize that the strict approach to object
orientation created a number of problems. These problems tended to be of the kind that makes code
complex, hard to understand, and hard to test.

It turned out that OOP was better suited to some problem domains than others. For example, OOP is
still the most natural way of building user interfaces — windows and buttons. But trying to adapt
object-orientation to relational databases has been an ongoing disaster.

Here are a number of problems that I’ve observed:

### **The “Platypus” effect**

The real world doesn’t always break down into neat categories with well-defined properties. For
example, suppose you create a class hierarchy that represents the animal kingdom. Over here, you’ve
got your reptiles — cold blooded, scaly, egg-laying and so on. Over there you’ve got your mammals —
warm blooded, furry, bearing live young. And so on with birds, amphibians, invertebrates, etc.

And then along comes a platypus, which doesn’t seem to fit into any of your categories. What do you
do? Do you create a brand new category, or do you rethink your entire classification scheme? Either
approach can have significant costs in terms of effort and program complexity.

*(Thanks to Anselm Hook for coining the term “platypus effect”.)*

### **Deep class hierarchies**

I remember when I worked at Google, there was a JavaScript library, goog.ui, for creating web-based
user interfaces. Here’s an example of the inheritance hierarchy for one of the UI components in this
library:

```txt
    class ToolbarColorMenuButton
    * inherits from ColorMenuButton
      * inherits from MenuButton
        * inherits from Button
          * inherits from Control
            * inherits from Component
              * inherits from EventTarget
                * inherits from Disposable
                  * inherits from Object
```

Nine levels of classes. That’s a *lot*.

It gets worse, though.

Many of those higher-level classes are “polluted” with methods and properties that are only relevant
to a small number of subclasses. For example, the “Control” class has over *ninety* methods. It has
methods for setting states, even if a specific subclass is stateless; it has methods for adding and
removing children, even if it makes no sense for a control to have children.

A big reason for this complexity is that the authors of this library were trying to organize
different aspects of the components — such as whether a component is a button or a slider, or
whether it has color — by putting them into different parts of the class hierarchy.

But these different aspects really have nothing to do with each other. The fact that a coffee cup is
red, and the fact that it is made of ceramic, are mostly independent properties. It is no more
correct to put a red coffee cup into a “category of red things” than it is to put it into the
category of “things made from ceramics”, or even “housewares”. Either one is an arbitrary choice,
because categories are *mental and social constructs*.

During my last couple years working at Google, I created a new user interface toolkit called
“Quantum Wiz” that was intended as a replacement for goog.ui. One of the rules we had (in typical
Google style, written as an equation) was:

```txt
    composition > inheritance
```

In plain English, what this says is:

>***“Prefer composition — that is, the ability to assemble the functionality of a component out of smaller building blocks — rather than inheritance as a means of code re-use.”***

So for example, if a button has a color, rather than making a new “Color Button” class, you would
take a regular “Button” object and add a “Color” aspect to it, either as a property or as a child
object.

As a result of this mandate, the class hierarchy for the new toolkit was relatively shallow, only
two or three levels if I recall correctly. And it was much easier to understand and work with, as
well as being more *powerful.*

*(Thanks to Malte Ubl for introducing me to the concept of composition \> inheritance.)*

### **Objects aren’t real**

Buckminster Fuller once said: “there are no things”. What he meant is that the distinction between
one thing and another is largely a human prejudice.

For example, the couch that I am sitting on is a collection of atoms that are bound together by
molecular forces. However, those atoms also experience forces from other objects in the room — the
carpet, the end table, even the air within the room. And the couch itself is comprised of various
parts — fabric, wood, metal springs — that are also bound by molecular forces. Is the couch one
object, or many? Maybe there’s only one object — the entire universe.

Because human vision and touch are largely responsive to surface properties — color and texture — we
tend to classify the world based on surfaces. Imagine, instead, if we could directly sense the
molecular composition within the objects around us. We might see a “copper” object representing all
of the wiring and plumbing in the house, a “nitrogen” object representing the gaseous contents of
the rooms, a “water” object, a “wood” object, and so on.

>**Fuller’s point is that our ability to “parse” the world into discrete “things” is arbitrary and is more a reflection of our human psychology than physical reality.**

Because object oriented inheritance is about organizing things into classes, it doesn’t model the
real world very well; what it *does* model well is the way humans *think* about the real world.

### Methods aren’t real, either

I remember an episode from about twenty years ago where a technical representative from a software
vendor was trying to explain OOP to the engineering staff at my company. He was trying to argue that
object-orientation was a way to model the real world, and the example he gave was something like a
coffee cup. He said that the cup might have a `drink()` method.

What I remember is that I had a very strong reaction to this — I thought what he was saying was
utter nonsense. A physical object has many uses other than the specific purpose for which it was
built. I can use a coffee cup as a paperweight or a doorstop; does that mean that it has a
`holdDownPapers()` or `keepDoorOpen()` method? I can use it as a weapon, a toy, or a work of art. I
can even shatter the cup into fragments, or grind it into powder, and use the remnants in creative
ways.

(I think the poor fellow was rather taken aback by my rebuttal.)

### Internal vs External Logic

One of the precepts of the strict OOP style was that it should never be possible to change the
internal state of an object from the outside. Any business or application logic that alters the
object’s state has to be implemented as methods on the object itself. So, for example, if you wanted
to erase all the text in a text field, you couldn’t simply say:

```cpp
    textField.value = ""; // Set to empty string
```

That would be against the rules. Instead you had to say something like:

```cpp
    textField.clear(); // Clear the content of the field
```

And for simple kinds of operations, this is fine. But it’s all too easy to get carried away,
especially when the operations being performed deal with complex relationships between objects.

Sometimes it’s better if the algorithm exists outside of any object. It’s really a question of
emphasis: for this problem set, do you care more about the *nouns* or the *verbs*?

Here’s a concrete example: Recently I started work on a compiler (writing compilers is a hobby of
mine; I’ve invented a number of scripting languages during my time as a game developer). In the
past, when I’ve written compilers, I’ve taken a very strict OOP approach to the design of the
internal data structures. There are various class hierarchies representing abstract syntax trees,
expression graphs, types, and so on.

Typically a compiler processes these data structures through a series of phases or “passes”, the
output of each pass being fed into the input of the next pass.

In the past, I’ve tended to put a some of the logic for each pass in the individual objects being
operated on, per the recommended OOP style. This had the unfortunate consequence that as I added
more passes, the more complex the objects became.

Worse, it made writing unit tests for those objects very difficult. These complex objects needed a
lot of infrastructure before they could even be created. And this meant that in order to test an
object, I had to create a lot of scaffolding to satisfy all of the prerequisites.

As a result, my test coverage tended to be poor, since writing the tests was an exhausting amount of
work.

Recently, I’ve taken a different approach. In my latest compiler, all of these internal data
structures are “dumb”, meaning that all they do is hold data and nothing else. All of the code for
manipulating and transforming the objects is external to those objects.

This has had a significant benefit in the organization of the code. Each algorithm is concentrated
in one place rather than being spread out over a bunch of source files. When I want to test a given
compiler pass, I can easily create a few sample objects and feed it to that pass. As a consequence,
my tests are easier to write, which means I write more tests, which means that I have much better
test coverage than I did previously.

### Relational Databases

Earlier I mentioned the problem with dealing with relational databases in an object-oriented way.
Object-Relational Mapping (ORM) has been dubbed by one pundit as The Vietnam of Computer Science.
(Warning — that article is long, esoteric and somewhat tendentious.)

My general feeling is that when working with large data, you shouldn’t think of your records as
“objects”. Relational databases are very powerful, but the power they offer is not very
“object-like”. I tend to think of relational streams of data as more like a *fluid*, where you
divide, transform, and combine data using algebraic operations.

*(Thanks to Guido Van Rossum for pointing out the link to the above article on ORMs.)*

### Functional Programming

In the last decade or so, there has been increasing interest in *functional programming* (FP). Like
OOP, functional programming isn’t just one thing, but rather a collected set of stylistic
principles. However, the gist of it is that while OOP focuses on *interacting* or *communicating*
with objects, in FP the emphasis is on *transforming* them. By “transforming” I mean that you take
some object, pass it into a function, and the result is a brand new object that represents some
transformation of the input. The original object is either kept around or thrown away, but it is not
modified or altered in any way.

In my own programming, I prefer a “hybrid” approach that uses FP techniques in some places, and OOP
techniques in others. There are some kinds of problems where FP really shines, and others where OOP
is an obvious choice.

I know that a lot of FP enthusiasts are fervent advocates of “pure” functional languages, in which
all objects are immutable, and can only be transformed, not modified. However, I have found that the
pure approach tends to take certain relatively straightforward programming exercises and turn them
into *puzzles*, by which I mean clever, non-obvious tricks that amuse and appeal to the kind of
person who enjoys brain teasers, but which is completely inscrutable to everyone else.

As a result, I tend to use FP where I think it makes sense, and in ways that I think that an average
programmer reading my code will understand. If I am tempted to do anything clever, I’ll write a long
comment explaining what I have done and how it works (which satisfies my need to show off — I often
think programming should be a performing art.)


So object-oriented programming isn’t what it used to be. It’s still a great tool, and worth
learning. But it has been knocked off of it’s pedestal, and you hardly ever see anyone advocating it
with the kind of religious fervor that you might have seen twenty-five years ago.


