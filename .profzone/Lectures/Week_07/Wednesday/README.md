```yaml
title: Program 1
description: Image Viewer
id: 06-P01
name: 06-P01
category: program
date_assigned: 2026-03-02 12:00
date_due: 2026-03-09 11:00
resources: []
```

# Program 1 Starter Code (compiles as-is)

> File: `program1.cpp`

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

    const int channels = 3;
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

        // gray will already be in [0,255] for this formula
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

    // TODO (Student): open output file automatically in default viewer

    return 0;
}
```

---

# Your Tasks (Add the “Extras”)

## Task A — Add termcolor (colored output)

### 1) Add include
At the top, add:

```cpp
#include "termcolor.hpp"
```

### 2) (Optional) Add namespace shortcut
Add below includes:

```cpp
using namespace termcolor;
```

### 3) Replace messages with colored versions
Examples:

**Usage message**
```cpp
std::cout << red << "Usage: " << blue
          << "./imgtool <input_image> <output_image>\n"
          << reset;
```

**Load fail**
```cpp
std::cerr << red << "Failed to load image: " << reset
          << inputPath << "\n";
```

**Success**
```cpp
std::cout << green << "Saved output to: " << yellow
          << outputPath << reset << "\n";
```

That’s it. They’ll feel like terminal wizards immediately.

---

## Task B — Add “open output image in default viewer”

### 1) Add include for `system()`
At the top:

```cpp
#include <cstdlib>
```

### 2) Paste this function ABOVE `main()`

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

### 3) Call it after saving

Replace the TODO with:

```cpp
std::cout << "Opening output in default viewer...\n";
if (!open_file_default_app(outputPath)) {
    std::cout << "Warning: could not launch viewer automatically.\n";
}
```

(Students can color those messages too.)

---

# Build / Run

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic program1.cpp -o imgtool
./imgtool input.png output.png
```

---

# Notes you can tell students (quick)
- If you’re on a server with no GUI, the viewer won’t open. That’s normal.
- This is Program 1: hardcoded grayscale only.
- Program 2: you’ll add your `Args::parse()` and select the filter + `--view`.

---

If you want, I can also provide:
- a **“completed Program 1”** version (for you / solution key),
- and a **tiny checklist** students can use to verify they added termcolor + open correctly (without you answering 47 emails).