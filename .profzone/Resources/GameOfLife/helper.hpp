using namespace std;

// --------------------------------------------------------------
// Function: allocate()
// Purpose : Dynamically allocate a 2D array (height x width)
// Returns : Pointer to an array of int* (each row is a new[] allocation)
// --------------------------------------------------------------
int** allocate(int width, int height) {
    // Step 1: Allocate an array of int* (pointers to rows)
    // Each element of this array will later point to a row of ints.
    int** array = new int*[height];

    // Step 2: For each row, allocate a block of `width` integers.
    // This creates `height` separate rows in memory.
    for (int i = 0; i < height; i++) {
        array[i] = new int[width];
    }

    // Step 3: Return pointer to the first element (the row pointer array)
    // The caller will now have a "2D" array accessed as array[row][col].
    return array;
}