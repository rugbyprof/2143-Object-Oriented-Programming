# GameOfWar 06 — Separating Classes Into Header and Implementation Files

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 06 - Header and Implementation Files
previous: examples/05_counter.cpp
new_files:
  - examples/06_counter.cpp
  - examples/Counter.hpp
  - examples/Counter.cpp
concepts:
  - Header files
  - Implementation files
  - "#pragma once"
  - Compiling vs linking
  - Building one program from several .cpp files
```

Our `Counter` class works, but it's defined inside the same `.cpp` file as our FTXUI application.

That's fine for a small example. But suppose several programs need `Counter`. Copying the class into every file would be a terrible solution. Fix a bug in one copy and the others still have it.

Let's separate the class's **interface** (what it can do) from its **implementation** (how it does it).

## Step 6.1 — Copy the working program

```bash
cp examples/05_counter.cpp examples/06_counter.cpp
```

Change the title text to `"GameOfWar 06"`, then compile:

```bash
cmake -S . -B build
cmake --build build --target 06_counter
./build/06_counter
```

Verify that everything still works.

---

## Step 6.2 — Create `Counter.hpp`

Create `examples/Counter.hpp`:

```cpp
#pragma once

class Counter {
private:
    int value;

public:
    Counter();

    void increment();
    void decrement();
    void reset();

    int getValue() const;
};
```

### What changed?

Previously, we defined the methods inside the class:

```cpp
void increment() {
    value++;
}
```

Now the header has only a **declaration**:

```cpp
void increment();
```

The declaration tells the compiler that the method exists and how to call it.

The **definition** tells the compiler what the method actually does.

**Question:** Can we compile a program that calls `increment()` when only its declaration is available?

Yes, as long as the **linker** can find the definition later. This distinction will become important shortly.

### What does `#pragma once` do?

It prevents the same header from being included more than once in a single `.cpp` file. That can easily happen once headers start including other headers.

Without that protection, the compiler would see `class Counter` twice and report a redefinition error.

You'll also see the traditional **include guard**, which does the same job:

```cpp
#ifndef COUNTER_HPP
#define COUNTER_HPP

class Counter {
    // ...
};

#endif
```

For GameOfWar, we'll use `#pragma once`.

---

## Step 6.3 — Use the header in `06_counter.cpp`

At the top of `examples/06_counter.cpp`, add:

```cpp
#include "Counter.hpp"
```

Now **delete** the original `class Counter { ... };` from `06_counter.cpp`.

Compile:

```bash
cmake --build build --target 06_counter
```

**It fails, but not where you might expect.** Look closely at the error. It will look something like:

```text
Undefined symbols for architecture arm64:
  "Counter::increment()", referenced from: ...
ld: symbol(s) not found
```

or on Linux/Windows:

```text
undefined reference to `Counter::increment()'
```

Notice the `ld`. That's the **linker**, not the compiler.

`06_counter.cpp` *compiled* successfully because the header told the compiler every method exists. But when the linker tried to assemble the final program, it couldn't find the method **definitions** anywhere. We deleted them and haven't written them anywhere else yet.

**Compiler error:** "I don't know what this is." **Linker error:** "You told me this exists, but I can't find it."

---

## Step 6.4 — Create `Counter.cpp`

Create `examples/Counter.cpp`:

```cpp
#include "Counter.hpp"

Counter::Counter() : value(0) {
}

void Counter::increment() {
    value++;
}

void Counter::decrement() {
    value--;
}

void Counter::reset() {
    value = 0;
}

int Counter::getValue() const {
    return value;
}
```

Notice the scope resolution operator:

```cpp
void Counter::increment()
```

The `Counter::` tells the compiler that this `increment()` belongs to the `Counter` class, not a free function that happens to have the same name.

### Why isn't `Counter.cpp` its own program?

Look at our CMake loop from Lesson 01:

```cmake
file(GLOB EXAMPLES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/examples/[0-9]*.cpp"
)
```

The pattern `[0-9]*.cpp` only matches files whose names **start with a digit**. `06_counter.cpp` matches. `Counter.cpp` doesn't, so CMake won't try to turn it into a program. That's good, because it has no `main()`.

---

## Step 6.5 — Tell CMake to build with both files

The linker still can't find the definitions, because nothing tells CMake that `06_counter` needs `Counter.cpp`.

At the **bottom** of `CMakeLists.txt`, add:

```cmake
# Lessons 06-07: these programs are built from two .cpp files
target_sources(06_counter PRIVATE examples/Counter.cpp)
```

This says: "the `06_counter` program is built from `06_counter.cpp` **and** `Counter.cpp`."

### Compile and run

```bash
cmake -S . -B build
cmake --build build --target 06_counter
./build/06_counter
```

Our program works exactly as before, but it's now built from two separately compiled files.

---

## Step 6.6 — What did CMake just do?

```text
            Counter.hpp
          (included by both)
           │           │
           ▼           ▼
   Counter.cpp     06_counter.cpp
       │                 │
    compile           compile
       │                 │
       ▼                 ▼
   Counter.o       06_counter.o
       │                 │
       └──────┬──────────┘
              │
            link
              │
              ▼
         06_counter   (the program)
```

The important points:

1. **Header files are never compiled on their own.** They're pasted into each `.cpp` file that `#include`s them.
2. **Each `.cpp` file is compiled separately** into an object file (`.o`).
3. **The linker** combines the object files into one program and connects each call to its definition.

That's why you can change `Counter.cpp` and only that file gets recompiled. Try it: add a blank line to `Counter.cpp`, rebuild, and watch which files the build output mentions.

---

## Step 6.7 — Verify the separation

Open `examples/Counter.cpp`. It contains:

```cpp
#include "Counter.hpp"
```

and **nothing related to FTXUI**.

Now open `examples/06_counter.cpp`. It includes both our class and FTXUI:

```cpp
#include "Counter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
```

This is exactly what we want:

```text
┌────────────────────────────┐
│      FTXUI Application     │
│      06_counter.cpp        │
└─────────────┬──────────────┘
              │ uses
              ▼
┌────────────────────────────┐
│        Counter class       │
│  Counter.hpp / Counter.cpp │
└────────────────────────────┘
```

**Dependency direction matters.** The application depends on the class. The class does not depend on the application. A reusable class shouldn't require a terminal UI library just to compile.

---

## Step 6.8 — Student challenge

Add a new method to `Counter`:

```cpp
void setValue(int newValue);
```

Requirements:

1. Declare the method in `Counter.hpp`.
2. Define the method in `Counter.cpp`.
3. Restrict the value to the range 0–100.
4. Add a button in `06_counter.cpp` that calls `counter.setValue(50)`.
5. Compile and run.

Then deliberately **delete the definition** from `Counter.cpp` while leaving the declaration in the header. Rebuild.

Is that a compiler error or a linker error? How can you tell from the message?

If you did the Lesson 05 challenge (`add()` / `subtract()`), move those methods into `Counter.hpp` / `Counter.cpp` too.

---

## Where we are now

| Lesson | Major concept                               |
| ------ | ------------------------------------------- |
| 01     | Elements and layouts                        |
| 02     | Renderers and lambdas                       |
| 03     | Buttons and callbacks                       |
| 04     | Component containers                        |
| 05     | Encapsulation                               |
| **06** | **Header/implementation files and linking** |

```text
GameOfWar/
├── CMakeLists.txt
└── examples/
    ├── 01_box.cpp
    ├── 02_renderer.cpp
    ├── 03_buttons.cpp
    ├── 04_containers.cpp
    ├── 05_counter.cpp
    ├── 06_counter.cpp
    ├── Counter.hpp
    └── Counter.cpp
```

## Putting it Together

Here is the complete program at the end of this lesson. Compare it with yours before you commit.

### `examples/06_counter.cpp` (new)

<!-- file: examples/06_counter.cpp -->
```cpp
#include "Counter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

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
            text("GameOfWar 06") | bold | center,

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

<details>
<summary><code>examples/Counter.hpp</code> (new)</summary>

<!-- file: examples/Counter.hpp -->
```cpp
#pragma once

class Counter {
private:
    int value;

public:
    Counter();

    void increment();
    void decrement();
    void reset();

    int getValue() const;
};
```

</details>

<details>
<summary><code>examples/Counter.cpp</code> (new)</summary>

<!-- file: examples/Counter.cpp -->
```cpp
#include "Counter.hpp"

Counter::Counter() : value(0) {
}

void Counter::increment() {
    value++;
}

void Counter::decrement() {
    value--;
}

void Counter::reset() {
    value = 0;
}

int Counter::getValue() const {
    return value;
}
```

</details>

---

## Commit your work

```bash
git add .
git commit -m "Lesson 06: header and implementation files"
```

### Next: GameOfWar 07 — A Reusable FTXUI View Class

Now that `Counter` is separate, we can address another problem: our entire FTXUI interface still lives inside `main()`.

We'll introduce a `CounterView` class that **contains and composes FTXUI components rather than inheriting from them**. The goal is to reduce `main()` to:

```cpp
int main() {
    Counter counter;
    CounterView view(counter);

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(view.build());
}
```

That raises the architectural question at the heart of this course:

**When should we wrap a library's classes, and when should we inherit from them?**
