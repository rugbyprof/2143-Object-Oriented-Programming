# TinyChunks 03 — Buttons, Callbacks, and State

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 03 - Buttons and Callbacks
previous: examples/02_renderer.cpp
new_file: examples/03_buttons.cpp
concepts:
  - FTXUI Components
  - Button Components
  - Lambda Callbacks
  - State Modification
  - Event-Driven Programming
  - Component Rendering
```

In the previous lesson, we learned that a renderer can read variables captured by a lambda.

However, our application had a rather serious limitation:

**It didn't actually do anything.**

We could display a counter, but the user couldn't change it.

Today, we'll introduce a button that modifies our counter and causes the display to update.

Our goal is simple:

```text
┌─────────────────────────┐
│ TinyChunks 03           │
├─────────────────────────┤
│                         │
│ Counter: 0              │
│                         │
│ [ Increment ]           │
│                         │
└─────────────────────────┘
```

Clicking the button or activating it with the keyboard should increase the counter.

No inheritance. No complicated class hierarchy. Just a button.

---

### Step 3.1 — Copy the previous example

```bash
cp examples/02_renderer.cpp examples/03_buttons.cpp
```

Clean it up so it matches this starting point (counter starts at 0, title says 03):

```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    int counter = 0;

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("TinyChunks 03") | bold,
            separator(),
            text("Counter: " + std::to_string(counter)),
        }) | border;
    });

    screen.Loop(renderer);
}
```

Compile and run:

```bash
cmake -S . -B build
cmake --build build --target 03_buttons
./build/03_buttons
```

We haven't changed the functionality yet.

That's intentional.

**Rule #1: Always begin with something that works.**

---

## Step 3.2 — Create a button

FTXUI provides a `Button()` function that creates an interactive component.

Its basic form is:

```cpp
Button("Label", callback);
```

The callback is a function that executes when the button is activated.

Add this immediately after creating `screen`:

```cpp
auto button = Button("Increment", [&] {
    counter++;
});
```

That's it.

We have created a button.

But we haven't displayed it yet.

### Stop and discuss

Consider:

```cpp
[&] {
    counter++;
}
```

This is a lambda function.

It has:

- A capture list: `[&]`
- No parameter list. `()` is optional when a lambda takes no parameters.
- A function body: `{ counter++; }`

The lambda captures `counter` by reference.

When executed, it modifies the original variable.

**Question 1:** What happens if we change `[&]` to `[=]`?

**Question 2:** Does creating the button immediately execute the lambda?

**Question 3:** Who is responsible for calling the lambda?

That last question is important.

The callback is executed by the FTXUI button component when the user activates it.

We don't call it ourselves.

This is our first introduction to **event-driven programming**.

---

## Step 3.3 — Display the button

Now we need to include the button in our interface.

You might be tempted to write:

```cpp
auto renderer = Renderer([&] {
    return vbox({
        text("Counter: " + std::to_string(counter)),
        button->Render(),
    });
});
```

That compiles, and the button even *appears*. But pressing Enter or clicking does nothing.

Why? `button->Render()` only asks the button what it looks like. FTXUI delivers keyboard and mouse events by walking a tree of **components**. Our renderer has no children, so the events never reach the button.

The fix is to construct the renderer with the button as its child.

Change:

```cpp
auto renderer = Renderer([&] {
```

to:

```cpp
auto renderer = Renderer(button, [&] {
```

Then add:

```cpp
button->Render(),
```

to the `vbox`.

Our renderer becomes:

```cpp
auto renderer = Renderer(button, [&] {
    return vbox({
        text("TinyChunks 03") | bold,

        separator(),

        text("Counter: " + std::to_string(counter)),

        separator(),

        button->Render(),

    }) | border;
});
```

### Compile and run

```bash
cmake --build build --target 03_buttons
./build/03_buttons
```

You should now see an interactive button.

Activate it using Enter or your mouse.

The counter should increase.

**Stop here and let students experiment.**

---

## Step 3.4 — Understand what just happened

This is arguably the most important concept in the lesson.

Our application now follows this sequence:

```text
       USER
        │
        │ Presses Enter
        ▼
  ┌───────────────┐
  │ FTXUI Button  │
  └───────┬───────┘
          │
          │ Executes callback
          ▼
  ┌───────────────┐
  │  counter++    │
  └───────┬───────┘
          │
          │ State changed
          ▼
  ┌───────────────┐
  │   Renderer    │
  └───────┬───────┘
          │
          │ Reads new value
          ▼
  ┌───────────────┐
  │   Terminal    │
  │  Counter: 1   │
  └───────────────┘
```

Notice what we **didn't** do.

We didn't write:

```cpp
while (true) {
    clearScreen();
    printCounter();
    checkKeyboard();
}
```

FTXUI handles the event loop and requests rendering when appropriate.

Our responsibility is to describe the interface and provide callbacks that modify state.

This is a substantial architectural difference from a traditional console program.

---

## Step 3.5 — The complete program

At this checkpoint, `03_buttons.cpp` should look like this:

```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    // Application state
    int counter = 0;

    // Interactive terminal
    auto screen = ScreenInteractive::TerminalOutput();

    // Interactive component
    auto button = Button("Increment", [&] {
        counter++;
    });

    // Renderer with button as child
    auto renderer = Renderer(button, [&] {

        return vbox({
            text("TinyChunks 03") | bold,

            separator(),

            text("Counter: " + std::to_string(counter)),

            separator(),

            button->Render(),

        }) | border;
    });

    // Start event loop
    screen.Loop(renderer);
}
```

That's our first complete interactive FTXUI application.

And it's only about 40 lines of code.

---

## Step 3.6 — Student experiments

Before we move forward, have students make three small modifications.

### Experiment A — Change the increment

Instead of:

```cpp
counter++;
```

Change it to:

```cpp
counter += 5;
```

Compile and run.

**Question:** Does the renderer need to change?

No.

The renderer doesn't care how the counter changes. It only reads its current value.

That's a useful separation of responsibilities.

### Experiment B — Add a maximum value

Modify the callback:

```cpp
auto button = Button("Increment", [&] {
    if (counter < 10) {
        counter++;
    }
});
```

Compile and run.

**Question:** Should the button know the maximum allowed counter value?

For this small example, that's fine.

But what happens when we have five different buttons modifying the same variable?

Where should the rule live?

We're beginning to discover why a `Counter` class might be useful.

### Experiment C — Add conditional formatting

Modify the counter display:

```cpp
text("Counter: " + std::to_string(counter))
    | color(counter >= 10 ? Color::Red : Color::Green),
```

Compile and run.

Now the counter changes color when it reaches 10.

**Question:** Does changing the color modify the counter?

No.

We're changing its presentation, not its value.

That distinction will become extremely important when we introduce our card classes.

---

## Step 3.7 — A small challenge

Without looking up a complete solution, modify the program so that:

1. The counter starts at 0.
2. Clicking Increment increases it by 1.
3. The counter cannot exceed 20.
4. The counter displays green when below 10.
5. The counter displays yellow from 10 through 19.
6. The counter displays red at 20.

**Bonus:** Change the button label to `"Maximum Reached"` when the counter reaches 20.

For the bonus, investigate whether the button label can be supplied dynamically or whether a different rendering approach is needed. (Hint: look at `ButtonOption` in the FTXUI docs, or try rendering a different element when the maximum is reached.)

Don't introduce another class yet.

We're still learning how FTXUI works.

---

## What we've learned

We now have three distinct concepts:

| Concept   | Example       | Responsibility                 |
| --------- | ------------- | ------------------------------ |
| State     | `int counter` | Stores application data        |
| Component | `Button()`    | Handles interaction            |
| Renderer  | `Renderer()`  | Describes the visual interface |

These concepts work together, but they are not the same thing.

This distinction is the foundation of the larger application we're building.

---

## Commit your work

```bash
git add .
git commit -m "Lesson 03: buttons and callbacks"
```

## Next: TinyChunks 04 — Multiple Buttons and Component Containers

Our next problem is straightforward.

We want:

```text
┌─────────────────────────────┐
│ TinyChunks 04               │
├─────────────────────────────┤
│                             │
│ Counter: 5                  │
│                             │
│ [ Increment ] [ Decrement ] │
│                             │
│ [ Reset ]                   │
│                             │
└─────────────────────────────┘
```

That introduces `Container::Horizontal`, `Container::Vertical`, and keyboard focus.

It also gives us our first genuinely interesting composition example.

**Before moving on, make sure you can explain why `Renderer(button, ...)` works differently from simply calling `button->Render()` inside an unrelated renderer.**

That's the distinction between *drawing a component* and *integrating an interactive component into the event-handling hierarchy*.

And it's exactly the kind of distinction that makes FTXUI click.