<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: T01
name: T01
title: Test 1 — C++ Review and OOP Basics
description: Exam 1 study guide, combining the Test 1 review sheet with all Quiz 01-03 and Worksheet 01-04 material
category: Assignments
date_due:
  month: '09'
  day: '29'
  year: 2026
  hour: 11
```

</details>

## Test 1 — Study Guide

Everything you need to review for Test 1 lives here: the topic-by-topic study guide below, plus copies of every quiz and worksheet (blank **and** key) that fed into it.

| Type | Folder | Title |
| :--- | :----- | :---- |
| Quiz | [Quizzes/Q01](./Quizzes/Q01/) | Class Syntax & Datamembers |
| Quiz | [Quizzes/Q02](./Quizzes/Q02/) | Overloaded Constructor |
| Quiz | [Quizzes/Q03](./Quizzes/Q03/) | Streams, Friends & Constructors |
| Worksheet | [Worksheets/W01](./Worksheets/W01/) | Stacks and Access Control |
| Worksheet | [Worksheets/W02](./Worksheets/W02/) | Streams, Friends and Constructors |
| Worksheet | [Worksheets/W03](./Worksheets/W03/) | Operator Overloading and Copy Semantics |
| Worksheet | [Worksheets/W04](./Worksheets/W04/) | Constructors and Initializer Lists |

Each subfolder has the blank `.pdf`/`.html` and the `-Key.pdf`/`-Key.html`.

---

### Links

These are equivalent to my version of a text book. It's the content that describes and explains each concept or topic.

| Folder | Link |
| ------ | ---- |
| Week 1 | [Lectures/Week_01](../../Lectures/Week_01/) |
| Week 2 | [Lectures/Week_02](../../Lectures/Week_02/) |
| Week 3 | [Lectures/Week_03](../../Lectures/Week_03/) |

> Note: some of the deeper-dive lecture folders I reference below (`OOP_Fundamentals`, `DataStructures_and_Containers`) aren't published to the public `Lectures/` tree yet — only `Week_01`–`Week_03` are. Ask in class if a specific topic link doesn't resolve.

**I will talk more about OOP fundamentals and which ones will be on the exam!**

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
    Point3D(double , double , double);

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
         travel=travel->next;
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

- And then, if you were to assign one Book to another by overloading the assignment operator (`=`), look at the [lecture notes](../../Lectures/Week_03/). Mainly we need to **check for self assignment** before we determine its ok to go through with copying all the values.

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

---

## Review: Quiz & Worksheet Material

Everything below is pulled straight from Q01–Q03 and W01–W04 (and their keys, linked above). If a topic showed up on one of those, it's fair game here — especially the "find the error" style items, since that's my favorite question format.

### Stacks, Queues & Access Control (Q01, W01)

- **Default access:** `class` members are `private` by default; `struct` members are `public` by default.
- **Stack (array-based):** minimum data members are `int *array;` and `int top;` (an `int capacity;`/`size` is common and fine too). `top` starts at `-1` when empty; a push does `array[++top] = value;`.
- **Queue (linked list):** needs **two** pointers — `Node *front;` and `Node *rear;` — because it adds at one end and removes at the other. A single pointer can't give you O(1) access to both ends. A stack only needs `top` because it adds/removes at the *same* end.
- **LIFO vs FIFO:** Stack = LIFO ("last in, first out"). Queue = FIFO ("first in, first out").
- **Encapsulation vs. Abstraction:**
  - *Encapsulation* — bundling data with the functions that operate on it, and restricting outside access (e.g., making `array`/`top` private).
  - *Abstraction* — exposing only the operations a caller needs (`push()`, `pop()`) while hiding whether it's implemented with an array or a linked list.
- **Classic "does this compile?" traps:**
  - A constructor declared *above* the `public:` label is private by default — calling it from `main()` (`Stack S(10);`) is a compile error (`is private within this context`).
  - Forgetting to set `top = -1;` in a constructor leaves it as garbage — compiles, but undefined behavior on the first `push`.
  - Touching a private member directly from outside the class (`Q.front = nullptr;` in `main()`) doesn't compile, no matter how harmless it looks — access is a compile-time check, not about intent.
  - Missing the semicolon after a class's closing `}` merges the class body with whatever comes next (e.g. `int main()`) into one broken declaration.

### Constructors: Default, Overloaded, Copy (W04, Q02)

- A constructor: **same name as the class**, **no return type**, and its job is to initialize a new object.
- **Overload resolution is based on parameter *types*, never parameter names.** `Player(string n)` and `Player(string playerName)` are the *same* signature — a duplicate declaration, not two overloads. Won't compile.
- **Adding an overloaded constructor (e.g. a `Stack(int capacity)`):**
  - The new parameter must actually be *used* (e.g. `array = new int[capacity];`). A parameter that's declared but ignored (still `new int[10]`) defeats the whole point.
  - Don't forget to still initialize everything the default constructor does (e.g. `top = -1;`).
- **Copy constructor:** `Player b(a);` and `Player c = a;` are **both** copy-construction. `c = a` looks like assignment, but since `c` doesn't exist yet, it's *copy-initialization* and calls the copy constructor, not `operator=`. Only plain `d = a;` where `d` already exists calls the assignment operator.
- **Member initializer lists** are the *only* way to initialize:
  - `const` members
  - reference members
  - members with no default constructor
  - base-class constructors (once we cover inheritance)

  They're also more efficient: assignment in the body first default-constructs the member, then overwrites it — two steps instead of one.
- **Initialization order follows *declaration* order, not list order.** If `data` is declared before `size` but the initializer list says `size(s), data(new int[size])`, `data` is built first, while `size` is still garbage. Fix by reordering the *declarations* to match the dependency.
- **Trace-table skill:** given a sequence of `ClassName varName(args);` calls, be able to say which constructor fires and what each data member ends up holding. This showed up repeatedly (Player, Robot, Book examples) — practice tracing these by hand.

### Friends, Operator Overloading & Streams (Q03, W02, W03)

- **`operator<<` must be a non-member (free) function**, because the left operand in `cout << obj` is the `ostream`, not your class — you can't add a member function to a type you don't own. Written as a *member*, it would only work backwards (`obj << cout`).
- It's usually declared `friend` inside the class so it can reach private data directly, and it must **return `ostream&`** so chained calls (`cout << a << b;`) keep working — `void` breaks the chain after the first `<<`.
- Standard shape:
  ```cpp
  friend ostream& operator<<(ostream& os, const Fraction& f) {
      return os << f.num << "/" << f.den;
  }
  ```
- **Self-assignment-in-constructor bug:** if parameter names match member names exactly and the constructor body does `x = x; y = y;`, name lookup resolves the *unqualified* `x`/`y` to the **parameters**, so each just assigns to itself — the real members stay uninitialized garbage. Fix with a member initializer list, where `x(x)` is unambiguous (member on the left, parameter on the right):
  ```cpp
  Point(int x, int y) : x(x), y(y) {}
  ```
- **`const` members can only be set in the initializer list**, never assigned in the constructor body (`PI = 3.14159;` inside `{}` won't compile).
- **Ambiguous overloads from default arguments:** `Fraction(int n)` and `Fraction(int n = 0, int d = 1)` both match a single-`int` call like `Fraction b(3);` equally well — ambiguous, won't compile. Fix by deleting one or collapsing into a single constructor with defaults.
- **`operator+`/comparison operators need `const`:** if the method isn't marked `const`, it can't be called through a `const Fraction&` parameter — won't compile when called from a function that only has `const` references.
- **Member vs. non-member arithmetic operators:** `a + b` (left operand is your own class) works fine as a member. But `2 + a` fails if `operator+` is only a member — overload resolution looks for a member `operator+` on `int`, which doesn't exist, and there's no free `operator+(int, const Fraction&)` to fall back on. A non-member/`friend` version fixes both directions.
- **Meaningful equality vs. raw field comparison:** comparing `num == rhs.num && den == rhs.den` fails for equal-but-unreduced fractions (1/2 vs 2/4). Cross-multiply instead: `num * rhs.den == rhs.num * den`.

### Copy Semantics & the Rule of Three (W03, plus Book/Fraction examples)

- **Shallow copy:** the compiler-generated (default) copy constructor copies a pointer member's *address*, not the data it points to. Two objects end up pointing at the same heap block — a change through one shows up in the other, and when both are destroyed you get a double free / dangling pointer.
- **Deep copy:** allocate a *new* block and copy the actual contents over, so each object owns independent memory.
- **When a hand-written copy constructor is (and isn't) needed:**
  - A class whose members are plain value types (`int`, `double`, `string`, etc. with no ownership) is already safe with the compiler-generated copy constructor — a member-wise copy is a complete, independent copy.
  - A class with a raw *owning* pointer (`int *data;` allocated with `new`) needs a hand-written **copy constructor**, **destructor**, and **`operator=`** together — the "Rule of Three." Missing any one of them is a bug waiting to happen.
- **Self-assignment check in `operator=`:** always guard with `if (this == &other) return *this;` before releasing/reassigning resources, or `A = A;` can corrupt or free data out from under itself.
- **`operator=` vs. copy constructor:** the copy constructor builds a *brand-new* object (`LinkedList B = A;`, `LinkedList D(A);`); `operator=` is invoked when both objects already exist (`A = C;`).

### Exam-Style Traps — Quick Checklist

These are the specific "gotchas" that have shown up across every quiz/worksheet key so far. When you see a code snippet on the exam, scan for these first:

- [ ] Constructor declared above `public:` → private by accident.
- [ ] A data member declared but never initialized (`top`, etc.) → garbage/undefined behavior, not a compile error.
- [ ] Parameter name shadowing a member name in the constructor *body* (`x = x;`) → use a member initializer list instead.
- [ ] `const` member assigned in the constructor body instead of the initializer list → won't compile.
- [ ] Two constructors with the same parameter *types* (including ones created via default arguments) → ambiguous or duplicate, won't compile.
- [ ] `operator<<` (or any operator whose left-hand side isn't your class) written as a member instead of a free/friend function.
- [ ] Missing `const` on a comparison/arithmetic operator that needs to work on `const&` parameters.
- [ ] Member initializer list order assumed to control init order — it's actually **declaration** order.
- [ ] A class with a raw owning pointer that relies on the default (shallow) copy constructor/assignment/destructor.
- [ ] Missing semicolon after a class definition's closing brace.
