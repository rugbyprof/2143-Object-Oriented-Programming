# TinyChunks 02 — From Static Elements to Interactive Rendering

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 02 - Interactive Rendering
previous: examples/01_box.cpp
new_file: examples/02_renderer.cpp
concepts:
  - ScreenInteractive
  - Renderer
  - Lambda Functions
  - Captures
  - Application State
```

We have boxes, text, borders, and layouts. Now let's introduce **FTXUI's rendering loop and lambda functions**.

We're going to make the smallest possible changes and compile after each one.

## Step 2.1 — Create `02_renderer.cpp`

This time we'll start a new file instead of editing `01_box.cpp`. Lesson 01 stays runnable as a reference.

Create `examples/02_renderer.cpp`:

```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([] {
        return vbox({
            text("TinyChunks 02") | bold,
            separator(),
            text("Hello from a renderer!"),
        }) | border;
    });

    screen.Loop(renderer);
}
```

### Compile and run

```bash
cmake -S . -B build
cmake --build build --target 02_renderer
./build/02_renderer
```

Press **Ctrl+C** to exit.

### Stop and discuss

We introduced three new concepts.

**1. `ScreenInteractive`**

```cpp
auto screen = ScreenInteractive::TerminalOutput();
```

Unlike the static `Screen` from lesson 1, this manages an interactive terminal session.

**2. `Renderer`**

```cpp
auto renderer = Renderer([] {
    return text("Hello");
});
```

The renderer takes a function and calls it every time the screen needs to be redrawn. That function is written as a **lambda**, an unnamed function written inline:

```cpp
[] { return text("Hello"); }
```

The `[]` is the *capture list* (empty for now) and `{ ... }` is the body.

**3. `screen.Loop()`**

```cpp
screen.Loop(renderer);
```

FTXUI manages the event loop. We no longer explicitly call `Render()` and `Print()`.

**Question:** Why does the lambda return an `Element` instead of printing text directly?

Because FTXUI decides *when* to draw. It may call our lambda many times, for example after a key press or a terminal resize. Our job is only to describe what the screen should look like right now.

---

## Step 2.2 — Introduce State

Now let's give the renderer something to display.

Add this as the first line inside `main()`:

```cpp
int counter = 42;
```

Change:

```cpp
auto renderer = Renderer([] {
```

to:

```cpp
auto renderer = Renderer([&] {
```

And add the counter to the display:

```cpp
auto renderer = Renderer([&] {
    return vbox({
        text("TinyChunks 02") | bold,
        separator(),
        text("Counter: " + std::to_string(counter)),
    }) | border;
});
```

### Compile and run again

```bash
cmake --build build --target 02_renderer
./build/02_renderer
```

You should see:

```text
┌──────────────────┐
│TinyChunks 02     │
├──────────────────┤
│Counter: 42       │
└──────────────────┘
```

### Stop and discuss

Here's the important question:

**How does the lambda access `counter` when `counter` isn't passed as an argument?**

Because of:

```cpp
[&]
```

This captures the variables the lambda uses from the surrounding scope **by reference**. Without a capture, the compiler would refuse to let the lambda see `counter` at all. Try changing `[&]` back to `[]` and read the error.

The renderer can read the current value of `counter`.

Compare:

```cpp
[=]   // Capture used surrounding variables by value
[&]   // Capture used surrounding variables by reference
```

Neither form copies every local variable; only the variables the lambda actually uses are captured.

This is the same idea as passing a function parameter by reference versus by value.

---

## Step 2.3 — A Small Experiment

Change:

```cpp
int counter = 42;
```

to:

```cpp
int counter = 0;
```

Then add this line after the renderer is created, just before `screen.Loop()`:

```cpp
counter = 100;
```

Compile and run.

**Question:** What value appears on the screen?

It should be `100`.

Why?

Because the renderer's lambda reads the current value of `counter` when invoked.

It doesn't save the value that existed when the renderer was created.

### Experiment 2

Change:

```cpp
Renderer([&] {
```

to:

```cpp
Renderer([=] {
```

Compile and run again.

**Question:** What value appears now?

It should be `0`.

The lambda captured a copy of `counter` when it was created, before the assignment to `100`.

This is a particularly useful demonstration of **reference versus value semantics**.

Change it back to `[&]` before moving on. Every lesson from here on uses `[&]` or `[this]`.

---

## Step 2.4 — Student Challenge

Without looking up the solution, modify the renderer to display:

```text
┌────────────────────────────┐
│ TinyChunks 02              │
├────────────────────────────┤
│                            │
│ Counter: 100               │
│ Counter doubled: 200       │
│ Counter squared: 10000     │
│                            │
└────────────────────────────┘
```

Requirements:

1. Store only one integer variable named `counter`.
2. Calculate the doubled and squared values inside the renderer.
3. Do not create additional global variables.
4. Use `vbox`, `text`, `separator`, and `border`.
5. Explain why changing `counter` before entering the event loop changes the displayed values when using `[&]`.

**Bonus question:** What would happen if the renderer outlived the variable it captured by reference?

That's an introduction to object lifetimes and dangling references.

---

## What we accomplished

Our application now has:

```text
Application State
       │
       ▼
Lambda Function
       │
       ▼
FTXUI Renderer
       │
       ▼
Terminal Display
```

But something is missing.

**The user cannot change the counter.**

We have state, and we have a renderer that can read that state, but we don't have any mechanism for modifying it interactively.

That's exactly the problem we'll solve next.

## Commit your work

```bash
git add .
git commit -m "Lesson 02: renderer and lambdas"
```

### Next lesson: `03_buttons.cpp`

We'll introduce one FTXUI button that increments the counter.

That gives us our first complete event-driven interaction:

**User input → Callback → State change → Updated display**

And we'll do it with just a few additional lines of code.