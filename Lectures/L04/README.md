## Inheritance & Friendship - Overview

<sup>source: http://www.cplusplus.com/doc/tutorial/inheritance/</sup>

- In principle, private and protected members of a class cannot be accessed from outside the same class in which they are declared. 
- However, this rule does not apply to "friends".

- Friends are **`functions`** or **`classes`** declared with the **`friend`** keyword.

- A non-member function can access the **`private`** and **`protected`** members of a class if it is declared a **`friend`** of that class. That is done by including a declaration of this external function within the class, and preceding it with the keyword **`friend`**:

```cpp
// friend functions
#include <iostream>
using namespace std;

class Rectangle {
    int width, height;
  public:
    Rectangle() {}
    Rectangle (int x, int y) : width(x), height(y) {}
    int area() {return width * height;}
    friend Rectangle duplicate (const Rectangle&);
};

Rectangle duplicate (const Rectangle& param)
{
  Rectangle res;
  res.width = param.width*2;
  res.height = param.height*2;
  return res;
}

int main () {
  Rectangle foo;
  Rectangle bar (2,3);
  foo = duplicate (bar);
  cout << foo.area() << '\n';
  return 0;
}
```

The duplicate function is a **`friend`** of class Rectangle. Therefore, function duplicate is able to access the members width and height (which are private) of different objects of type Rectangle. Notice though that neither in the declaration of duplicate nor in its later use in main, function duplicate is considered a member of class Rectangle. It isn't! It simply has access to its private and protected members without being a member.

Typical use cases of **`friend`** functions are operations that are conducted between two different classes accessing private or protected members of both.