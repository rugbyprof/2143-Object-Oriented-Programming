## When To Use Dynamic Memory

You should use **dynamic memory allocation** (via `new`, `delete`, or better — smart pointers / containers like `std::vector`) when:

- You **don’t know how much memory you need** until runtime, or
- The data needs to **outlive the current scope** (e.g., returned from a function or shared between objects).

---

### ⚙️ **In Contrast**

**Automatic (stack) allocation** is used for local variables whose size and lifetime are known at compile time.  
They are faster and automatically cleaned up when the function ends — but limited in flexibility and size.

---

### 📦 **Examples**

#### ✅ **Prefer Dynamic Allocation When:**

1. **Variable size unknown at compile time**

   ```cpp
   int n;
   std::cin >> n;
   int* arr = new int[n];   // can't do this with stack arrays in standard C++
   ```

2. **You need large objects**

   ```cpp
   std::vector<int> bigList(1'000'000);  // safer than allocating huge arrays on the stack
   ```

3. **You need objects that persist beyond their scope**

   ```cpp
   class Node {
   public:
       int value;
       Node* next;
       Node(int v) : value(v), next(nullptr) {}
   };

   Node* createNode(int v) {
       return new Node(v);  // survives after function returns
   }
   ```

4. **You share ownership between objects**
   ```cpp
   #include <memory>
   auto sharedNode = std::make_shared<Node>(10);
   ```

---

### ⚡ **Avoid Dynamic Allocation When:**

- The data is small, short-lived, and local.
- You can use standard containers (`std::array`, `std::vector`, etc.) instead — they manage memory for you.
- You can avoid manual `new` / `delete` (to prevent leaks or undefined behavior).

---

### 📘 **Quick Summary**

| Case                                | Use Stack (Automatic) | Use Heap (Dynamic) |
| ----------------------------------- | --------------------- | ------------------ |
| Size known at compile time          | ✅                    | ❌                 |
| Size known only at runtime          | ❌                    | ✅                 |
| Short lifetime (ends with function) | ✅                    | ❌                 |
| Long lifetime (needs to persist)    | ❌                    | ✅                 |
| Very large data                     | ❌                    | ✅                 |
| Need shared or manual control       | ❌                    | ✅                 |

---

👉 **Rule of thumb:**  
Use stack allocation **by default**,  
and switch to dynamic **only when lifetime or size require it.**
