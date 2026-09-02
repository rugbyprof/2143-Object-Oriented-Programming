## Worksheet 1

1. answer 1
1. answer 2

```cpp

  void print() {
    Node *travel = front;
    while (travel) {
      cout << travel->val;
      if (travel->next) {
        cout << "->";
      }
      travel = travel->next;
    }
    cout << endl;
  }
};
```

## other section
