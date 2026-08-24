/*****************************************************************************
 *
 *  Author:           2143 Class
 *  Email:            none
 *  Label:            Lecture 02
 *  Title:            List Based Queue
 *  Course:           2143
 *  Semester:         Spring 2023
 *
 *  Description:
 *        List based implementation of a queue data structure written in class
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

struct Point
{
    int x;
    int y;
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

struct Node
{
    int data;
    Node *next;
    Node(int x)
    {
        data = x;
        next = nullptr;
    }
};

class Queue
{
    Node *front;
    Node *rear;

public:
    Queue() { front = rear = nullptr; }

    Queue(const Queue &other)
    {
        front = rear = nullptr;
        Node *Travel = other.front;

        while (Travel != nullptr)
        {
            this->Push(Travel->data);
            Travel = Travel->next;
        }
    }

    void Push(int x)
    {
        Node *temp = new Node(x);

        if (front == nullptr)
        {
            front = rear = temp;
        }
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }

    int Pop()
    {
        int temp = front->data;
        Node *deleteme = front;
        front = front->next;
        delete deleteme;

        return temp;
    }

    void Print()
    {
        Node *travel = front;
        while (travel != nullptr)
        {
            cout << "[" << travel->data << "]";
            if (travel->next)
            {
                cout << "->";
            }
            travel = travel->next;
        }
    }

    void destroy()
    {
        Node *prev = front;
        Node *curr = front;

        while (curr)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
        front = rear = nullptr;
    }

    friend ostream &operator<<(ostream &os, const Queue &q)
    {
        Node *travel = q.front;
        while (travel != nullptr)
        {
            os << "[" << travel->data << "]";
            if (travel->next)
            {
                os << "->";
            }
            travel = travel->next;
        }
        return os;
    }

    Queue &operator+(int x)
    {
        Push(x);
        return *this;
    }

    Queue &operator=(const Queue &rhs)
    {
        // check for self assignment
        if (this == &rhs)
        {
            return *this;
        }

        // if queue has items in it destroy the queue
        if (front)
        {
            this->destroy();
        }

        // get reference to beginning of incoming queue values
        Node *travel = rhs.front;

        // traverse the linked list
        while (travel)
        {
            this->Push(travel->data);
            travel = travel->next;
        }

        // return a copy of our new queue
        return *this;
    }
};

int main()
{
    Queue Q, Q2;

    for (int i = 0; i < 10; i++)
    {
        Q.Push(rand() % 100);
    }

    cout << "Q: " << Q << endl;
    // cout << "Q2: " << Q2 << endl;

    Queue Q3 = Q;

    Q3.Push(77);

    cout << "Q: " << Q << endl;
    cout << "Q3: " << Q3 << endl;

    //   Q.Pop();
    //   Q.Pop();
    //   Q.Pop();
    //   Q.Pop();
    //   Q.Pop();

    //   Q2 = Q;

    //   Q2.Push(77);

    //   cout << "Q: " << Q << endl;
    //   cout << "Q2: " << Q2 << endl;

    //   Queue Q3 = Q;

    //   for (int i = 0; i < 10; i++) {
    //     Q3.Push(rand() % 100);
    //   }
    //   cout<<endl;
    //   cout << "Q: " << Q << endl;
    //   cout << "Q2: " << Q2 << endl;
    //   cout << "Q3: " << Q3 << endl;

    //   Queue Q4(Q3);

    //   cout << "Q4: " << Q4 << endl;

    //   Queue Q5 = Q;

    //   cout << "Q5: " << Q5 << endl;
}