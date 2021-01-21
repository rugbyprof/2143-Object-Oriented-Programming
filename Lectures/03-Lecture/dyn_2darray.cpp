#include <iostream>

// These constants were used at first to
// determine the size of our dynamic 2D array
#define ROWS 10
#define COLS 10

using namespace std;

/**
 * Main Driver
 * 
 * Params:
 *      int argc    - number of params on command line (including program name)
 *      char** argv - cstring array of actual params
 */
int main(int argc,char** argv) {

    cout<<"There are "<<argc<<" arguments..."<<endl;

    for(int i=0;i<argc;i++){
        cout<<"    Argument "<<i<<": "<<argv[i]<<endl;
    }
    
    // Program name is first param in argv, so we need at least
    // 3 to assume two more were passed in for row and
    // column sizes.
    if(argc < 3){
        cout<<"Error: need rows and columns!"<<endl;
        exit(1);
    }
    
    // convert params to integer 
    int r = atoi(argv[1]);
    int c = atoi(argv[2]);

    // We need a pointer to a pointer to dynamically
    // allocate a 2d array
    int **array;

    // Dynamically allocate the number of rows 
    // needed that hold pointers to the cols 
    array = new int*[r];

    // Assume r = 10 and c = 5
    // After previous line, we have the following
    //
    // [0]=> (points to nothing)
    // [1]=>
    // [2]=>
    // [3]=>
    // [4]=>
    // ...
    // [9]=>

    for(int i=0;i<r;i++){
        array[i] = new int[c];
    }

    // After for loop, we have the following
    //       [0][1][2][3][4]
    // [0]=> [ ][ ][ ][ ][ ]    (each row pointing to another array of size cols)
    // [1]=> [ ][ ][ ][ ][ ]
    // [2]=> [ ][ ][ ][ ][ ]
    // [3]=> [ ][ ][ ][ ][ ]
    // [4]=> [ ][ ][ ][ ][ ]
    // ...      ...
    // [9]=> [ ][ ][ ][ ][ ]

    // We can treat `array` as if it were a normal 2D
    // array.

    array[3][4] = 8;
    array[4][2] = 9;
    array[9][0] = 5;

    //       [0][1][2][3][4]
    // [0]=> [ ][ ][ ][ ][ ]
    // [1]=> [ ][ ][ ][ ][ ]
    // [2]=> [ ][ ][ ][ ][ ]
    // [3]=> [ ][ ][ ][ ][8]
    // [4]=> [ ][ ][9][ ][ ]
    // ...      ...
    // [9]=> [5][ ][ ][ ][ ]
    
    return 0;
}