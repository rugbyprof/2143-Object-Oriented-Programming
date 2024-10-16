## Extracted Code Blocks:

```cpp

class Base {
    public:
    void Attack() {
        std::cout << "Base attack!" << std::endl;
    }
    void Attack(int damage) {
        std::cout << "Base attack for " << damage << " damage!" << std::endl;
    }
    virtual void SpecialAttack() {
        std::cout << "Base special attack!" << std::endl;
    }
};

class Derived : public Base {
    public:
    void Attack() {
        std::cout << "Derived attack!" << std::endl;
    }
    void SpecialAttack() {
        std::cout << "Derived special attack!" << std::endl;
    }
};


```

```cpp

class Character
{
    string name;
};
class Wizard: public Character
{
    int spellStrength;
};

```

```cpp

class Base {
    public:
    void print() {cout << "Base Function" << endl;}
};

class Derived : public Base {
    public:
    void print() {}cout << "Derived Function" << endl;}
};
int main() {
    Derived derived1;
    derived1.print();
}

```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

```

```cpp

int *ptr = new int(7);

```

```cpp

class Wizard {
    private:
    int mana_;
    public:

};

class Rogue {
    public:
    void StealMana(Wizard& wizard) {
        wizard.mana_ -= 10;
    }
};

```

```cpp

#include <iostream>

// Tell compiler Rogue is a class so the Wizard class
// wont error when it tries to friend it.
class Rogue;


class Wizard {
    private:
    int mana_;

    public:
    // Make Rogue a friend, so it has access to your privates
    // and can steal yousr manna.
    friend Rogue;   // <-------------
};

class Rogue {
    public:
    void StealMana(Wizard &wizard) { wizard.mana_ -= 10; }
};

int main() {
    Rogue R;
    Wizard W;
    R.StealMana(W);
}

```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
    void print(string x) {
        cout << name << X<< endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

```

```cpp

class Character
{
    string name;
};
class Wizard: public Character
{
    int spellStrength;
};

```

```cpp

class Base {
    public:
    void print() {cout << "Base Function" << endl;}
};

class Derived : public Base {
    public:
    void print() {}cout << "Derived Function" << endl;}
};
int main() {
    Derived derived1;
    derived1.print();
}

```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

```

```cpp

class Dad {
    private:
    string alcohol;

    protected:
    public:
};

class Kid {

    protected:
    public:
    Kid() {
    }

};

```

```cpp

class Character {
    protected:
    int name;
    public:
    void print() {
        cout << name << endl;
    }
};
class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};
class Warrior : public Character {
    public:
    void print() {
        cout << name << " is a warrior!" << endl;
    }
};

```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
    void print(string x) {
        cout << name << X<< endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

```

```cpp

class Bike
{
    Engine objEng;
};
class Engine
{
    float CC;
};

```

```cpp

class Base {
    public:
    void print() {cout << "Base Function" << endl;}
};

class Derived : public Base {
    public:
    void print() {}cout << "Derived Function" << endl;}
};
int main() {
    Derived derived1;
    derived1.print();
}

```

```cpp

class Character {
    protected:
    string name;
    public:
    void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

```

```cpp

class Dad {
    private:
    string alcohol;

    protected:
    public:
};

class Kid {

    protected:
    public:
    Kid() {
    }

};

```

```cpp


class Kid; // Forward declaration

class Dad {
    private:
    string alcohol;

    protected:
    public:
    friend Kid; // Make Kid a friend
};

class Kid {

    protected:
    public:
    Kid() {
    }

};

```

```cpp

class Character {
    protected:
    string name;
    public:
    virtual void print() {
        cout << name << endl;
    }
};

class Wizard : public Character {
    public:
    void print() {
        cout << name << " is a Wizard!" << endl;
    }
};

//optionally
int main{
    Character *ptr;
    Wizard w;
    ptr = &w;
    ptr->print(); // will correclty choose print method from Wizard
    return 0;
}


```

```cpp

class Animals {
    public:
    virtual void sound() {
        cout << "Playing generic animal sound..." << endl;
    }
};
class Dogs : public Animals {
    public:
    void sound() {
        cout << "Dogs bark..." << endl;
    }
};
int main() {
    Animals *a;
    Dogs     d;
    a = &d;
    a->sound();
    return 0;
}

```

```cpp
% class Checking{
    % private:
    %     double account_balance;
    % protected:
    %     int account_number;
    % public:
    %     Checking(string n){
        %         account_balance=0;
        %         account_number=rand();
        %     }
        % };
        %
```

```cpp

% class Checking{
    % private:
    %     double account_balance;
    % protected:
    %     int account_number;
    % public:
    %     Account(string n){
        %         account_balance=0;
        %         account_number=rand();
        %     }

        %     friend class Customer;
        % };

        % class Customer: public Checking{

            % };
            %
```

```cpp
struct Animal {
    virtual ~Animal() = default;
    virtual void Eat() {}
};

struct Mammal: Animal {
    virtual void Breathe() {}
};

struct WingedAnimal: Animal {
    virtual void Flap() {}
};

// A bat is a winged mammal
struct Bat: Mammal, WingedAnimal {};

Bat bat;

```

```cpp
struct Animal {
    virtual ~Animal() = default;
    virtual void Eat() {}
};

// Two classes virtually inheriting Animal:
struct Mammal: virtual Animal {
    virtual void Breathe() {}
};

struct WingedAnimal: virtual Animal {
    virtual void Flap() {}
};

// A bat is still a winged mammal
struct Bat: Mammal, WingedAnimal {};

```
