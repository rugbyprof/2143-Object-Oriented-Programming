#include "mygetch.hpp"
#include <iostream>

using namespace std;

int main() {
    char k;             // holder for character being typed
    string word = "";   // var to concatenate letters to

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        word += k;          // append char to word

        if((int)k != 10){   // if k is not a space print it
            cout << "Key: " << k << " = " << (int)k << endl;
            cout << "Word: " << word << endl;
        }

        // hitting enter sets word back to empty
        if((int)k == 10 ){
            word = "";
        }
    }
    return 0;
}