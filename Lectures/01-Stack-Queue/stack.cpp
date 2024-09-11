#include <iostream>

using namespace std;

/**
 * Stack class
 * Data members:
 * - array: pointer to array of integers
 * - size: size of the array
 * - top: index of the top element in the stack
 * Methods:
 * - init: initialize the stack with given size
 * - push: push an element to the stack
 * - pop: pop an element from the stack
 * - print: print the stack
 */
class Stack {
    int *array;  // pointer to array of integers
    int size;    // size of the array
    int top;     // index of the top element in the stack

    /**
     * Initialize the stack with given size
     */
    void init(int size) {
        array = new int[size];
        top   = -1;
    }

   public:
    /**
     * Default Constructor for the Stack class
     * Initializes the stack with a hard coded size (10)
     * @param int _size: size of the stack
     */
    Stack() {
        size = 10;
        init(size);
    }
    /**
     * Overloaded Constructor for the Stack class
     * Initializes the stack with a given size
     * @param int _size: size of the stack
     */
    Stack(int _size) {
        size = _size;
        init(size);
    }

    /**
     * Destructor for the Stack class
     * Deletes the array
     */
    void push(int val) {
        top++;
        // check for out of bounds
        array[top] = val;
    }
    int pop() {
        int temp = array[top];
        top--;
        return temp;
    }
    /**
     * Print the stack
     * This is for academic purposes only (really)
     */
    void print() {
        cout << "\nSize:" << size << endl;
        for (int i = 0; i <= top; i++) {
            cout << array[i] << endl;
        }
    }
};

int main() {
    Stack S1;      // stack calls default constructor
    Stack S2(50);  // stack calls overloaded constructor

    // S1 and S2 are now objects of the Stack class

    S1.print();  // print the stack
    S2.print();  // print the stack

    // push 10 random numbers onto S1
    for (int i = 0; i < 10; i++) {
        S1.push(rand() % 100);
    }

    // various operations on S1
    S1.print();
    S1.pop();
    S1.pop();
    S1.pop();
    S1.pop();
    S1.pop();
    S1.push(99);
    S1.print();

    return 0;
}