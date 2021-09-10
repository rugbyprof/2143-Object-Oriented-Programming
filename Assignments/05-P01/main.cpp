
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class MyVector {
private:
    Node*           head;  // base pointer of list
    Node*           tail;
    int             size;
    static ofstream fout;
    string          fileName;

public:
    MyVector() {
        init();
    }

    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    MyVector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

    MyVector(const MyVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
    }

    void setFileName(string fname) {
        fileName = fname;
    }

    void print(bool printFile = 0) {
        if (printFile) {
            if (!fout.is_open()) {
                fout.open(fileName, std::ofstream::out | std::ofstream::trunc);
            }
        }

        bool flag = (printFile && fout.is_open());

        cout << "[";
        if (flag) {
            fout << "[";
        }

        Node* temp = head;

        while (temp) {
            cout << temp->data;

            if (flag) {
                fout << temp->data;
                ;
            }

            if (temp->next) {
                cout << ",";
                if (flag) {
                    fout << ",";
                }
            }

            temp = temp->next;
        }
        cout << "]";
        if (flag) {
            fout << "]";
        }
        cout << endl;
        if (flag) {
            fout << endl;
        }
        
    }

    /**
     * @brief Add value to front of list.
     * 
     * @param x 
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr;

        // otherwise adjust head pointer
        } else {
            tempPtr->next = head;
            head = tempPtr;
        }
        size++;
    }

    /**
     * @brief This method loads values from 'other' list in 'this' list.
     *          It loads an array first so we can process the values in
     *          reverse so they end up on 'this' list in the proper order.
     *          If we didn't use the array, we would reverse the values
     *          from the 'other' list.
     * 
     * @depends - Uses `pushFront(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushFront(const MyVector& other) {
        Node* otherPtr = other.head;         // get copy of other lists head
        int*  tempData = new int[other.size];// allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i;
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]);
        }
    }

    /**
     * @brief -  Add 'other' list's values to end of 'this' list.
     * @depends - Uses `pushRear(int)`
     * @param MyVector& other 
     * @return None
     */
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;         // get copy of other lists head

        while (otherPtr) {      // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     * @brief - Add value to rear of list
     * 
     * @param x 
     * @return None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        } else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << "->";
            }
            temp = temp->next;  // move to next Node
        }
        os << endl;
        return os;
    }

    ~MyVector() {
    }
};

ofstream MyVector::fout;

int main() {
    MyVector V1("input1.dat");
    V1.setFileName("googly1.out");

    MyVector V2("input2.dat");
    V2.setFileName("googly2.out");
    //MyVector V2(V1);
    MyVector V3("input2.dat");
    V3.setFileName("googly3.out");

    V2.pushFront(100);
    V2.pushFront(200);
    V2.pushFront(300);
    V2.pushFront(400);

    V2.pushFront(V1);

    cout << V1 << endl;
    cout << V2 << endl;
    cout << V3 << endl;  

    V1.print(true);
    V2.print(true);
    V3.print(true);
}