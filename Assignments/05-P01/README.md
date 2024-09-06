## Assignment 5 - Fraction Class

#### Due: 09-16-2024 (Monday)

## Overview

Given the fraction class written during lecture [here](https://replit.com/@rugbyprof/2143F24Fraction102#main.cpp) or using the provided code below (or both), create a proper fraction class that will overload the `+`, `-`, `*`, `/`, and `==` operators. Although I write classes **1`inline`** during lecture, I prefer (or mandate ... whatever makes you feel better) a `class definition` along with a `class implementation` where the definition has no variable names or implementation and the implementation is done outside of the definition using the scope resolution operator `::` to bind methods to the `Fraction` class. We will also discuss the need for public and private methods.

### Additional Helper Methods

Determine which additional methods you need and which protection level do they need to be at? You will add (along with sub, mul, div, and test for equality) fractions using methods like **LCM** (Least Common Multiple) and / or **LCD** (Least Common Denominator) to ensure the arithmetic gets done correctly.

## Fraction Class

Here is a starter version of the class I want you to implement:

```cpp
#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Constructor
    Fraction(int num, int den) : numerator(num), denominator(den) {
        // Consider validating that denominator is not 0
    }

    // Overloaded addition operator
    Fraction operator+(const Fraction& other) {
        // TODO: Use LCM and LCD to add fractions correctly
        // Add comments explaining how you use LCD and LCM to add fractions
        // Steps:
        // 1. Find the least common denominator (LCD)
        // 2. Adjust both fractions to have this denominator
        // 3. Add the numerators
        // 4. Return the result as a new fraction
    }

    // Additional overloaded operators (students should implement these)
    // Overloaded subtraction operator
    Fraction operator-(const Fraction& other) {
        // TODO: Implement the subtraction logic
    }

    // Overloaded multiplication operator
    Fraction operator*(const Fraction& other) {
        // TODO: Implement the multiplication logic
    }

    // Overloaded division operator
    Fraction operator/(const Fraction& other) {
        // TODO: Implement the division logic
    }

    // Overloaded equality operator (==)
    bool operator==(const Fraction& other) const {
        // TODO: Check if two fractions are equal by comparing numerators and denominators
    }

    // Overload output operator (<<) for printing fractions
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    // TODO: Implement methods to read input from stdin (lecture topic)
};

// Function to calculate Least Common Denominator (LCD)
int Fraction::lcd(int a, int b) {
    // TODO: Implement logic for LCD
}

// Function to calculate Least Common Multiple (LCM)
int Fraction::lcm(int a, int b) {
    // TODO: Implement logic for LCM
}

// Additional overloaded operators (you should implement these)
// Overloaded subtraction operator
Fraction Fraction::operator-(const Fraction& other) {
    // TODO: Implement the subtraction logic
}

// Overloaded multiplication operator
Fraction Fraction::operator*(const Fraction& other) {
    // TODO: Implement the multiplication logic
}

// Overloaded division operator
Fraction Fraction::operator/(const Fraction& other) {
    // TODO: Implement the division logic
}

int main() {
    // TODO: Design an input file that matches the format x/y operator i/j
    // Example: 1/2 + 3/4 should output 5/4 or 1 and 1/4, depending on how you format the output.

    // Example usage (students should implement actual logic)
    Fraction frac1(1, 2);
    Fraction frac2(3, 4);

    Fraction result = frac1 + frac2;  // This should call the overloaded + operator
    std::cout << result << std::endl; // This will print the result

    return 0;
}
```

### Key Concepts

### 1. Implementing LCM and LCD:

- **LCD**: The least common denominator is the smallest number that both denominators can divide evenly into. Use it to adjust the numerators before adding the fractions.
- **LCM**: The least common multiple is used in similar cases for simplifying fractions, but it's more commonly used in the addition of fractions.
- How do we know if a fraction is `fully reduced`?
- How do handle `improper fractions`?

### 2. **Operator Overloading**:

Here are the operators to overload `+`, `-`, `*`, `/`, and `==` making your class more intuitive and convenient to use. In fact we can add many methods that would incorporate other data types as well to ensure they behave as we would want them to behave. (Silly example but: "Hello World" \* 1/2 = "Hello")

### 3. **Method Access: Public vs Private**:

Remember

- **Public**: Methods that need to be accessed outside the class.
- **Private**: Helper methods that are only needed internally.

We need to determine what helper methods to make public or private. Helper methods are methods like: `print`, `reduce`, `reciprocol`, etc.

### 4. **Comments Format**:

- Here is how your program should be commented / formatted: [Comments](../../Resources/01-Comments/README.md)

- Make sure that each decision you make (like making methods private or public) is well-documented.

---

### Input File Format:

As part of the assignment, have them design a file that matches your described format. For example, the file could contain:

```
1/2 + 3/4
5/6 - 1/3
7/8 * 2/3
4/5 / 1/5
```

You'll need to read from this file and parse each line to:

- Extract the fractions.
- Identify the operator (`+`, `-`, `*`, `/`).
- Perform the correct operation using their overloaded operators.

---

### Sample Testing:

You should be able to test their program with inputs like:

```plaintext
1/2 + 3/4
```

Which should output:

```plaintext
5/4
```

Or by running your program like so: `fracMath 1/2 - 3/8` where `fracMath` is the executable and the rest are command line params that will get used in the operation specified.

## Deliverables

- Create an `Assignments` folder.
- Create a folder called `P01` IN the `Assignments` folder.
- Add all of your:
  - `header` files
  - `cpp` files
  - `input` files
  - and a `README.md` (written based on these [RULES](../../Resources/02-Readmees/))
- to your `P01` folder.
- All of your changes will be pushed to github by Monday September 16<sup>th</sup> @ classtime.
