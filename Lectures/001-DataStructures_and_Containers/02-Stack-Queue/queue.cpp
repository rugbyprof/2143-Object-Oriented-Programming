#include <time.h>

#include <iostream>

using namespace std;

/**
 * Node class
 * Data members:
 * - data: integer data
 * - next: pointer to the next node
 * Methods:
 * - print: print the node
 * - Default Constructor: initialize the node with 0 and nullptr
 * - Overloaded Constructor: initialize the node with given data and next node
 * - friend ostream operator: overload the << operator to print the node
 */
struct Node {
    int data;
    Node *next;
    Node() {
        data = 0;
        next = nullptr;
    }
    Node(int val, Node *n = nullptr) {
        data = val;
        next = n;
    }
    void print() { cout << data << "->" << next; }
    friend ostream &operator<<(ostream &os, const Node &other) {
        return os << "[" << other.data << "|" << other.next << "]";
    }
};

/**
 * Queue class
 * Data members:
 * - front: pointer to the front of the queue
 * - rear: pointer to the rear of the queue
 * - fakefront: pointer to the fake front of the queue
 * Methods:
 * - push: push an element to the queue
 * - pop: pop an element from the queue
 * - print: print the queue
 * - friend ostream operator: overload the << operator to print the queue
 */
class Queue {
   public:
    Node *front;
    Node *rear;

    /**
     * Default Constructor for the Queue class
     * Initializes the front and rear pointers to nullptr
     */
    Queue() { front = rear = nullptr; }

    /**
     * Push Method
     * Pushes an element to the queue
     * @param int val: value to be pushed
     * @return void
     */
    void push(int val) {
        Node *temp = new Node(val);  // allocate new node

        // empty queue gets handled here
        if (!front) {
            front = rear = temp;
            // non-empty queue gets handled here
        } else {
            rear->next = temp;
            rear       = temp;
        }
    }

    /**
     * Pop Method
     * Pops an element from the queue
     * @param void
     * @return int: value of the popped element
     */
    int pop() {
        Node *temp = front;        // save a reference to the front node
        int data   = front->data;  // save the data of the front node
        front      = front->next;  // update "front" to be the next node
        delete temp;               // delete the old front node
        return data;               // return the data of the old front node
    }
    /**
     * Print Method
     * Prints the queue
     * @param void
     * @return void
     */
    void print() {
        Node *temp = front;
        while (temp->next) {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout << temp->data;
    }
    /**
     * Overloaded << operator
     * Prints the queue
     * @param ostream &os: output stream
     * @param const Queue &other: queue to be printed
     * @return ostream: output stream
     */
    friend ostream &operator<<(ostream &os, const Queue &other) {
        Node *travel = other.front;
        while (travel->next) {
            os << "[" << travel->data << "|" << travel->next << "]->";
            travel = travel->next;
        }
        os << "[" << travel->data << "|" << travel->next << "]";
        return os;
    }
};

int main() {
    srand(time(0));
    Node temp(7);

    cout << temp << endl;

    Queue Q;

    for (int i = 0; i < 5; i++) {
        Q.push(rand() % 100);
    }

    // cout << endl;
    // Q.print();
    // cout << endl;
    // cout << Q.pop() << endl;
    // cout << Q.pop() << endl;
    // cout << endl;
    // Q.print();

    cout << Q << endl;
}