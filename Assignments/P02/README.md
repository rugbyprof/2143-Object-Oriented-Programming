<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: P02
name: P02
title: Image Tool
description: Grayscale conversion with colored output and auto-open
category: Assignments
date_due:
  month: '11'
  day: '16'
  year: 2026
  hour: 11
```

</details>



# P02 — Image Tool

## Overview

You are given working starter code that loads an image, converts it to grayscale using the luminance formula, and saves the result as a PNG. It builds and runs correctly as-is.

Your job is to add two small but meaningful extras:

- **Task A**: replace the plain terminal messages with colored ones built with **FTXUI**, the same library you used in P01.
- **Task B**: after saving the output image, open it automatically in the system's default image viewer.
  > If the image doesn't open on your machine, that's not a disaster. You get the points as long as the correct code is there.

Keep your code clean and organized. Later programs build on this one.

---

## Project Structure

```
P02/
├── README.md
├── CMakeLists.txt        ← build recipe (provided, downloads FTXUI)
├── src/
│   └── main.cpp          ← your working file
├── include/
│   ├── stb_image.h       ← image loading (provided)
│   └── stb_image_write.h ← image writing (provided)
├── images/
│   ├── Hulda.png         ← test input image
│   ├── Hulda.jpg         ← alternate input format
│   ├── HuldaBW.png       ← expected output (reference)
│   ├── my_82_jeep.png    ← extra test input
│   └── kenzie_dax_ou_game copy.jpeg ← extra test input
└── docs/
    └── compile_cmd.md    ← what the warning and optimization flags mean
```

---

## Starter Code

`src/main.cpp` builds and runs as-is. Read it carefully before making changes.

```cpp
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"

// ------------------------------------------------------------
// P02 Image Tool (Starter):
// - Uses argv[1] argv[2] for input/output
// - Loads an image, converts it to grayscale, saves as PNG
//
// YOU will add:
//   (A) FTXUI for colored messages
//   (B) a function to open the output image automatically
// ------------------------------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: ./imgtool <input_image> <output_image>\n";
        return 1;
    }

    std::string inputPath  = argv[1];
    std::string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Force RGB (3 channels), no matter what the file has
    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    if (!data) {
        std::cerr << "Failed to load image: " << inputPath << "\n";
        return 1;
    }

    const int channels    = 3;
    const int totalPixels = width * height;

    std::cout << "Loaded image: " << width << "x" << height
              << " channels: " << channels << "\n";

    // Hardcoded grayscale (luminance)
    for (int i = 0; i < totalPixels; ++i) {
        int idx = i * channels;

        int r = data[idx + 0];
        int g = data[idx + 1];
        int b = data[idx + 2];

        // The weights add up to 1.0, so gray is always in [0, 255]
        int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

        unsigned char gr = static_cast<unsigned char>(gray);

        data[idx + 0] = gr;
        data[idx + 1] = gr;
        data[idx + 2] = gr;
    }

    // Save PNG
    if (!stbi_write_png(outputPath.c_str(),
                        width,
                        height,
                        channels,
                        data,
                        width * channels)) {

        std::cerr << "Failed to write output image: " << outputPath << "\n";
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);

    std::cout << "Saved output to: " << outputPath << "\n";

    // TODO (Task B): open output file automatically in default viewer

    return 0;
}
```

---

## Build & Run

This project builds with **CMake**, exactly like P01. The first configure downloads and builds FTXUI for you, so it needs internet once and takes a minute. If your P01 setup works, this will too. If not, go back to P01's [SETUP.md](../P01/SETUP.md) and [CMake_Basics.md](../P01/CMake_Basics.md).

Run these from the `P02/` folder:

```bash
# 1) Configure (once, or after editing CMakeLists.txt)
cmake -S . -B build              # macOS / Linux
cmake -S . -B build -G Ninja     # Windows (MSYS2)

# 2) Build (every time you change main.cpp)
cmake --build build

# 3) Run
./build/imgtool images/Hulda.png output.png        # macOS / Linux
.\build\imgtool.exe images\Hulda.png output.png    # Windows
```

You don't type the warning flags yourself. `CMakeLists.txt` already turns on `-Wall -Wextra -pedantic` and an optimized (Release) build. See [docs/compile_cmd.md](./docs/compile_cmd.md) for what each flag means.

> **About the stb headers:** `stb_image_write.h` is third-party code, and some compilers warn about it. `CMakeLists.txt` marks `include/` as a **system** folder, which hides warnings from those headers. Any warning you see is about **your** code.

---

## Task A — Colored Terminal Output with FTXUI

In P01 you used FTXUI to build an interactive screen. Here you'll use only its **drawing** half (the `dom` and `screen` parts) to print one colored line at a time and then exit. You don't need a `ScreenInteractive` or a loop.

### How it works (30-second version)

- `text("hi")` makes an **`Element`**, something FTXUI knows how to draw.
- The `|` operator applies a **decorator** to an element: `text("hi") | color(Color::Red) | bold`
- `hbox({ a, b, c })` puts elements side by side on one line.
- To show an element, you **render** it onto a `Screen` and then print that screen.

### 1) Add the includes

```cpp
#include <ftxui/dom/elements.hpp>   // text, hbox, color, bold, ...
#include <ftxui/screen/screen.hpp>  // Screen, Render

using namespace ftxui;
```

> `using namespace ftxui;` is fine in a single `.cpp` file like this. Never put it in a header.

### 2) Add this helper function above `main()`

Writing render-and-print code for every message gets repetitive, so wrap it in one function:

```cpp
// Draws one FTXUI element and prints it, followed by a newline.
// Sends output to std::cout unless you pass std::cerr.
void printLine(Element line, std::ostream& out = std::cout) {
    auto screen = Screen::Create(Dimension::Fit(line));  // just big enough
    Render(screen, line);
    out << screen.ToString() << "\n";
}
```

The second parameter has a **default argument**. `printLine(x)` prints to `std::cout`, and `printLine(x, std::cerr)` prints to the error stream. Error messages belong on `std::cerr`.

### 3) Replace the three messages

**Usage error** (wrong number of arguments):

```cpp
printLine(hbox({
    text("Usage: ") | color(Color::Red) | bold,
    text("./imgtool <input_image> <output_image>") | color(Color::Blue),
}), std::cerr);
```

**Load failure:**

```cpp
printLine(hbox({
    text("Failed to load image: ") | color(Color::Red),
    text(inputPath),
}), std::cerr);
```

**Success:**

```cpp
printLine(hbox({
    text("Saved output to: ") | color(Color::Green),
    text(outputPath) | color(Color::Yellow),
}));
```

You should also color the **"Loaded image"** and **"Failed to write"** messages. It's good practice and keeps the output consistent. Hint: `text()` takes a `std::string`, so build numbers in with `std::to_string(width)`.

> **No more `reset`.** With raw escape codes (or libraries like termcolor), forgetting to reset the color makes it "bleed" into everything printed after it. FTXUI resets the colors after every element it draws, so this can't happen.

---

## Task B — Auto-Open Output Image

After saving, automatically open the output file in the default image viewer.

### 1) Add the include

```cpp
#include <cstdlib>   // std::system
```

### 2) Add this function above `main()`

```cpp
bool open_file_default_app(const std::string& path) {
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\"";
#endif
    return std::system(cmd.c_str()) == 0;
}
```

The `#if defined(...)` lines are handled by the **preprocessor** before the compiler runs. Only the branch for the machine you're compiling on ends up in the program. Each OS has its own "open this with the default app" command.

### 3) Replace the TODO comment with a call

Use `printLine` here too:

```cpp
printLine(text("Opening output in default viewer...") | dim);
if (!open_file_default_app(outputPath)) {
    printLine(text("Warning: could not launch viewer automatically.")
              | color(Color::Yellow));
}
```

> **Note:** In a remote environment with no display (GitHub Codespaces, an SSH server, etc.), the viewer won't open and you'll see the warning. That's expected. The program should still build and run without errors.

---

## Sample Output

Your colors can differ, but the run should look roughly like this:

```text
$ ./build/imgtool images/Hulda.png output.png
Loaded image: 546x640 channels: 3
Saved output to: output.png
Opening output in default viewer...
```

Compare your `output.png` against `images/HuldaBW.png`. They should look the same.

Then try the extra images in `images/`. If a file name has a space in it, put the path in quotes:

```bash
./build/imgtool "images/kenzie_dax_ou_game copy.jpeg" kenzie_bw.png
```

---

## Notes

- Don't refactor the grayscale logic into a class or add features beyond Tasks A and B. A later program does that.
- Submit only `src/main.cpp`. The headers, images and `CMakeLists.txt` are provided.
- Your code must build with the provided `CMakeLists.txt` with **no errors and no warnings**.
- Don't commit the `build/` folder or the program it makes.

---

## Rubric

> _The program must build. If it doesn't, it's graded as a failure._

| Category                      | Points  | Details                                                                     |
| ----------------------------- | ------- | --------------------------------------------------------------------------- |
| **Builds clean**              | 20      | No errors and no warnings from the provided `CMakeLists.txt`                |
| **Task A: FTXUI setup**       | 10      | FTXUI headers included, `printLine` helper (or equivalent) used, not copy-pasted |
| **Task A: Usage message**     | 10      | At least two distinct colors in one line, printed to `std::cerr`            |
| **Task A: Error message**     | 5       | Load failure uses color, printed to `std::cerr`                             |
| **Task A: Success message**   | 15      | Save success uses color                                                     |
| **Task B: Function defined**  | 20      | `open_file_default_app()` present, handles all 3 platforms                  |
| **Task B: Function called**   | 10      | Called after a successful save, with an appropriate message                 |
| **Code quality**              | 10      | No dead code, no unused variables or includes, consistent style             |
| **Total**                     | **100** |                                                                             |

### Deductions

| Issue                                                            | Penalty   |
| ---------------------------------------------------------------- | --------- |
| Raw ANSI escape codes (`"\033[31m"`) or termcolor instead of FTXUI | −10       |
| Hardcoded platform command instead of `#if defined(...)`          | −10       |
| Extra features added beyond what was asked                        | −10       |
| Does not build on the grader's machine                            | up to −50 |
