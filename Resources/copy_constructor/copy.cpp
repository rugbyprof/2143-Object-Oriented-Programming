#include <iostream>
#include <string>

using namespace std;

int A[100];

struct Node {
    int x;
    Node* next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

class List {
private:
    Node* Head;
    Node* Tail;
    int Size;

public:
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }

    List(const List& copyMe)
    {
        Head = Tail = NULL;
        Size = 0;
        if(copyMe.Head){
            Node* Temp = copyMe.Head;

            while (Temp != NULL) {
                Insert(Temp->x);
                Temp = Temp->next;
            }
        }else{
            Head = Tail = NULL;
            Size = 0;
        }
    }

    void Push(int val)
    {
        // allocate new memory and init node
        Node* Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void Insert(int val)
    {
        // allocate new memory and init node
        Node* Temp = new Node(val);

        if (!Tail) {
            Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }

        if (!Head) {
            Head = Tail;
        }
        Size++;
    }

    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    string Print()
    {
        Node* Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    int Pop()
    {
        return 0; //?
    }

    friend ostream& operator<<(ostream& os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main()
{
    List L1;

    

    for (int i = 0; i < 12; i += 2) {
        L1.Insert(rand()%100);
    }

    // for (int i = 1; i < 12; i += 2) {
    //     L2.Insert(i);
    // }

    cout << L1 << endl;

List L2(L1);

    cout << L2 << endl;
    //cout << L2 << endl;
    //cout << L3 << endl;

        //List L2;

    return 0;
}