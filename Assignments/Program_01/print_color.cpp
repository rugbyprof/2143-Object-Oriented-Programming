#include "colors.h"
#include <iostream>

const char* block = "\u2588";
const char* check = "✅";  // club symbol
const char* ex    = "❌";  // joker card symbol

using namespace std;
int main() {
    cout << RED << "This text is red." << OFF << endl;
    cout << GREEN << "This text is green." << OFF << endl;
    cout << BLUE << "This text is blue." << OFF << endl;
    cout << YELLOW << "This text is yellow." << OFF << endl;
    cout << PURPLE << block << OFF << YELLOW << block << OFF << endl;
    cout << YELLOW << block << OFF << PURPLE << block << OFF << endl;
    cout << PURPLE << check << OFF << YELLOW << ex << OFF << endl;
    cout << YELLOW << ex << OFF << PURPLE << check << OFF << endl;
    return 0;
}