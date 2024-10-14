
## Extracted Code Blocks:

```cpp

class Base {
    public:
    void Attack() {
        std::cout << "Base attack!" << std::endl;
    }
    void Attack(int damage) {
        std::cout << "Base attack for " << damage << " damage!" << std::endl;
    }
    virtual void SpecialAttack() {
        std::cout << "Base special attack!" << std::endl;
    }
};

class Derived : public Base {
    public:
    void Attack() {
        std::cout << "Derived attack!" << std::endl;
    }
    void SpecialAttack() {
        std::cout << "Derived special attack!" << std::endl;
    }
};
```

```cpp

% class Character {
    % protected:
    %     string name;
    % public:
    %     void print() {
        %         cout << name << endl;
        %     }
        %     void print(string x) {
            %         cout << name << X<< endl;
            %     }
            % };
            
            % class Wizard : public Character {
                % public:
                %     void print() {
                    %         cout << name << " is a Wizard!" << endl;
                    %     }
                    % };
                    %```

```cpp

class Character
{
    string name;
};
class Wizard: public Character
{
    int spellStrength;
};```

```cpp

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
}```

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
};```

```cpp
\begin{minted}[linenos=false]{c++}
int *ptr = new int(7);```

```cpp
\begin{minted}[linenos=false]{c++}
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
    
};```

```cpp
\begin{minted}[linenos=false]{c++}

class Kid; // Forward declaration

class Dad {
    private:
    string alcohol;
    
    protected:
    public:
    friend Kid; // Make Kid a friend
};

class Kid {
    
    protected:
    public:
    Kid() {
    }
    
};```

```cpp

class Character {
    string name;
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
};```

```cpp
\begin{minted}[linenos=false]{c++}
class Character {
    protected:
    string name;
    public:
    virtual void print() = 0;
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
        cout << name << " is a Warrior!" << endl;
    }
};
// optionally
int main{
    Character *ptr;
    Wizard wi;
    Warrior wa;
    ptr = &wi;
    ptr->print(); // will correctly choose print method from Wizard
    ptr = &wa;
    ptr->print(); // will correctly choose print method from Warrior
    return 0;
}```

```cpp

class Wizard {
    private:
    int mana_;
    public:
    
};

class Rogue {
    public:
    void StealMana(Wizard& wizard) {
        wizard.mana_ -= 10;
    }
};```

```cpp

#include <iostream>

// Tell compiler Rogue is a class so the Wizard class
// wont error when it tries to friend it.
class Rogue;

class Wizard {
    private:
    int mana_;
    
    public:
    // Make Rogue a friend, so it has access to your privates
    // and can steal yousr manna.
    friend Rogue;   // <-------------
};

class Rogue {
    public:
    void StealMana(Wizard &wizard) { wizard.mana_ -= 10; }
};

int main() {
    Rogue R;
    Wizard W;
    R.StealMana(W);
}```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
    void print(string x) {
        cout << name << X<< endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};```

```cpp

class Character
{
    string name;
};
class Wizard: public Character
{
    int spellStrength;
};```

```cpp

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
}```

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
};```

```cpp
\begin{minted}[linenos=false]{c++}
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
    
};```

```cpp
\begin{minted}[linenos=false]{c++}

class Kid; // Forward declaration

class Dad {
    private:
    string alcohol;
    
    protected:
    public:
    friend Kid; // Make Kid a friend
};

class Kid {
    
    protected:
    public:
    Kid() {
    }
    
};```

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
};```

```cpp
\begin{minted}[linenos=false]{c++}
class Character {
    protected:
    int name;
    public:
    virtual void print() = 0;
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
        cout << name << " is a Warrior!" << endl;
    }
};
// optionally
int main{
    Character *ptr;
    Wizard wi;
    Warrior wa;
    ptr = &wi;
    ptr->print(); // will correctly choose print method from Wizard
    ptr = &wa;
    ptr->print(); // will correctly choose print method from Warrior
    return 0;
}```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
    void print(string x) {
        cout << name << X<< endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};```

```cpp

class Bike
{
    Engine objEng;
};
class Engine
{
    float CC;
};```

```cpp

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
}```

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
};```

```cpp
\begin{minted}[linenos=false]{c++}
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
    
};```

```cpp
\begin{minted}[linenos=false]{c++}

class Kid; // Forward declaration

class Dad {
    private:
    string alcohol;
    
    protected:
    public:
    friend Kid; // Make Kid a friend
};

class Kid {
    
    protected:
    public:
    Kid() {
    }
    
};```

```cpp
\begin{minted}[linenos=false]{c++}
class Character {
    protected:
    string name;
    public:
    virtual void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

//optionally
int main{
    Character *ptr;
    Wizard w;
    ptr = &w;
    ptr->print(); // will correclty choose print method from Wizard
    return 0;
}
```

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
}```

```cpp
\begin{minted}[linenos=false]{c++}
### Simple Inheritance
class A:
pass

class B(A):
pass

### MultiLevel Inheritance
class A:
pass

class B(A):
pass

class C(B):
pass

### Multiple Inheritance
class A:
pass

class B:
pass

class C(A,B):
pass

### Hierarchical Inheritance
class A:
pass

class B(A):
pass

class C(A):
pass

class D(A):
pass

### We can stop here but ...

class E(B)
pass

class F(B):
pass
```

```cpp
\begin{minted}[linenos=false]{c++}
% class Checking{
    % private:
    %     double account_balance;
    % protected:
    %     int account_number;
    % public:
    %     Checking(string n){
        %         account_balance=0;
        %         account_number=rand();
        %     }
        % };
        %```

```cpp
\begin{minted}[linenos=false]{c++}
% class Checking{
    % private:
    %     double account_balance;
    % protected:
    %     int account_number;
    % public:
    %     Account(string n){
        %         account_balance=0;
        %         account_number=rand();
        %     }
        
        %     friend class Customer;
        % };
        
        % class Customer: public Checking{
            
            % };
            %```

```cpp
\begin{minted}[fontsize=\tiny]{c++}
//source: https://en.wikipedia.org/wiki/Virtual_inheritance
struct Animal {
    virtual ~Animal() = default;
    virtual void Eat() {}
};

struct Mammal: Animal {
    virtual void Breathe() {}
};

struct WingedAnimal: Animal {
    virtual void Flap() {}
};

// A bat is a winged mammal
struct Bat: Mammal, WingedAnimal {};

Bat bat;```

```cpp
\begin{minted}[fontsize=\tiny]{c++}
//source: https://en.wikipedia.org/wiki/Virtual_inheritance
struct Animal {
    virtual ~Animal() = default;
    virtual void Eat() {}
};

// Two classes virtually inheriting Animal:
struct Mammal: virtual Animal {
    virtual void Breathe() {}
};

struct WingedAnimal: virtual Animal {
    virtual void Flap() {}
};

// A bat is still a winged mammal
struct Bat: Mammal, WingedAnimal {};```

## Extracted Questions:

1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.?\\
1. Write a single C++ statement that dynamically allocates a single int and initializes it to 99.
1. Which of the following functions demonstrates function overloading in the code snippet?
1. Which of the following functions demonstrates function overriding in the code snippet?
1. Class **Wizard** is _______________  the print method in **Character**
1. The **Print** method is _______________ in class  **Character**
1. How can we make a class abstract?
1. Which of the following is true about the friend keyword in C++?
1. Which of the following is a potential drawback of using the friend keyword?
1. Which of the following statement is correct with respect to the use of **friend** keyword inside a class?
1. Which of the following keywords is used to control access to a class member?
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by?
1. What is the purpose of an **abstract class** in C++?
1. Given a **class Widget**, which of the following choices could access *private data members* or *private member functions* of Widget.
1. Which of the following type of data member can be shared by *all instances* of its class?
1. An object is a(n) \fillin of a class that resides in \fillin and has \fillin.
1. A *constructor* is executed when _______________?
1. How many objects can be created from an abstract class?
1. What does the class definitions in the following code represent?
1. Which of the following can be overloaded?
1. Which of the following means "*The use of an object of one class in the definition of another class*"?
1. Which of the following is the only technical difference between structures and classes in C++?
1. Which of the following concepts means "determine at runtime" what method to invoke?
1. In the code snippet below, we have an example of:
1. In the snippet below, if I wanted to make **Character** an abstract class, I would have to:
1. Which of the following can be an **object**:
1. A class that has all of its methods implemented, and can be instantiated is know as a(n):
1. What is the one thing that is necessary for **run time polymorphism**?
1. **Runtime Polymorphism** requires?
1. We typically choose **Inheritance** over **Composition**?
1. When a derived class inherits from more than one base-class directly, we call this?
1. The concept of determining which methods to invoke while a program is executing is known as:\\
1. The concept of determining which methods to invoke before a program is executing is known as:
1. Write a single C++ statement that dynamically allocates a single int and initializes it to 7.
1. Rewrite the snippet below so that the Kid can access his dad private stash of alcohol. The alcohol attribute must stay private.
1. Finish the Character class so that the print method in Character must be implemented in both sub-classes.
1. Add necessary code to snippet below, to ensure it works without error. You cannot change any code, you must add additional code. Simplest answer gets the most points.
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.?\\
1. Write a single C++ statement that dynamically allocates a single int and initializes it to 99.
1. Class **Wizard** is _______________  the print method in **Character**
1. The **Print** method is _______________ in class  **Character**
1. How can we make a class abstract?
1. Which of the following statement is correct with respect to the use of **friend** keyword inside a class?
1. Which of the following keywords is used to control access to a class member?
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by?
1. Which of the following can access *private data members* or *private member functions* of a class?
1. Which of the following type of data member can be shared by *all instances* of its class?
1. Which of the following is also known as an instance of a class?
1. A *constructor* is executed when _______________?
1. How many objects can be created from an abstract class?
1. What does the class definitions in the following code represent?
1. Which of the following can be overloaded?
1. Which of the following means "*The use of an object of one class in the definition of another class*"?
1. Which of the following is the only technical difference between structures and classes in C++?
1. Which of the following concepts means "determine at runtime" what method to invoke?
1. In the code snippet below, we have an example of:
1. In the snippet below, if I wanted to make **Character** an abstract class, I would have to:
1. Which of the following can be an **object**:
1. What is the one thing that is necessary for **run time polymorphism**?
1. We typically choose **Inheritance** over **Composition**?
1. When a derived class inherits from more than one superclass directly, we call it?
1. Rewrite the snippet below so that the Kid can access his dad private stash of alcohol. The alcohol attribute must stay private.
1. Rewrite the necessary component of the code snippet below, so that the print method in Character must be implemented in both sub-classes.
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.?\\
1. Class **Wizard** is _______________  the print method in **Character**
1. The **Print** method is _______________ in class  **Character**
1. How can we make a class abstract?
1. Which of the following statement is correct with respect to the use of **friend** keyword inside a class?
1. Which of the following keywords is used to control access to a class member?
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by?
1. Which of the following can access *private data members* or *member functions* of a class?
1. Which of the following type of data member can be shared by *all instances* of its class?
1. Which of the following is also known as an instance of a class?
1. A *constructor* is executed when _______________?
1. How many objects can be created from an abstract class?
1. What does the class definitions in the following code represent?
1. Which of the following can be overloaded?
1. Which of the following means "*The use of an object of one class in the definition of another class*"?
1. Which of the following is the only technical difference between structures and classes in C++?
1. Which of the following concepts means "determine at runtime" what method to invoke?
1. In the code snippet below, we have an example of:
1. In the snippet below, if I wanted to make Character an abstract class, I would have to:
1. An interface is a C++ class that:
1. Which of the following is a mechanism of static polymorphism?
1. Rewrite the snippet above so that the Kid can access his dad private stash of alcohol.
1. Rewrite the code snippet from question 17, so that it can properly use run time polymorphism.
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.?\\
1. Which of these is a base class: Vehicle or Minivan?\\
1. Like private members, protected members are inaccessible outside of the class. However, they can be accessed by:\\
1. The concept portrayed in the previous snippet is known as $\rule{2cm}{0.15mm}$ ? (choose the best answer)\\
1. What is the output of the previous code snippet?\\
1. Depending on your previous answer, is there anything you could do to either make it work (if you thought it was broken) or make it print the "other" output without altering main?\\
\question *Encapsulation v Abstraction:* Use the answer sheet to answer. label each question with an *A* for abstraction or *E* for encapsulation.
1. Hides certain methods from users of the class by protecting them or making them private.
1. Hides whether an array or linked list is used.
1. Solves problem at implementation level.
1. Wraps code and data together.
1. Is focused mainly on what should be done.
1. Is focused on how it should be done.
1. Helps developers to design projects more easily.
1. Lets a developer use a class without worrying about how it's implemented.
1. Solves problem at design level.
1. Hides the irrelevant details found in the code.
1. **A** Hides certain methods from users of the class by protecting them or making them private.
1.  **E** Hides whether an array or linked list is used.
1.  **E** Solves problem at implementation level.
1.  **E** Wraps code and data together.
1.  **A** Is focused mainly on what should be done.
1.  **E** Is focused on how it should be done.
1.  **A** Helps developers to design projects more easily.
1.  **A** Lets a developer use a class without worrying about how it's implemented.
1.  **A** Solves problem at design level.
1.  **E** Hides the irrelevant details found in the code.
\question *Definitions:* Use the answer sheet to answer. Read the definitions following the list of words below, and choose the proper word for the definition. Place the number for the word to the corresponding letter on the answer sheet. Warning: at least 2 of the statements below have NO answer. They sound correct, but are not. On the answer sheet simply write: *??* (two question marks)
1. This is also known as a function, it just resides within a class.
1. This can be called even if no objects of the class exist.
1. There is only one copy of this which is shared by all objects of the class,
1. This is what you get when you have at least one pure virtual member function defined.
1. This can be done in a class or outside of a class. It happens when you share the same name, but not the same parameter list.
1. This happens when you share the same name, but are in different classes. \solutionline[maroon]{??} {Overriding needs more}
1. You define arithmetic operators for your own class. This is an example of: _______________.
1. You have a simple problem where you need to give elevated access to a class, but inheritance is not that answer. So you label this class as _______________
1. This is a term not necessarily from C++, but definitely exists in other OOP languages. Where C++'s version would require a single pure virtual function, other languages assume no data and no implementation at all.
1. This is basically a contract agreeing that at some point, you may redefine some method in a child class.
1. This thing resides in memory and has its own state.
1. The level of access known as _______________ can only be circumvented by another entity by giving that entity the *Friend* label.
1. What type of inheritance are you seeing in the graphic below?
1. An instance variable is the exact same thing as a _______________ variable unless they are in an abstract base class. \solutionline[maroon]{??}{Bad Question}
1. In a somewhat oversimplified view of OOP, _______________ deals with hiding things and _______________ deals with exposing things. \solutionline[def]{23,17}{Encapsulation, Abstraction}
1. An abstract method is just a regular method in many instances. When we set an abstract method equal to zero we turn it into a _______________
1. By defining a base abstract method as pure public, you are guaranteeing that any _______________ access level will not cause problems in a derived class. \solutionline[maroon]{??}{No Answer}
1. Short Answer. Write a simple example in Python (using class names like A, B, and C) showing:
1. Given the code in *snippet 2*, write a class called *Customer* that can access both the **account\_number** AND the **account\_balance** if possible. If not explain why and make any fixes necessary to *Account*.
1.  Short Answer. Explain and write an example in C++ describing the diamond problem and how to fix and/or avoid it.
