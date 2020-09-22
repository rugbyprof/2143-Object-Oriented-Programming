# Addresses, Pointers, References

### Memory addresses

Every byte in memory has an integer memory ___address___. Addresses start at zero and go to the maximum amount of memory that the computer has. For example, in a computer that has 256 MB of RAM the bytes would be numbered 0, 1, 2, 3, 4, 5, etc (up to the power of 2 closest to 256,000,000). Instructions and data are stored in RAM when a program is running, so each instruction or data element is identified by its memory address, or the address of its first byte because many types are longer than one byte. The CPU uses these memory addresses for all operations. One of the great advantages of higher-level language is that all these addressing details are taken care of automatically by the programming language and the programmer doesn't have to worry about them. However, it can be very useful for the programmer to be able to explicitly use memory addresses as data. This data type is called a ___pointer___.

### Pointers

C and C++ have variables that hold memory addresses. These are called ___pointers___. Pointers are an extremely powerful programming feature, long regarded as essential to any full-strength programming language. But the power of pointers also comes at a price, and safe use of pointers turns out to be rather difficult in large programs and the source of many bugs. The most common uses of pointers are:
- Working with arrays, especially char arrays.
- For dynamic memory allocation of data structures.
- To link data structures together.

Pointers are so powerful they are dangerous. They are dangerous because they can access any memory location and a small error in their use can have mysteriously bizarre results, often showing up only later in execution or when the program is run in a different environment. It is estimated that about 50% of the bugs in production ("shrink-wrapped") software are due to pointer misuse. Consequently, some languages do not have pointers, and only have a more restricted use of memory addresses called references.
See Pointers

### References

A much safer and simpler use of memory addresses are ___references___. References are pointers that can't be modified with addition and subtraction. Removing this capability makes references much safer to use than pointers. In addition, they are automatically dereferenced so the programming notation is simpler and less error prone. Newer programming languages, such as Java, have completely eliminated pointers and only use references for greater reliability and security.


## Pointers in C/C++

Pointers are variables that contain memory addresses (see Addresses, Pointers, and References). They are an essential data type in C and C++, and are used for the following:
- Array variables are pointers.
- Dynamic memory allocation/deallocation uses pointers.
- To pass the address of a struct or object instead of the entire object to a function.
- For function parameters that will be changed by the function (out or inout parameters).

#### Declaring a pointer

Pointers are declared to point to a particular datatype. A `*` is written after the type to indicate that this is a pointer to that type. For example, a pointer to an `int` would be declared like this.

~~~cpp
int* ip;  // declares ip to be a pointer to an int.
~~~

You will also see variations in the spacing such as (and it doesn't matter).

~~~
int *ip;
int * ip;
~~~

#### NULL

NULL is a pointer to nothing, and should be used as the initial value for pointers. For example:

~~~cpp
//When we declare an integer variable "x", we initialize it to zero.
int x = 0;
//When you declare a pointer variable "x", you should intialize it to NULL.
int *x = NULL;
~~~

#### Pointer operators: * (dereference) and & (address of)

Two operators are used when dealing with memory addresses:
- Unary `&` gives the address of some variable. This can be assigned to a pointer variable of the same data type, and then used to manipulate it (if desired).
- Unary `*` takes the contents of a pointer and locates the "pointee". This is called dereferencing.

#### Examples

~~~cpp
char* cp;     // declare pointer to char
char  c, d;   // declare char variables

cp  = &c;     // puts address of c into cp
c   = 'x';    // assigns 'x' to c
*cp = 'x';    // also assigns 'x' to c
d   = *cp;    // copies c's value to d
cp  = &d;     // puts address of d into cp
*cp = c;      // puts value of c into d
~~~

### The `New` operator and a different approach to `pointers`:

Before we talk about the `NEW` operator, logically we need to talk about
`pointers` ( too late, weve used `new` plenty:) ). Here is a small tutorial
I found from the web.

***C/C++ Tutorial: An Introduction To Pointers***
***by John Kopp***

`Pointers` are variables that hold addresses in C and C++. They provide much power
and utility for the programmer to access and manipulate data in ways not seen
in some other languages. They are also useful for passing parameters into functions
in a manner that allows a function to modify and return values to the calling
routine. When used incorrectly, they also are a frequent source of both program
bugs and programmer frustration.

#### Introduction

As a program is executing all variables are stored in memory, each at its own unique
address or location. Typically, a variable and its associated memory address contain
data values. For instance, when you declare:

~~~cpp
int count = 5;
~~~

The value "5" is stored in memory and can be accessed by using the variable "count".
A pointer is a special type of variable that contains a memory address rather than a
data value. Just as data is modified when a normal variable is used, the value of the
address stored in a pointer is modified as a pointer variable is manipulated.

Usually, the address stored in the pointer is the address of some other variable.

~~~cpp
int *ptr;
ptr = &count /* Stores the address of count in ptr */
             /* The unary operator & returns the address of a variable */
~~~

To get the value that is stored at the memory location in the pointer it is necessary
to dereference the pointer. Dereferencing is done with the unary operator `*`.

~~~cpp
int total;
total = *ptr; /* The value in the address stored in ptr is assigned to total */
~~~

The best way to learn how to use pointers is by example. There are examples of the
types of operations already discussed below. Pointers are a difficult topic. Don't
worry if everything isn't clear yet.

#### Declaration and Initialization

Declaring and initializing pointers is fairly easy.

~~~cpp
main()
{
     int j;
     int k;
     int l;
     int *pt1;    /* Declares an integer pointer */
     int *pt2;    /* Declares an integer pointer */
     float values[100];
     float results[100];
     float *pt3;    /* Declares a float pointer */
     float *pt4;    /* Declares a float pointer */

     j = 1;
     k = 2;
     pt1 = &j;    /* pt1 contains the address of the variable j */
     pt2 = &k;    /* pt2 contains the address of variable k */
     pt3 = values;    /* pt3 contains the address of the first element of values */
     pt3 = &values[0];    /* This is the equivalent of the above statement */

}
~~~

#### Pointer Dereferencing/Value Assignment

`Dereferencing` allows manipulation of the data contained at the memory address stored in
the pointer. The pointer stores a memory address. Dereferencing allows the data at that
memory address to be modified. The unary operator `*` is used to dereference.
For instance:

~~~cpp
*pt1 =*pt1 + 2;
~~~

This adds two to the value `pointer to` by `pt1`. That is, this statement adds 2 to the contents
of the memory address contained in the pointer `pt1`. So, from the main program, `pt1` contains
the address of `j`. The variable `j` was initialized to `1`. The effect of the above statement is
to add `2` to `j`.

The contents of the address contained in a pointer may be assigned to another pointer or to a
variable.

~~~cpp
*pt2 = *pt1; /* assigns the contents of the memory pointed to by pt1 to the contents of
                the memory pointer to by pt2; */
k = *pt2;    /* assigns the contents of the address pointer to by pt2 to k. */
~~~

#### Pointer Arithmetic

Part of the power of pointers comes from the ability to perform arithmetic on the pointers
themselves. Pointers can be incremented, decremented and manipulated using arithmetic expressions.
Recall the float pointer `pt3` and the float array `values` declared above in the main program.

~~~cpp
pt3 = &values[0];    /* The address of the first element of "values" is stored in pt3*/
pt3++;               /* pt3 now contains the address of the second element of values */
*pt3 = 3.1415927;    /* The second element of values now has pie (actually pi)*/
pt3 += 25;           /* pt3 now points to the 26th element of values */
*pt3 = 2.22222;      /* The 26th element of values is now 2.22222 */

pt3 = values;        /*pt3 points to the start of values, now */
for (ii = 0; ii < 100; ii++)
{
     *pt3++ = 37.0;   /* This sets the entire array to 37.0 */
}
pt3 = &values[0];     /* pt3 contains the address of the first element of values */
pt4 = &results[0];    /* pt4 contains the address of the first element of results */

for (ii=0; ii < 100; ii++)
{
     *pt4 = *pt3;     /*The contents of the address contained in pt3 are assigned to
     pt4++;           /*the contents of the address contained in pt4 */
     pt3++;
}
~~~

The first 2 chapters at this web site might help also. Look [HERE](http://pweb.netcom.com/~tjensen/ptr/pointers.htm).
