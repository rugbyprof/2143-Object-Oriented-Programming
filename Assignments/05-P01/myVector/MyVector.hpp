/*****************************************************************************
*                    
*  Author:           Griffin
*  Title:            Singly linked list vector implementation
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        Uses a singly linked list as the backend for an STL like "vector" 
*        class definition.
*   
*  NO ERROR DETECTION USED. SO RETURNING 'TRUE' FOR A SUCCESFUL PUSH ONTO LIST
*  IS NOT FULLY ACCURATE AS WE ARE NOT INCLUDING ANY "TRY" "CATCH" BLOCKS TO CAPTURE
*  ERRORS CORRECTLY. WE WILL COVER THESE LATER.
* 
*  Usage:
*        Usually command line examples go here.
* 
*  Files: TBD
*****************************************************************************/
#pragma once
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000  // infinity

using namespace std;

// Node
//             +--------+      +--------+      +--------+      +--------+
//   Head ---> |        | ---> |        | ---> |        | ---> |        | ---> NULL
//   NULL <--- |        | <--- |        | <--- |        | <--- |        |
//             +--------+      +--------+      +--------+      +--------+

/**
 * 
 * @param: {s []} undefined : 
 */
struct Node {
    int   data;
    Node* next;
    Node* prev;

    Node(int x);

    Node(int x, Node*& p, Node*& n);
};

/**
 * Node::Node 
 * 
 *      Default constructor
 * 
 * @param: {int} x : data for node
 */
Node::Node(int x) {
    data = x;
    prev = next = NULL;
}

/**
 * Node::Node 
 * 
 * Construct a new Node object and connect it to its neighbors 
 *        directly in the constructor.
 * 
 * @param: {int} x   : data value 
 * @param: {Node*} p : previous node reference
 * @param: {Node*} n : next node reference 
 */
Node::Node(int x, Node*& p, Node*& n) {
    data = x;

    // `p` was passed by address, so changes to `p` are
    // remembered! So, we point `p` to `this` ( `this` = the new node we are in right now ).
    if (p) {
        p->next = this;
    }
    // Same for `n` as was for `p`.
    if (n) {
        n->prev = this;
    }

    // Now point `this` nodes previous and next to the nodes we passed in.

    prev = p;
    next = n;

    // Below is the same as above but we explicitly use the `this` keyword.
    // this->prev = p;
    // this->next = n;
}

class MyVector {
private:
    Node*           head;  // base pointer of list
    Node*           tail;
    int             size;
    static ofstream fout;
    string          fileName;
    bool            sorted;
    void            _inorderPush(int);

public:
    void init();
    MyVector();
    MyVector(int[], int);
    MyVector(string);
    MyVector(const MyVector&);

    void inorderPush(int);
    void sortList();
    bool pushFront(int);
    void pushFront(const MyVector&);
    void pushRear(const MyVector&);
    bool pushRear(int);
    bool pushAt(int, int);
    ~MyVector();

    friend ostream& operator<<(ostream&, const MyVector&);
};

/**
 * private MyVector : Private version of inOrder push.
 * 
 * @param: {int} x : value for list
 */
void MyVector::_inorderPush(int x) {
    Node* current = head;

    while (current->data > x) {  // loop to find proper location
        current = current->next;
    }

    // create new node with data, and neighboring node pointers
    Node* newNode = new Node(x, current->prev, current);

    size++;  // add to size :)
}

/**
 * public MyVector 
 *      Initialize the data members so we don't
 *      have duplicate lines in each constructor.
 * @param: None
 * @return: None
 */
void MyVector::init() {
    head = tail = NULL;
    fileName = "";
    size = 0;
    sorted = 0;
}

/**
 * public MyVector
 *      Default constructor 
 * 
 * @param:None
 * @return:None
 */
MyVector::MyVector() {
    init();
}

/**
 * public MyVector
 *      Overloaded constructor to init vector with array.
 * 
 * @param: {int *} A  : pointer to array 
 * @param: {int} aSize : size of array
 * 
 * @return: None
 */
MyVector::MyVector(int A[], int aSize) {
    init();

    for (int i = 0; i < aSize; i++) {
        pushRear(A[i]);
    }
}

/**
 * public MyVector
 *      Overloaded constructor
 * 
 *      Assumes infile will contain numbers only delimited by 
 *      spaces or new lines.
 * 
 * @param: {string} FileName : file to load
 * 
 * @return: None
 */
MyVector::MyVector(string FileName) {
    this->init();  // initialize class vars

    ifstream fin;       // filestream reference
    int      temp = 0;  // temp var to read vals

    fin.open(FileName);  // loop through and load file
    while (!fin.eof()) {
        fin >> temp;
        this->pushRear(temp);  // pushRear keeps values in the order
                               //      that they were read.
    }
}

/**
 * public MyVector
 *      Overloaded constructor
 * 
 * @param: const {MyVector&} other : Another vector of same type
 * 
 * @return:None
 */
MyVector::MyVector(const MyVector& other) {
    this->init();  // initialize class vars

    Node* temp = other.head;  // Reference other list

    while (temp) {
        this->pushRear(temp->data);  // pushRear keeps values in the same
                                     //      order as other list.

        temp = temp->next;  // goto next node
    }
}

/**
 * public inorderPush
 * 
 * @param: {int} x : value to be added
 * 
 * @return:None
 */
void MyVector::inorderPush(int x) {
    if (!sorted) {
        sortList();
    }
    if (!head) {
        pushFront(x);  // call push front for empty list (or pushRear would work)
    } else if (x < head->data) {
        pushFront(x);  // call push front if x is less than head
    } else if (x > tail->data) {
        pushRear(x);  // call push rear if x > tail
    } else {
        _inorderPush(x);  // call private version of push in order
    }
}

/**
 *  public sortList
 *      Sort the current values in the linked list. This doesn't require any changing
 *      because its a doubly linked list as we are swapping DATA not actual nodes.
 * 
 * @param: None
 * @return:None
 */
void MyVector::sortList() {
    Node* newFront = head;
    while (newFront->next) {
        Node* smallest = newFront;
        Node* current = newFront;
        int   minimum = INF;
        while (current) {
            if (current->data < minimum) {
                smallest = current;
                minimum = current->data;
            }
            current = current->next;
        }
        smallest->data = newFront->data;
        newFront->data = minimum;
        newFront = newFront->next;
    }
    sorted = true;
}

/**
 * public pushFront 
 *      Add value to front of list.
 * 
 * @param: {int} x : value to be added
 * @return {bool}  : true = successful push
 */
bool MyVector::pushFront(int x) {
    Node* newNode = new Node(x);

    // empty list make head and tail
    // point to new value
    if (!head) {
        head = tail = newNode;
        // otherwise adjust head pointer
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
    return true;
}

/**
 * public pushFront
 *      This method loads values from 'other' list in 'this' list.
 *      It loads an array first so we can process the values in
 *      reverse so they end up on 'this' list in the proper order.
 *      If we didn't use the array, we would reverse the values
 *      from the 'other' list.
 * 
 *      Uses `pushFront(int)`
 * 
 * @param: const {MyVector&} other : Another vector of same type
 * @return:None
 */
void MyVector::pushFront(const MyVector& other) {
    Node* otherPtr = other.head;           // get copy of other lists head
    int*  tempData = new int[other.size];  // allocate memory to hold values

    // load other list into array
    int i = 0;
    while (otherPtr) {
        tempData[i] = otherPtr->data;
        otherPtr = otherPtr->next;
        ++i;
    }

    // process list in reverse in order to keep them
    // in their original order.
    for (int i = other.size - 1; i >= 0; i--) {
        this->pushFront(tempData[i]);
    }
}

/**
 * public  pushRear
 *      Add 'other' list's values to end of 'this' list.
 * 
 * @param: const {MyVector&} other : Another vector of same type
 * @return:None
 */
void MyVector::pushRear(const MyVector& other) {
    Node* otherPtr = other.head;  // get copy of other lists head

    while (otherPtr) {  // traverse and add
        this->pushRear(otherPtr->data);
        otherPtr = otherPtr->next;
    }
}

/**
 * public pushRear 
 *      Add value to rear of list
 * 
 * @param: {int} x : value to be added
 * @return {bool}  : true = successful push
 */
bool MyVector::pushRear(int x) {
    Node* newNode = new Node(x);

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;  // add to size of list
    return true;
}

/**
 * public pushAt 
 *      Push a value onto the vector at a specified index location.
 * 
 * @param  {int} i : location index 
 * @param  {int} x : value to be added
 * @return {bool}  : true add successful / false add failed 
 */
bool MyVector::pushAt(int i, int x) {
    // If index is greater then size -1 call a pushRear.
    if (i >= size - 1) {
        return pushRear(x);
    }
    // If index is 0, call pushFront
    if (i == 0) {
        return pushFront(x);
    }

    // Index is not front or rear so ... traverse
    // to ith location in the list.

    Node* newNode = new Node(x);  // allocate new node
    Node* current = head;

    // loop to find proper location
    while (i > 0) {  
        current = current->next;
        i--;
    }

    // We have the location, and now newNode is getting placed in front of current
    // and we need to fix 4 pointers to properly insert the new node.

    // 1. update temp's previous pointer to point to node before current
    // 2. update temp's next to point to current (making current come after newNode)
    newNode->prev = current->prev;
    newNode->next = current;

    // 3. update the node before current to now point to newNode
    // 4. and update current to point back to newNode
    current->prev->next = newNode;
    current->prev = newNode;

    // current->next is already pointing to proper node so we leave it.

    size++;  // add to size :)
    return true;
}

/**
 * friend ostream 
 *      Lets us print to std out using `<<`
 * 
 * @param  {ostream&} os   : copy of ostream (by address)
 * @param  {MyVector&} rhs : Some copy of a MyVector
 * @return {ostream&}      : The ostream were writing to
 */
ostream& operator<<(ostream& os, const MyVector& rhs) {
    Node* temp = rhs.head;  // temp pointer copies head

    while (temp) {  // this loops until temp is NULL
                    // same as `while(temp != NULL)`

        os << temp->data;  // print data from Node
        if (temp->next) {
            os << "->";
        }
        temp = temp->next;  // move to next Node
    }

    return os;
}


/**
 * MyVector::~MyVector 
 *      Our destructor to give back memory allocated in the heap.
 * 
 *      Remember, a destructor is necessary for objects that will get
 *      created and destroyed before the program is over. When your
 *      program ends, the allocated memory for that process gets 
 *      cleaned up by the OS.
 */
MyVector::~MyVector() {
    Node* temp = head;
    while (head) {
        temp = head;
        head = head->next;
        //cout << "deleting: " << temp->data << endl;
        delete temp;
    }
}
