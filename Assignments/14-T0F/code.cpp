#include <iostream>

using namespace std;

class Vehicle { 
public: 
	Vehicle() { 
	    cout << "This is a Vehicle" << endl; 
	} 
}; 
class FourWheeler { 
public: 
	FourWheeler() { 
	    cout << "This is a 4 wheeler Vehicle" << endl; 
	} 
}; 
class Car: private Vehicle, private FourWheeler { 

}; 

// main function 
int main() 
{ 
	Car obj; 
	return 0; 
}