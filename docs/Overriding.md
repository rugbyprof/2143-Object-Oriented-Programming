Method overriding, in object oriented programming, is a language feature that allows a subclass or child class to provide a specific implementation of a method that is already provided by one of its super-classes or parent classes. The implementation in the subclass overrides the implementation in the super-class by providing a method that has same name, same parameters or signature, and same return type as the method in the parent class.The version of a method that is executed will be determined by the object that is used to invoke it. If an object of a parent class is used to invoke the method, then the version in the parent class will be executed, but if an object of the subclass is used to invoke the method, then the version in the child class will be executed.In object-oriented terms, overriding means to override the functionality of an existing method.
If a class inherits a method from its super class, then there is a chance to override the method provided that it is not marked final.
Source: \[[1](https://en.wikipedia.org/wiki/Method_overriding),[2](http://www.tutorialspoint.com//java/java_overriding.htm)]
##Java   
An Example, class Animal:   

    class Animal{
        public void move(){
            System.out.println("Animals can move");
        }
    }
    class Dog extends Animal{
        public void move(){
            System.out.println("Dogs can walk and run");
        }
    }
    public class TestDog{
        public static void main(String args[]){
            Animal a = new Animal(); // Animal reference and object
            Animal b = new Dog(); // Animal reference but Dog object
            a.move();// runs the method in Animal class
            b.move();//Runs the method in Dog class
        }
    }
## Result
    Animals can move
    Dogs can walk and run
In the above example, you can see that the even though b is a type of Animal it runs the move method in the Dog class. The reason for this is: In compile time, the check is made on the reference type. However, in the runtime, JVM figures out the object type and would run the method that belongs to that particular object.
Therefore, in the above example, the program will compile properly since Animal class has the method move. Then, at the runtime, it runs the method specific for that object.
Consider the following example :
## Example for using Super Keyword   
    class Animal{
        public void move(){
            System.out.println("Animals can move");
        }
    }
    class Dog extends Animal{
        public void move(){
            System.out.println("Dogs can walk and run");
        }
        public void bark(){
            System.out.println("Dogs can bark");
        }
    }    
    public class TestDog{
        public static void main(String args[]){
            Animal a = new Animal(); // Animal reference and object
            Animal b = new Dog(); // Animal reference but Dog object
            a.move();// runs the method in Animal class
            b.move();//Runs the method in Dog class
            b.bark();
        }
    }
## Result   
    TestDog.java:30: cannot find symbol
    symbol  : method bark()
    location: class Animal
            b.bark();
            ^
The program will throw a compile time error since b's reference type Animal doesn't have a method by the name of bark.
## Rules for overriding
- The argument list should be exactly the same as that of the overridden method.
- The return type should be the same or a sub type of the return type declared in the original overridden method in the super-class.
- The access level cannot be more restrictive than the overridden method's access level. For example: if the super-class method is declared public then the overriding method in the sub class cannot be either private or protected.
- Instance methods can be overridden only if they are inherited by the subclass.
- A method declared final cannot be overridden.
- A method declared static cannot be overridden but can be re-declared.
- If a method cannot be inherited, then it cannot be overridden.
- A subclass within the same package as the instance's super-class can override any super-class method that is not declared private or final.
- A subclass in a different package can only override the non-final methods declared public or protected.
- An overriding method can throw any unchecked exceptions, regardless of whether the overridden method throws exceptions or not. However the overriding method should not throw checked exceptions that are new or broader than the ones declared by the overridden method. The overriding method can throw narrower or fewer exceptions than the overridden method.
- Constructors cannot be overridden     


## C++ Example
    #include <iostream>
    class TRectangle
    {
    Public:
        TRectangle(double l, double w) : length(l), width(w) {}
        virtual void print() const;
    Private:
        double length;
        double width;
    };
    void TRectangle::print() const
    {
        // print() method of base class.
        std::cout << "Length = " << this->length << "; Width = " << this->width;
    }
    class TBox : public TRectangle
    {
    Public:
        TBox(double l, double w, double h) : TRectangle(l, w), height(h) {}
        // virtual is optional here, but it is a good practice to remind it to the developer
        virtual void print() const;
    Private:
        double height;
    };
    // print() method of derived class.
    void TBox::print() const
    {
        // Invoke parent print() method.
        TRectangle::print();
        std::cout << "; Height = " << this->height;
    }
The method print() in class TBox, by invoking the parent version of method print(), is also able to output the private variables length and width of the base class. Otherwise, these variables are inaccessible to TBox.   
The following statements will instantiate objects of type TRectangle and TBox, and call their respective print() methods:   

    int main(int argc, char** argv)
    {
        TRectangle rectangle(5.0, 3.0);
        // Outputs: Length = 5.0; Width = 3.0
        rectangle.print();
        TBox box(6.0, 5.0, 4.0);
        // The pointer to the most overridden method in the vtable in on TBox::print,
        // but this call does not illustrate overriding.
        box.print();
        // This call illustrates overriding.
        // outputs: Length = 6.0; Width = 5.0; Height= 4.0
        static_cast<TRectangle&>(box).print();
    }
In C++11, similar to Java, a method that is declared final in the super class cannot be overridden; also, a method can be declared override to make the compiler check that it overrides a method in the base class.   

##Sources:   

1. https://en.wikipedia.org/wiki/Method_overriding
2. http://www.tutorialspoint.com//java/java_overriding.htm