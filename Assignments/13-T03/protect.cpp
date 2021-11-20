// C++ program to demonstrate function overriding

#include <iostream>
using namespace std;

struct Account1 {
    double balance;

    // local implementation simply reduces the balance
    // and returns a bool for success
    bool withDraw (double amnt){
        if (balance - amnt > 0){
            balance -= amnt;
            return true;
        }
        return false;
    }

    Account1():balance{static_cast<double>(rand()%10000)}{}
    Account1(double b):balance{b}{}
};

// Even using "composition" this is not secure.
class BankClient1{
    Account1 *account;

    // ...
public:
    bool useATM(double amnt){
        // add to our balance!! Since we have access.
        account->balance += amnt;
        if(account->withDraw(amnt)){
            return true;
        }
        return false;
    }

    void showBalance(){
        cout<<"Balance: "<<account->balance<<endl;
    }

    BankClient1(){
        account = new Account1();
    }
    BankClient1(int x){
        account = new Account1(x);
    }
};

// SECURE ENCAPSULATION EXAMPLE
class Account2 {
// When balance private! Even derived classes cannot
// gain access to it.
private:
    double balance;
public:
// Balance can only be accessed by public methods
    bool withDraw (double amnt){
        if (balance - amnt > 0){
            balance -= amnt;
            return true;
        }
        return false;
    }
    Account2():balance{static_cast<double>(rand()%10000)}{}
    Account2(double b):balance{b}{}
};

// Inheriting Account doesn't give access to private data members
class BankClient2: public Account2{
public:
    bool useATM(double amnt){
        //balance += amnt; //ERROR!!
        if(withDraw(amnt)){
            return true;
        }
        return false;
    }

    void showBalance(){
        //ERROR:
        //cout<<"Balance: "<<balance<<endl;
    }

    BankClient2(){}
    BankClient2(double x) : Account2(x){}
};

void test1(){
    BankClient1 B;
    B.showBalance();
    B.useATM(1000.0);
    B.showBalance();
}

void test2(){
    // would error in above example since balance
    // is private. If we uncomment some of the code
    // above, it wont compile!!
    BankClient2 B;
    B.showBalance();
    B.useATM(1000.0);
    B.showBalance();
}

int main() {
    test1();
    cout<<"==================="<<endl;
    test2();
    return 0;
}

