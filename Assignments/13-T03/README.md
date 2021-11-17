## Test 3 - Beginning Python and Intermediate C++ Concepts
#### Due: 11-22-2021 (Monday @ 12:00 p.m.)

#NOT DONE

## Study Guide

- Remember Overloading vs Overriding?
- When does one happen vs the other?
- Write examples in **Python and C++** showing both.

-----------

- Why  are  method  overloading  and  method  overriding  called  compile-time  and  run-time polymorphism respectively?
- Write code to illustrate both concepts.
- Does Python have run-time polymorphism? Explain why or why not.
- See [override.cpp](override.cpp) for some help.


------------

- How does inheritance help eliminate duplicate code?
- To explain write some c++ and python code that shows multiple inheritance.
 
-------------

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

C c;
c.print()

-------

- Write a simple example in **C++ AND Python** using class names A, B, and C showing:
  - Simple Inheritance
  - MultiLevel Inheritance
  - Multiple Inheritance
  - Hierarchical Inheritance

For each class just add a constructor like the code example above. No methods needed.

--------

- **C++ Only**
- What is the diamond problem?
- We have not explicitly written code in class discussing the problem, but here is a good article showing the problem and solution: https://www.makeuseof.com/what-is-diamond-problem-in-cpp/

-------

#### Define

* Abstract Base Class
* Abstraction
* Class
* Class-Variable
* Composition
* Destructor
* Diamond Problem
* Encapsulation
* Friends
* Inheritance
* Instance-Variable (aka member-variable)
* Interface
* Member-Variable (aka instance-variable)
* Method
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

