# GameOfWar 04 — Multiple Buttons and Component Containers

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 04 - Component Containers
previous: examples/03_buttons.cpp
new_file: examples/04_containers.cpp
concepts:
  - Multiple components
  - Container::Horizontal
  - Container::Vertical
  - Keyboard focus
  - Composition
```

We currently have one button that increments a counter. Let's add a second button and discover why FTXUI needs component containers.

**Today's goal:** Three buttons, one counter, and keyboard navigation.

We'll make one change at a time, compiling and testing along the way.

## Step 4.1 — Copy the previous lesson

```bash
cp examples/03_buttons.cpp examples/04_containers.cpp
```

Compile the copied program before modifying it:

```bash
cmake -S . -B build
cmake --build build --target 04_containers
./build/04_containers
```

We should still have our working Increment button.

## Step 4.2 — Add a second button

Find:

```cpp
auto button = Button("Increment", [&] {
    counter++;
});
```

Replace it with:

```cpp
auto increment = Button("Increment", [&] {
    counter++;
});

auto decrement = Button("Decrement", [&] {
    counter--;
});
```

We now have two `Component` objects.

But how do we connect both to the renderer?

Previously, we used:

```cpp
auto renderer = Renderer(button, [&] {
```

We need something that can hold multiple components.

**Enter `Container`.**

## Step 4.3 — Create a horizontal container

Immediately after declaring the buttons, add:

```cpp
auto buttons = Container::Horizontal({
    increment,
    decrement
});
```

Now modify the renderer.

Change:

```cpp
auto renderer = Renderer(button, [&] {
```

to:

```cpp
auto renderer = Renderer(buttons, [&] {
```

And replace:

```cpp
button->Render(),
```

with:

```cpp
buttons->Render(),
```

That's it!

### Compile and run

```bash
cmake --build build --target 04_containers
./build/04_containers
```

You should now have something resembling:

```text
┌────────────────────────────────┐
│ GameOfWar 03                   │
├────────────────────────────────┤
│ Counter: 0                     │
├────────────────────────────────┤
│ [ Increment ] [ Decrement ]    │
└────────────────────────────────┘
```

The heading still says GameOfWar 03 because we copied the file. Change it to `"GameOfWar 04"` now.

### Experiment

Try moving between the buttons with the arrow keys (or Tab).

Activate each button using Enter.

Notice that FTXUI manages which button currently has focus.

**Question:** Did we write any code to detect arrow keys?

No.

The container handles navigation between its children.

---

## Step 4.4 — Understand the component hierarchy

Our application now looks like this:

```text
ScreenInteractive
        │
        ▼
     Renderer
        │
        ▼
Container::Horizontal
        │
        ├── Button: Increment
        │
        └── Button: Decrement
```

There are two distinct relationships worth understanding.

**The component hierarchy** determines how input events reach interactive components.

**The element hierarchy** (the `vbox`/`hbox`/`text` tree returned by our lambda) determines how things are displayed.

These hierarchies are related, but they aren't identical.

For example:

```cpp
auto buttons = Container::Horizontal({
    increment,
    decrement
});
```

This creates a component container.

Meanwhile:

```cpp
hbox({
    text("Hello"),
    text("World")
})
```

creates a horizontal arrangement of visual elements.

### Discussion

What's the difference between `hbox()` and `Container::Horizontal()`?

| `hbox()`                   | `Container::Horizontal()`       |
| -------------------------- | ------------------------------- |
| Arranges elements visually | Groups interactive components   |
| Produces an `Element`      | Produces a `Component`          |
| Does not manage focus      | Manages focus and navigation    |
| Used during rendering      | Used in the component hierarchy |

This distinction is fundamental to FTXUI.

---

## Step 4.5 — Add a Reset button

Now let's introduce a third button.

Add:

```cpp
auto reset = Button("Reset", [&] {
    counter = 0;
});
```

We want Increment and Decrement next to each other, but Reset underneath them.

Our layout should look something like:

```text
[ Increment ] [ Decrement ]

         [ Reset ]
```

We can accomplish this by composing containers.

Replace the existing container declaration:

```cpp
auto buttons = Container::Horizontal({
    increment,
    decrement
});
```

with:

```cpp
auto row = Container::Horizontal({
    increment,
    decrement
});

auto buttons = Container::Vertical({
    row,
    reset
});
```

Notice what happened.

We placed one container inside another.

**That's composition.**

We didn't create a subclass of `Container`.

We combined existing objects to produce more complicated behavior.

### Compile and run

```bash
cmake --build build --target 04_containers
./build/04_containers
```

Try navigating between all three buttons.

FTXUI handles the focus transitions.

### One small improvement

`buttons->Render()` draws the containers in their default arrangement, which is a little cramped. We can arrange the individual buttons ourselves.

Replace:

```cpp
buttons->Render(),
```

with:

```cpp
vbox({
    hbox({
        increment->Render(),
        text("  "),
        decrement->Render()
    }) | center,

    separatorEmpty(),

    reset->Render() | center

}),
```

Our **component hierarchy hasn't changed**, but our visual layout has.

That's worth emphasizing.

The `Container` objects manage interaction. The `vbox` and `hbox` elements control presentation.

---

## Step 4.6 — Complete checkpoint

At this point, `04_containers.cpp` should look like this:

```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    int counter = 0;

    auto screen = ScreenInteractive::TerminalOutput();

    // Individual components
    auto increment = Button("Increment", [&] {
        counter++;
    });

    auto decrement = Button("Decrement", [&] {
        counter--;
    });

    auto reset = Button("Reset", [&] {
        counter = 0;
    });

    // Compose components
    auto row = Container::Horizontal({
        increment,
        decrement
    });

    auto buttons = Container::Vertical({
        row,
        reset
    });

    // Render the interface
    auto renderer = Renderer(buttons, [&] {

        return vbox({
            text("GameOfWar 04") | bold | center,

            separator(),

            text("Counter: " + std::to_string(counter))
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

    screen.Loop(renderer);
}
```

Compile:

```bash
cmake --build build --target 04_containers
```

Run:

```bash
./build/04_containers
```

---

## Step 4.7 — Student challenge

Modify the program so that it supports five buttons:

| Button      | Action          |
| ----------- | --------------- |
| Increment   | `counter++`     |
| Decrement   | `counter--`     |
| Add 10      | `counter += 10` |
| Subtract 10 | `counter -= 10` |
| Reset       | `counter = 0`   |

Arrange them like this:

```text
┌─────────────────────────────────┐
│          GameOfWar 04           │
├─────────────────────────────────┤
│                                 │
│           Counter: 0            │
│                                 │
│   [ Increment ] [ Decrement ]   │
│                                 │
│   [  Add 10  ] [ Subtract 10 ]  │
│                                 │
│            [ Reset ]            │
│                                 │
└─────────────────────────────────┘
```

Use nested horizontal and vertical containers. Every button must be reachable with the keyboard. If one is drawn but you can't reach it, you forgot to add it to a container.

**Constraint:** Do not create a class yet.

The goal is to understand how FTXUI components cooperate before we start designing abstractions around them.

---

## Putting it Together

Here is the complete program at the end of this lesson. Compare it with yours before you commit.

### `examples/04_containers.cpp` (new)

<!-- file: examples/04_containers.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    int counter = 0;

    auto screen = ScreenInteractive::TerminalOutput();

    // Individual components
    auto increment = Button("Increment", [&] {
        counter++;
    });

    auto decrement = Button("Decrement", [&] {
        counter--;
    });

    auto reset = Button("Reset", [&] {
        counter = 0;
    });

    // Compose components
    auto row = Container::Horizontal({
        increment,
        decrement,
    });

    auto buttons = Container::Vertical({
        row,
        reset,
    });

    // Render the interface
    auto renderer = Renderer(buttons, [&] {
        return vbox({
            text("GameOfWar 04") | bold | center,

            separator(),

            text("Counter: " + std::to_string(counter)) | center,

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
git commit -m "Lesson 04: containers and focus"
```

---

## A design question before Lesson 05

Consider this code:

```cpp
auto increment = Button("Increment", [&] {
    counter++;
});

auto decrement = Button("Decrement", [&] {
    counter--;
});

auto reset = Button("Reset", [&] {
    counter = 0;
});
```

Every button directly modifies the same variable.

That's manageable with three buttons.

But imagine that our application has twenty buttons, each modifying different aspects of a deck of cards.

We could end up with callbacks scattered throughout the UI, all manipulating application data.

That's where our next lesson will take us.

**GameOfWar 05 — Introducing a `Counter` Class**

We'll move the counter's state and operations into a proper C++ class, leaving the FTXUI code responsible only for interaction and presentation.

That will be our first meaningful application of **encapsulation and composition**, rather than inheritance for inheritance's sake.