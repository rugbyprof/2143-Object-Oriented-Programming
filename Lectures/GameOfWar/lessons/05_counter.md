# GameOfWar 05 — Encapsulation: Introducing a Counter Class

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 05 - Encapsulation
previous: examples/04_containers.cpp
new_file: examples/05_counter.cpp
concepts:
  - Classes and objects
  - Private data members
  - Public interfaces
  - Constructor initialization
  - Composition
  - Separation of model and UI
```

We have three working buttons: Increment, Decrement, and Reset.

Currently, each button directly manipulates a variable:

```cpp
int counter = 0;

auto increment = Button("Increment", [&] {
    counter++;
});
```

That works, but it creates a design problem.

**Our interface is responsible for both user interaction and managing application data.**

Let's fix that without changing what the program does.

## Step 5.1 — Copy the working program

```bash
cp examples/04_containers.cpp examples/05_counter.cpp
```

Compile before making any changes:

```bash
cmake -S . -B build
cmake --build build --target 05_counter
./build/05_counter
```

Everything should work exactly as before. Change the title text to `"GameOfWar 05"`.

---

## Step 5.2 — Create our first class

At the top of `05_counter.cpp`, after the `using namespace ftxui;` statement, add:

```cpp
class Counter {
private:
    int value;

public:
    Counter() : value(0) {
    }

    void increment() {
        value++;
    }

    void decrement() {
        value--;
    }

    void reset() {
        value = 0;
    }

    int getValue() const {
        return value;
    }
};
```

**Don't change `main()` yet.**

Compile:

```bash
cmake --build build --target 05_counter
```

It should compile successfully.

We've introduced a class, but we haven't created an object or changed the program's behavior.

### Discussion: What did we just create?

Our `Counter` is an **Abstract Data Type (ADT)**.

It defines what operations are available without requiring other parts of the program to understand its internal implementation.

| Method        | Responsibility            |
| ------------- | ------------------------- |
| `Counter()`   | Initialize the counter    |
| `increment()` | Increase the value        |
| `decrement()` | Decrease the value        |
| `reset()`     | Restore the initial value |
| `getValue()`  | Return the current value  |

Notice the constructor:

```cpp
Counter() : value(0) {
}
```

The `: value(0)` part is a **member initialization list**. It initializes `value` before the constructor body runs.

Also notice:

```cpp
int getValue() const
```

The `const` promises that calling this method won't modify the object. The compiler enforces that promise.

**Question:** Why is `getValue()` public while `value` is private?

---

## Step 5.3 — Replace the primitive variable

Inside `main()`, find:

```cpp
int counter = 0;
```

Replace it with:

```cpp
Counter counter;
```

Now compile:

```bash
cmake --build build --target 05_counter
```

**It should fail!** That's expected. Read the error messages before fixing them.

Our existing callbacks expect an integer, but `counter` is now an object.

For example:

```cpp
counter++;
```

The compiler doesn't know how to increment a `Counter` object.

We haven't overloaded `operator++`.

And we don't need to.

We already have:

```cpp
counter.increment();
```

### Discussion

We could overload `operator++` for our class.

But should we?

For a counter, that might make sense.

For a deck of cards, what would `deck++` mean?

Just because C++ lets us overload an operator doesn't mean doing so improves the design.

---

## Step 5.4 — Fix the callbacks

Find:

```cpp
auto increment = Button("Increment", [&] {
    counter++;
});
```

Change it to:

```cpp
auto increment = Button("Increment", [&] {
    counter.increment();
});
```

Now change Decrement:

```cpp
auto decrement = Button("Decrement", [&] {
    counter.decrement();
});
```

And Reset:

```cpp
auto reset = Button("Reset", [&] {
    counter.reset();
});
```

Compile again:

```bash
cmake --build build --target 05_counter
```

We still have one problem.

Our renderer contains:

```cpp
text("Counter: " + std::to_string(counter))
```

But `std::to_string()` doesn't know how to convert a `Counter` object.

Change it to:

```cpp
text("Counter: " + std::to_string(counter.getValue()))
```

Now compile and run:

```bash
cmake --build build --target 05_counter
./build/05_counter
```

**The program should behave exactly as it did before.**

That's the important result.

We changed the internal architecture without changing the user experience.

---

## Step 5.5 — Why bother?

Compare our original code:

```cpp
auto increment = Button("Increment", [&] {
    counter++;
});
```

With our new code:

```cpp
auto increment = Button("Increment", [&] {
    counter.increment();
});
```

The difference seems trivial.

But consider a new requirement:

> The counter must never exceed 100 or fall below 0.

### Original design

We would need to modify every callback that changes the counter:

```cpp
auto increment = Button("Increment", [&] {
    if (counter < 100) {
        counter++;
    }
});
```

And:

```cpp
auto decrement = Button("Decrement", [&] {
    if (counter > 0) {
        counter--;
    }
});
```

As the application grows, these rules become scattered throughout the interface.

### Encapsulated design

We change only the `Counter` class:

```cpp
void increment() {
    if (value < 100) {
        value++;
    }
}

void decrement() {
    if (value > 0) {
        value--;
    }
}
```

**Our FTXUI code doesn't change at all.**

This is the real benefit of encapsulation.

We centralize the rules governing an object's state.

---

## Step 5.6 — Introduce composition

Look at our current application:

```cpp
int main() {

    Counter counter;

    auto screen = ScreenInteractive::TerminalOutput();

    auto increment = Button("Increment", [&] {
        counter.increment();
    });

    // ...
}
```

We now have two different kinds of objects cooperating.

```text
              APPLICATION
                   |
          +--------+--------+
          |                 |
          v                 v
       Counter         FTXUI Components
          |                 |
          |                 |
     Stores state      Handles input
     Enforces rules    Renders output
```

The FTXUI callbacks use the public methods of our `Counter` object.

Our `Counter` class knows absolutely nothing about FTXUI.

**That's exactly what we want.**

We can reuse `Counter` in a command-line program, a graphical application, or a unit test without changing its implementation.

---

## Step 5.7 — A small experiment

Let's prove that our class is independent of the interface.

Temporarily add this before creating the buttons:

```cpp
counter.increment();
counter.increment();
counter.increment();
```

Compile and run.

The interface should initially display:

```text
Counter: 3
```

Why?

Because the renderer displays the state of the existing `Counter` object.

The buttons aren't responsible for creating or initializing that state.

They're merely one way of modifying it.

Remove those three lines afterward.

---

## Step 5.8 — Student challenge

Modify the `Counter` class to support:

```cpp
void add(int amount);
void subtract(int amount);
```

Then create two additional buttons:

```cpp
auto addTen = Button("Add 10", [&] {
    counter.add(10);
});

auto subtractTen = Button("Subtract 10", [&] {
    counter.subtract(10);
});
```

**Requirements:**

1. The counter must stay between 0 and 100.
2. The `Counter` class must enforce those limits.
3. No button callback may directly access `value`.
4. The renderer must use `getValue()`.
5. The class must not include any FTXUI headers.

For an extra challenge, add:

```cpp
bool isMaximum() const;
bool isMinimum() const;
```

Use those methods to change the counter's displayed color.

---

## What we accomplished

Our program still looks and behaves the same, but the architecture has improved.

**Before:**

```text
Button
  |
  v
Directly modifies int
  |
  v
Renderer reads int
```

**After:**

```text
Button
  |
  v
Counter public method
  |
  v
Counter private state
  |
  v
Renderer calls getValue()
```

We have introduced encapsulation without inheritance, virtual functions, or abstract base classes.

And we have a genuine reason for doing it.

## Putting it Together

Here is the complete program at the end of this lesson. Compare it with yours before you commit.

### `examples/05_counter.cpp` (new)

<!-- file: examples/05_counter.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

class Counter {
private:
    int value;

public:
    Counter() : value(0) {
    }

    void increment() {
        value++;
    }

    void decrement() {
        value--;
    }

    void reset() {
        value = 0;
    }

    int getValue() const {
        return value;
    }
};

int main() {

    Counter counter;

    auto screen = ScreenInteractive::TerminalOutput();

    auto increment = Button("Increment", [&] {
        counter.increment();
    });

    auto decrement = Button("Decrement", [&] {
        counter.decrement();
    });

    auto reset = Button("Reset", [&] {
        counter.reset();
    });

    auto row = Container::Horizontal({
        increment,
        decrement,
    });

    auto buttons = Container::Vertical({
        row,
        reset,
    });

    auto renderer = Renderer(buttons, [&] {
        return vbox({
            text("GameOfWar 05") | bold | center,

            separator(),

            text("Counter: " + std::to_string(counter.getValue())) | center,

            separator(),

            hbox({
                increment->Render(),
                text("  "),
                decrement->Render(),
            }) | center,

            separatorEmpty(),

            reset->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

---

## Commit your work

```bash
git add .
git commit -m "Lesson 05: Counter class"
```

### Next: GameOfWar 06 — Moving Classes Into Header Files

Our `Counter` class currently lives inside `05_counter.cpp`.

That's acceptable for a small example, but what happens when multiple programs need the same class?

Next, we'll introduce:

```text
GameOfWar/
├── CMakeLists.txt
└── examples/
    ├── Counter.hpp        ← new: the class declaration
    ├── Counter.cpp        ← new: the method definitions
    ├── 05_counter.cpp
    └── 06_counter.cpp
```

We'll move the class into a reusable header, discuss `#pragma once`, and see how two `.cpp` files are compiled separately and linked into one program.

**One change, one compile, one concept at a time.**