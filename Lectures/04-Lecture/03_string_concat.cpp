#include <iostream>
#include <string>

using namespace std;


/**
 * @description: Strings are already overloaded for the "addition" (+) operator. 
 *               They use it for concatentation. 
 * 
 */
int main() {

    string S1 = "So you ";
    string S2 = "think you're smart.";
    string S3 = " You're not...";

    S1 = S1 + S2 + S3;

    cout<<S1<<endl;


}