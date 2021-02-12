## Assignment 7 - Designing your Game
#### Due: 02-16-2021 (Tuesday @ 9:30 p.m.)

### Overview

When designing classes with the OOP mindset, you should follow a few principles to keep you out of trouble. I will list a few to help you when designing your poker game. 

#### Dry (Don't Repeat Yourself)

- Don't write duplicate code.
- A class should do its own thing. If two classes are doing the same thing, to the same data, maybe it should be its own class entirely.
- Similarly, if you have a block of code in more than two places consider making it a separate method.
  
#### Single Responsibility Principle (SRP)

- A class should be written to handle **one** defined thing, and handle it well. 
- The definition of "one" is the question here.
- Think along the lines of `decoupling`. For example when **ClassA** depends heavily on **ClassB**, the chances of **ClassA** being affected when **ClassB** is changed are high. We don't want this to happen.


#### Favor Composition over Inheritance

- We haven't discussed inheritance yet, but still here are a couple of points to think about.
- To favor composition over inheritance is a design principle that gives the design higher flexibility. 
- It is more natural to build classes out of various separate components rather than trying to find commonality between them in order to create an inheritance hierarchy.

#### Requirements / Attributes

When writing "requirements" for your classes (and we are following a very **loose** design process for now) you should think in the following terms:  
- The ***\<thing\>*** should provide ***\<something\>*** so we can do ***\<this\>***. 
- They don't ALL have to fit this exactly, but each "requirement" or "attribute" should at least have a ***\<subject\>*** => ***\<verb\>*** approach.

**Example:**

- A **score** (the \<**thing**\>) should know its **value** (the <**something**\>) so it can be **displayed** (the \<**this**\>) on a game window.
- A player (the \<**thing**\>) should know its **location** (the <**something**\>) so it can be **checked** (the \<**this**\>) for collisions.
- Without all the keywords embedded now:
  - A debris item should know its speed and direction so we can update its location.
  - A player should know its speed and direction so we can update its location.

What do we notice about a debris item and a player? Seems to be a lot of overlap! We can leverage that information in our design!

Lets look at some of the requirements for our game, and then think about designing it. 

### Possible Classes

#### Player
  - Has a Shape 
  - Has a Size
  - Has a Color
  - Has a Speed
  - Has a Location (could change) 
  - Can move in any direction using keys
  - Has a score
  - Can collide with other "objects"

#### Debris
  - Has a Shape 
  - Has a Size
  - Has a Color
  - Has a Speed
  - Has a Location (could change) 
  - Can move in any direction
  - Can collide with other "objects"
  
#### Scoring
  - When a `Player` comes collides with `Debris` score is negatively effected.
  - When a piece of `Debris` leaves game screen (on the left), score is positively effected.

#### Text
  - Has a Font (can change)
  - Has a Location
  - Has a Color
  - Has a Size

#### Game
  - Has player(s)
  - Has score(s)
  - Has debris(s) (yes "debris" can be plural but it doesn't make the point)

### UML Unified Modeling Language

At the start of this document, we discuss some heuristics for designing your classes (dry method, single responsibility, etc.) but how do we turn that into an actual class design? 
One way is to use UML to visually model your classes using UML. This is where we are gonna start for our first program. I have an overview of [UML](../../Resources/04-UML/README.md) in the resources folder. However, there is a video from a site called Lucidcharts that explains it in a very understandable and concise way. Better than I could do :) 

[![Class Diagram Video](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_vid_250.png)](https://www.youtube.com/embed/UI6lqHOVHic) 

You can use lucidcharts to do your diagrams, or you can use [draw.io](https://draw.io) to make your diagrams. Lucidchart is free to some extent, but it makes you create an account where  [draw.io](https://www.draw.io/) does not. 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step1" width="250">

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step2" width="250">

### Example Document

You would replace the example lables with your game labels:

```
### Person

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.person" width="200">

### Street

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.street" width="200">

### Student

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.student" width="200">

### Professor

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.professor" width="200">

### Diagram

<img src="draw.io.wholething" width="400">
```
Would result in:

### Person

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.person.png" width="150">

### Street

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.street.png" width="150">

### Student

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.student.png" width="150">

### Professor

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.professor.png" width="150">

### Diagram

<img src="draw.io.wholething.png" width="400">


### Deliverables

- Create a folder called `A07` in your `Assignments` folder. 
- Add a `README.md` file in your `A07` folder with all of your class designs listed in an orderly fashion.
- Your document should be written in markdown. 
- Don't forget to include your Name and essentials at the top of the document.
- No hand written anything will be graded.
- Bring a print out of your readme to class on the due date.
- There is an extension called `Markdown PDF` that will convert markdown files to PDF's to assist in printing.
- If your not using VSCode then you can replace `github` with `gitprint` in the url of your readme and print it that way.
- Don't forget your banner (cover page).

```
A07
2143
LASTNAME
```
- If your banner is wrong - you lose a letter grade. Its VERY confusing if you don't include the correct banner.