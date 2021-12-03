#include <iostream>

using namespace std;

class base { 
public: 
	void fun_1() { cout << "base-1\n"; } 
	virtual void fun_2() { cout << "base-2\n"; } 
	virtual void fun_3() { cout << "base-3\n"; } 
	virtual void fun_4() { cout << "base-4\n"; } 
}; 

class derived : public base { 
public: 
	void fun_1() { cout << "derived-1\n"; } 
	void fun_2() { cout << "derived-2\n"; } 
	void fun_4(int x) { cout << "derived-4\n"; } 
}; 

int main() { 
    base *p; 
    derived obj1; 
    p = &obj1; 

    p->fun_1();  
    p->fun_2();
    p->fun_3();  
    p->fun_4(); 
    //p->fun_4(5); 

    // Are the three lines below valid? State why or why not.
    // derived *p1;
    // base p2;
    // p1 = &p2;
}