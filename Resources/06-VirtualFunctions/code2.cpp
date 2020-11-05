#include <iostream> 
using namespace std; 
  
class A 
{ 
public: 
    virtual void fun(); 
}; 
  
class B 
{ 
public: 
   void fun(); 
}; 
  
int main() 
{ 
    int a = sizeof(A), b = sizeof(B); 
    if (a == b) cout << "a == b"; 
    else if (a > b) cout << "a > b"; 
    else cout << "a < b"; 
    return 0; 
} 