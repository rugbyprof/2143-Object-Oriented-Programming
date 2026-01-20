/*****************************************************************************
 *
 *  Author:           2143 Class
 *  Email:            none
 *  Label:            Lecture 01
 *  Title:            Array Based Stack
 *  Course:           2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        Array based implementation of a stack data structure written in class
 *        by all of us.
 *
 *  Usage:
 *        None (ask me in class)
 *
 *  Files:
 *        main.cpp
 *****************************************************************************/

#include <iostream>

using namespace std;

class Stack
{
  int *array;
  int size;
  int top;
  bool empty() { return top == -1; }

  bool full() { return top == size - 1; }

public:
  Stack()
  {
    top = -1;
    size = 10;
    array = new int[size];
  }

  Stack(int _size)
  {
    top = -1;
    size = _size;
    array = new int[size];
  }

  void Push(int x)
  {
    if (!full())
    {
      top++;
      array[top] = x;
    }
    else
    {
      cout << "Stack Full!" << endl;
    }
  }

  int Pop()
  {
    if (!empty())
    {
      int temp = array[top];
      top--;
      cout << "top:" << top << endl;
      return temp;
    }
    else
    {
      cout << "Stack Empty!" << endl;
    }
    return 0;
  }

  void Print()
  {
    for (int i = 0; i <= top; i++)
    {
      cout << array[i] << " ";
    }
  }
};

int main()
{
  srand(time(0));
  Stack S(10);
  int x;

  S.Push(99);

  for (int i = 0; i < 19; i++)
  {
    S.Push(rand() % 100);
  }

  S.Print();
  cout << endl;

  x = S.Pop();

  S.Print();
  cout << endl;

  for (int i = 0; i < 190; i++)
  {
    S.Pop();
  }
}