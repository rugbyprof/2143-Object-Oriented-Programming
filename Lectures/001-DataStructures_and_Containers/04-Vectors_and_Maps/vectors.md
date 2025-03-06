## Vectors - Introduction and Overview

#### Due: NA

Introduction to Vectors, some vector methods, and some newer C++ syntax. Ok, not NEW syntax but not ubiquitous either. You can use the example code and lists below to get a feel for what vectors offer. This tiny collection is part of what is cool in OOP. Not so much large project design (which is one aspect where OOP excels) but in creating data types that act like they were native to the language. You've heard me mention this in class, and below will have some examples of this, but using vectors.

|      Example Code Files      |
| :--------------------------: |
| [vectors 01](vectors_01.cpp) |
| [vectors 02](vectors_02.cpp) |
| [vectors 03](vectors_03.cpp) |

And a list of methods below

### Size Methods

These methods deal with the current size of OR resizing the vector.

| Name              | Description                                                                                              |
| :---------------- | :------------------------------------------------------------------------------------------------------- |
| `size()`          | Returns the number of elements currently in the vector.                                                  |
| `max_size()`      | Returns the maximum number of elements that the vector can hold.                                         |
| `capacity()`      | Returns the size of the storage space currently allocated to the vector expressed as number of elements. |
| `resize()`        | Resizes the container so that it contains ‘g’ elements.                                                  |
| `empty()`         | Returns whether the container is empty.                                                                  |
| `shrink_to_fit()` | Reduces the capacity of the container to fit its size and destroys all elements beyond the capacity.     |
| `reserve()`       | Requests that the vector capacity be at least enough to contain n elements.                              |

### Iterator Methods

These methods return references to vector locations so the vector can be iterated over.

| Name        | Description                                                                                                                                   |
| :---------- | :-------------------------------------------------------------------------------------------------------------------------------------------- |
| `begin()`   | Returns an iterator pointing to the first element in the vecto.                                                                               |
| `end()`     | Returns an iterator pointing to the theoretical element that follows the last element in the vecto.                                           |
| `rbegin()`  | Returns a reverse iterator pointing to the last element in the vector (reverse beginning). It moves from last to first elemen.                |
| `rend()`    | Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (considered as reverse end.          |
| `cbegin()`  | Returns a constant iterator pointing to the first element in the vector.                                                                      |
| `cend()`    | Returns a constant iterator pointing to the theoretical element that follows the last element in the vector.                                  |
| `crbegin()` | Returns a constant reverse iterator pointing to the last element in the vector (reverse beginning). It moves from last to first elemen.       |
| `crend()`   | Returns a constant reverse iterator pointing to the theoretical element preceding the first element in the vector (considered as reverse end. |

## Vector References

These methods point to or return a memory location within the vector.

| Name                       | Description                                                                                             |
| :------------------------- | :------------------------------------------------------------------------------------------------------ |
| `reference operator`: `[]` | Returns a reference to the element at a position (integer index) specified within the `[]` brackets.    |
| `at(g)`                    | Returns a reference to the element at position ‘g’ in the vector.                                       |
| `front()`                  | Returns a reference to the first element in the vector.                                                 |
| `back()`                   | Returns a reference to the last element in the vector.                                                  |
| `data()`                   | Returns a direct pointer to the memory array used internally by the vector to store its owned elements. |

### Vector Manipulation

Adding and removing data from the vector.

| Name             | Description                                                                                                      |
| :--------------- | :--------------------------------------------------------------------------------------------------------------- |
| `assign()`       | It assigns new value to the vector elements by replacing old ones.                                               |
| `push_back()`    | It push the elements into a vector from the back.                                                                |
| `pop_back()`     | It is used to pop or remove elements from a vector from the back.                                                |
| `insert()`       | It inserts new elements before the element at the specified position.                                            |
| `erase()`        | It is used to remove elements from a container from the specified position or range.                             |
| `swap()`         | It is used to swap the contents of one vector with another vector of same type and size.                         |
| `clear()`        | It is used to remove all the elements of the vector container.                                                   |
| `emplace()`      | It extends the container by inserting new element at position.                                                   |
| `emplace_back()` | It is used to insert a new element into the vector container, the new element is added to the end of the vector. |
