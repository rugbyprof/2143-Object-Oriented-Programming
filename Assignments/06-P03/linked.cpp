#include <iostream>

struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }

    void push(int data)
    {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }

    void printList()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

int main()
{
    LinkedList list;
    list.push(5);
    list.push(10);
    list.push(15);
    list.printList();
    return 0;
}
