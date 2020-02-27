///////////////////////////////////////////////////////////////////////////////
//
// Author:           Terry Griffin
// Email:            terry.griffin@msutexas.edu
// Title:            Abstraction, Operator Overloading, Deep vs Shallow Copy
// Course:           CMPS 2143
// Semester:         Spring 2020
//
// Description:
//       This program has a few examples of abstraction, operator overloading and
//       shows the difference between deep and shallow copies
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

using namespace std;

/*
 
  █████╗ ██████╗ ███████╗████████╗██████╗  █████╗  ██████╗████████╗██╗ ██████╗ ███╗   ██╗     █████╗ ███╗   ██╗██████╗     
 ██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║    ██╔══██╗████╗  ██║██╔══██╗    
 ███████║██████╔╝███████╗   ██║   ██████╔╝███████║██║        ██║   ██║██║   ██║██╔██╗ ██║    ███████║██╔██╗ ██║██║  ██║    
 ██╔══██║██╔══██╗╚════██║   ██║   ██╔══██╗██╔══██║██║        ██║   ██║██║   ██║██║╚██╗██║    ██╔══██║██║╚██╗██║██║  ██║    
 ██║  ██║██████╔╝███████║   ██║   ██║  ██║██║  ██║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║    ██║  ██║██║ ╚████║██████╔╝    
 ╚═╝  ╚═╝╚═════╝ ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝    ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝     
                                                                                                                           
 ██████╗ ███████╗███████╗██████╗     ██╗   ██╗███████╗    ███████╗██╗  ██╗ █████╗ ██╗     ██╗      ██████╗ ██╗    ██╗      
 ██╔══██╗██╔════╝██╔════╝██╔══██╗    ██║   ██║██╔════╝    ██╔════╝██║  ██║██╔══██╗██║     ██║     ██╔═══██╗██║    ██║      
 ██║  ██║█████╗  █████╗  ██████╔╝    ██║   ██║███████╗    ███████╗███████║███████║██║     ██║     ██║   ██║██║ █╗ ██║      
 ██║  ██║██╔══╝  ██╔══╝  ██╔═══╝     ╚██╗ ██╔╝╚════██║    ╚════██║██╔══██║██╔══██║██║     ██║     ██║   ██║██║███╗██║      
 ██████╔╝███████╗███████╗██║          ╚████╔╝ ███████║    ███████║██║  ██║██║  ██║███████╗███████╗╚██████╔╝╚███╔███╔╝      
 ╚═════╝ ╚══════╝╚══════╝╚═╝           ╚═══╝  ╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝  ╚══╝╚══╝       
                                                                                                                           
 
*/

/**
 * The following class has an example of a copy contructor which allows us to  
 * do a deep copy of the data from one "container" to the other. The data members
 * like a,b,c,id are no problem. But when you have heap allocated memory (like the
 * new operator) it matters.
 * 
 * It also gives an example of "abstraction" by using two different container types
 * Array and Vector. Would we ever use them at the same time? NO! But whoever uses
 * the class only knows that PUSH and POP put values on, and take them off. They
 * have no clue what container we are using: Abstraction (also implementation hiding).
 */
class ClassA {
private:
    // high level vars to show copy constructor will handle nicely
    int a;     // some val
    int b;     // some val
    int c;     // some val
    string id; // unique id for class (used for printing)
    int size;

    // The following code has two "containers" one is
    // an Array and the other is a Vector. They are both
    // somewhat "interchangeable", meaning the user does
    // not know or care how thier integers are stored, as
    // long as they have access to them (abstraction).

    int *abstract_array;         // integer array version
    vector<int> abstract_vector; // vector version
    int index;                   // location to push next value

public:
    /**
     * Default constructor
     * 
     * Param: 
     *      string id : used to identify class (for debugging)
     */
    ClassA(string _id = "", int _size = 10) {
        srand(345);
        a = rand() % 1000;
        b = rand() % 1000;
        c = rand() % 1000;
        id = _id;
        size = _size;

        // Two containers. User doesn't know which one we are using
        // but, push and pop will still work the same!

        // Container type 1: Array
        abstract_array = new int[size];
        for (int i = 0; i < size; i++) {
            abstract_array[i] = 0;
        }

        // Container type 2: Vector
        for (int i = 0; i < size; i++) {
            abstract_vector.push_back(0);
        }

        index = 0;
    }

    /**
     * Copy Constructor:
     *      This makes sure that our "containers" get copied over in a deep
     *      way. For the array, we allocate new memory. For the vector we 
     *      just push the values on.
     */
    ClassA(ClassA &rhs) {
        cout << "copy construct" << endl;
        a = rhs.a;
        b = rhs.b;
        c = rhs.c;
        id = rhs.id;
        size = rhs.size;

        // Two containers. User doesn't know which one we are using
        // but, push and pop will still work the same!

        // Container type 1: Array
        abstract_array = new int[size];
        for (int i = 0; i < size; i++) {
            abstract_array[i] = rhs.abstract_array[i];
        }

        // Container type 2: Vector
        for (int i = 0; i < size; i++) {
            abstract_vector.push_back(rhs.abstract_vector[i]);
        }

        index = 0;
    }

    /**
     * Overloaded assignment (=) operator
     * 
     */
    ClassA &operator=(const ClassA &rhs) {
        cout << "in assignment operator" << endl;
        this->a = rhs.a;
        this->b = rhs.b;
        this->c = rhs.c;
        this->size = rhs.size;
        this->index = rhs.index;

        // Container type 1: Array
        // Copy values over.
        for (int i = 0; i < this->size; i++) {
            abstract_array[i] = rhs.abstract_array[i];
        }

        // Container type 2: Vector
        // Copy values over
        this->abstract_vector = rhs.abstract_vector;

        return *this;
    }

    /**
     * Overloaded ostream (<<)
     * 
     */
    friend ostream &operator<<(ostream &os, const ClassA &rhs) {
        string stuff = "\nID: " + rhs.id + " ";
        stuff += "A: " + to_string(rhs.a) + " B: " + to_string(rhs.b) + " C: " + to_string(rhs.c) + "\n";
        stuff += "Container: ";
        for (int i = 0; i < rhs.size; i++) {
            if (rand() % 2 == 0) {
                stuff += to_string(rhs.abstract_array[i]);
            } else {
                stuff += to_string(rhs.abstract_vector[i]);
            }
            if (i < rhs.size - 1) {
                stuff += ",";
            }
        }
        return os << stuff << endl;
    }

    /**
     * updateRandIndex - 
     *      Updates a random location in our container.
     *      Why? who cares were just using this as an
     *      abstraction example.
     */
    void updateRandIndex(int x) {
        int i = rand() % 10;
        abstract_array[i] = x;  // array
        abstract_vector[i] = x; // vector
    }

    /**
     * setID - 
     *      Sets the ID of this instance of the class.
     *      We use it to show whos getting printed for
     *      learning purposes.
     */
    void setID(string id) {
        this->id = id;
    }

    /**
     * push - 
     *      Push value onto our container.
     *      This is the ABSTRACTION we talked about. 
     *      The user doesn't know which container we are using (Array or Vector).
     *      They only know how to PUSH onto the abstract container.
     */
    void push(int x) {
        if (full()) {
            return;
        }
        abstract_array[index] = x;  // array
        abstract_vector[index] = x; // vector
        ++index;
    }

    /**
     * pop - 
     *      Pop value from our container.
     *      This is again ... the ABSTRACTION we talked about. 
     *      The user doesn't know which container we are using (Array or Vector).
     *      They only know how to POP from the abstract container.
     */
    int pop() {
        --index;

        if (!empty()) {
            if (rand() % 2 == 0) {
                return abstract_array[index]; // array
            } else {
                return abstract_vector[index]; // vector
            }
        }
        return -9999999; // sentinal value
    }

    bool full() { return index == size; }

    bool empty() { return index == 0; }
};

/*
 
  ██████╗ ██████╗ ███████╗██████╗  █████╗ ████████╗ ██████╗ ██████╗                       
 ██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗                      
 ██║   ██║██████╔╝█████╗  ██████╔╝███████║   ██║   ██║   ██║██████╔╝                      
 ██║   ██║██╔═══╝ ██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗                      
 ╚██████╔╝██║     ███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║                      
  ╚═════╝ ╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝                      
                                                                                          
  ██████╗ ██╗   ██╗███████╗██████╗ ██╗      ██████╗  █████╗ ██████╗ ██╗███╗   ██╗ ██████╗ 
 ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║     ██╔═══██╗██╔══██╗██╔══██╗██║████╗  ██║██╔════╝ 
 ██║   ██║██║   ██║█████╗  ██████╔╝██║     ██║   ██║███████║██║  ██║██║██╔██╗ ██║██║  ███╗
 ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗██║     ██║   ██║██╔══██║██║  ██║██║██║╚██╗██║██║   ██║
 ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║███████╗╚██████╔╝██║  ██║██████╔╝██║██║ ╚████║╚██████╔╝
  ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝                                                                                    
 
*/
class MyClass {
private:
    string id; // unique class id (for example purposes)
    int a;     // value to help show change using overloaded assignment operators
    int b;     // same
    int c;     // same

public:
    /**
     * Default Constructor
     * 
     * Params:
     *      void
     */
    MyClass() {
        id = "";
        a = b = c = 0;
    }

    /**
     * Overloaded Constructor
     * 
     * Params:
     *      string  id  : name of instance (for display purposes)
     *      int     a   : so we have an val to overload operators with
     *      int     b   : same
     *      int     c   : same
     */
    MyClass(string id, int a, int b, int c) : id{id}, a{a}, b{b}, c{c} {}

    /**
     * Public Methods
     */
    friend ostream &operator<<(ostream &, const MyClass &);
    MyClass &operator=(const MyClass &);
    const MyClass operator+(const MyClass &) const;
    MyClass &operator+=(const MyClass &);
    bool operator==(const MyClass &) const;
};

/**
 * params:
 *      const MyClass &rhs : An instance of a `MyClass` passed in by reference
 * returns:
 *      a reference to "this" (current instance of the object MyClass)
 */
MyClass &MyClass::operator=(const MyClass &rhs) {
    if (this == &rhs) { // Same object?
        cout << "oops: self assignment ..." << endl;
        return *this;
    }
    this->id = rhs.id;
    this->a = rhs.a;
    this->b = rhs.b;
    this->c = rhs.c;

    return *this;
}

/**
 * params:
 *      ostream &os         :   ostream to write to
 *      const MyClass &rhs  :   instance of class to write
 *      
 * returns:
 *      an instance of ostream (print to standard out)
 */
ostream &operator<<(ostream &os, const MyClass &rhs) {
    return os << rhs.id << ": " << rhs.a << "," << rhs.b << "," << rhs.c << "\n";
}

/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to compare with
 *      
 * returns:
 *      bool (equal : true / notequal : false)
 */
bool MyClass::operator==(const MyClass &rhs) const {
    return (this->id == rhs.id) && (this->a == rhs.a) && (this->b == rhs.b) && (this->c == rhs.c);
}

/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to compare with
 *      
 * returns:
 *      dereferenced instance of "this" (current instance representation)
 */
MyClass &MyClass::operator+=(const MyClass &rhs) {
    this->id += rhs.id; // add rhs elements to local elements
    this->a += rhs.a;   // for each data member
    this->b += rhs.b;
    this->c += rhs.c;
    return *this;
}
/**
 * params:
 *      const MyClass &rhs  : instance of MyClass to add to
 *      
 * returns:
 *      A new instance of "MyClass" with new results in it. 
 */
const MyClass MyClass::operator+(const MyClass &rhs) const {
    MyClass result = *this; // Make a copy of myself.  Same as MyClass result(\*this);
    result += rhs;          // Use += to add other to the copy.
    return result;          // All done!
}

/*
 ███╗   ███╗ █████╗ ██╗███╗   ██╗
 ████╗ ████║██╔══██╗██║████╗  ██║
 ██╔████╔██║███████║██║██╔██╗ ██║
 ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
 ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
 ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝
*/
int main() {

    cout << "Operator Overloading ######################################################################\n";
    MyClass A("A", 1, 2, 3); // make an instance of the class
    MyClass B("B", 4, 5, 6); // same
    MyClass C = A + B;       // make a new instance using A+B as the content

    cout << C << endl;       // write out instance "C" to stdout
    cout << (C + B) << endl; // write out C + B (see what prints out)
    A += C;                  // add C to A and save answer in A
    cout << A << endl;       // write out A to stdout

    B = B; // try to "self assign"

    cout << B << endl; // see what B has now

    cout << "Deep Copy / Abstraction ######################################################################\n";
    cout << "Init D\n";
    ClassA D("D");
    while(!D.full()){
        D.push(rand()%100);
    }
    cout << "Init E = D\n";
    ClassA E = D;
    E.setID("E");
    
    // Should have same data
    cout << D << endl;
    cout << E << endl;

    // Change E:
    while(!E.empty()){
        E.pop();
    }
    while(!E.full()){
        E.push(rand()%100);
    }

    // Should have different data
    cout << D << endl;
    cout << E << endl;
    return 0;
}