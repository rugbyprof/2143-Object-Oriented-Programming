# Abstract Factory Pattern

```python
"""Implementation of the abstract factory pattern

This type of design pattern comes under creational pattern as this pattern provides one of the best ways to create an object. In Factory pattern, we create object without exposing the creation logic to the client and refer to newly created object using a common interface.

"""
import random

class PetShop:
    """A pet shop"""

    def __init__(self, animal_factory=None):
        """pet_factory is our abstract factory.
        We can set it at will."""

        self.pet_factory = animal_factory

    def show_pet(self):
        """Creates and shows a pet using the
        abstract factory"""

        pet = self.pet_factory.get_pet()
        print "This is a lovely", pet
        print "It says", pet.speak()
        print "It eats", self.pet_factory.get_food()

# Stuff that our factory makes

class Dog:
    def speak(self):
        return "woof"
    def __str__(self):
        return "Dog"

class Cat:
    def speak(self):
        return "meow"
    def __str__(self):
        return "Cat"

# Factory classes

class DogFactory:
    def get_pet(self):
        return Dog()
    def get_food(self):
        return "dog food"

class CatFactory:
    def get_pet(self):
        return Cat()
    def get_food(self):
        return "cat food"

# Create the proper family
def get_factory():
    """Let's be dynamic!"""
    return random.choice([DogFactory, CatFactory])()

# Show pets with various factories
shop = PetShop()
for i in range(3):
    shop.pet_factory = get_factory()
    shop.show_pet()
    print "=" * 10
```
```
Sample output:

This is a lovely Dog
It says woof
It eats dog food
==========
This is a lovely Cat
It says meow
It eats cat food
==========
This is a lovely Cat
It says meow
It eats cat food
==========
```
