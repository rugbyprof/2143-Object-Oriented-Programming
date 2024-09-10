#include <iostream>

using namespace std;

/**
 * Class Simple
 * Description:
 *    A simple class that contains an integer value and does not require a
 *    custom copy constructor.
 * Methods:
 *    Simple(int v) : value(v) - Constructor that initializes the value
 */
class Simple {
public:
  int value;

  /**
   * Constructor that initializes the value
   * @param int v - The value to store in the object
   */
  Simple(int v) : value(v) {}

  // No need for custom copy constructor

  // No need for destructor
};

/**
 * Class Complex
 * Description:
 *    A class that contains a pointer to dynamically allocated memory
 *    and a custom copy constructor to handle a deep copy.
 * Methods:
 *    Complex(int v) : value(new int(v)) - Constructor that dynamically
 * allocates memory Complex(const Complex& other) - Custom copy constructor to
 * handle deep copy ~Complex() - Destructor that frees the dynamically allocated
 * memory when the object is destroyed
 *
 * Note:
 * To test this class and the need for a custom copy constructor, comment out
 * the custom copy constructor then change the value for one of the objects
 * (obj3 or obj4) and print the values of both objects. You will see that the
 * value of both objects is the same, which means that they are sharing the same
 * memory location. This is why a custom copy constructor is needed to allocate
 * new memory and copy the value.
 */
class Complex {
public:
  int *value; // Pointer to dynamically allocated memory

  /**
   * Constructor that dynamically allocates memory
   * @param int v - The value to store in the dynamically allocated memory
   */
  Complex(int v) {
    value = new int(v); // Dynamically allocate memory
  }

  /**
   * Custom copy constructor to handle deep copy since value is a pointer
   * @param const Complex& other - The object to copy
   */
  Complex(const Complex &other) {
    value = new int(*other.value); // Allocate new memory and copy the value
  }

  /**
   * Destructor that frees the dynamically allocated memory when the object is
   * destroyed
   */
  ~Complex() {
    delete value; // Free the dynamically allocated memory
  }
};

int main() {
  Simple obj1(10);
  Simple obj2 = obj1; // Default copy constructor works fine

  std::cout << "obj1 value: " << obj1.value << std::endl;
  std::cout << "obj2 value: " << obj2.value << std::endl;

  Complex obj3(10);
  Complex obj4 = obj3; // Calls the custom copy constructor

  std::cout << "obj1 value: " << *obj3.value << std::endl;
  std::cout << "obj2 value: " << *obj4.value << std::endl;

  return 0;
}
