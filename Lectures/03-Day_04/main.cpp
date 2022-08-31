#include <iostream>

using namespace std;

/**
 *
 *__   _____ ___ _____ ___  ___    ___ _      _   ___ ___
 *\ \ / / __/ __|_   _/ _ \| _ \  / __| |    /_\ / __/ __|
 * \ V /| _| (__  | || (_) |   / | (__| |__ / _ \\__ \__ \
 *  \_/ |___\___| |_| \___/|_|_\  \___|____/_/ \_\___/___/
 *
 * @methods:
 *     // I would normally give brief descript of each method, but I'm not going to now.
 *     Vector()
 *     Vector()
 *     Push(int)
 *     Pop()
 *     Print()
 *     PushAt()
 */
class Vector {
private:
    int *array;     // container for vector class
    int  index;     // current location of back of vector
    int  size;      // size of container
    bool Full();    // is container full?
    bool Empty();   // is container empty?
    void Resize();  // resize container

public:
    Vector();     // default constructor
    Vector(int);  // overloaded constructor

    void Push(int);
    int  Pop();
    void Print();
    void PushAt(int, int);

    // make friends with ostream so it can access private members of this class when printing
    friend ostream &operator<<(ostream &, const Vector &);
};

/*
    ___ ___  _  _ ___ _____ ___ _   _  ___ _____ ___  ___  ___
   / __/ _ \| \| / __|_   _| _ \ | | |/ __|_   _/ _ \| _ \/ __|
  | (_| (_) | .` \__ \ | | |   / |_| | (__  | || (_) |   /\__ \
   \___\___/|_|\_|___/ |_| |_|_\\___/ \___| |_| \___/|_|_\|___/
   =============================================================
*/

/**
 * Default constructor sets size to 10
 */
Vector::Vector() {
    index = 0;
    size = 10;
    array = new int[size];
}

/**
 * Overloaded constructor sets size to whatever `s` is.
 * @params:
 *     int s : size of container for our vector
 */
Vector::Vector(int s) {
    index = 0;
    size = s;
    array = new int[size];
}

/*
    _____   _____ ___ _    ___   _   ___  ___ ___     ___  ___ ___ ___    _ _____ ___  ___  ___
   / _ \ \ / / __| _ \ |  / _ \ /_\ |   \| __|   \   / _ \| _ \ __| _ \  /_\_   _/ _ \| _ \/ __|
  | (_) \ V /| _||   / |_| (_) / _ \| |) | _|| |) | | (_) |  _/ _||   / / _ \| || (_) |   /\__ \
   \___/ \_/ |___|_|_\____\___/_/ \_\___/|___|___/   \___/|_| |___|_|_\/_/ \_\_| \___/|_|_\|___/
   ==============================================================================================
*/
/**
 * Overload ostream to print a vector to std out.
 * @params:
 *      ostream : copy of ostream (cout) so we can print to stdout
 *      Vector : the vector to be printed
 * @returns:
 *      ostream& : the copy of ostream (cout) we printed to
 */
ostream &operator<<(ostream &os, const Vector &v) {
    // loop over container
    for (int i = 0; i < v.index; i++) {
        // send each value to std out
        os << v.array[i] << " ";
    }
    // return ostream so it can be "printed"
    return os;
}

/*
   __  __ ___ _____ _  _  ___  ___  ___
  |  \/  | __|_   _| || |/ _ \|   \/ __|
  | |\/| | _|  | | | __ | (_) | |) \__ \
  |_|  |_|___| |_| |_||_|\___/|___/|___/
  ======================================
*/

/**
 * Is our array full?
 * @params:
 *      none
 * @returns:
 *      bool : full = true
 */
bool Vector::Full() { return index == (size - 1); }

/**
 * Add item to our vector.
 * @params:
 *     int item : item to be added
 * @returns:
 *     none
 */
void Vector::Push(int item) {
    // if container is full, make it bigger!
    if (Full()) {
        Resize();
    }

    // now guaranteed to have room to add an item to the container
    array[index] = item;
    index++;
}

/**
 * Print our container for debugging purposes
 * @params:
 *     none
 * @returns:
 *     none
 */
void Vector::Print() {
    for (int i = 0; i < index; i++) {
        cout << array[i] << " ";
    }
}

/**
 * Resize the container when it gets full
 * @params:
 *      none
 * @returns:
 *      none
 */
void Vector::Resize() {
    int *tempArray = new int[size * 2];  // double the size of previous container
    for (int i = 0; i < index; i++) {    // loop over current values
        tempArray[i] = array[i];         // copy to new (bigger) container
    }
    delete[] array;     // delete old container
    array = tempArray;  // point to new container so we can access it
}

/**
 * Main function. Look how small and readable it is! BS code should never be in main. Always
 * try and create classes or functions to do things. Makes programs more readable.
 */
int main() {
    Vector V1;
    V1.Push(8);
    V1.Push(6);
    cout << V1 << endl;
}