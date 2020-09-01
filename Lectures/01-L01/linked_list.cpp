///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Terry Griffin
// Email:            terry.griffin@msutexas.edu
// Label:            L01
// Title:            Linked List Example
// Course:           2143
// Semester:         Fall 2020
//
// Description:
//       Example implementation of a linked list that holds integers.
//
// Usage:
//       Nothing special right now.
//
// Files:            
//       None
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

using namespace std;

/**
 * Node: A linked list node that holds integers.
 * Description:
 *      int data    : var to hold our data ! (very very complex node).
 *      Node* next  : a pointer to the "next" node.
 * 
 * Methods:
 *      Node(int)   : constructor to init data.
 */
struct Node{
    int data;
    Node* next;
    Node(int d){
        data = d;
        next = NULL;
    }
};


/**
 * List
 * 
 * Description:
 *      Integer singly linked list implementation
 * 
 * Public Methods:
 *      - int Pop()
 *      - void Delete(int)
 *      - void Print()
 * 
 * Private Methods:
 *      - None
 * 
 * Usage: 
 * 
 *  List L;
 *  L.Push(80);
 *  L.Push(90);
 *  L.Print();
 *  int x = L.Pop();
 *      
 */
class List{
private:
    int size;           // size of list
    Node* head;         // pointer to head of list
public:
    /**
     * Constructor
     */
    List(){     
        size = 0;       // init size to 0
        head = NULL;    // Null means NO list!
    }

    /**
     * Push:
     *    Add item to end of list.
     * Params:
     *    int data  : value to put into list
     * 
     * Returns:
     *     Void
     */
    void Push(int data){
        //Allocate new memory (of type Node), and put our data value in it.
        Node* N = new Node(data);

        // list is empty so point head to our new Node
        if(!head){
            head = N;
        }else{
            // Get a temporary pointer to head
            Node* temp = head;

            // Traverse the list to get to the end
            while(temp->next != NULL){
                temp = temp->next;
            }

            // Link the node to the end of the list
            temp->next = N;
        }
    }

    /**
     * Pop:
     *    Remove item from front of list.
     * Params:
     *    Void
     * 
     * Returns:
     *     int  : value in the node were removing
     */
    int Pop(){
        Node* temp = head;      // get a temp pointer to head (so we can delete in a minute)
        int d = head->data;     // get the data from the head node
        head = head->next;      // move the head pointer to the next node
        delete temp;            // delete the old head node
        return d;               // return the data!
    }

    /**
     * Delete:
     *    Remove item from anywhere in the list.
     *    
     * Params:
     *    int key   : value to find and remove
     * 
     * Returns:
     *     Void
     */
    void Delete(int key){
        // Get a pointer to the head so we can traverse the list
        // I'm calling it "prev" for "previous" because we always
        // want to stay one before the node that we want to delete
        // in a singly linked list.
        Node* prev = head;

        // CASE 1: Key is at front of list
        if(head->data == key){
            head = head->next;  // move head to next node
            delete prev;        // delete the old head
            return;             // return kills the function
        }

        // CASE 2 and 3: Key is either in the middle or end, so traverse
        //               and go find the node!
        // This will stop one node before the data (if it exists)
        while(prev->next && prev->next->data != key){
            prev = prev->next;
        }

        // CASE NULL: The key is not in the list, so just return.
        if(!prev->next){
            return;
        }else{
            // Create another temp pointer that points to the node to be deleted.
            Node* temp = prev->next;

            // Point the previous pointer OVER to temp pointer (to the next node)
            prev->next = temp->next;

            // Now we can delete the node with the key.
            delete temp;
        }
    }

    /**
     * Print:
     *    Prints the list.
     *    
     * Params:
     *    Void
     * 
     * Returns:
     *     Void
     */
    void Print(){
        Node* temp = head;      // temp pointer to head of list (again!)

        while(temp != NULL){    // while we are still pointing to an existing node
            cout<<temp->data;   // write out the "data"
            if(temp->next){     // if there is a node to my right
                cout<<"->";     // print an "->" 
            }
            temp = temp->next;  // move down the list (traverse)
        }
        cout<<endl;             // new line
    }

    /**
     * Empty:
     *    Is list empty
     *    
     * Params:
     *    Void
     * 
     * Returns:
     *     bool     : true means empty list
     */
    bool Empty(){
        return head==NULL;
    }
};


int main() {
    srand(1000);                // seed random number generator
    List L;                     // create instance of a list

    for(int i=0;i<10;i++){      // loop 10 times and load 10 nums
        L.Push(rand()%100);     // into list (values between 0-99)
    }

    L.Print();                  // Print the list
    L.Delete(90);               // Delete the key 90 from the list
    L.Delete(3);                // Delete the key 3 from the list
    L.Delete(55);               // Delete 55 from the list
    L.Print();                  // print the list
    
    // While the list still has values in it
    // remove and print
    while(!L.Empty()){
        int d = L.Pop();
        cout<<d<<endl;
    }

}