# Handout: CMake Basics (Just Enough for P01)

> You don't need to become a CMake expert. You need to know **what it is**, the **two commands** you'll type every day, and **what each line** in your `CMakeLists.txt` does, so that when something breaks you know which part to look at.
>
> Install instructions are in **[SETUP.md](./SETUP.md)**. This handout explains what you installed.

---

## 1. Why not just use `g++`?

For one file, plain `g++` is perfect:

```bash
g++ -std=c++17 main.cpp -o game
```

For P01's console milestone, it's still fine:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o game
```

But once you add **FTXUI**, a library that lives somewhere else and has its own code to compile, the command grows into something like this:

```bash
g++ -std=c++17 -Iinclude -I/somewhere/ftxui/include src/*.cpp \
    -L/somewhere/ftxui/lib -lftxui-component -lftxui-dom -lftxui-screen \
    -lpthread -o game
```

And it's a **different** command on every computer, because `/somewhere` is different on a Mac, on Windows, and on your friend's laptop. That's before anyone has even downloaded and compiled FTXUI itself.

**CMake's job is to write that long command for you, correctly, on whatever machine you're on.**

Here's proof. This is (a shortened version of) the real command CMake ran to compile *one* Hi-Lo file:

```text
/usr/bin/c++ -I.../hilo/include -I.../starter/include -isystem .../ftxui-src/include
             -std=gnu++17 -arch arm64 -o CMakeFiles/hilo.dir/src/HiLo.cpp.o
             -c .../hilo/src/HiLo.cpp
```

It's just a compiler command. CMake isn't magic. It's a very good command-writer. You can always see what it's doing with:

```bash
cmake --build build --verbose
```

---

## 2. The big picture

```text
  CMakeLists.txt          ← YOU write this (the recipe)
        │
        │   cmake -S . -B build          (step 1: CONFIGURE)
        ▼
  build/  (Makefile or build.ninja, plus FTXUI downloaded here)
        │
        │   cmake --build build          (step 2: BUILD)
        ▼
  g++ / clang++ runs on each .cpp        ← the actual compiling
        │
        ▼
  build/game   (or build\game.exe)       ← your program
```

Three things to remember:

1. **CMake is not a compiler.** It *calls* your compiler (`g++` or `clang++`). That's why you still need one installed.
2. **`CMakeLists.txt` is a recipe**, not C++. It describes *what* to build. CMake figures out *how*.
3. **Everything CMake generates goes into `build/`.** Your source files are never touched.

---

## 3. Install and check

Follow **[SETUP.md](./SETUP.md)** for your OS. Then check that it worked:

```bash
cmake --version
```

You need **3.20 or higher**. If you see `command not found` or `'cmake' is not recognized`, CMake isn't on your PATH. Go back to SETUP.md, and remember to **close and reopen your terminal** afterwards.

---

## 4. The only two commands you need

Run both from the folder that contains `CMakeLists.txt` (`starter/` or `examples/hilo/`).

### Step 1: Configure (once)

**macOS / Linux / WSL**

```bash
cmake -S . -B build
```

**Windows**

```powershell
cmake -S . -B build -G Ninja
```

| Piece | Means |
| --- | --- |
| `-S .` | "The **S**ource (where `CMakeLists.txt` is) is **this** folder." |
| `-B build` | "Put all generated **B**uild files in a folder named `build`." |
| `-G Ninja` | "Use the **Ninja** build tool." Windows only. Without it, CMake looks for Visual Studio, which you don't have. |

This step reads `CMakeLists.txt`, finds your compiler, and **downloads FTXUI** the first time, so it's slow once and then never again.

### Step 2: Build (every time you change code)

```bash
cmake --build build
```

This compiles **only the files that changed** since last time, then links your program. It's the command you'll type a hundred times.

### Then run it

```bash
./build/game            # macOS / Linux
.\build\game.exe        # Windows
```

### When do I configure again?

Only when one of these happens:

- you **added a new `.cpp` file**
- you **edited `CMakeLists.txt`**
- you **deleted the `build/` folder**

Otherwise, just `cmake --build build`.

---

## 5. The `build/` folder

- It's **generated**. Everything in it can be recreated by running Step 1 again.
- **Deleting it is always safe.** Delete it and configure again: it's the "turn it off and on again" of CMake, and it fixes about half of all weird problems.
- **Never submit it** and never commit it to git. It's big, and it's specific to your machine.

Add this line to your repo's `.gitignore`:

```text
build/
```

---

## 6. Reading the `CMakeLists.txt`, line by line

Here's the starter's file, one piece at a time.

### The header

```cmake
cmake_minimum_required(VERSION 3.20)
project(CardGame LANGUAGES CXX)
```

- "This recipe needs CMake 3.20 or newer." Older versions stop here with a clear error.
- The project is named `CardGame` and uses C++ (`CXX` is CMake's name for C++).

### The C++ standard

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

This is the CMake way of writing `-std=c++17`. `REQUIRED ON` means "fail if the compiler can't do C++17", rather than silently using an older standard.

### Getting FTXUI

```cmake
include(FetchContent)
FetchContent_Declare(ftxui
  URL https://github.com/ArthurSonzogni/FTXUI/archive/refs/tags/v6.1.9.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(ftxui)
```

This is why you never install FTXUI yourself:

- `FetchContent_Declare` says *where* to get FTXUI: a specific version (6.1.9), so everyone in class has the same one.
- The four `set(... OFF ...)` lines say "just the library, please". There's no need to compile FTXUI's examples, docs, or tests.
- `FetchContent_MakeAvailable` downloads it into `build/_deps/` and adds it to the build. It gets compiled **with your compiler**, which avoids a whole category of "library built with a different compiler" errors.

### The programs

```cmake
set(FTXUI_LIBS ftxui::component)

add_executable(check check/check.cpp)
target_link_libraries(check PRIVATE ${FTXUI_LIBS})
```

The two most important commands in CMake:

| Command | Means | `g++` equivalent |
| --- | --- | --- |
| `add_executable(check check/check.cpp)` | "Make a program named `check` from this file." | `g++ check/check.cpp -o check` |
| `target_link_libraries(check PRIVATE ftxui::component)` | "`check` uses FTXUI. Add its include folders *and* link its libraries." | all those `-I`, `-L`, `-l` flags |

A **target** is just "a thing CMake builds", usually a program. Most CMake commands start with `target_` and name which target they affect.

### The game

```cmake
file(GLOB GAME_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game ${GAME_SOURCES})
target_include_directories(game PRIVATE include)
target_link_libraries(game PRIVATE ${FTXUI_LIBS})
```

- `file(GLOB ...)` makes a list of every `.cpp` in `src/` and calls it `GAME_SOURCES`. This is why you don't edit `CMakeLists.txt` when you add a class. **But** the list is made during *configure*, which is why a new `.cpp` file means re-running Step 1.
- `${GAME_SOURCES}` uses that list. `${NAME}` is how CMake reads a variable.
- `target_include_directories(game PRIVATE include)` is the CMake way of writing `-Iinclude`. It's why `#include "Card.hpp"` works.

### The Windows fix

```cmake
if(MINGW)
  target_link_options(check PRIVATE -static)
  target_link_options(game  PRIVATE -static)
endif()
```

`MINGW` is true only when you use MSYS2's `g++` on Windows. `-static` packs the C++ runtime into the `.exe`, so it runs outside the MSYS2 terminal without "missing DLL" errors. On a Mac, this block is skipped.

> **What's `PRIVATE`?** It means "this setting is for this target only." It matters when targets depend on each other in larger projects. For P01, just always write `PRIVATE`.

### How Hi-Lo's file differs

[`examples/hilo/CMakeLists.txt`](./examples/hilo/CMakeLists.txt) is nearly the same. The only new idea is that it borrows `Card`, `Deck`, and `GameView` from the starter instead of keeping its own copies:

```cmake
set(STARTER ${CMAKE_CURRENT_SOURCE_DIR}/../../starter)

add_executable(hilo ${HILO_SOURCES} ${STARTER}/src/Card.cpp ${STARTER}/src/Deck.cpp)
target_include_directories(hilo PRIVATE include ${STARTER}/include)
```

`CMAKE_CURRENT_SOURCE_DIR` means "the folder this `CMakeLists.txt` is in". So `STARTER` points two folders up, then into `starter/`. That's why `examples/` and `starter/` have to stay side by side.

---

## 7. Small changes you might make

**Turn on compiler warnings (recommended).** Add these lines after `add_executable(game ...)`:

```cmake
if(NOT MSVC)
  target_compile_options(game PRIVATE -Wall -Wextra)
endif()
```

Warnings catch real bugs, such as an unused variable that should have been used or comparing `int` with `size_t`.

**Build just one program:**

```bash
cmake --build build --target game
```

**Force a full rebuild without reconfiguring:**

```bash
cmake --build build --clean-first
```

**Build faster using all your CPU cores:**

```bash
cmake --build build -j
```

---

## 8. Which step failed? (Reading errors)

When something goes wrong, the **first question** is: *which step broke?* The step tells you where to look.

| Failed during… | Looks like | Usually means |
| --- | --- | --- |
| **Configure** (`cmake -S . -B build`) | `CMake Error at CMakeLists.txt:12` | A problem with tools or the recipe: CMake is too old, no compiler was found, no internet for the FTXUI download, `-G Ninja` is missing on Windows, or there's a typo in `CMakeLists.txt`. **Not your C++.** |
| **Compile** (`cmake --build build`) | `src/Hand.cpp:42:10: error: ...` | **Your C++.** A file name and line number are included. Fix the *first* error first; later ones are often caused by it. |
| **Link** (`cmake --build build`, at the end) | `undefined reference to 'Hand::clear()'` or `Undefined symbols ... Hand::clear()` | You **declared** a function in a `.hpp` but never **defined** it in a `.cpp`, misspelled it, or forgot a `ClassName::`. Or you added a `.cpp` and didn't re-run configure. |

The compile line also tells you a lot:

```text
src/Hand.cpp:42:10: error: no member named 'push' in 'std::vector<Card>'
│            │  │
file         │  column
             line
```

---

## 9. What about VS Code?

The **CMake Tools** extension (by Microsoft) adds Build and Run buttons to the bottom bar of VS Code. They run the same two commands for you. It's optional, and it's convenient once you understand what's happening underneath.

**Learn the terminal commands first.** When a button fails, the terminal commands are what you, the TA, and your instructor can all debug.

---

## 10. Cheat sheet

```bash
# first time (or after adding a .cpp / editing CMakeLists.txt / deleting build/)
cmake -S . -B build              # macOS / Linux
cmake -S . -B build -G Ninja     # Windows

# every time you change code
cmake --build build

# run
./build/game                     # macOS / Linux
.\build\game.exe                 # Windows

# something weird? start fresh
rm -rf build                     # macOS / Linux
Remove-Item -Recurse -Force build   # Windows PowerShell
# ...then configure again

# see the real compiler commands
cmake --build build --verbose
```

| Word | Plain meaning |
| --- | --- |
| `CMakeLists.txt` | The recipe: what to build, from which files, with which libraries |
| configure | CMake reads the recipe and prepares `build/` |
| build | The compiler actually runs |
| target | One thing being built, like `game` or `check` |
| generator (`-G`) | Which build tool CMake prepares for: Make (Mac default) or Ninja (we use it on Windows) |
| `FetchContent` | "Download this library and build it with my project" |
