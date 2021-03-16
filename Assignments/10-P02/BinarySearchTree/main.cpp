/**
 * Binary Search Tree Example
 * Date: 28 January 2021
 * 
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Bst.hpp"  // Bring in our BST

using namespace std;

/**
 * @brief  Shuffles an array to randomize it.
 *  
 * @param  *A: 
 * @param  size: 
 * @param  shuffles: 
 * @retval None
 */
void Shuffle(string *A, int size, int shuffles = 1) {
    string temp;
    int    i, j;
    for (int s = 0; s < shuffles; s++) {
        for (int k = 0; k < size; k++) {
            i = rand() % size;
            j = rand() % size;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
}
int myrandom(int i) { return std::rand() % i; }

int main() {
    Bst< int > Tree;

    std::vector< int > myvector;

    // set some values:
    for (int i = 0; i <= 1000; i += 10) {
        if (i == 500) {
            continue;
        }
        myvector.push_back(i);
    }

    //using built-in random generator:
    std::random_shuffle(myvector.begin(), myvector.end());

    Tree.Insert(500);

    for (int i = 0; i < myvector.size(); i++) {
        Tree.Insert(myvector[i]);
    }

    Tree.Print();

    int f = 610;
    if (Tree.Find(f)) {
        cout << "Found: " << f << endl;
    }

    cout << endl;
}