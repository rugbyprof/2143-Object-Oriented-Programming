---
title: "Factory Methods in C++"
subtitle: "Constructors, Static Factories, and the Factory Method Design Pattern"
language: C++
level: Intermediate Object-Oriented Programming
topics:
  - Object Creation
  - Static Member Functions
  - Factory Method Pattern
  - Polymorphism
  - Encapsulation
---

# Factory Methods in C++

## 1. Introduction

Object creation is a fundamental responsibility in object-oriented programming. In C++, objects are typically created using constructors. However, as applications become more complex, constructors may not provide the flexibility or clarity needed to create different configurations of objects.

**Factory methods** provide an alternative by encapsulating object creation inside a function.

A factory method is responsible for creating and returning an object, allowing the calling code to focus on using the object rather than constructing it.

This handout examines three approaches:

1. Traditional constructors
2. Static factory methods
3. The Factory Method design pattern

Although these approaches share similarities, they solve different problems.

---

## 2. Traditional Constructors

Consider a `Deck` class representing a standard deck of playing cards.

Each card is represented by an integer from `0` to `51`.

Using this encoding:

- `card / 13` determines the suit (0–3).
- `card % 13` determines the rank (0–12).

A simple implementation might be:

```cpp
#include <vector>
#include <numeric>

class Deck {
private:
    std::vector<int> cards;

public:
    Deck() {
        cards.resize(52);
        std::iota(cards.begin(), cards.end(), 0);
    }
};
```

Creating a deck:

```cpp
Deck deck;
```

This approach works well when every `Deck` is constructed the same way.

### Limitations

Suppose the application must support several card games:

- War: 52 cards
- Euchre: 24 cards
- Pinochle: 48 cards, including duplicate cards

We could introduce overloaded constructors:

```cpp
Deck();
Deck(int deckType);
```

Usage:

```cpp
Deck deck(2);
```

But what does `2` mean?

This design introduces ambiguity and requires developers to remember special parameter values.

We could replace the integer with a descriptive type, but another option is to use **named factory methods**.

---

## 3. Static Factory Methods

A static factory method is a static member function that creates and returns an object.

Because the method is static, it belongs to the class rather than to a particular instance.

Consider:

```cpp
#include <vector>

class Deck {
private:
    std::vector<int> cards;

    Deck() = default;

public:
    static Deck standard();
    static Deck euchre();

    const std::vector<int>& getCards() const {
        return cards;
    }
};
```

The private constructor prevents ordinary default construction. Clients must use one of the public factory methods.

### Implementation

```cpp
Deck Deck::standard() {
    Deck deck;

    for (int i = 0; i < 52; ++i) {
        deck.cards.push_back(i);
    }

    return deck;
}

Deck Deck::euchre() {
    Deck deck;

    // Ranks 9 through Ace, using 0-12 rank encoding.
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 7; rank < 13; ++rank) {
            deck.cards.push_back(suit * 13 + rank);
        }
    }

    return deck;
}
```

### Usage

```cpp
Deck warDeck = Deck::standard();
Deck euchreDeck = Deck::euchre();
```

This syntax communicates the intended object configuration directly.

Unlike a constructor, a static factory method can have a descriptive name.

### Why use `static`?

A static member function:

- Can be called without an existing object.
- Cannot directly access non-static members without an object.
- Can create and return new objects.
- Can access private constructors and private members of its class.

The factory methods above create a local `Deck`, populate it, and return it by value.

Modern C++ supports efficient return-by-value through copy elision and move semantics. In this example, named return value optimization (NRVO) may eliminate the copy or move entirely.

### Important distinction

A static factory method is a common object-creation technique.

**It is not necessarily the formal Factory Method design pattern.**

---

## 4. The Factory Method Design Pattern

The Factory Method pattern is one of the Gang of Four (GoF) creational design patterns.

Its purpose is to define an interface for object creation while allowing subclasses to determine which objects are created.

The important difference is **polymorphism**.

A static factory selects what to create using ordinary function calls or parameters.

The traditional Factory Method pattern delegates creation decisions to subclasses through virtual functions.

### Example: Deck Factory Hierarchy

First, define an abstract factory interface:

```cpp
class DeckFactory {
public:
    virtual ~DeckFactory() = default;

    virtual Deck createDeck() const = 0;
};
```

This class cannot be instantiated because `createDeck()` is pure virtual.

Concrete factories implement the creation behavior.

```cpp
class StandardDeckFactory : public DeckFactory {
public:
    Deck createDeck() const override {
        return Deck::standard();
    }
};

class EuchreDeckFactory : public DeckFactory {
public:
    Deck createDeck() const override {
        return Deck::euchre();
    }
};
```

Both subclasses implement the same interface but produce differently configured decks.

### Using Polymorphism

```cpp
void initializeGame(const DeckFactory& factory) {
    Deck deck = factory.createDeck();

    // Initialize the game using this deck.
}
```

The function does not need to know which concrete factory it receives.

```cpp
StandardDeckFactory standard;
EuchreDeckFactory euchre;

initializeGame(standard);
initializeGame(euchre);
```

This is an example of **runtime polymorphism**.

The specific factory implementation determines which deck is created.

### A Design Pattern Nuance

The example above is a simplified polymorphic factory interface. In the canonical GoF Factory Method pattern, a creator class typically defines a virtual creation operation that subclasses override, often while the creator also performs other operations using the created product.

The essential teaching concept is the same: subclasses customize object creation through polymorphism.

---

## 5. Static Methods Cannot Be Virtual

One important C++ restriction is that a static member function cannot be declared `virtual`.

The following is invalid:

```cpp
class Factory {
public:
    // Invalid C++
    // virtual static Deck create();
};
```

Why?

Virtual functions operate through an object's dynamic type.

Static functions belong to the class and do not have a `this` pointer.

Therefore, static member functions cannot participate in virtual dispatch.

If object creation must vary through inheritance, use a non-static virtual member function.

If inheritance is unnecessary, a static factory is often simpler.

---

## 6. Using a Separate Factory Class

Another option is to move object creation into a dedicated class.

```cpp
#include <stdexcept>
#include <string>

class DeckFactory {
public:
    static Deck create(const std::string& game) {
        if (game == "war") {
            return Deck::standard();
        }

        if (game == "euchre") {
            return Deck::euchre();
        }

        throw std::invalid_argument("Unknown game");
    }
};
```

Usage:

```cpp
Deck deck = DeckFactory::create("war");
```

This design separates the responsibility of creating decks from the `Deck` class's responsibility for managing cards.

However, it introduces another class into the application.

A separate factory becomes more useful when creation requires substantial configuration, external dependencies, or coordination among multiple object types.

For a simple card game, it may provide little practical benefit.

---

## 7. Comparing Object-Creation Techniques

| Feature                                                                | Constructor                    | Static Factory            | GoF Factory Method   |
| ---------------------------------------------------------------------- | ------------------------------ | ------------------------- | -------------------- |
| Creates objects                                                        | Yes                            | Yes                       | Yes                  |
| Descriptive creation names                                             | No                             | Yes                       | Yes                  |
| Requires inheritance                                                   | No                             | No                        | Typically            |
| Supports virtual dispatch                                              | No                             | No                        | Yes                  |
| Can return different configurations                                    | Yes                            | Yes                       | Yes                  |
| Can return different concrete product types through a common interface | No                             | Yes                       | Yes                  |
| Complexity                                                             | Low                            | Low                       | Moderate             |
| Typical use                                                            | Straightforward initialization | Named creation operations | Polymorphic creation |

The Factory Method pattern is not inherently better than a static factory.

It provides additional flexibility at the cost of additional abstraction.

---

## 8. Choosing the Appropriate Approach

### Use constructors when:

- Object initialization is straightforward.
- There is one obvious way to construct the object.
- Constructor parameters clearly describe the desired object.
- No specialized creation logic is necessary.

### Use static factory methods when:

- Multiple named configurations are available.
- Construction requires internal setup.
- The application benefits from descriptive creation methods.
- Polymorphism is unnecessary.

### Use the Factory Method pattern when:

- Different subclasses must customize object creation.
- The application works through an abstract interface.
- The concrete product choice varies dynamically.
- Object creation is part of an extensible class hierarchy.

### Use a separate factory class when:

- Construction logic is substantial.
- Creation depends on configuration or external services.
- Multiple related objects must be assembled.
- Separating creation from the product improves maintainability.

---

## 9. Design Considerations: Avoiding Unnecessary Abstraction

Consider a small game of War.

A single static factory may be sufficient:

```cpp
Deck deck = Deck::standard();
```

Creating an abstract factory interface, multiple subclasses, and a polymorphic factory hierarchy provides little benefit if the application will only ever create a standard deck.

However, a card-game framework supporting several games might benefit from configurable creation behavior.

The important question is not:

*Which design pattern can be used here?*

Instead, ask:

**What problem does the additional abstraction solve?**

Good object-oriented design should reduce complexity, not introduce complexity merely to demonstrate a pattern.

---

## 10. Student Exercise

### Part A: Static Factories

Extend the `Deck` class with the following static factory methods:

```cpp
static Deck standard();
static Deck euchre();
static Deck pinochle();
```

Requirements:

- `standard()` creates 52 cards.
- `euchre()` creates 24 cards.
- `pinochle()` creates 48 cards, consisting of two copies of each 9-through-Ace card.
- All cards use integer values from 0 through 51.
- Duplicate card values are permitted in the Pinochle deck.

### Part B: Polymorphic Factories

Create an abstract `DeckFactory` interface containing:

```cpp
virtual Deck createDeck() const = 0;
```

Implement three concrete factories:

```cpp
StandardDeckFactory
EuchreDeckFactory
PinochleDeckFactory
```

Write a function that accepts a `const DeckFactory&` and constructs a deck without knowing which concrete factory was supplied.

### Part C: Design Analysis

Answer the following questions:

1. Why might a static factory be preferable to an overloaded constructor?
2. What advantage does a virtual factory method provide?
3. Why can't static methods be virtual in C++?
4. When would a separate factory class be unnecessary?
5. Does adding a Factory Method hierarchy automatically improve the design? Explain.

---

## 11. Key Takeaways

- Constructors provide the simplest mechanism for object creation.
- Static factory methods offer descriptive names and encapsulate construction logic.
- Static methods are commonly used to create objects without requiring an existing instance.
- The GoF Factory Method pattern uses polymorphism to delegate creation decisions to subclasses.
- Static factory methods and the formal Factory Method pattern are related but distinct concepts.
- Returning objects by value is a normal and efficient practice in modern C++.
- Design patterns should be introduced to solve identifiable design problems.

**Fundamental principle:** Choose the simplest object-creation mechanism that satisfies the application's current requirements while allowing reasonable future extension.