Generally, the ability to appear in many forms. In object-oriented programming, polymorphism refers to a programming language's ability to process objects differently depending on their data type or class. More specifically, it is the ability to redefine methods for derived classes. For example, given a base class shape, polymorphism enables the programmer to define different area methods for any number of derived classes, such as circles, rectangles and triangles. No matter what shape an object is, applying the area method to it will return the correct results. Polymorphism is considered to be a requirement of any true object-oriented programming language.

Source: [ [1] ]

#Examples:

### Real life example of polymorphism:
Suppose if you are in class room that time you behave like a student, when you are in market at that time you behave like a customer, when you at your home at that time you behave like a son or daughter, Here one person have different-different behaviors.
![](http://www.tutorial4us.com/cpp/images/oops/polymorphism-example.png)

Source: [ [4] ]

### Python Example:
We create two classes:  Bear and Dog, both  can make a distinct sound.  We then make two instances and call their action using the same method.
```python
class Bear(object):
    def sound(self):
        print "Groarrr"
 
class Dog(object):
    def sound(self):
        print "Woof woof!"
 
def makeSound(animalType):
    animalType.sound()
 
 
bearObj = Bear()
dogObj = Dog()
 
makeSound(bearObj)
makeSound(dogObj)

```
Source: [ [2] ]

### Java Example:

Let us look at an example.

``` Java
public interface Vegetarian{}
public class Animal{}
public class Deer extends Animal implements Vegetarian{}
```
Now, the Deer class is considered to be polymorphic since this has multiple inheritance. Following are true for the above example:

A Deer IS-A Animal

A Deer IS-A Vegetarian

A Deer IS-A Deer

A Deer IS-A Object

When we apply the reference variable facts to a Deer object reference, the following declarations are legal:
```Java
Deer d = new Deer();
Animal a = d;
Vegetarian v = d;
Object o = d;
```
All the reference variables d,a,v,o refer to the same Deer object in the heap.

Source: [ [3] ]

#Sources:


1. http://www.webopedia.com/TERM/P/polymorphism.html
2. https://pythonspot.com/en/poylmorphism/
3. http://www.tutorialspoint.com/java/java_polymorphism.htm
4. http://www.tutorial4us.com/cpp/cpp-polymorphism

[1]: http://www.webopedia.com/TERM/P/polymorphism.html
[2]: https://pythonspot.com/en/poylmorphism/
[3]: http://www.tutorialspoint.com/java/java_polymorphism.htm
[4]: http://www.tutorial4us.com/cpp/cpp-polymorphism