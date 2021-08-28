/**
*                    
*  Author:           Terry
*  Title:            Linked List Example
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        Linked List Example 
* 
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Node for our linked list
struct node {
    int data;  // data value (could be a lot more values)

    node* next;  // we always need a "link" in a linked list

    node(int x) {  // cunstructor to make adding values easy
        data = x;
        next = NULL;
    }
};

/**
 * @brief Load array with values from a file
 * 
 * @param string filename 
 * @param int*& arr 
 * @param int& size 
 */
void loadArr(string filename, int*& arr, int& size) {
    ifstream fin;         // stream reference
                          //
    fin.open(filename);   // open the file
                          //
    fin >> size;          // get first value which contains
                          // number of remaining values in file
                          //
    arr = new int[size];  // allocate new array of correct size
                          //
    int i = 0;            // need an array index for our while loop
                          //
    // Can also use for loop since we know the exact count in file.
    // eof = end of file flag
    // `!fin.eof()` evaulates to true when we hit end of file.
    while (!fin.eof()) {
        fin >> arr[i];  // read file value straight into array
                        // at index i
        i++;            // increment array index
    }
}

/**
 * @brief Prints an array
 * 
 * @param int arr 
 * @param int size
 * 
 * @returns void
 */
void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << arr[i] << "]";
    }
    cout << "\n";
}

class LinkedList {
private:
    node* head;  // base pointer of list
public:
    /**
     * @brief Default Constructor 
     * 
     * Creates a new Linked List object.
     * 
     * @param void
     * @return void
     */
    LinkedList() {
        head = NULL;  // NULL = zeros
                      // and zeros imply empty
    }

    /**
     * @brief Overloaded Constructor 
     * 
     * Creates a new Linked List object from 
     * an array of values.
     * 
     * @param int* A - array of values
     * @param int size - size of array
     * 
     * @return void
     */
    LinkedList(int A[], int size) {
        head = NULL;  // NULL = zeros
                      // and zeros imply empty

        for (int i = 0; i < size; i++) {
            Push(A[i]);
        }
    }

    /**
     * @brief Adds a value to our list
     * 
     * @param int x - value to push on linked list
     * 
     * @return void
     */
    void Push(int x) {
        node* tempPtr = new node(x);  // create a new node and
                                      // add data to it

        if (!head) {  // `!head` implies empty list
                      // So does `head == NULL`

            head = tempPtr;  // `head = tempPtr` places addrress of
                             // tempPtr in head (points head to tempPtr)

        } else {                   // list not empty
            tempPtr->next = head;  // point tempPtr's next to what head points to
            head = tempPtr;        // now point head to tempPtr
        }
    }

    /**
     * @brief Prints a linked list to std out
     * 
     * @param void
     * 
     * @return void
     */
    void print() {
        node* temp = head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            cout << temp->data;  // print data from node
            if (temp->next) {
                cout << "->";
            }
            temp = temp->next;  // move to next node
        }
        cout << endl;
    }

    ~LinkedList() {
    }
};

int main() {
    int        A[] = {1, 2, 3, 4, 5, 6};    // array initialized with 1-6
    LinkedList L(A, 6);                     // linked list built with array

    L.print();  // print the list

    int* B;     // Int pointer to reference a linked list
    int  size;  // used to hold a count for list and array

    loadArr("input.dat", B, size);  // Stand alone function to
                                    //    read values in from file
    printArr(B, size);              // Stand alone function to print array
    LinkedList L2(B, size);         // Create 2nd instance of list
    L2.print();                     // Print list 2
}