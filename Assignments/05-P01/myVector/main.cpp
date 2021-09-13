/*****************************************************************************
*                    
*  Author:           Griffin
*  Title:            Singly linked list vector implementation
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        Uses a singly linked list as the backend for an STL like "vector" 
*        class definition.
*   
*  NO ERROR DETECTION USED. SO RETURNING 'TRUE' FOR A SUCCESFUL PUSH ONTO LIST
*  IS NOT FULLY ACCURATE AS WE ARE NOT INCLUDING ANY "TRY" "CATCH" BLOCKS TO CAPTURE
*  ERRORS CORRECTLY. WE WILL COVER THESE LATER.
* 
*  Usage:
*        Use it like a linked list now. More like a vector next program
* 
*  Files: TBD
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include "MyVector.hpp"

#define INF 1000000000  // infinity

using namespace std;


int main() {
    //MyVector V1;
    MyVector V2("input.dat");
    //cout << V2 << endl;
    V2.sortList();
    //cout << V2 << endl;

    // V1.pushFront(56);
    // V1.pushFront(42);
    // V1.pushFront(30);
    // V1.pushFront(48);
    // V1.pushAt(0, 1);
    // V1.pushAt(10, 10);
    // cout << V1 << endl;

    // V1.pushAt(2, 88);
    // cout << V1 << endl;

    // V2.pushRear(V1);
    // cout << V2 << endl;

    //V2.sortList();
    cout << V2 << endl;
}