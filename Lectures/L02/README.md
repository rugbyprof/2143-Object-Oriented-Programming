## Lecture 2 - Improving a basic class

### Friends

- A *friend* class can access **private** and **protected** members of the class in which it is declared as a friend. 
- It is sometimes useful to allow a particular class to access private members of another class. 
- By declaring `ostream` as a friend, it can access the private members of a class in order to print them out. 

Add ability to print a node:

```cpp
  friend ostream& operator<<(ostream& os,const Node& obj){
    return os
      << "[" << obj.data << "]";
  }
```

- Same thing for the vector class:

```cpp
  // This implementation will give problems for a templated solution
  // because it assumes that temp->data is an integer. We will fix 
  // that issue. 
  friend ostream& operator<<(ostream& os,const MyVector& obj){

      Node* temp = obj.Head;
      string output = "";

      while(temp){
        output += "["+to_string(temp->data)+"]";
        if(temp->next){
          output += "->";
        }
        temp = temp->next;
      }
      
      return os<<output;
  }
```

- Friendship is not mutual. If class A is a friend of B, then B doesn’t become a friend of A automatically.
- Friendship is not inherited.
- The concept of friends does not exist in all languages (Java for example).
- Friends should be used only for limited purpose, if too many functions or external classes are declared as friends of a particular class with protected or private data, it lessens the value of encapsulation which is a core concept in OOP.

### Overloading (Type of Polymorphism)

**Function Overloading:**

```cpp
  Node(){
    data = 0;
    next = prev = NULL;
  }

  Node(int d){
    data = d;
    next = prev = NULL;
  }
```

**Operator Overloading:**

```cpp
  void operator=(const Node& obj){
    this->data = obj.data;
  }
```

```cpp
// Overloading the square brackets to return the value of the node
// is a limited solution. We can improve that.
// Add the `&` operator to your return value, and you can overwrite
// the previous value that was there!
int operator[](int index) 
{ 
    if (index >= size) 
    { 
        cout << "Array index out of bound, exiting"; 
        exit(0); 
    }
    Node* temp = Head;
    for(int i=0;i<index;i++){
        temp = temp->next;
    }
    return temp->data;
}
```



```cpp
MyVector operator+(const MyVector &lhs){

    Node* temp1 = Head;
    Node* temp2 = lhs.Head;

    MyVector V;

    while(temp1){
        V.pushBack(temp1->data);
        temp1 = temp1->next;
    }

    while(temp2){
        V.pushBack(temp2->data);
        temp2 = temp2->next;
    }

    return V;
}
```

### Copy Constructor

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/shallow_vs_deep_1.png" width="500">

#### Shallow Copy


<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/shallow_vs_deep_2.png" width="500">

#### Deep Copy


<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/shallow_vs_deep_3.png" width="500">


```cpp
MyVector(const MyVector& obj){
    Node* Temp = obj.Head;
    while(Temp){
        this->pushBack(Temp->data);
        Temp = Temp->next;
    }
}
```