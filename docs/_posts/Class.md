---
layout: post
title: Classes
---

**Classes**: A class is a abstract or user-defined data type, contrast to built-in fundamental types such as `int` or `double` . A class is represented as a three-compartment box: 
- `name`, 
- `data members` (or variables or attributes)
- `member functions` (or methods, or operations)

- The data member and member functions are collectively called `class members`. 
- The syntax of defining a class consists of two sections: 
    - `class declaration`  
    - `class implementation`. 

Class declaration is further divided into two sections: `private` and `public`. 
Class implementation contains member function definitions.

```cpp
// Class Declaration Section - in Header file
class ClassName {
private:
   private-data-members
   private-member-functions
public:
   public-data-members
   public-member-functions
};  // Class declaration must end with a semi-colon
 
// Class Implementation Section - in the Implementation file
member-function-definitions
```

___Sources:___
1. http://www.ntu.edu.sg/home/ehchua/programming/cpp/cp6_Inheritance.html

[1]: http://www.ntu.edu.sg/home/ehchua/programming/cpp/cp6_Inheritance.html