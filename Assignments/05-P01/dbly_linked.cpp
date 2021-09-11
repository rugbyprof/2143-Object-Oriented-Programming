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
*        Use it like a linked list now. More like a vector next program
* 
*  Files: TBD
*****************************************************************************/
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

// Node for our linked list
struct Node {
    int data;

    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        prev = next = NULL;
    }

    /**
     * @brief Construct a new Node object and connect it to its neighbors 
     *        directly in the constructor.
     * 
     * @param int x - data value 
     * @param Node*& p - previous node reference   
     * @param Node*& n - next node reference  
     */
    Node(int x, Node*& p, Node*& n) {
        data = x;
        
        // `p` was passed by address, so changes to `p` are
        // remembered! So, we point `p` to `this` ( `this` = the new node we are in right now ).
        if(p){
            p->next = this;
        }
        // Same for `n` as was for `p`.
        if(n){
            n->prev = this;
        }
        
        // Now point `this` nodes previous and next to the nodes we passed in.
        
        prev = p;
        next = n;

        // Below is the same as above but we explicitly use the `this` keyword.
        // this->prev = p;
        // this->next = n;
    }
};

class MyVector {
private:
    Node*           head;  // base pointer of list
    Node*           tail;
    int             size;
    static ofstream fout;
    string          fileName;
    bool            sorted;

    /**
     * @brief Private version of inOrder push. 
     * 
     * @param x 
     */
    void _inorderPush(int x) {
         
        Node* current = head;

        while (current->data > x) {  // loop to find proper location
            current = current->next;
        }

        Node* newNode = new Node(x,current->prev,current); 

        // current->prev->next = newNode;
        // newNode->prev = current->prev;
        // newNode->next = current;
        // current->prev = newNode;

        size++;  // add to size :)
    }

public:
    /**
     * @brief - Initialize the data members so we don't
     *      have duplicate lines in each constructor.
     * 
     */
    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
        sorted = 0;
    }

    /**
     * @brief Default constructor 
     * 
     */
    MyVector() {
        init();
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * @param int   *A - pointer to array 
     * @param int   aSize - size of array
     */
    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * @param string FileName - file to open and read
     * 
     * Assumes infile will contain numbers only delimited by spaces or 
     * new lines.
     */
    MyVector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

    /**
     * @brief Copy Constructor 
     * 
     * @param MyVector &other 
     */
    MyVector(const MyVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    /**
     * @brief Public version of inOrder push.
     * 
     * @param x 
     */
    void inorderPush(int x) {
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
     * @brief Sort the current values in the linked list. This doesn't require any changing
     * because its a doubly linked list as we are swapping DATA not actual nodes.
     * 
     * @returns None
     */
    void sortList() {
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
     * @brief Add value to front of list.
     * 
     * @param x 
     * @return bool - true = successful push
     */
    bool pushFront(int x) {
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
     * @brief This method loads values from 'other' list in 'this' list.
     *          It loads an array first so we can process the values in
     *          reverse so they end up on 'this' list in the proper order.
     *          If we didn't use the array, we would reverse the values
     *          from the 'other' list.
     * 
     * @depends - Uses `pushFront(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushFront(const MyVector& other) {
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
            pushFront(tempData[i]);
        }
    }

    /**
     * @brief -  Add 'other' list's values to end of 'this' list.
     * @note - Uses `pushRear(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     * @brief - Add value to rear of list
     * 
     * @param int x - value to be added 
     * @return bool - successful push = 1 
     */
    bool pushRear(int x) {
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
     * @brief Push value onto list at soecified position, if it exists.
     * 
     * @param int i - location index 
     * @param inr x - value to add 
     * @return bool - true add successful / false add failed 
     */
    bool pushAt(int i, int x) {
        // IF index is at the end of the list
        // OR beyond the end, do a push rear,
        if (i >= size - 1) {
            return pushRear(x);
        }

        if (i == 0) {
            return pushFront(x);
        }

        // Index is not front or rear so ... find proper
        //

        Node* newNode = new Node(x);  // allocate new node
        Node* current = head;

        while (i > 0) {  // loop to find proper location
            current = current->next;
            i--;
        }

        // newNode is getting placed in front of current

        // update temp's previous pointer to point to node before current
        // update temp's next to point to current (making current come after newNode)
        newNode->prev = current->prev;
        newNode->next = current;

        // update node before current to now point to newNode
        // and update current to point back to newNode
        current->prev->next = newNode;
        current->prev = newNode;

        // current->next is already pointing to proper node so we leave it.

        size++;  // add to size :)
        return true;
    }

    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
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
     * @brief Destroy the My Vector object
     * 
     */
    ~MyVector() {
        Node* current = head;
        Node* prev = head;

        while (current) {
            prev = current;
            current = current->next;
            //cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }
};

ofstream MyVector::fout;

int main() {
    MyVector V1;
    MyVector V2("input.dat");
    cout << V2 << endl;
    V2.sortList();
    cout << V2 << endl;

    V1.pushFront(56);
    V1.pushFront(42);
    V1.pushFront(30);
    V1.pushFront(48);
    V1.pushAt(0, 1);
    V1.pushAt(10, 10);
    cout << V1 << endl;

    V1.pushAt(2, 88);
    cout << V1 << endl;

    V2.pushRear(V1);
    cout << V2 << endl;

    V2.sortList();
    cout << V2 << endl;
}