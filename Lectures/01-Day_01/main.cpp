#include <iostream>

using namespace std;

/**
 * @brief: array based implementation of a stack
 * 
 */
class Stack{
  int *stack;   // pointer to stack container
  int top;      // index to top of stack
public:
  /**
   * @brief Construct a new Stack object
   * 
   * @param int size : size of stack to be allocated
   */
  Stack(int size){
    stack = new int[size];
    top = -1;
  }

  /**
   * @brief: Push values onto the stack
   * 
   * @param int val : value pushed onto stack
   */
  void Push(int val){
    stack[++top] = val;
  }

  /**
   * @brief: Remove item from stack
   * 
   * @param None
   * @return : item popped from stack
   */
  int Pop(){
    return stack[top--];
  }

  /**
   * @brief print values to screen that reside in stack
   * 
   */
  void Print(){
    for(int i=top;i>=0;i--){
      cout<<stack[i]<<endl;
    }
  }
};

int main() {
  //////////////////////////////////////////////////////////////

  // traditional method of allocating an array
  int container[100];
  
  // putting a value in the array
  container[34] = 29348;

  // using a pointer to dynamically allocate an array
  int *othercont;
  
  // size of our array (could be any integer value)
  int size = 98;

  // dynamically allocating memory for our array using "size"
  othercont = new int[size];

  // use array just as before
  othercont[5] = 29348;

  //////////////////////////////////////////////////////////////

  // Declare instance of a stack
  Stack s(10);

  // Push values onto the stack
  s.Push(8);
  s.Push(5);
  s.Pop(); // remove top item from stack
  s.Push(3);
  s.Push(10);

  // Print stack to standard out (terminal screen)
  s.Print();

  //////////////////////////////////////////////////////////////

  // declare variable
  int x = 9;

  // write value to standard out (terminal screen)
  cout<<x<<endl;
  
  // post increment
  cout<<x++<<endl;
 
  // pre increment
  cout<<++x<<endl;
  
}