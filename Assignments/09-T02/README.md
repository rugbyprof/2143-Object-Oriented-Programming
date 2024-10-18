## Test 2 - Intermediate Stuff

#### Due: 10-18-2024 (Friday @ 11/12)

Here are some vocabulary words. Some you know, others I will be discussing.

## Vocabulary List:

1. **Base Class**: The class from which other classes inherit. Other names include: `Parent` or a `Super` class.
2. **Derived Class**: A class that inherits properties and behaviors from another class. Other names include: `Child` or `Sub` class.
3. **Overloading**: Providing multiple definitions for the same function name, distinguished by parameter types or numbers.
4. **Overriding**: Redefining a function in a derived class that was already defined in the base class, typically using the same function signature.
5. **Polymorphism**: The ability of different classes to be treated as instances of the same class through inheritance, typically realized through function overriding.
6. **Static Polymorphism (Compile-time Polymorphism)**: Determining which function to invoke at compile time (e.g., through function overloading).
7. **Dynamic Polymorphism (Run-time Polymorphism)**: Determining which function to invoke at run time, typically via virtual functions.
8. **Virtual Function**: A function in a base class that can be overridden in derived classes to enable dynamic polymorphism.
9. **Pure Virtual Function**: A function that has no implementation in the base class and must be implemented by any derived class (declared with `= 0`).
10. **Abstract Class**: A class that contains at least one pure virtual function and cannot be instantiated directly.
11. **Concrete Class**: A class that has all its methods implemented and can be instantiated.
12. **Friend Class**: A class that can access the private and protected members of another class.
13. **Encapsulation**: The bundling of data (attributes) and methods (functions) that operate on the data, restricting access to some of the object’s components.
14. **Inheritance**: The mechanism by which one class (derived class) inherits the properties and behaviors of another class (base class).
15. **Multiple Inheritance**: A class that inherits from more than one base class.
16. **Access Modifiers**: Keywords that set the accessibility of class members, such as `private`, `protected`, and `public`.
17. **Protected**: A member that is inaccessible from outside the class but accessible by derived classes and friend classes.
18. **Private**: A member that is only accessible within the class it is declared.
19. **Public**: A member that is accessible from any other part of the program.
20. **Static Member**: A member that belongs to the class itself rather than to any particular object instance. Shared by all instances of the class.
21. **Constructor**: A special member function executed when an object is created, used to initialize the object.
22. **Destructor**: A special member function executed when an object is destroyed, used to clean up resources.
23. **Operator Overloading**: The ability to define or alter the behavior of operators (e.g., `+`, `-`) for user-defined types.
24. **Composition**: The use of an object of one class as a member of another class, indicating a "has-a" relationship.
25. **Instantiation**: The process of creating an instance of a class (i.e., an object).
26. **Pointer**: A variable that stores the memory address of another variable or object.
27. **Dynamic Memory Allocation**: The process of allocating memory at runtime using pointers (e.g., `new` and `delete` in C++).
28. **New**: A keyword used to dynamically allocate memory for an object or variable.
29. **Delete**: A keyword used to deallocate dynamically allocated memory.
30. **Friend Function**: A function that is not a member of a class but has access to its private and protected members.

## More of the Same Words

These words (1-2 or which are wrong), like Virtualizationism, I may put on the exam as help for fill in the blank questions. The list on the actual exam would be smaller.

|  #  |                      |  #  |                          |  #  |                           |
| :-: | :------------------- | :-: | :----------------------- | :-: | :------------------------ |
|     | Static Method        |     | Inheritance              |     | Virtualizationism         |
|     | Pure Virtual         |     | Polymorphism             |     | Object                    |
|     | Class-Variable       |     | Multiple-Inheritance     |     | Private                   |
|     | Protected            |     | Hierarchical-Inheritance |     | Method Overloading        |
|     | Pure Polymorphism    |     | Friends                  |     | Interface                 |
|     | Abstract Base Class  |     | Abstraction              |     | Instance-Variable         |
|     | Member-Variable      |     | Multilevel-Inheritance   |     | Diamond Problem           |
|     | Virtual              |     | Encapsulation            |     | Static Member             |
|     | Public               |     | Class                    |     | Overriding                |
|     | Destructor           |     | Method                   |     | Composition               |
|     | Derived Class        |     | Static Polymorphism      |     | Compile-time Polymorphism |
|     | Dynamic Polymorphism |     | Run-time Polymorphism    |     | Friend Class              |
|     | Virtual Function     |     | Virtual Function         |     | Constructor               |
|     | Concrete Class       |     | Abstract Class           |     | Operator Overloading      |
|     | Access Modifiers     |     | Instantiation            |     | Destructor                |
|     | Friend Function      |     |                          |     |                           |

## Extracted Questions:

- Write a single C++ statement that dynamically allocates a single int and initializes it to 99. `int* ptr = new int(99);`

- Looking at a C++ code snippet identify function overloading and overriding in the code snippet.
- Class **Wizard** is `___________________` the print method in **Character** (overloading / overriding)
- The **Print** method is `___________________` in class **Character** (overloading / overriding / nothing)

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

- Which of the following can be overloaded?

  - list the items in a class you see that could be overloaded

- What is the only technical difference between structures and classes in C++?

- How can we make a class abstract?

  - Explain what needs to be done.

- What is the purpose of an **abstract class** in C++?

- How many objects can be created from an abstract class? (no limit)

- Like private members, protected members are inaccessible outside of the class. However, they can be accessed by `___________________` & `___________________`?

- What does the friend keyword in C++ allow us to do and is it all good?

- What is a potential drawback of using the friend keyword?

- Like private members, protected members are inaccessible outside of the class. However, they can be accessed by `___________________`

<!-- - The level of access known as `___________________` can only be circumvented by another entity by giving that entity the _Friend_ label. -->

- Which keywords can be used control access to class members?

- Like private members, protected members are inaccessible outside of the class. However, they can be accessed by?

- What type of data member can be shared by _all instances_ of its class?

- An object is a(n) `___________________` of a class that resides in `___________________` and has `___________________`.

- A _constructor_ is executed when `___________________`?

- What does the class definitions in the following code represent? (IS-A HAS-A)

```cpp
class Character
{
    string name;
};
class Wizard: public Character
{
    int spellStrength;
};
```

- "The use of an object of one class in the definition of another class" means?

- What concept means "determine at runtime" what method to invoke?

- In the snippet below, if I wanted to make **Character** an abstract class, I would have to:

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

- What makes something an **object**? (as opposed to a class)
- A class that has all of its methods implemented, and can be instantiated is know as a(n): `_______________________` class.

- What is the one thing that is necessary for **Run Time polymorphism**?

- Do we typically choose **Inheritance** over **Composition**? Why?

- When a derived class inherits from more than one base-class directly, we call this?

- The concept of determining which methods to invoke while a program is executing is known as: `_______________________`

- Rewrite the snippet below so that the Kid can access his dad private stash of alcohol. The alcohol attribute must stay private.

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
    Kid() {
    }

};

```

- Rewrite the Character class so that the print method in Character must be implemented in both sub-classes.

```cpp

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

```

- When or how do we know a class has an instance?

- What does it mean: "_The use of an object of one class in the definition of another class_"?

- In the snippet below, if I wanted to make **Base** an abstract class, I would have to:

````cpp

class Base {
    public:
    void print() {cout << "Base Function" << endl;}
};

class Derived : public Base {
    public:
    void print() {}cout << "Derived Function" << endl;}
};
int main() {
    Derived derived1;
    derived1.print();
}



- When does a class become an **object**?


- When a derived class inherits from more than one superclass directly, we call it?


- Write a base class so that certain methods must be implemented in sub-classes.

- What keyword must a method have to ensure that run time polymorphism can happen?

- Know these words: class definition, instance, instantiated, object and state.

- What is the difference between an abstract class and an interface?

- What is static polymorphism?

- Be able to identify a Base Class vs a Derived Class.

- Know all the synonyms for Base and Derived

- What is the output of the following code snippet?
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
    Dogs     d;
    a = &d;
    a->sound();
    return 0;
}
````

- The concept portrayed in the previous snippet is known as `____________________`?

---

_Encapsulation v Abstraction:_ Label each question with an _A_ for abstraction or _E_ for encapsulation.

- Hides certain methods from users of the class by protecting them or making them private.
- Hides whether an array or linked list is used.
- Solves problem at implementation level.
- Wraps code and data together.
- Is focused mainly on what should be done.
- Is focused on how it should be done.
- Helps developers to design projects more easily.
- Lets a developer use a class without worrying about how it's implemented.
- Solves problem at design level.
- Hides the irrelevant details found in the code.

---

- This is also known as a function, it just resides within a class.
- This can be called even if no objects of the class exist.
- There is only one copy of this which is shared by all objects of the class,
- This is what you get when you have at least one pure virtual member function defined.
- This can be done in a class or outside of a class. It happens when you share the same name, but not the same parameter list.
- This happens when you share the same name, but are in different classes.
- You define arithmetic operators for your own class. This is an example of: `___________________`.
- You have a simple problem where you need to give elevated access to a class, but inheritance is not that answer. So you label this class as `___________________`
- This is a term not necessarily from C++, but definitely exists in other OOP languages. Where C++'s version would require a single pure virtual function, other languages assume no data and no implementation at all.
- This is basically a contract agreeing that at some point, you may redefine some method in a child class.
- This thing resides in memory and has its own state.
- An instance variable is the exact same thing as a `___________________` variable unless they are in an abstract base class.
- In a somewhat oversimplified view of OOP, `___________________` deals with hiding things and `___________________` deals with exposing things.
- An abstract method is just a regular method in many instances. When we set an abstract method equal to zero we turn it into a `___________________`

(trick question) By defining a base abstract method as pure public, you are guaranteeing that any `___________________` access level will not cause problems in a derived class. (does this make any sense?)

---

- Write a simple example in C++ (using class names like A, B, and C) showing:
  - Simple Inheritance
  - MultiLevel Inheritance
  - Multiple Inheritance
  - Hierarchical Inheritance

---

Explain and write an example in C++ describing the diamond problem and how to fix and/or avoid it.

---

Given the code below write a class called `Customer` that can access both the **account_number** AND the **account_balance** if possible. If not explain why and make any fixes necessary to `Account`.

```cpp
class Account{
private:
    double account_balance;
protected:
    int account_number;
public:
    Checking(string n){
        account_balance=0;
        account_number=rand();
    }
};
```
