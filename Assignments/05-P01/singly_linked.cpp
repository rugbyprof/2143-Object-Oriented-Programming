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
*  Usage:
*        Usually command line examples go here.
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
//             |        |      |        |      |        |      |        | 
//             +--------+      +--------+      +--------+      +--------+ 

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
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
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
    }

public:
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
     * @brief Sort the current values in the linked list.
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
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr;
            // otherwise adjust head pointer
        } else {
            tempPtr->next = head;
            head = tempPtr;
        }
        size++;
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
     * @brief Push value onto list at soecified position, if it exists.
     * 
     * @param int i - location index 
     * @param inr x - value to add 
     * @return bool - true add successful / false add failed 
     */
    bool pushAt(int i, int x) {
        if (i >= size) {
            return false;
        }

        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i > 0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
        return true;
    }

    /**
     * @brief - Add value to rear of list
     * 
     * @param int x - value to be added 
     * @return None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        } else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
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
        os << endl;
        return os;
    }

    /**
     * @brief Destroy the My Vector object
     * 
     */
    ~MyVector() {
        Node* curr = head;
        Node* prev = head;

        while (curr) {
            prev = curr;
            curr = curr->next;
            //cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }
};

ofstream MyVector::fout;

int main() {
    MyVector V1;
    MyVector V2("input.dat");

    V2.sortList();

    V1.pushFront(56);
    V1.pushFront(42);
    V1.pushFront(30);
    V1.pushFront(48);

    V1.sortList();
    cout << V1 << endl;

    V1.pushAt(3, 88);
    cout << V1 << endl;
    V1.sortList();
    cout << V1 << endl;

    V2.pushRear(V1);
    cout << V2 << endl;

    V2.sortList();
    cout << V2 << endl;
}