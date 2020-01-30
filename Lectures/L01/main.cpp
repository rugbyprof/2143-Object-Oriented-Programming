///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Terry Griffin
// Email:            terry.griffin@msutexas.edu
// Course:           CMPS 2143
// Semester:         Spring 2020
// Date:             Jan 28th 
//
// Description:
//       This is a review of 1063 code concepts. Basically creating a linked list
//       and adding the methods necessary to make it act somewhat like a vector.
//
// 
//       
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

/**
 * struct Node
 * 
 * Description:
 *      A doubly linked list node that holds integers
 * 
 * Public Methods:
 *      - Node()      default constructor
 *      - Node(int)   overloaded constructor
 *      
 */
struct Node{
  int data;
  Node* next;
  Node* prev;
  Node(){
    data = 0;
    next = prev = NULL;
  }
  Node(int d){
    data = d;
    next = prev = NULL;
  }
};

/**
 * Class MyVector
 * 
 * Description:
 *      A doubly linked list that acts like a vector
 * 
 * Public Methods:
 *    - MyVector()          default constructor
 *    - void pushBack(int)  add item to rear of vector
 *    - void pushFront(int) add item to front of vector
 *    - int popBack()       remove item from rear of vector
 *    - int popFront()      remove item from front of vector
 *    - void print()        print out data in vector
 *    - void sort()         sort vector in either direction
 *      
 */
class MyVector{
private:
  Node* Head;   // Pointer to front of list
  Node* Tail;   // Pointer to rear of list

public:
  /**
   * Public : MyVector
   * 
   * Description:
   *      Constructs class
   * 
   * Params:
   *    None
   * 
   * Returns:
   *    [void]
   */
  MyVector(){
    Head = Tail = NULL;
  }

  /**
   * Public : pushBack
   * 
   * Description:
   *    Add item to rear of list
   * 
   * Params:
   *    [int] data
   * 
   * Returns:
   *    [void]
   */
  void pushBack(int d){
    Node* temp = new Node(d); // allocate new memory

    // if list if empty 
    if(Head == NULL){
      Head = temp;
      Tail = temp;
    }else{
      Tail->next = temp;  // attach list to new node
      temp->prev = Tail;  // new node points to old rear
                 
      Tail = temp;        // point tail to new node
    }
  }

  /**
   * Public : pushFront
   * 
   * Description:
   *    Add item to front of list
   * 
   * Params:
   *    [int] data
   * 
   * Returns:
   *    [void]
   */
  void pushFront(int d){
    Node* temp = new Node(d); // allocate new memory

    // list is empty 
    if(Head == NULL){
      Head = temp;
      Tail = temp;
    }else{
      temp->next = Head;    // point new node to front
      Head->prev = temp;    // point old front to new node
      Head = temp;          // make new node the new head
    } 
  }

  /**
   * Public : popBack
   * 
   * Description:
   *    Remove item from rear of list
   * 
   * Params:
   *    None
   * 
   * Returns:
   *    [int]
   */
  int popBack(){
    // if Tail is not null (list not empty)
    if(Tail){
      int d = Tail->data;   // copy data from node
      Node* temp = Tail;    // temp pointer to tail so we can 
                            // delete it after we move the tail

      Tail = Tail->prev;    // move tail to previous node

      // This if statement makes sure that we didn't delete
      // the last node. If we did Tail would be NULL and 
      // setting Tail->next to anything would error
      if(Tail){
        Tail->next = NULL; // make tail next null
      }else{
        Head = NULL;       // list is empty so make head null as well
      }
      
      delete temp;        // Now we can actually delete temp

      return d;           // return the value from last node
    }
    
    return -1;            // sentinel value to return if list empty
  }

  /**
   * Public : popFront
   * 
   * Description:
   *    Remove item from front of list
   * 
   * Params:
   *    None
   * 
   * Returns:
   *    [int]
   */
  int popFront(){
    // if list is not empty
    if(Head){
      int d = Head->data;   // copy data from node
      Node* temp = Head;    // temp pointer to head so we can delete later
      Head = Head->next;    // adjust head my moving it to next node

      // if list is not empty
      if(Head){
        Head->prev = NULL;  // the new head used to point to old head
                            // so make it point to null
      }else{
        Tail = NULL;        // list is empty so make tail NULL like head
      }
      
      delete temp;          // now we can delete to node to give back memory

      return d;             // return nodes data
    }
    return -1;              // sentinel value for empty list
  }


  /**
   * Public : print
   * 
   * Description:
   *    Prints the list
   * 
   * Params:
   *    None
   * 
   * Returns:
   *    None
   */
  void print(){
    Node* temp = Head;    // point to front of list

    while(temp){          // while temp is not a null pointer
      cout<<temp->data;   // write out the data

      if(temp->next){     // if not at end of list
        cout<<"->";       // write a little arrow
      }

      temp = temp->next;  // move to next node
    }
    cout<<endl;          
  }

  /**
   * Public : Sort
   * 
   * Description:
   *    Sorts the list by swapping values not by manipulating pointers.
   *    At each pass one value will be placed into its proper location.
   *    `Current` holds that position while the `peek` goes and finds the value
   *    to be swapped with `Current`
   * 
   * 
   * Params:
   *    [bool] asc : true = ascending / false = descending
   * 
   * Returns:
   *    None
   */
  void Sort(bool asc=true){
    Node* Current = Head;         // start at head of list

    while(Current){               // while current is not null
      Node* minp = Current;       // min pointer initialized to current
      int   minv = Current->data; // min value initialized to currents value
      Node* peek = Current;       // pointer to walk down peeking at data 
                                  // to find minimum value

      bool doSwap=0;              // do not swap yet     

      // while peek is not at end of list
      while(peek){  
        // if asc is true test data is less than
        if(asc){
          doSwap = (peek->data < minv);
        }else{
          // otherwise test that peek data is greater than
          doSwap = (peek->data > minv);
        }
        
        // if doSwap is true
        if(doSwap){
          minp = peek;        // update min pointer to be where peek is
          minv = peek->data;  // grab a copy of the min value here
        }

        peek = peek->next;    // move peek down the list
      }

      // swap the minimum value found by peek
      // with value pointed to by current
      minp->data = Current->data;
      Current->data = minv;

      // Move Current down the list
      Current = Current->next;
    }

  }

};

/**
 * Main Driver
 * 
 * Simply used to test MyVector 
 */
int main() {
  MyVector V;

  for(int i=0;i<10;i++){
    V.pushFront(rand()%100);
  }

  V.print();

  int d = V.popBack();

  V.print();
  V.Sort(false);
  V.print();
    
}
