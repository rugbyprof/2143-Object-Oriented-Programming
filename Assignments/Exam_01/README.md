---
title: "Test 1"
description: "C++ Review and OOP basics"
due: "2025-09-01"
order: 4
slug: "Exam_01"
---

## Study Guide

| Read These                                                         |
| :----------------------------------------------------------------- |
| [Stack and Queue Overview](../../Lectures/01-Stack-Queue/)         |
| [Public vs Private Protection](../../Lectures/02-PublicVsPrivate/) |
| [Copy Constructors & More ](../../Lectures/03-CopyConstructor/)    |

## Question Types

There will be mostly multiple choice, with a couple of short answer questions to show me you can write code. Maybe some matching if we get to a place where we have a lot of concepts with definitions to match up, but not on this test. For now, my go to question is to give you small code snippets and see what information you can gather from those snippets.

I have a few examples in the next section walking you through the aforementioned question style. The topic of the next section is all about classes: constructors, data members, methods, and public / private sections.

## Class Snippets

This section gives you some code as if a class (or three) are being instantiated (declared) in main. Based on the lines of code used to declare those instances of a class, what information can you gather to tell you what the definition should look like?

> Note: All class definitions will have at a minimum: 1) a default constructor (zero params), 2) an overloaded constructor(all data member params), 3) getter and setter methods (two methods per data member one to "set" the value and one to "get" the value).
>
> Any other methods or constructors will be based on what you see in the usage.

---

### 1. Book Class

Books are pretty common. Well, they used to be. But we all know what a book is. Look below and based on those 5 lines of code where there are 3 lines that create 3 books, and another two lines that alter an object. What do these lines tell you?

#### Usage:

```cpp
1   Book B0;
2   Book B1("1984", "George Orwell", 328, 1949);
3   Book B2("To Kill a Mockingbird", "Harper Lee", 281);
4   B2.setIsbn("978-1-4028-9462-6");
5   B2.setPrice(23.99);
```

### Determine Class Contents

- Line 1 simply called a default constructor, which doesn't help with gleaning data information, but it does tell us that there has to be a default constructor with NO params.
- **Lines 2 & 3** give us a lot of information! Enough to glean the following:

  - Title (string)
  - Author (string)
  - PageCount (int)
  - PublicationYear (int)

- **Lines 2 & 3** are also different. One has a year and one doesn't. If this were a final exam and we had two hours, I would expect you to create every constructor to matche the usage, but in a 50 minute exam just put a comment in your code (see below) so I know that you saw it. I problably won't get tricky on the exam, but this is a study guide, so study!

> If you don't get the exact names as I might name them, it's ok, but they should make sense, be self documenting, and the data types should match the data in the calls to the constructors.

- Now by looking at **lines 4 & 5** we get even more information. We now know that a book has an Isbn and a Price.
- Based on all of this you should write something like this (no implementation) just definition:

### Definition

```cpp
class Book {
private:
    float price;
    int pages;
    int year;
    string author;
    string isbn;
    string title;
public:
    // Constructors
    // Usage showed multiple constructors with differing values, I'm implementing only two:
    Book();
    Book(string ,string, int,int);
    Book(string ,string, int;

    // Getters and Setters
    float getPrice();
    int getPages();
    int getYear();
    string getAuthor();
    string getISBN();
    string getTitle();
    void setPrice(float);
    void setPages(int);
    void setYear(int);
    void setAuthor(string);
    void setISBN(string);
    void setTitle(string);
};
```

---

### 2. Point3D Class

A **3D Point** is a simple yet multi-faceted concept with clear real-world applications, especially in geometry, computer graphics, or game development. Can you look at the usage below and determine what a class definition might look like?

#### Usage:

```cpp
1   Point3D P0;
2   Point3D P1(1.5, 2.0, -3.5,"Red");
3   Point3D P2(0, 0, 0);
4   P1.move2D(3.3,5.7);
5   P2.moveUp(3.9);
6   P2.setColor("Blue");
```

### Determine Class Contents

- Again Line 1 is not helpful except in reminding us that we need a default constructor.
- **Lines 2 & 3** give us good information where 2 has the most info about data members.
- Then we see **lines 4 & 5** giving us two additional methods and line 6 simply calling a "setter".
- So, based on the usage, you can guess the following data members and their data types:

- X coordinate (double)
- Y coordinate (double)
- Z coordinate (double)
- color (string)

Which leads us to the definition below.

### Definition:

```cpp
class Point3D {
private:
    double x;
    double y;
    double z;
    string color;
public:
    // Constructors
    // again we only provided 2 constructors the default and then one for all values
    Point3D();
    Point3D(double , double , double ,string);

    // Getters and Setters
    // These methods are always necessary unless explicit instructions say to forget them.
    double getX();
    double getY();
    double getZ();
    string getColor();
    void setX(double);
    void setY(double);
    void setZ(double);
    void setColor(string);
    // Methods gleaned from usage
    void move2D(double, double);
    void moveUp(double);
};

// Add two points together by adding each double data member.

Point3D operator+(Point3D &rhs){
    Point3D temp;
    temp.x = x + rhs.x;
    temp.y = y + rhs.y;
    temp.z = z + rhs.z;
    return temp;
}

// P1 = P1 + P3;


```

---

### 3. Movie Class

Another easily understood concept is a **Movie**. Look at the usage to determine how the class should be defined.

### Usage:

```cpp
1   Movie M1("Inception", "Christopher Nolan", 148, 2010);
2   Movie M2("The Matrix", "Lana Wachowski");
3   M1.setMovieBudget(23000000);
4   M1.isTrilogy(false);
5   M2.isFranchise(true);
```

### Determine Class Contents

- Based on the constructors on **lines 1 & 2**, we can guess the following data members and their data types:

  - Title (string)
  - Director (string)
  - Duration in minutes (int)
  - Year of release (int)

- But looking at **lines 3,4,5** we can see that there are more data members to deal with:

  Budget (int) (or long)
  Triology (bool)
  Franchise (bool)

- This does leave us some questions. Do I need to alter the constructors on lines 1 & 2 to fit the new data members? No.
- Do I need to add a constructor that would be considered a default constructor? YES! Always have a default constructor.
- And again, if you see different constructors that have different signatures, just make a note so I know that you saw.

### Definition:

```cpp
class Movie {
private:
    bool franchise;
    bool trilogy;
    int duration; // Duration in minutes
    int year;
    int budget;
    string director;
    string title;

public:
    // Constructors
    // There were multiple constructor signatures in the usage, but implementing these two
    Movie();
    Movie(string , string , int , int);
    Movie(string,string);


    // Getters and Setters
    bool getFranchise();
    bool getTrilogy();
    int getDuration();
    int getYear();
    int getBudget();
    int getBudget();
    string getDirector();
    string getTitle();
    // Add setters below (I'm not typing them :)
};



```

---

## Implementation

What if I want you to actually write code that does something besides define a class? I will ask you to implementa specific method. See below:

### Example 1 Point Class:

Given the Point class below:

```cpp
class Point{
private:
  int x;
  int y;
public:
  Point();
  Point(int,int);
  void Move(int,int);
  void Jump(int,int);
};
```

- Implement the `Move` and `Jump` methods for class `Point`.
- The `Move` method adds the incoming values to the `x` and `y` coordinates respectively, whereas the `Jump` method would be replace the `x` and `y` values with ones passed in.

#### Your Code

You write your implementation as if you were defining the method outside of the class definition using the scope resolution operator to tie the method to the class.

```cpp
void Point::Move(int _x,int _y){
  x += _x;
  y += _y;
}

void Point::Jump(int _x,int _y){
  x = _x;
  y = _y;
}

```

---

### More Implementation

Given:

```cpp
// linked list class
class LL{
    Node *start;
public:
    LL();
    void push(int);
    int pop();
    void print();
}
```

- Implement the `print` method as if you were writing the method outside of the `LL` definition.
- Remember the three lines I asked you to memorize? See [HERE](https://gist.github.com/rugbyprof/a6d2a0c507d621fe783cce41222601fd)

#### Your Code

```cpp

void LL::print(){

    // your code here
}
```

---

## Friend Keyword

- What is the significance of the `friend` function? Meaning, what does it do? [Example Snippet](https://gist.github.com/rugbyprof/2b1d02ad0815ce247cc610fc42ad9d54)

---

## Overload Ostream

- Given **any** struct or class definition along with some example output, be able to overload ostream for that class or struct in order to reproduce that output.

#### Given

Look at the output below and overload the << operator. Write your function as if you were defining it inline (inside the class definition).

```
OUTPUT:
The point that gave us the biggest headache was point P1, of which the values can be seen here: [x: 22.5 | y: 12.2 | z: 7.9 | Color: Red]. You should be able to see why we rejected this point.
```

> Note: You need to determine which portions of that output string are from the class ostream method, and which do not. Only place the portions of the output that make sense in your ostream overload, meaning only the data stored in the object and possibly a few additional enhancements like you see below.

```cpp
  friend ostream &operator<<(ostream &os, const Point3D &p) {
    return os << "[ x: " << p.x << " | y: " << p.y << " | z: " << p.z << " | Color: " << p.color << "]";
  }
```

---

### Copy constructor vs Overloaded Assignment Operator?

- Given a struct or class, overload a specified set of operators in order to compare or assign one item to another.

```cpp
LinkedList{
  Node* head;
public:
  LinkedList(){
    head = NULL;
  }
  LinkedList(vector<int> v){
     // builds list from v
  }
  // Copy Constructor
  LinkedList(const LinkedList &other){
     this->head = NULL
     Node* travel = other.head;
     while(travel){
         Push(travel->data);
     }
  }
  // ...
  void Push(int x){
     // adds a node to the LL with x in it.
  }
  LinkedList &operator=(const LinkedList &other){
      if(this == &other)
          return *this;
      // otherwise create  a new list like in the copy constructor and return it.
      //return the new list;
  }
  ~LinkedList(){
      // iterate over each node and delete it.
  }
};

int main(){

LinkedList A(vector<int>({3,5,7,8,12}));
LinkedList B = A; // this invokes the copy constructor because B is a NEW object!
LinkedList D(A);  // same as line above.
LinkedList C(vector<int>({3,8,7,8,77}));
A = A; // this would return *this because they are the same;
A = C; // this invokes the assignment operator because neither are new objects.
}
```

### Testing Objects for Equality

- Example: Overload the `==` to compare two books. Think about what makes a book unique. You could compare all the values in each book, but that would be overkill when a books ISBN is unique to that book. So comparing isbn's could determine the same book. **Don't confuse this with comparing to see if it's the same object.**

```cpp
bool operator==(const Book& rhs){
  return rhs.isbn == this->isbn;
}
```

---

- Whereas if it was a Point or Point3D that you were comparing, how would you check for equality?

---

- And then, if you were to assign one Book to another by overloading the assignment operator (`=`), look at the [lecture notes](../../Lectures/03-CopyConstructor/README.md). Mainly we need to **check for self assignment** before we determine its ok to go through with copying all the values.

---

### More Stuff on Copy Constructors

- What is and when do we need and when de we need a copy constructor?
- When do we need to overload the assignment (=) operator.
- When do we need a specialized destructor?
- What is the "rule of three"
- Be able to explain Deep Copy vs Shallow Copy and when you should write a method to handle copying.

---

## Basic Definitions

- There are 3 major concepts when we think about OOP. Encapsulation, Inheritance, and Polymorphism
- I will give you my laymen definition of each, but will need to add to my definition for the exam.
- Encapsulation: The packaging of data and methods together in the same construct which allows us to hide some of the inner goings on from the world.
- Inheritance: Defining a set of classes in a hierarchical manner so that as we move down the hierarchy the classes below can re-use the data and methods from the classes above. And by adding or changing things in a small way we can quickly change the behavior of a lower class without lots of effort or code.
- Polymorphism: Changing the behavior of a class by overloading or overriding methods from a class higher in the hierarchy to change the behavior of that higher class. Basically this means we can alter the behavior or adapt the behavior of a data type based on the context in which its used.

### Other Key Words

- class
- data member
- public
- private
- friend
- overload
- constructor
- destructor
- deep copy
- shallow copy
