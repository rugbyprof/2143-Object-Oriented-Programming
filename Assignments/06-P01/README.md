```yaml
title: Program 1 — Image Tool
description: Grayscale conversion with colored output and auto-open
id: 06-P01
course: 2143 - Object Oriented Programming
date_assigned: 2026-03-02 12:00
date_due: 2026-03-09 11:00
points: 100
```

# Program 1 — Image Tool

## Overview

You are given working starter code that loads an image, converts it to grayscale using the luminance formula, and saves the result as a PNG. It compiles and runs correctly as-is.

Your job is to add two small but meaningful extras:

- **Task A** — Replace plain terminal output with colored messages using the `termcolor` library
- **Task B** — After saving the output image, automatically open it in the system's default image viewer
  > Image not opening is not catastrophic if the proper code is there.

This is **Program 1 of 4**. Each program builds on the previous one. Keeping your code clean and organized here pays off later.

---

## Project Structure

```
06-P01/
├── README.md
├── src/
│   └── main.cpp          ← your working file
├── include/
│   ├── stb_image.h       ← image loading (provided)
│   ├── stb_image_write.h ← image writing (provided)
│   └── termcolor.hpp     ← colored terminal output (provided)
├── images/
│   ├── Hulda.png         ← test input image
│   ├── Hulda.jpg         ← alternate input format
│   └── HuldaBW.png       ← expected output (reference)
└── docs/
    └── compile_cmd.md    ← breakdown of compiler flags
```

---

## Starter Code

`src/main.cpp` compiles and runs as-is. Read it carefully before making changes.

```cpp
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"

// ------------------------------------------------------------
// Program 1 (Starter):
// - Uses argv[1] argv[2] for input/output
// - Loads an image, converts it to grayscale, saves as PNG
//
// YOU will add:
//   (A) termcolor for colored messages
//   (B) a function to open the output image automatically
// ------------------------------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cout << "Usage: ./imgtool <input_image> <output_image>\n";
        return 1;
    }

    std::string inputPath  = argv[1];
    std::string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Force RGB (3 channels)
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

```bash
# Compile from the project root (06-P01/)
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o imgtool

# Run it
./imgtool images/Hulda.png output.png
```

The `-Iinclude` flag tells the compiler to search the `include/` folder for header files.

For a full breakdown of every compiler flag, see [docs/compile_cmd.md](./docs/compile_cmd.md).

---

## Task A — Colored Terminal Output

Include the `termcolor` header and replace the plain `cout`/`cerr` messages with colored versions.

### 1) Add the include

```cpp
#include "termcolor.hpp"
```

### 2) Optional namespace shortcut

```cpp
using namespace termcolor;
```

### 3) Replace the three messages

**Usage error** (bad argument count):

```cpp
std::cout << red    << "Usage: "
          << blue   << "./imgtool <input_image> <output_image>\n"
          << reset;
```

**Load failure:**

```cpp
std::cerr << red   << "Failed to load image: "
          << reset << inputPath << "\n";
```

**Success:**

```cpp
std::cout << green  << "Saved output to: "
          << yellow << outputPath
          << reset  << "\n";
```

You can color the "Loaded image" message too — it's good practice.

---

## Task B — Auto-Open Output Image

After saving, automatically open the output file in the default image viewer.

### 1) Add the include

```cpp
#include <cstdlib>
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

### 3) Replace the TODO comment with a call

```cpp
std::cout << "Opening output in default viewer...\n";
if (!open_file_default_app(outputPath)) {
    std::cout << "Warning: could not launch viewer automatically.\n";
}
```

> **Note:** If you are working in a remote environment (GitHub Codespaces, SSH server, etc.) with no display, the viewer will not open. That is expected — the code should still compile and run without errors.

---

## Notes

- This is Program 1 of 4. Do not refactor the grayscale logic into a class or add extra features — that is Program 2's job.
- Submit only `src/main.cpp`. The headers and images are provided.
- Your code must compile with the exact command shown above, with no errors and no warnings.

---

## Rubric

> _Program must compile. Or it will be considered a failure._

| Category                      | Points  | Details                                                      |
| ----------------------------- | ------- | ------------------------------------------------------------ |
| **Compiles clean**            | 20      | No errors, no warnings with `-Wall -Wextra -pedantic`        |
| **Task A — Usage message**    | 15      | Usage error uses at least two distinct colors + reset        |
| **Task A — Error message**    | 10      | Load failure uses color                                      |
| **Task A — Success message**  | 15      | Save success uses color                                      |
| **Task B — Function defined** | 20      | `open_file_default_app()` present, handles all 3 platforms   |
| **Task B — Function called**  | 10      | Called after successful save with appropriate output message |
| **Code quality**              | 10      | No dead code, no unused variables, consistent style          |
| **Total**                     | **100** |                                                              |

### Deductions

| Issue                                                              | Penalty           |
| ------------------------------------------------------------------ | ----------------- |
| Missing `reset` after colored output (colors bleed into next line) | −5 per occurrence |
| Hardcoded platform string instead of `#if defined(...)`            | −10               |
| Extra features added beyond what was asked                         | −10               |
| Does not compile on grader's machine                               | up to −50         |
