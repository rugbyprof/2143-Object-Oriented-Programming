# Test 2 - OOP Study Guide

#### Due: 03-27-2025 (Thursday)

<!-- # Overview of Topics -->

<!-- ## 1. Introduction to OOP

1. **Definition of Object-Oriented Programming**
   - Emphasis on objects rather than just procedures/functions.
   - Real-world modeling with classes and objects.
2. **Key Benefits**
   - Reusability, maintainability, and modular design.
   - Abstraction of complex systems into manageable components.
3. **Common Terminology**
   - Class, Object, Instance, Member variables, Methods.

---

## 2. Basic Principles of OOP

1. **Encapsulation**
   - Hiding internal details of objects.
   - Accessor (get) and mutator (set) methods.
2. **Inheritance**
   - “Is-a” relationships (e.g., `Car` is a `Vehicle`).
   - Base (parent) and derived (child) classes.
3. **Polymorphism**
   - Ability for methods to take many forms (e.g., method overriding, method overloading).
   - Dynamic vs. static binding.
4. **Abstraction**
   - Abstract classes and interfaces.
   - Benefits of hiding implementation details.
5. **Examples & Use Cases**
   - Real-world modeling like shapes, animals, vehicles, etc.

---

## 3. Class and Object Design

1. **Constructors and Destructors**
   - Purpose and usage in object lifecycle.
   - Overloading constructors.
2. **Member Functions (Methods)**
   - Function signatures, return types, and parameters.
   - Inline functions vs. separate implementation.
3. **Access Modifiers**
   - `public`, `private`, `protected` in class design.
   - Implications for encapsulation and class hierarchies.
4. **Static Members**
   - Class-level methods/variables vs. instance-level.
   - Typical use cases and examples (utility methods, counters, etc.).

---

## 4. Inheritance Deep Dive

1. **Single vs. Multiple Inheritance**
   - Language differences (e.g., C++ vs. Java).
   - Diamond problem and virtual inheritance in C++.
2. **Overriding vs. Overloading**
   - Method overloading (same name, different parameters).
   - Method overriding (subclass redefines a parent class method).
3. **Base Class Initialization**
   - Order of constructor calls.
   - Virtual destructors in C++ for safe polymorphic deletion.
4. **Abstract Classes and Interfaces**
   - Pure virtual functions (in C++).
   - Interface-based programming.

---

## 5. Polymorphism in Practice

1. **Runtime Polymorphism (Dynamic Dispatch)**
   - Virtual functions (in C++), `override` keyword.
   - Vtable (virtual table) concept.
2. **Compile-Time Polymorphism (Static Binding)**
   - Function templates and operator overloading.
   - Method overloading with different parameter signatures.
3. **Examples**
   - Polymorphic containers (e.g., storing a list of `Shape*`).
   - Polymorphic function calls based on the actual object type.

---

## 6. Advanced OOP Concepts

1. **Exception Handling**
   - Basic try/catch blocks.
   - Best practices for error reporting and handling.
2. **Templates / Generics**
   - Parametric polymorphism for writing reusable code.
   - Separating algorithm logic from data types (in C++ or Java generics).
3. **Multiple Inheritance Workarounds (Interfaces)**
   - Common patterns to avoid complexity.
   - Mix-in classes or interface approach in languages like C++ and Java.
4. **Design Patterns (Optional)**
   - Basics of the most common patterns (Singleton, Factory, Observer, etc.).
   - Encourages best-practice OOP design strategies.

---

## 7. Memory Management and OOP

1. **Heap vs. Stack Allocation**
   - Automatic vs. dynamic memory in C++.
   - `new`/`delete` usage and the RAII principle.
2. **Copy Constructors and Assignment Operators**
   - Deep vs. shallow copies.
   - Rule of Three/Five in modern C++.
3. **Smart Pointers (C++-Specific)**
   - `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
   - Automatic resource management.

---

## 8. Example Exercises (Hypothetical)

1. **Class Implementation**
   - Implement a `Car` class with constructor, getters/setters, and a method to “drive.”
2. **Inheritance Demo**
   - Create `ElectricCar` derived from `Car` and override a method like `refuel` to do nothing or charge instead.
3. **Polymorphism**
   - Store pointers to different `Car` subclasses (e.g., `GasCar`, `ElectricCar`) in a vector and call a `drive` method.

---

## 9. Summary & Additional Resources

1. **Key Takeaways**
   - OOP is about organizing code into cohesive, interoperable objects.
   - Encapsulation, Inheritance, Polymorphism, and Abstraction form the foundation of good OOP design.
2. **Recommended Reading**
   - “Object-Oriented Programming in C++” by Robert Lafore.
   - “Effective C++” by Scott Meyers.
   - Official documentation/tutorials for whichever language you’re focusing on.
3. **Online Tutorials & Practice**
   - Codecademy, Udemy, Coursera courses on OOP.
   - Community resources like Stack Overflow for Q&A.

--- -->

# Study Guide

### 1. Key Vocabulary

Before diving deeper, review these terms. (Many will appear in the questions later.)

1. Base Class (Parent / Super class)
2. Derived Class (Child / Sub class)
3. Overloading
4. Overriding
5. Polymorphism
6. Static Polymorphism (Compile-time Polymorphism)
7. Dynamic Polymorphism (Run-time Polymorphism)
8. Virtual Function
9. Pure Virtual Function
10. Abstract Class
11. Concrete Class
12. Friend Class
13. Encapsulation
14. Inheritance
15. Multiple Inheritance
16. Access Modifiers (private, protected, public)
17. Protected
18. Private
19. Public
20. Static Member
21. Constructor
22. Destructor
23. Operator Overloading
24. Composition (“has-a” relationship)
25. Instantiation
26. Pointer
27. Dynamic Memory Allocation
28. New
29. Delete
30. Friend Function

Additional Terms (some are alternative names or appear in other OOP languages):

1. Class Variable / Instance Variable
<!-- 1. Pure Polymorphism -->
1. Interface: a class with ALL pure virtual methods.
<!-- 1. Virtualizationism (likely a nonsense or trick term) -->
1. Hierarchy (e.g., hierarchical inheritance)
1. Multi-level Inheritance
1. Diamond Problem
1. Method vs Function
1. Method Overloading vs Method Overriding

### 2. Class Fundamentals & Basic Object Concepts

1.  What is the only technical difference between a struct and a class in C++?
2.  What does it mean to instantiate a class?
3.  When or how do we know a class has an instance?
4.  When does a class become an object?
5.  An object is a(n) `_________________` of a class that resides in `_________________` and has `_________________`. (Fill in the blanks.)
6.  How do we define a constructor and a destructor in a C++ class, and when do each of these get called?
7.  Why might you choose to store data as static in a class?
8.  Which keywords can be used to control access to class members?
9.  What type of data member can be shared by all instances of its class?
10. Rewrite the snippet below so that Kid can access his dad’s private stash of alcohol, but keep alcohol private. This is an example of controlling access in a class:

```cpp
class Dad {
private:
    string alcohol;
protected:
public:
};

class Kid {
protected:
public:
    Kid() { }
    };
```

---

### 3. Access Modifiers & Friend Keyword

1. What is the difference between private and protected access?
2. What does the friend keyword in C++ allow us to do?
3. Does everyone agree that friend fits neatly into the OOP paradigm, or are there drawbacks?
4. Which access level can be circumvented with the friend keyword?
5. Who or what can access a protected data member of a class?
6. Is there ever a time you would use private in a base class and prevent access to a derived class? Give an example.
7. What is a potential drawback of using the friend keyword?

## Practice Exercise

- Given the code:

```cpp
class Account {
private:
    double account_balance;
protected:
    int account_number;
public:
    Account() {
        account_balance = 0;
        account_number = rand();
    }
};
```

Write a class called Customer that can access both account_number and account_balance if possible. If not, explain why. Make any fixes necessary to Account if your design calls for it.

⸻

### 4. Inheritance Fundamentals

1.  Describe IS-A vs HAS-A relationships.
2.  Using the snippet below, what is the relationship between Character and Wizard (IS-A or HAS-A)?

```cpp
class Character {
    string name;
};
class Wizard : public Character {
    int spellStrength;
};
```

3.  What is multiple inheritance, and when might it be used?
4.  What is the diamond problem, and how can it be addressed or avoided?
5.  Explain or write an example in C++ describing the diamond problem and how to fix/avoid it.
6.  Compare composition vs inheritance. When do we typically choose one over the other?
7.  What is aggregation, and how does it differ from composition? Give an example.
8.  Give a concise example in C++ showing:
    - Simple Inheritance
    - Multi-Level Inheritance
    - Multiple Inheritance
    - Hierarchical Inheritance

⸻

### 5. Polymorphism (Overloading & Overriding)

1. What is the difference between overloading and overriding?
2. In a snippet like this:

```cpp
class Character {
protected:
    string name;
public:
    void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};
```

- Is Wizard overloading or overriding the print method from Character?
- Is the print method in Character itself an example of overloading, overriding, or neither?

---

### 6. Which of the following can be overloaded in C++?

- Constructors
- Operators
- Functions with different parameter lists
- Etc. 4. What concept means “determine at runtime what method to invoke”? 5. What is the one thing that is necessary for run-time polymorphism to happen? 6. What is static (compile-time) polymorphism, and how do you implement it in C++? 7. What is operator overloading? Give an example of how you might overload + or <<. 8. What is the output of the following code snippet, and what concept is it demonstrating?

```cpp
class Animals {
public:
    virtual void sound() {
        cout << "Playing generic animal sound..." << endl;
    }
};

class Dogs : public Animals {
public:
    void sound() {
        cout << "Dogs bark..." << endl;
    }
};
int main() {
    Animals *a;
    Dogs d;
    a = &d;
    a->sound();
    return 0;
}
```

**Fill in the blank:** The concept portrayed here is known as **\*\*\*\***\_\_\_\_**\*\*\*\***.

⸻

### 7. Abstract Classes & Pure Virtual Functions

1.  How can we make a class abstract in C++?
2.  What is the purpose of an abstract class in C++?
3.  How many objects can be created from an abstract class?
4.  What is the difference between an abstract class and an interface?
5.  Rewrite the following Character class so that its print method is pure virtual, forcing each derived class (Wizard, Warrior, etc.) to implement its own version:

````cpp
class Character {
protected:
    int name;
public:
    void print() {
        cout << name << endl;
    }
};
class Wizard : public Character {
public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};
class Warrior : public Character {
public:
    void print() {
        cout << name << " is a warrior!" << endl;
    }
};


6.	Similarly, if we have:

```cpp
class Base {
public:
    void print() {
        cout << "Base Function" << endl;
    }
};

class Derived : public Base {
public:
    void print() {
        cout << "Derived Function" << endl;
    }
};
````

What changes would make Base an abstract class so that Derived must implement print?

---

7. Write a base class so that certain methods must be implemented in sub-classes.
   > Hint: This typically involves pure virtual functions.

⸻

### 8. Encapsulation vs. Abstraction

Label each scenario E (Encapsulation) or A (Abstraction) to indicate whether it deals with hiding internal details (Encapsulation) or presenting a simplified interface (Abstraction):

1. Hides certain methods from users of the class by protecting or making them private.
2. Hides whether an array or linked list is used internally.
3. Solves problems at the implementation level.
4. Wraps code and data together in a single unit.
5. Is focused mainly on what should be done, not how.
6. Is focused on how it should be done.
7. Helps developers design projects more easily at a high level.
8. Lets a developer use a class without worrying about its internal details.
9. Solves problems at the design level.
10. Hides the irrelevant details found in the code.

⸻

### 9. Memory & Pointers

1.  Write a single C++ statement that dynamically allocates a single int and initializes it to 99.

- **Example:** int\* ptr = new int(99);

2.  Explain new and delete in C++, and why they are important for dynamic memory.
3.  What is a pointer, and why do we use pointers in OOP?
4.  When is dynamic memory allocation preferable over automatic (stack) allocation?

⸻

### 10. Miscellaneous (Short Questions / Quick Checks)

1. What does it mean: “The use of an object of one class in the definition of another class”?
2. In an oversimplified way, encapsulation deals with hiding things and **\*\***\_**\*\*** deals with exposing things.
3. An abstract method in C++ is basically a regular method except it’s declared as a pure virtual function (= 0). We sometimes call this a(n) **\*\*\*\***\_\_**\*\*\*\*** in other OOP languages.
4. By defining a base abstract method as public pure virtual, are you guaranteeing that protected or private access in derived classes won’t cause conflicts? (Trick question, reflect on access levels!)
5. Do we typically choose inheritance over composition? Why or why not?

⸻

### 11. Here’s a concise reference table and some small code examples illustrating:

- How public, private, and protected work in C++.
- The table shows where each specifier is visible and how it behaves in inheritance scenarios.

#### Quick Overview Table

| Specifier | Visible Within the Same Class? | Visible in Derived Classes? | Visible Outside the Class (Non-Friend)? | Typical Use Case                                                                |
| :-------- | :----------------------------- | :-------------------------- | :-------------------------------------- | :------------------------------------------------------------------------------ |
| public    | Yes                            | Yes                         | Yes                                     | Public API for other parts of the program.                                      |
| protected | Yes                            | Yes                         | No                                      | Internal mechanisms, intended for subclasses but hidden from “the world.”       |
| private   | Yes                            | No                          | No                                      | Strictly internal data, kept hidden from derived classes and the outside world. |

⸻

### Code Demonstration

Below is a small C++ example showing how these specifiers actually work. Notice which members you can access in Derived and which ones are off-limits in main().

```cpp
#include <iostream>
using namespace std;

class Base {
private:
    int privVar = 1;      // Only accessible within Base
protected:
    int protVar = 2;      // Accessible within Base and Derived
public:
    int pubVar  = 3;      // Accessible anywhere
};

class Derived : public Base {
public:
    void tryAccess() {
        // privVar = 10;  // ERROR: Can't access private from Base
        protVar = 20;     // OK: protected members are accessible
        pubVar  = 30;     // OK: public members are accessible
        cout << "Inside Derived - protVar: " << protVar
             << ", pubVar: " << pubVar << endl;
    }
};

int main() {
    Base b;
    // b.privVar = 100; // ERROR: private is not accessible outside Base
    // b.protVar = 200; // ERROR: protected is not accessible from outside
    b.pubVar   = 300;   // OK: public members are accessible from anywhere

    Derived d;
    d.tryAccess();

    // d.protVar = 999; // ERROR: protected is not accessible from outside
    // d.privVar = 999; // ERROR: private is not accessible from outside

    cout << "Inside main - b.pubVar: " << b.pubVar << endl;
    return 0;
}
```

### Explanation

1. private Members

- Can only be accessed by the class itself (i.e., within the same class where they are declared).
- Not accessible by derived classes.
- Not accessible from outside the class.

2. protected Members

- Accessible by the class itself and its derived classes.
- Not accessible by non-friend classes/functions outside the inheritance chain.

3. public Members

- Accessible from anywhere in the program, as long as you have an instance or a pointer/reference to that object.

⸻

### Why Use Each Specifier?

- Private: To encapsulate and hide data (a key OOP principle) and prevent unintended modifications from derived classes or external code.
- Protected: To share data between a base class and its derived classes while still hiding it from the rest of the world.
- Public: To expose an interface (API) that any part of the program can use safely.

### 12. Final Practice Challenges

1. Rewrite the snippet below so that the Kid can access his dad’s private stash of alcohol. (Ensuring alcohol remains private.)
2. Rewrite the Character class so that the print method in Character must be implemented in both sub-classes (Wizard and Warrior).
3. What keyword must a method have to ensure that run time polymorphism can happen?
4. Know these words: class definition, instance, instantiated, object and state.
5. Explain or demonstrate how multiple inheritance might lead to the “diamond problem.”
6. Fix the diamond problem using either virtual inheritance or a suitable alternative.

⸻

### Static Keyword

Here’s an example of a “team dice game” that tracks each team’s average roll.

- We do two things here:

1. Compute each Team’s own average via instance data (just summing the vector of rolls).
2. Compute a global average of all dice rolls among all teams using static members (sumAllRolls and totalRolls).

⸻

The Code

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Team {
private:
// Instance data: specific to each team
string teamName;
vector<int> diceRolls;

    // Class-level (static) variables: shared among all teams
    static int   totalTeams;     // How many Team objects exist
    static int   sumAllRolls;    // Sum of dice rolls across *all* teams
    static int   totalRolls;     // Count of dice rolls across *all* teams

public:
// Constructor
Team(const string& name)
: teamName(name) {
++totalTeams;
}

    // Add a single dice roll to this team's record
    void addDiceRoll(int roll) {
        diceRolls.push_back(roll);

        // Update static counters for global tracking
        sumAllRolls += roll;
        ++totalRolls;
    }

    // Calculate and return the *per-team* average
    double getTeamAverage() const {
        if (diceRolls.empty()) {
            return 0.0;
        }

        int sum = 0;
        for (int roll : diceRolls) {
            sum += roll;
        }
        return static_cast<double>(sum) / diceRolls.size();
    }

    // Return the global average of *all* rolls from *all* teams
    static double getGlobalAverage() {
        if (totalRolls == 0) {
            return 0.0;
        }
        return static_cast<double>(sumAllRolls) / totalRolls;
    }

    // Print the team's name and average
    void printStatus() const {
        cout << "Team: " << teamName
             << " | Average Roll: " << getTeamAverage() << endl;
    }

};

// Definitions of static members must appear outside the class
int Team::totalTeams = 0;
int Team::sumAllRolls = 0;
int Team::totalRolls = 0;

int main() {
// Create a few teams
Team t1("Red Dragons");
Team t2("Blue Phoenix");

    // Add dice rolls for the Red Dragons
    t1.addDiceRoll(6);
    t1.addDiceRoll(4);
    t1.addDiceRoll(5);

    // Add dice rolls for the Blue Phoenix
    t2.addDiceRoll(2);
    t2.addDiceRoll(2);

    // Print their individual statuses
    t1.printStatus();
    t2.printStatus();

    // Show the overall average across *all* teams
    cout << "Global Average of all Teams' Rolls: "
         << Team::getGlobalAverage() << endl;

    return 0;

}
```

⸻

### How It Works

1. Per-Team Average:
   - Each Team object keeps its own list of diceRolls. We compute the team’s average by summing its rolls and dividing by the number of rolls.
2. Global Average (Static Members):
   - `static int sumAllRolls` stores the sum of every roll from all teams.
   - `static int totalRolls` stores how many total dice rolls have been recorded across all teams.
   - Each time we call `addDiceRoll()`, we update these `static` members, allowing us to compute the global average via `Team::getGlobalAverage()`.

- 3. Static Data:
  - Because sumAllRolls and totalRolls are declared static, they’re shared by all instances of Team and We must define them outside the class, for example:

```cpp
int Team::sumAllRolls = 0;
int Team::totalRolls = 0;
```

4. Printing:

- `printStatus()` shows each team’s name and that team’s current average.
- The main function also prints out the overall average for all teams.

⸻

### Why Use a Static Variable for the Global Average?

- If you need to track game-wide metrics (e.g., how many dice have been rolled total, or what the global average is), static class variables allow you to maintain a single source of truth shared among all Team objects.
- Meanwhile, each Team can still calculate its own average independently.

⸻

## Closing Thoughts

- Make sure you understand each subtopic and practice writing your own short code snippets.
- Focus on how keywords (virtual, friend, public, etc.) alter program behavior.
- Don’t forget the fundamentals of memory management, especially in C++.
- Try rewriting or combining the example code from different questions to solidify your understanding of inheritance, composition, and polymorphism.

title: "Composition vs. Aggregation"
description: "A comparison of composition and aggregation in object-oriented programming, including definitions, characteristics, examples, and key differences."
author: "ChatGPT"

Below is an overview that explains the two relationships clearly without repeating details from previous topics:

⸻

Composition vs. Aggregation

Composition
• Definition:
A strong form of association where a whole object is made up of one or more parts. In composition, the parts cannot exist independently of the whole.
• Key Characteristics:
• Ownership: The composite object owns the component objects.
• Lifetime Dependency: When the composite is destroyed, its parts are also destroyed.
• Example:
A Car composed of an Engine, Wheels, and Chassis. If the Car is destroyed, its Engine and other components are also disposed of.
• Code Example:

class Engine {
public:
Engine() { /_ ... _/ }
~Engine() { /_ ... _/ }
};

class Car {
private:
Engine engine; // Composition: Car owns the Engine.
public:
Car() { /_ ... _/ }
// The Engine's lifetime is bound to the Car's lifetime.
};

⸻

Aggregation
• Definition:
A weaker form of association where an object (the aggregate) contains other objects, but those objects can exist independently of the container.
• Key Characteristics:
• Association: Represents a “has-a” relationship, but the contained objects are not exclusively owned.
• Independent Lifetime: The aggregated objects can exist even if the aggregate is destroyed.
• Example:
A Library that contains Book objects. Books may exist independently of the library and might even be shared with another library.
• Code Example:

class Book {
public:
Book() { /_ ... _/ }
~Book() { /_ ... _/ }
};

class Library {
private:
std::vector<Book*> books; // Aggregation: Library aggregates Book objects.
public:
Library() { /* ... _/ }
~Library() {
// Books might not be deleted here, since they could be shared or exist independently.
}
void addBook(Book_ book) {
books.push_back(book);
}
};

⸻

Key Differences

Aspect Composition Aggregation
Ownership Strong; the composite exclusively owns its parts Weak; parts can exist independently and may be shared
Lifetime Parts are destroyed when the composite is destroyed Parts outlive the aggregate if needed
Coupling Tightly coupled Loosely coupled
Use Case Use when parts are inseparable from the whole Use when parts can exist and be managed independently

⸻

This concise comparison should give your students the key insights they need to understand the difference between composition and aggregation. Let me know if you’d like any further examples or clarifications, Terry!
