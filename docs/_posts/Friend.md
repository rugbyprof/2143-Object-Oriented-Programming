## Friend Classes

Friend Class A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class. For example a LinkedList class may be allowed to access private members of Node.

```cpp

class Node { 
private: 
  int key; 
  Node *next; 

  /* Other members of Node Class */
  
  friend class LinkedList; // Now class  LinkedList can  
                           // access private members of Node 
}; 
```

## Friend Functions
Friend Function Like friend class, a friend function can be given special grant to access private and protected members. A friend function can be:
- A method of another class
- A global function

```cpp
class Node { 
private: 
   int key; 
   Node *next; 
  
   /* Other members of Node Class */
   friend int LinkedList::search(); // Only search() of linkedList  
                                   // can access internal members 
}; 
```

Following are some important points about friend functions and classes:

1. Friends should be used only for limited purpose. too many functions or external classes are declared as *friends* of a class with `protected` or `private` data, it lessens the value of encapsulation of separate classes in object-oriented programming.
2. *Friendship* is not mutual. If a class A is friend of B, then B doesn’t become friend of A automatically.
3. *Friendship* is not inherited.
4. The concept of friends is implemented in all OOP languages, Java for one.
---
layout: post
title: Friend Keyword
---

## Friend and Inheritance

In C++, friendship is not inherited. If a base class has a friend function, then the function doesn’t become a friend of the derived class(es).

For example, following program prints error because show() which is a friend of base class A tries to access private data of derived class B.

<script src="https://gist.github.com/rugbyprof/0efab0263f31d652316b2adb65f825de.js"></script>
<code data-gist-id="0efab0263f31d652316b2adb65f825de"></code>
___Sources:___

1. https://www.geeksforgeeks.org/friend-class-function-cpp/
2. http://en.wikipedia.org/wiki/Friend_class
3. http://en.wikipedia.org/wiki/Friend_function
4. http://www.cprogramming.com/tutorial/friends.html
5. http://www.parashift.com/c++-faq/friends-and-encap.html
6. https://www.geeksforgeeks.org/g-fact-34/