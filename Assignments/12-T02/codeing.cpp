#include <iostream>

class Base {
   public:
    // virtual void randomSilly() = 0;
    virtual void randomStupid() {
    }
};

class SubClass1 : public Base {
   public:
    void randomStupid() {
        std::cout << "randStupid SubClass1" << std::endl;
    }
    void randomSilly() {
        std::cout << "SubClass1" << std::endl;
    }
};

class SubClass2 : public Base {
    void randomStupid() {
        std::cout << "randStupid SubClass2" << std::endl;
    }
    void randomSilly() {
        std::cout << "SubClas2" << std::endl;
    }
};

class Momma {
    int val;
   public:
    Momma() {
        std::cout << "Momma" << std::endl;
    }
    Momma(int a) {
        std::cout << "Momma" << std::endl;
    }
    int sum(int *A, int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += A[i];
        }
        return sum;
    }
    int sum(int *A, int n, int m) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += A[i];
        }
        return sum;
    }
};

class dad{
    int sum(int *A, int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += A[i];
        }
        return sum;
    }
};

int main() {
    Base *base;

    SubClass1 s1;
    SubClass2 s2;

    base = &s1;

    base->randomSilly();

    base = &s2;

    base->randomSilly();

    // hello

    Base b;

    b.randomSilly();

    SubClass1 s3;
    s3.randomStupid();

    SubClass2 s4;
    s4.randomStupid();

    return 0;
}

virtual keyword is an agreement to be overridden by the derived class.rIf the derived class does not override the function,
    the base class function will be called.In the above code, the randomSilly() function is declared as pure virtual in the Base class.So,
    the Base class is an abstract class.The SubClass1 and SubClass2 classes are derived from the Base class
        .The random

    pure virtual function randomSilly() is not overridden in the SubClass2 class.So,
    the Base class randomSilly



class Character{
public:
void move();
void jump();
void attack();
};


class MagickUser : public Character{
    void attack();
};

class Warrior : public Character{
    void attack();
};

class Palladin : MagickUser, Warrior{

    // void attack()[

    // ]

    void attack(bool useMagick){
        
        MagickUser::attack();
        Warrior::attack();
    }
};




