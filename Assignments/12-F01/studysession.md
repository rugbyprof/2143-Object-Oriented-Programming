Object vs Class

Class = definition that is not instantiated. 
Object = a class that has been (declared) instantiated. 

```cpp

// class definition
class something{

};


int main(){
    // object ...
    something s;
}
```


---


- Abstract classes:
  - contains at least one pure virtual function


```cpp
class bs{
    virtual method() = 0;
};
```

- Constructors
  - Default Constructor
  - Overloaded Constructor
  - Copy Constructor

Write a class definition
```cpp

struct Node {
    int data;
    Node * next;
}

// version 1
class classALinked{
    //LinkedList *linkedlist;
    Node* root; 
    //stuff
};

// write a copy constructor for classALinked that copies a linked list from the class
// coming in to the local new version...

classALinked::classALinked(const classALinked &other){
    Node* root;

    // code to loop over other.root and assign all values to our internal
    // linked list. 
}

//version 2
class classA{
    // this still provides a copy constructor because an array
    // does not know how to assign 100 values to another "array"
    int array[100]; // this guy or gal is a pointer. its just a sneaky pointer.
    //[]
    //stuff
};

//version 3
class classA{
    int a;
    double b;
    int c;
    float d;
    string name;
    //[]
    //stuff
};
```

No pointers = no copy constructor


### usage
```cpp
classA other();
classA var1(double,double);
classA var2(int, int, int);
classA var3(classA other);

```

### Copy Constructor as gotten from ChatGPT

```cpp
class listClass {
public:
    // Default constructor
    listClass() : head(nullptr) {}

    // Copy constructor - must be defined
    listClass(const listClass& other) {
        // Copy the head pointer of the other object
        head = nullptr;

        // If the other object's linked list is not empty, copy its contents
        if (other.head != nullptr) {
            // Create the first node of the new linked list
            head = new Node(other.head->data);

            // Traverse the other object's linked list and copy its nodes
            Node* current = head;
            Node* otherCurrent = other.head->next;
            while (otherCurrent != nullptr) {
                current->next = new Node(otherCurrent->data);
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        }
    }

private:
    // Node struct for the linked list
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    // Pointer to the head of the linked list
    Node* head;
};
```

In this updated version, the `listClass` includes a private `Node` struct for the linked list and a pointer to the head of the linked list. The copy constructor performs a deep copy of the linked list by traversing the other object's linked list and copying its nodes one by one.

The `Node` struct includes a constructor that takes a `T` value and initializes the node's data and `next` pointer. The `listClass` constructor initializes the `head` pointer to `nullptr`.

Note that in this implementation, we assume that the `T` type used in the linked list has a default copy constructor. If the `T` type requires a custom copy constructor, we would need to define one and use it to copy the node data during the deep copy process.

- Why do we need to make destructors virtual.
  - This uses the virtual key word for all the same reasons we use the virtual keyword when dealing with methods.

### Link to Code
https://replit.com/@rugbyprof/2143lastweek#main.cpp


### When Do We Need Assignment Operator

- Do we need to overload assignment for a class with now complex (pointer) structurs? NO
- Do we need a copy constructor for a class with (same as above)? NO
- ONLY WHEN DEEP COPY IS INVOLVED.

```cpp
// still requires a deep(ish) copy so everyone doesn't become an asshole.
class A{
    string *name;

    A(){
        name = new string("Griffin");
    }
}

### Static Keyword

Class level variables (google borg pattern c++)

// using static variable to know how many instances of a class exist currently
