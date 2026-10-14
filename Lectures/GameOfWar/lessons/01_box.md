# GameOfWar 01 — Project Setup and Your First FTXUI Box

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 01 - Elements and Layout
new_file: examples/01_box.cpp
concepts:
  - CMake project setup
  - FTXUI Elements
  - text, border, separator
  - vbox and hbox layouts
  - Decorators with the | operator
```

Over sixteen short lessons we'll build a playable game of War in the terminal. Along the way we'll use the FTXUI library to learn lambdas, classes, encapsulation, composition, and separate compilation.

Every lesson follows the same rhythm: **make one small change, compile, run, discuss.**

## How the project is organized

Lessons 01–07 are small, standalone **examples**. Each one is its own program, so you can always go back and run an earlier one.

Lessons 08–16 build **one application**, the War game. Those lessons edit the same files over and over, so you'll commit your work to git at the end of every lesson.

By the end of the course your project will look like this:

```text
GameOfWar/
├── CMakeLists.txt
├── .gitignore
├── examples/          ← Lessons 01–07 (one program per file)
├── include/           ← Class declarations (.hpp)
└── src/               ← main.cpp + class implementations (.cpp)
```

---

## Step 1.1 — Create the project

```bash
mkdir GameOfWar
cd GameOfWar
mkdir examples
git init
```

Create a file named `.gitignore`:

```text
build/
```

The `build/` folder holds generated files. They can always be rebuilt, so we don't commit them.

---

## Step 1.2 — Create `CMakeLists.txt`

Create `CMakeLists.txt` in the project folder:

```cmake
cmake_minimum_required(VERSION 3.20)

project(GameOfWar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Static linking for MinGW (Windows) so the .exe runs outside the build shell
if(MINGW)
    add_link_options(-static)
endif()

# --------------------------------------------------
# FTXUI
# --------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    ftxui
    URL https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v6.1.9.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(ftxui)

# --------------------------------------------------
# Lessons 01-07: every examples/NN_*.cpp becomes its own program
# --------------------------------------------------
file(GLOB EXAMPLES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/examples/[0-9]*.cpp"
)

foreach(SOURCE ${EXAMPLES})
    get_filename_component(NAME ${SOURCE} NAME_WE)

    add_executable(${NAME} ${SOURCE})

    target_link_libraries(${NAME} PRIVATE
        ftxui::component
    )
endforeach()
```

You don't need to understand every line yet. Two parts matter today:

1. **`FetchContent`** downloads FTXUI the first time you configure, so nothing has to be installed by hand.
2. **The `foreach()` loop** turns every file in `examples/` whose name starts with a digit into its own program. `examples/01_box.cpp` becomes a program named `01_box`.

---

## Step 1.3 — Draw a box

Create `examples/01_box.cpp`:

```cpp
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>

using namespace ftxui;

int main() {

    Element document = text("Hello, GameOfWar!") | border;

    auto screen = Screen::Create(
        Dimension::Fixed(40),
        Dimension::Fit(document)
    );

    Render(screen, document);
    screen.Print();

    std::cout << '\n';
}
```

### Compile and run

```bash
cmake -S . -B build
cmake --build build --target 01_box
./build/01_box
```

The first `cmake -S . -B build` takes a while because it downloads and builds FTXUI. Later builds are fast.

You should see:

```text
╭──────────────────────────────────────╮
│Hello, GameOfWar !                    │
╰──────────────────────────────────────╯
```

### Stop and discuss

There are three steps here:

| Step                   | What it does                                   |
| ---------------------- | ---------------------------------------------- |
| `Element document = …` | **Describe** what we want to see               |
| `Render(screen, …)`    | **Draw** that description onto a grid of cells |
| `screen.Print()`       | **Output** the grid to the terminal            |

An `Element` is a *description* of something visual. Creating it doesn't print anything.

Now look at this line:

```cpp
text("Hello, GameOfWar!") | border
```

The `|` operator applies a **decorator**. It takes an element and returns a new element with a border around it.

**Question:** `|` normally means bitwise OR. Why can FTXUI use it for something completely different?

Because C++ lets libraries **overload operators**. FTXUI defines what `|` means when the left side is an `Element`.

---

## Step 1.4 — Stack elements vertically

Replace the `document` line with:

```cpp
Element document = vbox({
    text("GameOfWar 01") | bold,
    separator(),
    text("Hello, GameOfWar!"),
}) | border;
```

Compile and run:

```bash
cmake --build build --target 01_box
./build/01_box
```

```text
╭──────────────────────────────────────╮
│GameOfWar 01                          │
├──────────────────────────────────────┤
│Hello, GameOfWar !                    │
╰──────────────────────────────────────╯
```

`vbox` stacks its children **vertically**. The braces `{ ... }` hold a list of elements.

Notice that the trailing comma after the last element is allowed. It makes adding lines later easier.

---

## Step 1.5 — Place elements side by side

Add an `hbox` between the separator and the text:

```cpp
Element document = vbox({
    text("GameOfWar 01") | bold | center,

    separator(),

    hbox({
        text("Left") | border,
        text("Middle") | border | flex,
        text("Right") | border,
    }),

    separator(),

    text("Static screens are drawn once.") | color(Color::Green),

}) | border;
```

Compile and run:

```text
╭──────────────────────────────────────╮
│            GameOfWar 01              │
├──────────────────────────────────────┤
│╭────╮╭───────────────────────╮╭─────╮│
││Left││Middle                 ││Right││
│╰────╯╰───────────────────────╯╰─────╯│
├──────────────────────────────────────┤
│Static screens are drawn once.        │
╰──────────────────────────────────────╯
```

`hbox` arranges its children **horizontally**. The `flex` decorator lets "Middle" grow to fill the leftover space.

Decorators chain left to right:

```cpp
text("GameOfWar 01") | bold | center
```

That means: make some text, make it bold, then center it.

**Layouts nest.** We put an `hbox` inside a `vbox`. That's the same idea we'll use to build every screen in this course.

---

## Step 1.6 — Student challenge

Modify `01_box.cpp` to draw a small "business card":

```text
╭──────────────────────────────────────╮
│             Your Name                │
├──────────────────────────────────────┤
│ Major:   Computer Science            │
│ Course:  CMPS 2143                   │
├──────────────────────────────────────┤
│╭──────────╮              ╭──────────╮│
││  Python  │              │   C++    ││
│╰──────────╯              ╰──────────╯│
╰──────────────────────────────────────╯
```

Requirements:

1. Use at least one `vbox` and one `hbox`.
2. Use `separator()` at least twice.
3. Make your name `bold` and centered.
4. Use `filler()` to push the two language boxes to opposite sides.
5. Give one element a color.

---

## If the build fails

| Symptom                                       | Fix                                                                |
| --------------------------------------------- | ------------------------------------------------------------------ |
| `No rule to make target '01_box'`             | Re-run `cmake -S . -B build` so CMake notices the new file.        |
| Still missing after reconfiguring             | Check the file is in `examples/` and its name starts with a digit. |
| Strange cache errors after moving the project | `cmake -S . -B build --fresh`                                      |

To list every target CMake knows about:

```bash
cmake --build build --target help
```

---

## Putting it Together

Here is the complete program at the end of this lesson. Compare it with yours before you commit.

### `examples/01_box.cpp` (new)

<!-- file: examples/01_box.cpp -->
```cpp
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>

using namespace ftxui;

int main() {

    Element document = vbox({
        text("GameOfWar 01") | bold | center,

        separator(),

        hbox({
            text("Left") | border,
            text("Middle") | border | flex,
            text("Right") | border,
        }),

        separator(),

        text("Static screens are drawn once.") | color(Color::Green),

    }) | border;

    auto screen = Screen::Create(
        Dimension::Fixed(40),
        Dimension::Fit(document)
    );

    Render(screen, document);
    screen.Print();

    std::cout << '\n';
}
```

---

## Commit your work

```bash
git add .
git commit -m "Lesson 01: project setup and first box"
```

## Next: GameOfWar 02 — Interactive Rendering

Our program draws once and exits. Next we'll switch to an interactive screen that keeps running, and we'll meet the tool FTXUI uses everywhere: the **lambda function**.
