## Test 3 - Beginning Python and Intermediate C++ Concepts
#### Due: 11-22-2021 (Monday @ 12:00 p.m.)

## Study Guide

------
- What's the purpose behind inheritance?
- Is it always the answer? Or does composition and/or aggregation have something to say about that?
- How does inheritance (or composition) help eliminate duplicate code?
- How does inheritance (or composition) make your code more stable or reliable? 

-------

- Write a simple example in **C++ AND Python** using class names like A, B, and C ... showing:
  - Simple Inheritance
  - MultiLevel Inheritance
  - Multiple Inheritance
  - Hierarchical Inheritance
  
- I'll answer `Simple Inheritance` to get you started

#### C++
#### Simple Inheritance
This code is worthless except for showing syntax. 
```c++
class A{
public:
  A(){
    cout<<"construct A"<<endl;
  }
};

class B: public A{
public:
    B(){
      cout<<"construct B"<<endl;
    }
};
```

#### Python
```python
class A(object):
  def __init__(self):
    print("construct A")
    
class B(A):
  def __init__(self):
    print("construct B")
```
For each class just add a constructor like the code example above. No methods needed.

Now do the rest of the inheritance examples.

----------

#### In C++ only

- In the snippet below, add a `print` method to `A` that says: "printing in A is super".
- Now **overload** and **override** that method without regard to runtime polymorphism (pointers will never be used) ... 
```c++
class A{
public:
  A(){
    cout<<"construct A"<<endl;
  }
};

class B: public A{
public:
    B(){
      cout<<"construct B"<<endl;
    }
};
```

- If I now told you pointers would be used when accessing your classes. What changes would you need to make and why?

-------

- Are  method  overloading  and  method  overriding  called  compile-time  and  run-time polymorphism respectively? 
- Can you override a method and it not be considered run time polymorphism?
- When does one happen vs the other?
- Does Python have run-time polymorphism? Explain why or why not.

------------


-  How does encapsulation provide security? We talked about hiding or protecting the "implementation" in class, but what does that really mean? Let me show you with code.

```cpp
// NOT SECURE EXAMPLE of bad ENCAPSULATION
// A little contrived, but not too out of the realm of possibility.
struct Account {
    double balance;

    // local implementation simply reduces the balance
    // and returns a bool for success
    bool withDraw (double amnt){
        if (balance - amnt > 0){
            balance -= amnt;
            return true;
        }
        return false;
    }
};

// Even using "composition" this is not secure.
class BankClient{
    Account account;

    // ...

    bool useATM(double amnt){
        // add to our balance!! Since we have access.
        account.balance += amnt;
        if(account.withDraw(amnt)){
            return true;
        }
        return false
    }
    
};
```

```cpp
// SECURE ENCAPSULATION EXAMPLE
class Account {
// When balance private! Even derived classes cannot
// gain access to it.
private:
    double balance;
public:
// Balance can only be accessed by public methods
    bool withDraw (double amnt){
        if (balance - amnt > 0){
            balance -= amnt;
            return true;
        }
        return false;
    }
};

// Inheriting Account doesn't give access to private data members
class BankClient: public Account{
    bool useATM(double amnt){
        balance += amnt; //ERROR!!
        if(withDraw(amnt)){
            return true;
        }
        return false
    }
};
```

- This example shows how that even inheriting from a parent class, that we can lock down (secure) values by keeping them private. 
- If we kept `balance` private, suggest how we may still access `balance` in a sub class, but keep it safe.

-----------

I complain a lot about the overlapping nature of Abstraction vs Encapsulations. Sometimes, when discussing examples, you can argue both ways whether or not the example represents Encapsulation or Abstraction. That to me is annoying. So, out of frustration, I would tell my class that to understand the difference use the following:
- Anything dealing with implementation = `Encapsulation`
- Anything dealing with design = `Abstraction`

One could argue that that may be to broad of a definition. But I finally found a nice "concise" definition for both (fitting with my previous heuristic just fine):
  
- `Encapsulation` means to hide complexities and internal implementation details from users.
- `Abstraction` means to expose only essential details to users.

The key takeaways from here are "hide" and "expose". So even though both concepts essentially result in the same thing, its **how** they go about doing so that matters. **Hiding** has to do with utilizing protection mechanisms in our classes, where **Exposing** has to do with what methods we decide to make public ... wait ... are they still the same thing?!? F*%$!!!

I guess Encapsulation and Abstraction are not to dissimilar from pornography. In a famous court case, one individual stated (and I'm paraphrasing) that "*I may not know how to define pornography, but I sure know it when he see it!*"[<sup>[1]("https://en.wikipedia.org/wiki/I_know_it_when_I_see_it)</sup>]. I'm going to go with that definition for both of these concepts.


----------

Given the following class:

```cpp

class Account{
private:
    double account_balance;
protected:
    int account_number;
    string name;
public:
    Account(string n){
        name = n;
        account_balance=0;
        account_number=rand();
    }
};
```

Write 1 or more classes that can access both the `account_number` AND the `account_balance` if possible. If not explain why and make any fixes necessary to `Account`.

---------

What is the output of the following code?

```cpp
class Animals {
public:
    virtual void sound() {
        cout << "This is parent class" << endl;
    }
};

class Dogs : public Animals {
public:
    void sound() {
        cout << "Dogs bark" << endl;
    }
};

int main() {
    Animals *a;
    Dogs     d;
    a = &d;
    a->sound();
    return 0;
}
```

What can you do to make it print the other statement without changing main? What kind of polymorphism is this? Is this overloading or overriding?

-------

What is the output of the following code:

```cpp
struct A{
  A(){
    cout<<"Running A's constructor"<<endl;
  }
  void print(){
    cout<<"A's print"<<endl;
  }
  void print(string val){
    cout<<"A's overloaded print: "<<val<<endl;
  }

};

struct B: public A{
  B(){
    cout<<"Running B's constructor"<<endl;
  }
  void print(){
    cout<<"B's print"<<endl;
  }
  void print(string val){
    cout<<"B's overloaded print: "<<val<<endl;
  }
};

struct C: public B{
  C(){
    cout<<"Running C's constructor"<<endl;
  }
};
```
```
C c;
c.print()
```

-------

- **C++ Only** (It exists in Python or any language with multiple inheritance) but limit your reading to C++ examples)
- What is the diamond problem?
- We have not explicitly written code in class discussing the problem, but here is a good article showing the problem and solution: https://www.makeuseof.com/what-is-diamond-problem-in-cpp/
- Possible question types:
  - Given a set of classes choose what the output will be.
  - Given a set of classes where should I add certain keywords to fix an issue.

-------

#### Define

You won't necessarily have to write a definition for each one, but you will have to know what each one means. Hmmmm so what's the difference? I will most likely have some kind of matching question, or multiple choice question with various choices to make.

* Abstract Base Class
* Abstraction
* Class
* Class-Variable
* Composition
* Destructor
* Diamond Problem
* Encapsulation
* Friend
* Hierarchical Inheritance
* Inheritance
* Instance-Variable (aka member-variable)
* Interface
* Member-Variable (aka instance-variable)
* Method
* Multilevel-Inheritance
* Multiple-Inheritance
* Object
* Overloading
* Overriding
* Polymorphism
* Private
* Protected
* Public
* Pure Virtual
* Static Member
* Static Method
* Virtual
