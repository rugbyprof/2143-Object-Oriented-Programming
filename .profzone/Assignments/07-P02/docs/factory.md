# 🧱 Constructor vs Factory Method

### _(aka: Stop Making Constructors Do Everything)_

---

## 🎯 The Problem

You are building an `Args` class to parse:

```bash
./program input.txt -o output.txt --rotate 90 --verbose
```

You must decide:

> Should parsing happen in the **constructor** or a **factory method**?

---

## 🧠 Key Idea

> **Construction = building from clean data**  
> **Parsing = interpreting messy input**

These are not the same job.

---

# 🧱 Option 1 — Constructor-Based Parsing

```cpp
class Args {
public:
    std::string input_file;
    std::string output_file;
    bool verbose = false;
    int rotate = 0;

    Args(int argc, char* argv[]) {
        parse_impl(argc, argv);
        validate();
    }

private:
    void parse_impl(int argc, char* argv[]) {
        // parse flags and values
    }

    void validate() {
        // check correctness
    }
};
```

### ✅ Pros

- Works fine
- Can be clean with helper methods

### ❌ Cons

- Constructor now does parsing + validation
- Object creation is tied to messy input
- No alternative ways to construct object

---

# 🏭 Option 2 — Static Factory Method

```cpp
class Args {
public:
    std::string input_file;
    std::string output_file;
    bool verbose = false;
    int rotate = 0;

    static Args parse(int argc, char* argv[]) {
        Args args;
        args.parse_impl(argc, argv);
        args.validate();
        return args;
    }

private:
    Args() = default;

    void parse_impl(int argc, char* argv[]) {
        // parse flags and values
    }

    void validate() {
        // check correctness
    }
};
```

---

# ⚔️ Usage Comparison

```cpp
// Constructor
Args a(argc, argv);

// Factory
Args a = Args::parse(argc, argv);
```

👉 Which one tells you what’s happening?

---

# 🧠 Why Use a Factory Here?

### 1. 📣 **Clear Intent**

```cpp
Args::parse(argc, argv);
```

➡️ “We are parsing command-line input.”

---

### 2. 🧩 **Separation of Responsibility**

- Constructor → builds object
- Factory → interprets input + builds object

---

### 3. 🔒 **Control Object Creation**

```cpp
private:
    Args() = default;
```

➡️ Forces use of `parse()`  
➡️ Prevents invalid objects

---

### 4. 🔮 **Future Flexibility**

```cpp
Args::parse(argc, argv);
Args::fromFile("config.txt");
Args::defaults();
```

➡️ Clean, named construction paths

---

# 🤔 “But couldn’t the constructor just call helper methods?”

Yes.

But that still means:

> “You must parse input every time you construct this object.”

Factories say:

> “Parsing is a **special way** to create this object.”

That distinction matters.

---

# 🏭 What is a “Factory” Really?

A **factory method** is just:

> A method that **creates and returns an object**

It does NOT require:

- multiple objects
- loops
- threads
- queues
- industrial machinery noises

---

### Example

```cpp
Args args = Args::parse(argc, argv);
```

✔ Takes raw input  
✔ Builds object  
✔ Returns it

👉 That’s a factory.

---

# 🧠 When to Use Each

### Use a Constructor When:

- Data is already clean
- No parsing needed

```cpp
Args("in.txt", "out.txt", true, 90);
```

---

### Use a Factory When:

- Input is messy (CLI, files, JSON)
- Validation is required
- Creation has meaning (parse, load, build)

```cpp
Args::parse(argc, argv);
```

---

# 🔥 The Rule

> **If creating an object requires interpreting messy input → use a factory.**

---

# 🧨 Final Thought

Constructor version:

> “It works.”

Factory version:

> “It makes sense.”

…and future you (or your poor TA) will care deeply about that difference.

---
