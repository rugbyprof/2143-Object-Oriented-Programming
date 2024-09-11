## Arrays Lists Stacks & Queues - Data Structures Review

#### Due: NA

Both **array-based** and **list-based** data structures have their strengths and weaknesses depending on the use case, especially in terms of memory management and operation efficiency. Let’s break them down with examples and show how each type can be used to implement basic data structures like **stacks** and **queues**.

---

### 1. Array-Based Data Structures

#### **Definition**:

Array-based structures use **contiguous memory** to store elements. The size of the array is either fixed (in static arrays) or dynamically managed (in dynamic arrays like `std::vector` in C++).

#### **Examples**:

- Static Arrays (fixed-size)
- Dynamic Arrays (`std::vector`)

#### **Pros**:

- **Random Access**: Accessing an element at a specific index is an **O(1)** operation because the array provides direct access to memory locations.
- **Memory Locality**: Elements are stored contiguously in memory, which leads to better cache performance.

#### **Cons**:

- **Fixed Size** (for static arrays): If using a fixed-size array, it can’t grow beyond its capacity. Dynamic arrays handle this by reallocating, but it incurs overhead.
- **Costly Insertions/Deletions**: Inserting or deleting elements (other than at the end) requires shifting elements, leading to an **O(n)** operation in the worst case.

---

### **2. List-Based Data Structures**

#### **Definition**:

List-based structures, such as **linked lists**, use nodes that store data and pointers to the next (and sometimes previous) nodes. They do not use contiguous memory.

#### **Examples**:

- Singly Linked List
- Doubly Linked List

#### **Pros**:

- **Dynamic Size**: Linked lists can easily grow and shrink as needed without worrying about reallocating memory.
- **Efficient Insertions/Deletions**: Inserting or deleting elements in a linked list is efficient (**O(1)** for inserting or removing at the head or tail), provided you have the reference to the correct node.

#### **Cons**:

- **No Random Access**: Accessing an element requires traversing the list from the head (or tail in doubly linked lists), leading to **O(n)** access time.
- **Memory Overhead**: Each element in a linked list requires additional memory to store pointers, leading to greater memory consumption compared to arrays.

---

### **3. Comparison: Array-Based vs List-Based**

| Feature                | Array-Based Structures                          | List-Based Structures                             |
| ---------------------- | ----------------------------------------------- | ------------------------------------------------- |
| **Access Time**        | **O(1)** (Direct access by index)               | **O(n)** (No direct access, must traverse)        |
| **Insertion/Deletion** | **O(n)** (Shifting elements required)           | **O(1)** (If inserting/deleting at the head/tail) |
| **Memory Usage**       | Less memory overhead (contiguous memory)        | More memory overhead (due to pointers)            |
| **Resizing**           | Resizing can be costly (copying array elements) | Dynamic by nature, no need for resizing           |
| **Cache Performance**  | Better (due to memory locality)                 | Poorer (nodes may be scattered in memory)         |

---

### **4. Implementing Stacks and Queues Using Array-Based vs List-Based Structures**

#### **Stack**:

A **stack** is a **Last In, First Out (LIFO)** data structure where the last element inserted is the first one to be removed.

- **Array-Based Stack**:

  - Implemented using a dynamic array (`std::vector` in C++).
  - **Push** (insert element) is typically **O(1)** unless the array needs resizing, which makes it **O(n)**.
  - **Pop** (remove element) is **O(1)** if the element is removed from the end.

- **List-Based Stack**:
  - Implemented using a **singly linked list**.
  - **Push** and **Pop** operations are **O(1)** if you operate at the head of the list.

##### Example for Array-Based Stack:

```cpp
#include <vector>

class ArrayStack {
    std::vector<int> stack;

public:
    void push(int value) {
        stack.push_back(value);  // O(1) unless resizing
    }

    void pop() {
        stack.pop_back();  // O(1)
    }

    int top() {
        return stack.back();  // O(1)
    }
};
```

##### Example for List-Based Stack:

```cpp
struct Node {
    int data;
    Node* next;
};

class ListStack {
    Node* head = nullptr;

public:
    void push(int value) {
        Node* newNode = new Node{value, head};
        head = newNode;  // O(1)
    }

    void pop() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;  // O(1)
        }
    }

    int top() {
        return head ? head->data : -1;  // O(1)
    }
};
```

---

#### **Queue**:

A **queue** is a **First In, First Out (FIFO)** data structure where the first element inserted is the first to be removed.

- **Array-Based Queue**:

  - Implemented using a **circular array** or a **dynamic array**.
  - **Enqueue** (insert element) and **Dequeue** (remove element) are **O(1)** with proper management of head/tail pointers.

- **List-Based Queue**:
  - Implemented using a **doubly linked list** (or singly linked list with tail pointer).
  - Both **Enqueue** and **Dequeue** are **O(1)** if the queue is managed from both head and tail.

##### Example for Array-Based Queue:

```cpp
#include <vector>

class ArrayQueue {
    std::vector<int> queue;
    int front = 0;

public:
    void enqueue(int value) {
        queue.push_back(value);  // O(1)
    }

    void dequeue() {
        if (!queue.empty()) {
            front++;  // O(1), assuming no resizing needed
        }
    }

    int frontElement() {
        return queue[front];  // O(1)
    }
};
```

##### Example for List-Based Queue:

```cpp
struct Node {
    int data;
    Node* next;
};

class ListQueue {
    Node* front = nullptr;
    Node* rear = nullptr;

public:
    void enqueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = rear;
        }
    }

    void dequeue() {
        if (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        if (!front) {
            rear = nullptr;
        }
    }

    int frontElement() {
        return front ? front->data : -1;  // O(1)
    }
};
```

---

### **Summary of Usage**:

- **Stacks** can be implemented efficiently using either arrays or linked lists, with array-based stacks potentially benefitting from better cache performance but suffering from resizing overhead.
- **Queues** work efficiently with both arrays (using circular logic) and linked lists, but linked lists avoid resizing issues and handle memory dynamically.

Both **array-based** and **list-based** data structures have their strengths. The choice between them depends on the application, the size of data, and whether efficient memory usage or access speed is prioritized.
