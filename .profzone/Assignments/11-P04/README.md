```yaml
title: Program 4 — Color, Kernels, and Convolution
description: Operator overloading, named constructors, convolution kernels
id: 11-P04
course: 2143 - Object Oriented Programming
date_assigned: 2026-04-20 12:00
date_due: 2026-05-04 11:00
points: 100
```

# Program 4 — Color, Kernels, and Convolution

## Overview

P03 gave you a working image pipeline. This program extends it in two directions:

1. **`Color`** replaces the raw `Pixel` struct with a type that has operator overloading, named constructors, and indexed channel access. When a type has these, filter arithmetic becomes expressive — `p = p * 0.5` instead of `p.r = p.r/2; p.g = p.g/2; p.b = p.b/2`.

2. **`Kernel`** generalizes the blur effect from P03 into a convolution kernel. The same 15-line loop can produce blur, sharpen, edge detection, emboss, and more — the only thing that changes is the numbers in the 3×3 grid.

`KernelFilter` is the bridge: it wraps a `Kernel` in the `Filter` interface, so every kernel plugs directly into your existing `Pipeline`. You write one new class, and the pipeline from P03 gains five new effects without touching `Pipeline` or `main.cpp`.

---

## From P03 to P04

### `Pixel` → `Color`

In P03, pixels were stored as a plain `struct Pixel { int r, g, b; }`. In P04, pixels are `Color` objects — the same three integer channels, but with operators:

```cpp
// P03 style
p.r += 50; p.g += 50; p.b += 50;

// P04 style — same result, cleaner code
p = p + Color(50, 50, 50);
```

Your P03 filters still compile unchanged in P04 because `Filter.h` defines:

```cpp
using Pixel = Color;
```

That alias means any code that says `Pixel` is using `Color` under the hood. Study `Brighten.cpp` — it is the exact P03 implementation running inside P04 without modification.

### `Blur` → `KernelFilter`

P03's `Blur` class manually computed a 3×3 average using a hand-written loop. In P04, the same effect is:

```cpp
pipeline.add(new KernelFilter(Kernel::boxBlur(), "blur"));
```

And sharpening, edge detection, and emboss are:

```cpp
pipeline.add(new KernelFilter(Kernel::sharpen(),    "sharpen"));
pipeline.add(new KernelFilter(Kernel::edgeDetect(), "edgeDetect"));
pipeline.add(new KernelFilter(Kernel::emboss(),     "emboss"));
```

The convolution loop is the same every time. That's the point: one general algorithm, different data.

---

## Project Structure

```
11-P04/
├── README.md
├── src/
│   ├── main.cpp              ← do not modify
│   ├── Image.h / Image.cpp   ← updated: uses Color, adds Image::apply()
│   ├── Color.h / Color.cpp   ← your main task (Part 1)
│   ├── Kernel.h / Kernel.cpp ← your second task (Part 2)
│   ├── Filter.h              ← updated: Grid uses Color, adds Pixel alias
│   ├── Pipeline.h/.cpp       ← unchanged from P03
│   ├── KernelFilter.h/.cpp   ← provided complete — the P03→P04 bridge
│   ├── Brighten.h/.cpp       ← provided (P03 implementation, unchanged)
│   ├── Grayscale.h/.cpp      ← stub — paste and optionally refactor P03
│   ├── FlipH.h/.cpp          ← stub — paste P03
│   ├── FlipV.h/.cpp          ← stub — paste P03
│   └── Rotate.h/.cpp         ← stub — paste P03
├── include/
│   ├── stb_image.h           ← do not modify
│   └── stb_image_write.h     ← do not modify
├── images/
│   ├── Hulda.jpg             ← test image
│   └── in.png                ← test image
└── docs/
    ├── image_example.cpp     ← standalone demo (reference, not compiled with imgtool)
    └── ppm_example.cpp       ← legacy reference showing what Image replaced
```

---

## Build & Run

```bash
# Compile from the project root (11-P04/)
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -isystem include \
    src/main.cpp src/Image.cpp src/Color.cpp src/Kernel.cpp \
    src/Pipeline.cpp src/KernelFilter.cpp \
    src/Brighten.cpp src/Grayscale.cpp \
    src/FlipH.cpp src/FlipV.cpp src/Rotate.cpp \
    src/Args.cpp -o imgtool
```

---

## Example Commands

```bash
# P03 filters still work
./imgtool images/Hulda.jpg out.png --grayscale --brighten 30

# Blur is now routed through KernelFilter
./imgtool images/Hulda.jpg out.png --blur

# New kernel effects
./imgtool images/Hulda.jpg out.png --sharpen
./imgtool images/Hulda.jpg out.png --edgeDetect
./imgtool images/Hulda.jpg out.png --emboss
./imgtool images/Hulda.jpg out.png --gaussian

# Chain effects: grayscale first, then find edges
./imgtool images/Hulda.jpg out.png --grayscale --edgeDetect

# Chain effects: soft blur, then sharpen
./imgtool images/Hulda.jpg out.png --gaussian --sharpen

# Mix P03 and P04 filters
./imgtool images/Hulda.jpg out.png --flipH --sharpen --brighten 20

# Short flags
./imgtool images/Hulda.jpg out.png -g -s -b 10
```

### Expected output (success)

```
INPUT   : images/Hulda.jpg
OUTPUT  : out.png
ORDER   : grayscale edgeDetect

Loaded: Image(546 x 640, 349440 pixels)
FILTERS : grayscale -> edgeDetect
Saved: out.png
```

---

## Part 1: The `Color` Class

Every operator and factory in `Color.cpp` is a student TODO except:

- **Constructors** — provided (clamp on construction)
- **`operator[]`** — provided (needed by `KernelFilter` and `Image::apply`)
- **`clamp` / `clampDouble`** — provided private helpers

### Operators to implement

| Operator    | Behavior                                     |
| ----------- | -------------------------------------------- |
| `c + d`     | Add channels, clamp result to [0, 255]       |
| `c * 0.5`   | Scale each channel by a double, clamp        |
| `0.5 * c`   | Same (already delegating to the above)       |
| `c == d`    | True if all three channels match             |
| `c != d`    | Already implemented (delegates to `==`)      |
| `cout << c` | Print as `rgb(r, g, b)`                      |
| `cin >> c`  | Read three integers into r, g, b; clamp each |

### Static factories to implement

```cpp
Color Color::fromRGB(int r, int g, int b);           // thin wrapper around constructor
Color Color::fromHex(const std::string& hex);         // "#ff8000" or "ff8000"
Color Color::fromHSL(double h, double s, double l);   // h in [0,360), s/l in [0,1]
```

`fromHex` and `fromHSL` must throw `std::invalid_argument` on bad input.

#### HSL → RGB Conversion

HSL (Hue, Saturation, Lightness) is a human-friendly color model. The standard algorithm is well-documented — look it up, understand it, implement it.

Test cases:

| HSL           | Expected RGB           |
| ------------- | ---------------------- |
| (0, 1, 0.5)   | (255, 0, 0) — red      |
| (120, 1, 0.5) | (0, 255, 0) — green    |
| (240, 1, 0.5) | (0, 0, 255) — blue     |
| (0, 0, 0.5)   | (128, 128, 128) — gray |
| (0, 0, 0)     | (0, 0, 0) — black      |

---

## Part 2: Kernel Factories

`Kernel.h`, `Kernel.cpp` stubs, and the two constructors are provided. Your task is the six named factories and the `operator<<`.

Each factory builds and returns a 3×3 `Kernel` using the values from the table below. The stubs in `Kernel.cpp` include the kernel grid in comments — fill in the data:

```cpp
Kernel Kernel::boxBlur() {
    //   1/9  1/9  1/9
    //   1/9  1/9  1/9       all nine values are 1.0/9.0
    //   1/9  1/9  1/9
    return Kernel(3, { 1.0/9, 1.0/9, 1.0/9,
                       1.0/9, 1.0/9, 1.0/9,
                       1.0/9, 1.0/9, 1.0/9 });
}
```

You also need to implement the flat-vector constructor that unpacks values into `data_[row][col]`, and the `at(row, col)` accessor with bounds checking.

### Kernel reference table

| Name         | Grid                            | Kernel sums to |
| ------------ | ------------------------------- | -------------- |
| identity     | center = 1, rest = 0            | 1.0            |
| boxBlur      | all 1/9                         | 1.0            |
| sharpen      | `0 -1 0 / -1 5 -1 / 0 -1 0`     | 1.0            |
| edgeDetect   | all -1, center = 8              | 0.0            |
| emboss       | diagonal from -2..+2 (see stub) | 1.0            |
| gaussianBlur | `1 2 1 / 2 4 2 / 1 2 1` ÷ 16    | 1.0            |

Notice the relationship between sum and effect: sum = 1.0 preserves overall brightness; sum = 0.0 turns uniform regions black (edges only).

---

## Part 3: Bring Forward Your P03 Filters

Paste your P03 implementations into the corresponding `*.cpp` files. They will compile unchanged because `Filter.h` defines `using Pixel = Color`.

Optionally (for the 10-point "Color operators" credit), refactor one or more filters to use `Color` operators. For example:

```cpp
// Grayscale — P03 style
int gray = (p.r + p.g + p.b) / 3;
p.r = p.g = p.b = gray;

// Grayscale — P04 style (uses Color(int,int,int) + operator[])
int gray = (p[0] + p[1] + p[2]) / 3;
p = Color(gray, gray, gray);
```

Both are correct. The refactored version demonstrates why `operator[]` is useful.

---

## Part 4: `Image::apply` (non-destructive convolution)

`Image::apply(const Kernel& k)` returns a new `Image` — `*this` is unchanged. The algorithm is identical to `KernelFilter::apply()` which is provided as a complete working example. Study it, then implement `Image::apply`.

The difference in intent:

- `KernelFilter::apply(Grid&)` — modifies in place, for use in the pipeline
- `Image::apply(const Kernel&)` — non-destructive, returns a copy

```cpp
// Non-destructive: pass1 and pass2 are separate images, img is untouched
Image pass1 = img.apply(Kernel::gaussianBlur());
Image pass2 = pass1.apply(Kernel::edgeDetect());
pass2.save("edges.png");
```

The stub in `Image.cpp` has the algorithm spelled out in comments. Boundary handling: skip the outer `half = k.size()/2` pixels (copy them unchanged from `*this`).

---

## What to Submit

- `src/Color.cpp` — operators and factories implemented
- `src/Kernel.cpp` — factories and accessors implemented
- `src/Grayscale.cpp`, `FlipH.cpp`, `FlipV.cpp`, `Rotate.cpp` — P03 implementations pasted (and optionally refactored)
- `src/Image.cpp` — `Image::apply()` implemented
- A short section added to your `README.md`:
  - 5 example commands (at least 2 demonstrating kernel filter effects)
  - Which HSL algorithm you used and one test case you verified
  - Whether you refactored any P03 filters to use Color operators, and what changed

Do **not** modify: `main.cpp`, `Image.h`, `Color.h`, `Kernel.h`, `Filter.h`, `Pipeline.h/.cpp`, `KernelFilter.h/.cpp`, `Brighten.h/.cpp`.

---

## Rubric

> _Program must compile. Or it will be considered a failure._

| Category                | Points  | Details                                                             |
| ----------------------- | ------- | ------------------------------------------------------------------- |
| **Color operators**     | 20      | `+`, `*`, `==` correct and clamped                                  |
| **Color factories**     | 15      | `fromHex` and `fromHSL` correct, throw on bad input                 |
| **Kernel factories**    | 15      | All 6 return correct values                                         |
| **Kernel accessors**    | 5       | `at()` with bounds check; flat-vector constructor unpacks correctly |
| **P03 filters updated** | 10      | Paste and compile; +bonus for Color operator refactor               |
| **`Image::apply`**      | 15      | Correct convolution, boundary skip, non-destructive                 |
| **Pipeline ordering**   | 10      | Kernel filters run in CLI order, mixed with P03 filters             |
| **Compiles clean**      | 5       | Zero errors and zero warnings with the given compile command        |
| **Example commands**    | 5       | README section with 5 examples and notes                            |
| **Total**               | **100** |                                                                     |

### Extra Credit (up to +20)

| Option                                                                            | Points |
| --------------------------------------------------------------------------------- | ------ |
| `Color::fromHSL` also handles edge cases (s=0 gray path, boundary hue=360)        | +5     |
| `Color::operator*(Color, Color)` — channel multiply (useful for lighting effects) | +5     |
| `Image::resize(int w, int h)` — nearest-neighbor scaling                          | +10    |

### Deductions

| Issue                                            | Penalty      |
| ------------------------------------------------ | ------------ |
| Does not compile on grader's machine             | up to −50    |
| Modifies provided files                          | −10 per file |
| `Image::apply` is destructive (modifies `*this`) | −10          |
| Off-by-one in boundary skip                      | −5           |
