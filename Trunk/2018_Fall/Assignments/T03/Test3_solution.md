# 2143 OOP - Test 3
Name: __________________________________

<center>

| # | Possible | Earned | #  | Possible | Earned |
|---|----------|--------|----|----------|--------|
| 1 | 10       |        | 7  | 10       |        |
| 2 | 10       |        | 8  | 10       |        |
| 3 | 10       |        | 9  | 10       |        |
| 4 | 10       |        | 10 | 10       |        |
| 5 | 10       |        | 11 | 10       |        |
| 6 | 10       |        | 12 | 10       |        |
|   |          |        |    | **120**  |        |

</center>

### Instructions
- Use pencil only
- Write your name at the top of all pages turned in (unless they are stapled).
- When stapling pages together, do it at the extreme top left corner.
- Make sure your pages are in order, with questions also in order.
- Handwriting that is illegible (messy, small, not straight) will lose points.
- Indentation matters. Keep code aligned correctly.
- All answers will be written on the paper provided, and not directly on the test.
- When possible, write your answers vertically and mark clearly:
>A) answer one
>B) answer two
>C) answer three
- NOT 
>a.answer one b.answer two c.answer three
- Failure to comply will result in **loss of letter grade**.
<div class="page"/>

### Question 1

- A) `person` Is the object definition;
- B) `p1` Is the object;
- C) The data members `name` and `id` are:
	- a) public
	- **b) private**
	- c) protected
	- d) private and protected
	- e) a b & c
	
```cpp
class person { 
	char name[20]; 
	int id; 
	void getdetails(){}
}; 

int main() { 
	person p1;
} 
```

-----

### Question 2

A) **True** / False : The structure below provides an adequate example of encapsulation.

```cpp
struct Fraction { 
	int numerator; 
	int denominator;
		
	void set(int n,int d) 
	{ 
		numerator = n;
		denominator = d;
	} 
	
	void print() 
	{ 
		cout<<numerator<<"/"<<denominator<<endl;
	} 
}; 
```
B) What minimal changes to the struct above would you have to make to implement proper **data abstraction** or **implementation hiding**.


```cpp
//one way
struct Fraction { 
private:
	int numerator; 
	int denominator;
public:
	void set(int n,int d) 
	{ 
		numerator = n;
		denominator = d;
	} 
	
	void print() 
	{ 
		cout<<numerator<<"/"<<denominator<<endl;
	} 
}; 
```


### Question 3

Polymorphism means to have many forms. What this means in OOP is that we override and overload methods in our classes. There are two distinct categories of polymorphism: **compile time** and **run time**. Look at the list below and on your answer sheet indicate which type they are: **C** for compile time, **R** for run time, or **B** for both.

- A) Operator overloading. **B**
- B) Method overloading.   **B**
- C) Method overriding.    **B**

-----

### Question 4

```cpp
class Vehicle { 
public: 
	Vehicle() 
	{ 
	cout << "This is a Vehicle" << endl; 
	} 
}; 
class FourWheeler { 
public: 
	FourWheeler() 
	{ 
	cout << "This is a 4 wheeler Vehicle" << endl; 
	} 
}; 
class Car: public Vehicle, public FourWheeler { 

}; 

// main function 
int main() 
{ 
	Car obj; 
	return 0; 
} 
```
What is the output of the inheritance example above?

```
Answer:
This is a Vehicle
This is a 4 wheeler Vehicle
```

-----

### Question 5

- Explain what abstraction means from an OOP standpoint. 
> Answer:
> Simply put, hiding the details / implementation of your class. 
- Does storing data in a linked list vs an array have any relation to abstraction? Explain.
> Answer:
> Yes. The data structures you choose are what you are abstracting from a user. In the instance of a list or an array, a user only cares (performance aside) that they can put values in or get values out. Not how they are stored.



### Question 6
To add two fractions you need to:
-   Find a common denominator by finding the LCM (Least Common Multiple) of the two denominators. 
-   Change the fractions to have the same denominator and add both terms.
-   Reduce the final fraction obtained into its simpler form by dividing both numerator and denominator by the largest common factor.

Assume you have the following class that has all of those listed methods implemented for you.
```cpp
class fraction{
	int numerator;
	int denominator;
	fraction reduce(fraction f);
	int  lcm(int a, int b);
public:
	fraction(int n,int d);
	void setumerator(int n);
	void setDenominator(int d);
};
```
Overload the **`+`** sign to add two fractions. You can assume your defining your method inline. Assume all the methods above are implemented. Just write the overloaded method ... nothing else.

```cpp
//Answer

fraction operator+ (const fraction &rhs){
    
    int l = lcm(rhs.denominator,denominator);

    int n = ((l / rhs.numerator) * rhs.numerator) + ((l / numerator) * numerator);

    return reduce(fraction(n,l));

}
```
-----

### Question 7

- A) All class members declared as `public` will be available to everyone. 
  
- B) This access modifier is similar to one of the other access modifiers, the difference is that the class member declared as `protected` are inaccessible outside the class but they can be accessed by any subclass (derived class).

- C) Only member functions or `friend methods` of another class are allowed to access the private data members of this class.

- D) The `public` data members of this class can be accessed from anywhere in the program using the dot operator.

- E) The class members declared as `private` can be accessed only by the functions inside the class. 



### Question 8

```cpp
class base 
{ 
public: 
	void fun_1() { cout << "base-1\n"; } 
	virtual void fun_2() { cout << "base-2\n"; } 
	virtual void fun_3() { cout << "base-3\n"; } 
	virtual void fun_4() { cout << "base-4\n"; } 
}; 

class derived : public base 
{ 
public: 
	void fun_1() { cout << "derived-1\n"; } 
	void fun_2() { cout << "derived-2\n"; } 
	void fun_4(int x) { cout << "derived-4\n"; } 
}; 

int main() 
{ 
    base *p; 
    derived obj1; 
    p = &obj1; 

    p->fun_1();  // Question A
    p->fun_2();  // Question B
    p->fun_3();  // Question C
    p->fun_4();  // Question D
    p->fun_4(5); // Question E

    // Question F: are the three lines below valid? State why or why not.
    derived *p1;
    base p2;
    p1 = &p2;
}
```

For questions A-F write on your answer sheet what prints out, or if it errors and why. 

```
Answer:

A: base-1
B: derived-2
C: base-3
D: base-4
E: error : no matching function in base class 
F: error : pointing a derived class pointer to a base class is illegal
```

### Question 9

A **copy constructor** is automatically created by the compiler when needed. However there are certain times a **copy contructor** needs to be created by the user. When we create our own copy constructor, especially of we have pointers (assume a linked list), we need to make sure we do it correctly. Given the class below:

```cpp
class LinkedList{
	nodePtr *head;
	int size;
public:
	LinkedList(){
		head = null;
		size = 0;
	}
    Insert(int x){
        //insert is done
    }
};
```

Using the above class definition, write a copy constructor for the ***LinkedList*** class that will initialize an instance of a linked list with a copy another linked list. Just write the constructor as if it were inline.

```cpp
//answer

LinkedList(const LinkedList &L){
    Node* Temp = L.head;

    while(Temp){
        insert(Temp->data);
        Temp = Temp->next;
    }
}

```

-----

### Question 10

When discussing the concept of friendship between class we must remember that: 

- A) The purpose of making class **X** a friend of class **Z** is so you give **X** access to  **Z**'s `private members`. 
- B) However the friendship between **X** and **Z** is not `mutual`.
- C) And friendship is also not `inheritable`.
 
-----

### Question 11

Write a function called **`countMe`** that counts the number of times it has been called.

```cpp
// Answer

int countMe(){
    static int count = 0;
    return ++count;
}
```

-----

### Question 12

Write a class called **`NumObjects`** that counts the number of objects in existance. You should assume that each object will be created and destroyed before your program ends. So your count should be equal to the number of existing objects.

```cpp
// Answer
class NumObjects{
  static int count;
public:
  NumObjects(){
    if(count)
      count++;
    else
      count=1;
  }
  ~NumObjects(){
    count--;
  }
};

// Must init outside object. Remember static does this once for 
// you and sets the value to zero (since it is an int)
int NumObjects::count;
```