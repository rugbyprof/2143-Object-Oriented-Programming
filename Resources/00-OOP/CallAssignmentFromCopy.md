### Why not just call the assignment operator from copy constructor?

A common mistake is to call the assignment operator from the copy constructor. Take the Array class for example. Inside the copy you might think it's simple to write:
```cpp
Array::Array(const Array &init) {
   *this = init;
}
```
Here's the problem with this. The first thing the operator= does is to check for self assignment and delete the old memory:

```cpp
const Array& Array::operator=(const Array& right) {
   if (&right != this) {                    
      delete [] arrayPtr;                   
      ...
```
Since the copy constructor is constructing a brand new object, it won't be the same as the parameter right. BUT ... the current object is a brand new object and its data members have just gotten memory, and have no valid values in them. They are garbage values, meaning that arrayPtr may or may not be a valid address. Typically it is not a valid address, so trying to use delete makes your program crash.

One way to solve this is to assign any necessary data members values before calling the assignment operator. Setting arrayPtr to NULL first makes the copy constructor work okay:
```cpp
Array::Array(const Array &init) {
   arrayPtr = NULL;
   *this = init;
}
```
We don't need to set size before calling operator= because it will get set first thing in operator
