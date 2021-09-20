## Program 2 - MyVector Class 2
#### Due: 09-24-2021 (Friday @ 12:00 p.m.)

## Overview

Using code from [Program 1](../05-P01/singly_linked.cpp) create a more robust `MyVector` class that includes some added functionality with the overloading of some C++ operators. The operations performed by using a particular operator will be defined by us with a brief discussion on what we should do. We do not have to abide by convention, we can define each operator to do anything we want.

## Requirements

- Overload `<<` (ostream) so that printing to std out is easy. 
- Overload `<<` (ofstream) so that printing to outfile is easy. 
- Overload `[]` so that your `MyVector` can be treated as an array 
- Overload `+` (addition)  
- Overload `-` (subtraction)  
- Overload `*` (multiplication)  
- Overload `/` (division)  
- Overload `==` (equality) 
- Overload `=` (assignment) 


## Testing your code

Given:

```cpp

MyVector v1;
MyVector v2;

int a1[] = { 1, 2, 3, 4, 5 };
int a2[] = { 10, 20, 30 };

ofstream fout;
ofile.open("output.txt");

cout << v1[2] << endl;
// writes out 3

v1[4] = 9;
// v1 now = [1,2,3,4,9]

cout << v1 << endl;
// writes out [1,2,3,4,9]` to console.

fout << v1 << endl;
// writes out [1,2,3,4,9]` to your output file.

Vector v3 = v1 + v2;
cout << v3 << endl;
// writes out [11,22,33,4,9]` to console.

v3 = v1 - v2;
cout << v3 << endl;
// writes out [-9,-18,-27,4,9]` to console.

v3 = v2 - v1;
cout << v3 << endl;
// writes out [9,18,27,4,9]` to console.

v3 = v2 * v1;
cout << v3 << endl;
// writes out [10,40,90,4,9]` to console.

v3 = v1 * v2;
cout << v3 << endl;
// writes out [10,40,90,4,9]` to console.

v3 = v1 / v2;
cout << v3 << endl;
// writes out [0,0,0,4,9]` to console.

v3 = v2 / v1;
cout << v3 << endl;
// writes out [10,10,10,4,9]` to console.

cout << v2 == v1 << endl;
// writes 0 to console (false) .

MyVector v4 = v1;
cout << v2 == v1 << endl;
// writes 1 to console (true) .

```


### Deliverables
- Create a folder in your assignments folder called `P02`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.
  - Make sure your banner is readable and does NOT have blank lines between every other row.

```
2143 
P02
Name
```

- Print out your source code. Make sure it's **[commented](../../Resources/01-Comments/README.md)**.
- Print out your output file.
- Put your assignment on the lecture podium at the beginning of class.
- Staple everything in this order:
  - **1)** Banner (on top)
  - **2)** Source code (middle)
  - **3)** Output (bottom)
- Any hand writing on your assignment is reduction in 1 letter grade.
- Failure to follow instructions is a reduction in 1 letter grade.
- Unreadable banner is a reduction in 1 letter grade.



