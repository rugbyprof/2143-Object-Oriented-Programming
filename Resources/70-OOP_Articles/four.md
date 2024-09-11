

# Object-oriented programming is dead. Wait, really?

Original Article: https://towardsdatascience.com/object-oriented-programming-is-dead-wait-really-db1f1f05cc44

## Functional programming evangelists, you’re pointing your guns at the wrong enemy


<img src='./images/2*8TyJoz2oyfux06hOJujerQ.jpeg'>

Rhea Moutafis

Sep 20, 2020

>**If so many people are hating on object-oriented programming, why is it still so dominant?**

<!-- ![If so many people are hating on object-oriented programming, why is it still so dominant? Photo by
Vale Zmeykov on Unsplash](https://miro.medium.com/max/2000/1*r2xrdAE5CYUX6A1BT_0NXA.jpeg) -->

Programming in the 1960s had a big problem: computers weren’t that powerful yet, and somehow they
needed to split the capacities between data structures and procedures.

This meant that if you had a large set of data, you couldn’t do that much with it without pushing a
computer to its limits. On the other hand, if you needed to do a lot of things, you couldn’t use too
much data or the computer would take forever.

Then Alan Kay came around in 1966 or 1967 and theorized
that one could use encapsulated mini-computers that didn’t share their data, but rather communicated
through messaging. This way, compute resources could be used much more economically.

Despite the ingenuity of the idea, it would take until 1981 until object-oriented programming hit
the mainstream. Since then, however, it hasn’t stopped attracting new and seasoned software
developers alike. The market for object-oriented programmers is as busy as ever.

But in recent years, the decade-old paradigm has received more and more criticism. Could it be that,
four decades after object-oriented programming hit the masses, technology is outgrowing this
paradigm?

## Is coupling functions with data that stupid?

The main idea behind object-oriented programming is as simple as can be: you try to break a program
in parts that are as powerful as the whole. It follows that you couple pieces of data and those
functions that only get used on the data in question.

Note that this only covers the notion of encapsulation, that is, data and functions that sit inside
an object are invisible to the outside. One can only interact with the contents of an object through
messages, typically called getter and setter functions.

What is not contained in the initial idea, but is considered essential to object-oriented
programming today, are inheritance and polymorphism. Inheritance basically means that developers can
define subclasses that have all the properties that their parent class has. This wasn’t introduced
to object-oriented programming until 1976, a decade after its conception.

Polymorphism came to object-oriented programming another decade later. In basic terms, it means that
a method or an object can serve as a template for others. In a sense it’s a generalization of
inheritance, because not all properties of the original method or object need to be transmitted to
the new entity; instead, you can choose to override properties.

What’s special about polymorphism is that even if two entities depend on each other in the source
code, a called entity works more like a plugin. This makes life easier for developers because they
don’t have to worry about dependencies at runtime.

It’s worth mentioning that inheritance and polymorphism aren’t exclusive to object-oriented
programming. The real differentiator is encapsulating pieces of data and the methods that belong to
them. In a time where compute resources were a lot scarcer than today, this was a genius idea.

<img src='./images/1*ywsjK3i-bfWG_R5aWTaIVw.jpeg' width='300'>

## The five big problems in object-oriented programming

Once object-oriented programming hit the masses, it transformed the way developers see code. What
prevailed before the 1980s, procedural programming, was very machine-oriented. Developers needed to
know quite a bit about how computers work to write good code.

By encapsulating data and methods, object-oriented programming made software development more
human-centered. It matches human intuition that the method `drive()` belongs to the data group
`car`, but not to the group `teddybear`.

When inheritance came around, that was intuitive, too. It makes perfect sense that `Hyundai` is a
subgroup of `car` and shares the same properties, but `PooTheBear` does not.

This sounds like a powerful machinery. The problem, however, is that programmers who only know
object-oriented code will force this way of thinking on everything they do. It’s like when people
see nails everywhere because all they have is a hammer. As we will see below, when your toolbox
contains only a hammer, that can lead to fatal problems.

### The banana gorilla jungle problem

Imagine you’re setting up a new program, and you’re thinking about designing a new class. Then you
think back to a neat little class that you’ve created for another project, and you realize that it
would be perfect for what you’re currently trying to do.

No problem! You can reuse the class from the old project for your new one.

Except for the fact that this class may actually be a subclass of another class, so now you need to
include the parent class too. Then you realize that the parent class depends on other classes as
well, and you end up including heaps of code.

The creator of Erlang, Joe Armstrong, famously proclaimed:

> The problem with object-oriented languages is they’ve got all this implicit environment that they
> carry around with them. You wanted a banana but what you got was a gorilla holding the banana and
> the entire jungle.

That pretty much says it all. It’s fine to reuse classes; in fact, it can be a major virtue of
object-oriented programming.

But don’t take it to the extreme. Sometimes you’re better off writing a new class instead of
including masses of dependencies for the sake of DRY (don’t repeat yourself).

<img src='./images/1*XZJM1j9JIpnI7BJcVHQ1XQ.jpeg' width='300'>

### The fragile base class problem

Imagine you’ve successfully reused a class from another project for your new code. What happens if
the base class changes?

It can corrupt your entire code. You might not even have touched it. But one day your project works
like a charm, the next day it doesn’t because somebody changed a minor detail in the base class that
ends up being crucial for your project.

The more you use inheritance, the more maintenance you potentially have to do. So even though
reusing code seems very efficient in the short term, it can get costly in the long run.

### The diamond problem

Inheritance is this cute little thing where we can take properties of one class and transfer it to
others. But what if you want to mix the properties of two different classes?

Well, you can’t do it. At least not in an elegant way. Consider for example the class `Copier`. (I
borrowed this example, as well as some info about the problems presented here, from Charles
Scalfani’s viral story *Goodbye, Object Oriented Programming*.) A copier scans the content of a
document and prints it on an empty sheet. So should it be the subclass of `Scanner`, or of
`Printer`?

There simply is no good answer. And even though this problem isn’t going to break your code, it
comes up often enough to be frustrating.

### The hierarchy problem

In the diamond problem, the question was which class `Copier` is a subclass of. But I lied to you —
there is a neat solution. Let `Copier` be the parent class, and `Scanner` and `Printer` be
subclasses that only inherit a subset of the properties. Problem fixed!

That’s neat. But what if your `Copier` is only black-and-white, and your `Printer` can handle color,
too? Isn’t `Printer` in that sense a generalization of `Copier`? What if `Printer` is connected to
WiFi, but `Copier` is not?

The more properties you heap on a class, the more difficult it becomes to establish proper
hierarchies. Really, you’re dealing with clusters of properties, where `Copier` shares some, but not
all properties of `Printer`, and vice versa. And if you try to stick that into hierarchies, and you
have a big complex project, this might lead you to a messy disaster.


<img src='./images/1*r2o2OjtmKbUQJbDjGdLsSw.jpeg' width='300'>

### The reference problem

You might say, alright, then we’ll just do object-oriented programming without hierarchies. Instead,
we could use clusters of properties, and inherit, extend, or override properties as needed. Sure,
that would be a bit messy, but it would be an accurate representation of the problem at hand.

There’s just one problem. The whole point of encapsulation is to keep pieces of data safe from one
another and thus make computing more efficient. This doesn’t work without strict hierarchies.

Consider what happens if an object `A` overrides the hierarchy by interacting with another object
`B`. It doesn’t matter what relationship `A` has with `B`, except that `B` is not the direct parent
class. Then `A` must contain a private reference to `B`, because otherwise, it couldn’t interact.

But if `A` contains the information that the children of `B` also have, then that information can be
modified in multiple places. Therefore, the information about `B` isn’t safe anymore, and
encapsulation is broken.

Although many object-oriented programmers build programs with this kind of architecture, this isn’t
object-oriented programming. It’s just a mess.

## The danger of the single paradigm

What these five problems have in common is that they implement inheritance where it’s not the best
solution. Since inheritance wasn’t even included in the original form of object-oriented
programming, I wouldn’t call these problems inherent to object orientation. They’re just examples of
a dogma taken too far.

Not only object-oriented programming can be overdone, though. In pure functional programming, it’s
extremely difficult to process user input or print messages on a screen. Object-oriented or
procedural programming is much better for these purposes.

Still, there are developers who try to implement these things as pure functions and blow their code
up to dozens of lines that nobody can understand. Using another paradigm, they could have easily
reduced their code to a couple of readable lines.

Paradigms are a bit like religions. They’re good in moderation — arguably, Jesus, Mohamed and Buddha
said some pretty cool stuff. But if you follow them to the last little detail, you might end up
making the lives of yourself and of people around you quite miserable.

The same goes for programming paradigms. There’s no doubt that functional programming is gaining
traction, whereas object-oriented programming has attracted some harsh criticism in the last few
years.

It makes sense to get informed about new programming paradigms and use them when appropriate. If
object-oriented programming is the hammer that makes developers see nails wherever they go, is that
a reason to throw the hammer out the window? No. You add a screwdriver to your toolbox, and maybe a
knife or a pair of scissors, and you choose your tool based on the problem at hand.

Functional and object-oriented programmers alike, stop treating your paradigms like a religion.
They’re tools, and they all have their use somewhere. What you use should only depend on what
problems you are solving.



## The big question: are we on the cusp of a new revolution?

At the end of the day, the — admittedly rather heated — debate of functional versus object-oriented
programming boils down to this: could we be reaching the end of the era of object-oriented
programming?

More and more problems are coming up where functional programming is often the more efficient
option. Think data analysis, machine learning, and parallel programming. The more you get into those
fields, the more you’ll love functional programming.

But if you look at the status quo, there are a dozen offers for object-oriented programmers to one
offer for functional coders. That doesn’t mean you won’t get a job if you prefer the latter;
functional developers are still pretty scarce these days.

The most likely scenario is that object-oriented programming will stay around for another decade or
so. Sure, the avant-garde is functional, but that doesn’t mean you should ditch object-oriented yet.
It’s still incredibly good to have in your repertoire.

So don’t throw object-oriented programming out of your toolbox in the next few years. But make sure
that it’s not the only tool you have.

