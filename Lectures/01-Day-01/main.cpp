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
#include <iostream>

using namespace std;

// Node for our linked list
struct node {
    int d;              // data value (could be a lot more values)

    node* next;         // we always need a "link" in a linked list

    node(int x){        // cunstructor to make adding values easy
        d = x;
        next = NULL;
    }
};

/**
* LinkedList
*   
* Description:
*   A list of integers 
*/
class LinkedList{
private:
    node* head;         // base pointer of list
public:
    /**
    * Constructor
    * 
    * Description:
    *      Inits our list
    * 
    * Params:
    *      void
    * 
    * Returns:
    *      void
    */
   LinkedList(){        // constructor

       head = NULL;     // NULL = zeros
                        // and zeros imply empty
   }

    /**
    * Public : Push
    * 
    * Description:
    *      Adds a node to the front of the list (by head)
    * 
    * Params:
    *      - int x : data value
    * 
    * Returns:
    *      void
    */
   void Push(int x){
        node* n = new node(x);      // create a new node and
                                    // add data to it

        if(!head){                  // `!head` implies empty list
                                    // So does `head == NULL`

            head = n;               // `head = n` places addrress of
                                    // n in head (points head to n)

        }else{                      // list not empty
            n->next = head;         // point n's next to what head points to
            head = n;               // now point head to n
        }
   }

    /**
    * Public : Print
    * 
    * Description:
    *      Prints a linked list by traversing over it.
    * 
    * Params:
    *      void
    * 
    * Returns:
    *      void
    */
   void print(){
       node* temp = head;       // temp pointer copies head

       while(temp){             // this loops until temp is NULL
                                // same as `while(temp != NULL)`

           cout<<temp->d<<"->"; // print data from node
           temp = temp->next;   // move to next node
       }
   }

    ~LinkedList(){

    }

};

int main() {
    LinkedList L;       // create instance of list
    L.Push(8);          // add a bunch of numbers
    L.Push(12);
    L.Push(23);
    L.Push(42);
    L.print();          // print the list
}