#include <iostream>

using namespace std;

/**
 * @brief A node data type for our linked list
 *
 */
struct Node {
    int   data;  // holds our value
    Node *next;  // points to next node

    /**
     * @brief Default constructor
     *
     */
    Node() {
        data = 0;
        next = nullptr;
    }

    /**
     * @brief Overloaded constructor
     *
     * @param x : int value
     */
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

/**
 * @brief A list based queue.
 * - Queue's are FIFO: First In First Out
 * - We add items to the rear of the queue
 * - We remove items from the front of the queue
 */
class Queue {
    Node *Front;   // front of queue
    Node *Rear;    // rear of queue
    int   spaces;  // used to print visual queue

public:
    /**
     * @brief Construct a new Queue object
     *
     */
    Queue() {
        Front = Rear = nullptr; // set pointers to null
        spaces = 0; // set spaces to zero
    

    /**
     * @brief Adds item to the rear of the queue
     * 
     * @param val : int item to be added
     */
    void Push(int val) {
        // allocate new memory pointed to by temp.
        Node *temp = new Node(val);

        // if no front, then we have an empty queue
        if (!Front) {
            // Empty queue means front and rear should
            // point to the new node.
            Front = Rear = temp;
        } else {
            // Not empty, so we update the rear of the queue
            // (where items are added).
            Rear->next = temp;
            Rear = temp;

            // Update spaces for my stupid fancy print option :)
            spaces += 3;
            if (val > 9) {
                spaces++;
            }
        }
    }
    /**
     * @brief Remove item from queue
     * 
     * @return int : item taken from front of queue
     */
    int Pop() {

        // Update spaces for my stupid fancy print option :)
        spaces -= 3;
        if (retVal > 9) {
            spaces--;
        }

        // Point a temporary pointer to current front
        Node *temp = Front;

        // get a copy of the data since we will delete
        // the Front node in a second.
        int retVal = Front->data;

        // Move the front pointer to the next node.
        // (Does this work if the list has only 1 node??????)
        Front = Front->next;

        // Delete the memory pointed to by temp (old front)
        delete temp;

        // return our value
        return retVal;
    }

    /**
     * @brief Advanced 3D graphical representation of
     *        our integer queue :) 
     * 
     */
    void PrintFancy() {
        cout << endl;
        cout << "^";
        for (int i = 0; i < spaces; i++) {
            cout << " ";
        }
        cout << "^" << endl;
        cout << "|";
        for (int i = 0; i < spaces; i++) {
            cout << " ";
        }
        cout << "|" << endl;
        cout << "F";
        for (int i = 0; i < spaces; i++) {
            cout << " ";
        }
        cout << "R" << endl;
    }

    /**
     * @brief Ubiquitous print method for academic purposes
     * 
     * @param printfancy : true print fancy, pass in false to turn off
     */
    void Print(bool printfancy = true) {
        Node *temp = Front;
        while (temp != nullptr) {
            cout << temp->data;

            if (temp->next) {
                cout << "->";
            }
            temp = temp->next;
        }
        if (printfancy) {
            PrintFancy();
        }
    }
};

void PointerFun() {
    Node X(5);  // New node with value 5
    Node Y;     // New node with value 0 (default constructor)

    cout << X.data << endl;
    cout << Y.data << endl;

    // SELF::TEST SELF::TEST SELF::TEST SELF::TEST SELF::TEST
    // Add a print method to the  Node struct and print
    // the value out using it instead (e.g. X.Print() )

    /////////////////////////////////////////////////////////////////
    Node *A = nullptr;  // Declare three pointers that will point
    Node *B = nullptr;  // to a 'Node' type.
    Node *C = nullptr;

    // Now allocate new memory and place the address of that new
    // memory in the pointer on the left of the '=' sign.
    A = new Node(7);
    B = new Node(3);
    C = new Node(11);

    A->next = B;  // A's next now points to B
    B->next = C;  // B's next now points to C

    C->data = 33;  // Change C's data to 33

    // Write out data member of each Node
    cout << A->data << endl;
    cout << B->data << endl;
    cout << C->data << endl;

    // This next print statement prints 'address' of C.
    // It makes sense, since C is a 'pointer' and pointers
    // hold addresses!
    cout << C << endl;

    // What does this print out?
    cout << A->next->next->data << endl;
}

int main() {
    srand(time(0));
    // run code that deals with the small pointer explanation
    // done in class
    PointerFun();

    Queue Q;     // Declare instance of a queue
    int   temp;  // temp variable to hold data from node

    // push 10 random numbers onto the queue
    for (int i = 0; i < 10; i++) {
        temp = rand() % 100;  // random num between 0-99
        Q.Push(temp);
        cout << "Pushed: " << temp << endl;
    }
    // print the queue
    Q.Print();
    cout << endl;

    // pop some values off the queue
    for (int i = 0; i < 5; i++) {
        temp = Q.Pop();
        cout << "Popped: " << temp << endl;
    }
    Q.Print();
}