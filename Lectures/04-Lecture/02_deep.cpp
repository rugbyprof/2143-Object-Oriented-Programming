#include <iostream>
#include <string>

using namespace std;

class Nums {
private:
    int *A;
    int size;

public:
    // Default Constructor
    Nums() {
        size = 10;
        A = new int[size];
        for (int i = 0; i < size; i++) {
            A[i] = rand() % 100;
        }
    }

    // Parameterized Constructor
    Nums(int s) {
        size = s;
        A = new int[size];
        for (int i = 0; i < size; i++) {
            A[i] = rand() % 100;
        }
    }

    // Parameterized Constructor that takes another array!
    Nums(int *Other,int s) {
        size = s;
        A = new int[size];
        for (int i = 0; i < size; i++) {
            A[i] = Other[i];
        }
    }

    /**
     * Copy constructor
     * 
     * We have to copy values over explicitly when dealing with pointers
     * otherwise, the "pointers" end up pointing at the same memory locations,
     * and when we make changes, it effects BOTH copies!
     * 
     * Shallow copy 
     * Obj1.A => [5][6][7][8][9][4]
     *          ^
     *        /
     * Obj2.A 
     * 
     * Deep copy
     * Obj1.A => [5][6][7][8][9][4]
     *     
     *   
     * 0bj2.A => [5][6][7][8][9][4]
     * 
     */
    Nums(const Nums &other) {
        size = other.size;
        A = new int[size];
        for (int i = 0; i < size; i++) {
            A[i] = other.A[i];
        }
    }

    /**
     * SetVal - Sets a value in array  
     * 
     * Params:
     *      int i - where to set value
     *      int v - what value is
     * 
     * Returns:
     *      none (or void)
     */
    void SetVal(int i, int v) {
        A[i] = v;
    }

    void Print() {
        for (int i = 0; i < size; i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
     * @description: Overloaded assignment operator (=) 
     * 
     * I had trouble with this in class because I was trying not to edit the values in "this" instance.
     * I was trying to create an entirely new instance to be returned. It makes total sense now that 
     * my memory has been refreshed, but it has to do with "chaining" (stringing together) multiple 
     * operations. 
     * 
     * NOTE!! There is a BIG problem with the code below if the arrays are not the same size!!
     * How would you fix it??
     */

    Nums &operator=(const Nums &other) {
        this->size = other.size;                // make my size same as "others"
        for (int i = 0; i < this->size; i++) {  // loop through and 
            this->A[i] = other.A[i];            // copy other values to me
        }
        return *this;                           // return copy of me
    }

    /**
     * @description: Overloaded addition operator (+)  
     * 
     */
    Nums operator+(const Nums &other) {
        int newsize = this->size + other.size;              // new size is both sizes added together
        Nums N(newsize);                                    // create new instance with new size
        for (int i = 0; i < this->size; i++) {              // copy first set of values
            N.A[i] = this->A[i];
        }
        for (int i=0,j = this->size; j < newsize; i++,j++) {// copy second set of values
            N.A[j] = other.A[i];
        }
        return N;                                           // return new copy 
    }
};

int main() {

    int A[] = {1,2,3,4,5};          // for use in a bit ()
    int B[] = {6,7,8,9,10,11,12};   // for use in a bit
    Nums N1(5);                     // init with random nums
    Nums N2(A,5);
    Nums N3(B,7);
    Nums N4 = N1;
    Nums N5 = N1 + N2 + N3 + N4;

    N1.Print();
    N2.Print();
    N3.Print();
    N4.Print();
    N5.Print();

    N3 = N2 + N3;

    cout << endl;

    N3.Print();



}