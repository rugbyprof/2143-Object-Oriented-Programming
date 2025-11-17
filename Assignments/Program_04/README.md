# 🧬 **Project: Conway’s Game of Life — SDL2 Edition**

This README is your full guide.

**Upgrade your existing terminal version into a fully interactive graphical program using SDL2.**  
This project merges everything you’ve learned so far:

- **Object-oriented design**
- **Event loops & graphics (SDL2)**
- **Refactoring and modular architecture**
- **JSON parsing (via nlohmann::json)**
- **Loading patterns from data files**
- **Mapping pixels → grid coordinates**
- **Building real tools, not toy demos**

SDL2 Code Examples are [HERE](../../Resources/Sdl2_Graphics/README.md)

---

# 🎯 **Project Overview**

You already have:

1. A **terminal-based Game of Life engine** (`CellularAutomaton`, `ConwayLife`).
2. Working **SDL2 examples**:
   - Opening a window
   - Drawing a grid
   - Clicking to toggle grid cells
   - Rendering text (optional)
3. Code to **parse command-line arguments** into JSON using:
   ```cpp
   json params = ArgsToJson(argc, argv);
   ```
4. JSON-based **pattern files** containing classic Life shapes.

Your job is to **merge all of this into a single SDL2-powered application** that:

- Loads ConwayLife simulation logic
- Displays cells graphically
- Allows clicking cells to toggle them
- Supports pause/run/step/reset/randomize
- Loads Life patterns from a JSON file
- Is configurable via command-line args

**You will NOT rewrite the logic of ConwayLife.**  
You will integrate it into a GUI.

---

# ⭐ **Features You Must Implement**

This is the “no exceptions” checklist.

### ✔️ **1. SDL2 Window & Renderer**

- Create a window using width & height from command-line JSON.
- Use integer `cellSize` to decide how many rows/columns your grid holds.

### ✔️ **2. Replace TextScreen with SdlScreen**

Implement a new class:

```
SdlScreen : public Screen
```

which:

- Draws each cell as an SDL_Rect
- Draws alive cells in one color (e.g., white)
- Draws dead cells in another (e.g., dark gray)
- Optionally draws grid lines (recommended)

### ✔️ **3. Interactive Mouse Input**

Clicking on a cell toggles its state.

You may use:

- Your own event logic, or
- The provided `Click` class pattern

Either is fine, but the behavior must be intuitive and responsive.

### ✔️ **4. Keyboard Controls**

Minimum set:

| Key              | Action                               |
| ---------------- | ------------------------------------ |
| **Space**        | Pause/Resume simulation              |
| **N**            | Step 1 generation (only when paused) |
| **R**            | Randomize grid                       |
| **C**            | Clear grid (set all cells to 0)      |
| **Q** or **Esc** | Quit                                 |

Additional controls (optional): color change, speed change, wrap mode toggle, etc.

### 🎯 **5. JSON Pattern Loader — REQUIRED**

You must load Life patterns from a JSON file, such as:

```json
{
  "shapes": {
    "glider": {
      "size": { "w": 3, "h": 3 },
      "cells": [
        { "x": 0, "y": -1 },
        { "x": 1, "y": 0 },
        { "x": -1, "y": 1 },
        { "x": 0, "y": 1 },
        { "x": 1, "y": 1 }
      ]
    }
  }
}
```

Required behavior:

- Program loads this JSON file on startup (hardcoded filename is acceptable, e.g. `shapes.json`).
- User presses a key (you choose which, e.g. `L` or numeric keys 1–9).
- When that key is pressed:
  - Program loads the selected shape
  - Places it at the location of the mouse cursor (or at a fixed center position)

### ✔️ **6. Command-Line Configuration**

Your program must accept:

```
./SDL_GOL_main window_width=1024 window_height=768 cellSize=8 frameDelayMs=50
```

And merge with default JSON values (provided in your code).

---

# 📁 **Required File Structure**

Your repo should look like this:

```
includes/
    CellularAutomaton.hpp
    ConwayLife.hpp
    AutomatonUtils.hpp
    Screen.hpp
    ArgsToJson.hpp
    json.hpp
    SdlScreen.hpp
    click.hpp          (optional)
    grid.hpp           (from examples)

src/
    ConwayLife.cpp
    SdlScreen.cpp
    SDL_GOL_main.cpp   <-- YOU create this
    click.cpp          (optional)
    other SDL examples (not required for final build)

assets/
    shapes.json        <-- REQUIRED
```

---

# 🧩 **Step-by-Step Assignment Guide**

## 1️⃣ Step 1 — Build the terminal version

Ensure the logic is correct before touching SDL2.

```
./gol_terminal generations=200 frameDelayMs=50
```

Compare results with known patterns.

---

## 2️⃣ Step 2 — Build the SDL2 examples

Confirm your environment is configured correctly.

---

## 3️⃣ Step 3 — Create `SdlScreen`

This class replaces `TextScreen`.

It must:

- Initialize SDL2
- Own a window and renderer
- Draw your grid
- Limit frame rate using `pause(ms)`

---

## 4️⃣ Step 4 — Integrate ConwayLife logic

Your SDL version should call:

```cpp
screen.render(gol.getGrid());
gol.step();
```

inside a loop.

---

## 5️⃣ Step 5 — Add Interactivity

You must support:

- Clicking to toggle cells
- Pausing
- Stepping
- Randomizing
- Clearing

---

## 6️⃣ Step 6 — JSON Pattern Loader

This is a **major required feature**.

**Behavior required:**

- Load the JSON once at program start:
  ```cpp
  json patterns = LoadPatterns("shapes.json");
  ```
- When user presses your pattern key (e.g., “G” for glider):
  - Read the coordinates from JSON
  - Adjust offsets so pattern is centered at mouse location
  - Place alive cells into `gol`'s grid

**Goal:**  
You must show that you know how to:

- navigate JSON structures,
- extract values,
- handle errors,
- and merge JSON data into your grid.

---

# 🧪 **Testing Requirements (Manual)**

Before submitting, verify:

- Grid updates visually
- Clicking toggles correctly
- Pausing works exactly
- Single-step works exactly
- Randomize creates a new scattered state
- JSON pattern loads correctly and matches known shape
- Does not crash on:
  - small windows
  - very large windows
  - clicking outside grid
  - loading pattern partially off-screen

---

# 🎨 **Optional Enhancements (Extra Credit or Resume Boost)**

- **Color themes** (`1`, `2`, `3` keys)
- **Speed control** (`+` / `-`)
- **HUD text** showing generation number (via SDL_ttf)
- **Drag-to-paint** cells
- **Zoom** (change `cellSize` at runtime)
- **Pan** (hold space and drag)
- **Toroidal mode** (grid wraps around)

---

# 📦 **Submission Requirements**

You must submit:

1. **Your entire project folder**
2. Must compile with:
   ```
   make          # or your build instructions
   ```
3. Must run with:
   ```
   ./SDL_GOL_main window_width=900 window_height=900 cellSize=12
   ```
4. Include **screenshots**:
   - paused mode
   - random mode
   - pattern loaded
   - a 200+ generation run
5. A short 1–2 page write-up:
   - what you implemented
   - what was challenging
   - what you’d improve

---

# 🎓 **Grading Rubric**

| Category                                          | Points  |
| ------------------------------------------------- | ------- |
| SDL window initializes, draws grid                | **20**  |
| ConwayLife logic integrated correctly             | **20**  |
| Mouse clicking → toggles cells                    | **20**  |
| Controls implemented (pause/step/reset/randomize) | **15**  |
| JSON pattern loader (required)                    | **20**  |
| Style, comments, file organization                | **5**   |
| **Total**                                         | **100** |

---

# 🏁 Final Notes

This project produces a **full graphical simulator** that is fun to play with, educational, and architecturally similar to real simulation engines.

You’re building:

- event loop
- simulation update
- renderer
- asset/JSON loader
- user interface controls

Which is exactly how real game engines and graphics software are structured.
