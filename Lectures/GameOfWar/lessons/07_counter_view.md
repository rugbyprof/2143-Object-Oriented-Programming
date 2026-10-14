# GameOfWar 07 — Composition: Building a Reusable FTXUI View

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 07 - Composition and UI Classes
previous: examples/06_counter.cpp
new_file: examples/07_counter_view.cpp
concepts:
  - Composition vs inheritance
  - References to existing objects
  - Member initialization lists
  - Component ownership
  - Separating application logic from presentation
```

We now have a reusable `Counter` class, but our `main()` function still creates buttons, manages containers, defines callbacks, and renders the interface.

That's a lot of responsibility for one function.

**Our goal:** Move the FTXUI interface into its own class without changing how the application behaves.

We're not going to inherit from FTXUI. Instead, we'll build a class that *uses* FTXUI components.

And we're not going to write everything at once.

## Step 7.1 — Copy our working application

```bash
cp examples/06_counter.cpp examples/07_counter_view.cpp
```

The new program also uses `Counter.cpp`. At the bottom of `CMakeLists.txt`, under the line you added in Lesson 06, add:

```cmake
target_sources(07_counter_view PRIVATE examples/Counter.cpp)
```

Change the title text to `"GameOfWar 07"`, then compile:

```bash
cmake -S . -B build
cmake --build build --target 07_counter_view
./build/07_counter_view
```

We should have the same working application from Lesson 06.

**Checkpoint:** Nothing new happens yet. We've simply established a working starting point.

---

## Step 7.2 — Introduce an empty `CounterView` class

We'll define our new class directly inside `07_counter_view.cpp`. Get it working first; splitting into files is easy afterward.

Above `main()`, add:

```cpp
class CounterView {
private:
    Counter& counter;

public:
    CounterView(Counter& c) : counter(c) {}
};
```

Inside `main()`, immediately after:

```cpp
Counter counter;
```

Add:

```cpp
CounterView view(counter);
```

Compile:

```bash
cmake --build build --target 07_counter_view
```

It should compile successfully.

### Stop and discuss

Look at:

```cpp
Counter& counter;
```

This is a reference to an existing `Counter` object.

We're not creating a second counter.

We're not copying the counter.

Our view simply refers to the same object that `main()` created.

And notice the constructor:

```cpp
CounterView(Counter& c) : counter(c) {}
```

The initialization list binds our reference member to the existing object.

**Question:** Why can't we simply assign the reference inside the constructor body?

Because a reference must be bound to an object the moment it is created, and can never be re-bound. By the time the constructor body runs, every member already exists, so it's too late. The initialization list is the only place to do it.

### Is this inheritance?

No.

There is no:

```cpp
class CounterView : public Counter
```

A `CounterView` is not a specialized counter.

It is an object that **uses a counter**.

That's the relationship we want.

---

## Step 7.3 — Move one button into the class

Let's start with only the Increment button.

Modify `CounterView`:

```cpp
class CounterView {
private:
    Counter& counter;

    Component increment;

public:
    CounterView(Counter& c) : counter(c) {

        increment = Button("Increment", [this] {
            counter.increment();
        });
    }
};
```

Compile again:

```bash
cmake --build build --target 07_counter_view
```

We haven't removed anything from `main()` yet.

That means we temporarily have two Increment buttons: one created in `main()` and another stored inside `CounterView`.

Only the original button is displayed.

That's fine for this checkpoint.

### Discussion: What is `[this]`?

Previously, we used:

```cpp
[&] {
    counter.increment();
}
```

Now we're using:

```cpp
[this] {
    counter.increment();
}
```

The lambda captures the pointer to the current `CounterView` object.

Through that pointer, it accesses the view's `counter` member.

This is an important distinction:

```cpp
[this]
```

does not create a copy of the `CounterView`.

It allows the callback to access the existing object.

**Lifetime warning:** The callback must not outlive the `CounterView` object whose `this` pointer it captured.

**Copy warning:** The same problem happens if a `CounterView` is *copied*. The copy's buttons still hold the *original's* `this`. In this course we create each view once and never copy it.

---

## Step 7.4 — Add the other buttons

Now add two more members:

```cpp
Component decrement;
Component reset;
```

And initialize them in the constructor body:

```cpp
decrement = Button("Decrement", [this] {
    counter.decrement();
});

reset = Button("Reset", [this] {
    counter.reset();
});
```

Our class now looks like this:

```cpp
class CounterView {
private:
    Counter& counter;

    Component increment;
    Component decrement;
    Component reset;

public:
    CounterView(Counter& c) : counter(c) {

        increment = Button("Increment", [this] {
            counter.increment();
        });

        decrement = Button("Decrement", [this] {
            counter.decrement();
        });

        reset = Button("Reset", [this] {
            counter.reset();
        });
    }
};
```

Compile again.

**Checkpoint:** We've moved button construction into the class, but the original interface in `main()` still works.

Next, we'll make the class responsible for its own layout.

---

## Step 7.5 — Add a `build()` method

We want our view to provide a single method:

```cpp
Component build();
```

Its job is to assemble the interface and return a component that FTXUI can display.

Add this method inside `CounterView`, under `public:`:

```cpp
Component build() {

    auto row = Container::Horizontal({
        increment,
        decrement
    });

    auto buttons = Container::Vertical({
        row,
        reset
    });

    return Renderer(buttons, [this] {

        return vbox({
            text("GameOfWar 07") | bold | center,

            separator(),

            text("Counter: " +
                 std::to_string(counter.getValue()))
                | center,

            separator(),

            hbox({
                increment->Render(),
                text("  "),
                decrement->Render()
            }) | center,

            separatorEmpty(),

            reset->Render() | center,

        }) | border;
    });
}
```

Compile again.

We now have a view that can construct its own interface.

Notice the two kinds of composition happening here.

**C++ object composition:**

```cpp
Component increment;
Component decrement;
Component reset;
```

Our class stores FTXUI components as members.

**FTXUI component composition:**

```cpp
auto buttons = Container::Vertical({
    row,
    reset
});
```

We assemble smaller components into a larger component.

Neither requires inheritance.

---

## Step 7.6 — Simplify `main()`

Now we're ready to remove the original UI code from `main()`.

Replace the entire `main()` function with:

```cpp
int main() {

    Counter counter;

    CounterView view(counter);

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(view.build());
}
```

Compile:

```bash
cmake --build build --target 07_counter_view
```

Run:

```bash
./build/07_counter_view
```

The interface should work exactly as before.

We have changed the architecture without changing the behavior.

**That's our major checkpoint.**

---

## Step 7.7 — Examine the architecture

Our application now looks like this:

```text
                  main()
                    |
                    |
          +---------+---------+
          |                   |
          v                   v
       Counter           CounterView
          ^                   |
          |                   |
          +----- uses --------+
                              |
                              v
                       FTXUI Components
                              |
                   +----------+----------+
                   |          |          |
                   v          v          v
                Increment  Decrement   Reset
```

Our responsibilities are now separated:

| Class         | Responsibility                              |
| ------------- | ------------------------------------------- |
| `Counter`     | Store state and enforce counter rules       |
| `CounterView` | Create UI components and connect callbacks  |
| `main()`      | Construct objects and start the application |

Notice that `Counter` doesn't know anything about `CounterView`.

And neither class needs to inherit from the other.

---

## Step 7.8 — Why not inherit from FTXUI?

We could create something like:

```cpp
class CounterView : public ComponentBase {
    // ...
};
```

FTXUI supports custom components through inheritance.

But we don't need that functionality yet.

Our `CounterView` already works by composing existing components and returning a `Component`.

Compare the approaches:

**Inheritance:**

```cpp
class CounterView : public ComponentBase
```

We're saying:

> CounterView is an FTXUI component.

**Composition:**

```cpp
class CounterView {
private:
    Component increment;
    Component decrement;
    Component reset;
};
```

We're saying:

> CounterView uses FTXUI components to build an interface.

For our current requirements, composition is simpler.

We don't need to override rendering or event-handling methods.

We simply assemble existing components.

---

## Step 7.9 — A subtle lifetime issue

Look at our `build()` method:

```cpp
return Renderer(buttons, [this] {
    // ...
});
```

The returned renderer retains a callback that accesses `CounterView` through `this`.

This works because `view` remains alive throughout:

```cpp
screen.Loop(view.build());
```

But consider this function:

```cpp
Component makeCounterView(Counter& counter) {
    CounterView view(counter);
    return view.build();
}
```

That would be dangerous.

The local `view` is destroyed when the function returns.

The returned component still contains callbacks that refer to the destroyed object.

**Question:** What C++ concept does this demonstrate?

Object lifetime.

Composition and lambda captures are powerful, but they don't eliminate the need to understand ownership and lifetimes.

---

## Step 7.10 — Student challenge

Extend `CounterView` with two additional buttons:

```text
[ Increment ] [ Decrement ]

[  Add 10   ] [ Subtract 10 ]

          [ Reset ]
```

Requirements:

1. Add two new `Component` members.
2. Initialize them in the constructor.
3. Use `Counter::add()` and `Counter::subtract()` from the Lesson 05 challenge. Add them to `Counter.hpp` / `Counter.cpp` if you haven't already.
4. Modify `build()` to arrange the buttons.
5. Do not change `main()`.
6. Do not modify `Counter` unless those methods are missing.

**The most important requirement is number 5.**

If our architecture is doing its job, adding interface functionality shouldn't require rewriting the application entry point.

---

## What we accomplished

We've now introduced an important reusable pattern:

```cpp
class SomeView {
private:
    SomeModel& model;

    Component controls;

public:
    SomeView(SomeModel& model);

    Component build();
};
```

This isn't necessarily a formal *Facade* pattern.

It's better described as a **compositional view wrapper**.

It hides the details of assembling the FTXUI interface while exposing a simple method for constructing the finished component.

The design is useful because we can apply it repeatedly.

For example:

```cpp
CounterView
DeckView
HandView
CardTableView
```

Each view can manage its own FTXUI components while referring to the application data it needs.

## Putting it Together

Here is the complete program at the end of this lesson. Compare it with yours before you commit.

### `examples/07_counter_view.cpp` (new)

<!-- file: examples/07_counter_view.cpp -->
```cpp
#include "Counter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

class CounterView {
private:
    Counter& counter;

    Component increment;
    Component decrement;
    Component reset;

public:
    CounterView(Counter& c) : counter(c) {

        increment = Button("Increment", [this] {
            counter.increment();
        });

        decrement = Button("Decrement", [this] {
            counter.decrement();
        });

        reset = Button("Reset", [this] {
            counter.reset();
        });
    }

    Component build() {

        auto row = Container::Horizontal({
            increment,
            decrement,
        });

        auto buttons = Container::Vertical({
            row,
            reset,
        });

        return Renderer(buttons, [this] {
            return vbox({
                text("GameOfWar 07") | bold | center,

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
    }
};

int main() {

    Counter counter;

    CounterView view(counter);

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(view.build());
}
```

<details>
<summary><code>examples/Counter.hpp</code> (unchanged)</summary>

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
<summary><code>examples/Counter.cpp</code> (unchanged)</summary>

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
git commit -m "Lesson 07: CounterView"
```

This is the last lesson in `examples/`.

### Next: GameOfWar 08 — Starting the War Application

We're ready to move beyond counters. From Lesson 08 on, we stop making a new file per lesson. Instead we build **one application**, a game of War, in `src/main.cpp`, and add classes to `include/` and `src/` as we need them.

We'll start with a `Card` class: **52 cards numbered 0–51**, with rank and suit calculated from the card ID.

No enumerations. No unnecessary inheritance. And no fifty-two individually allocated card objects just to represent a deck.