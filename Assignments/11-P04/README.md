```yaml
title: Program 4
description: Color Class + PPM Image Type
id: 11-P04
name: 11-P04
category: program
date_assigned: 2026-04-20 12:00
date_due: 2026-05-04 11:00
resources: []
```

# Program 4: Build a Type That Fits (C++)

## Overview

A well-designed type feels like it belongs in the language. You don't look up how to use it — it just works the way you'd expect. `std::string` is like that. `nlohmann::json` is like that. In this assignment you'll build two types that aim for that standard:

- `Color` — an RGB color value with arithmetic, comparison, indexing, and named constructors
- `PPM` — an image file that stores `Color` pixels and knows how to load, save, and be accessed naturally

The `PPM` class is built *from* `Color` — this is **composition**: a `PPM` has a grid of `Color` objects, not raw integers. You will replace the primitive `Pixel` struct from P03 with your new `Color` type.

---

## Part 1: The `Color` Class

### Storage

Internally store `r`, `g`, `b` as integers clamped to `[0, 255]`. Enforce this in every method that sets a channel — an invalid value should clamp, not crash or silently overflow.

```cpp
Color c(300, -10, 128);   // stored as (255, 0, 128)
```

### Required Operator Overloads

| Operator | Behavior |
|---|---|
| `c + d` | Add channels, clamp result to [0, 255] |
| `c * 0.5` | Scale each channel by a double, clamp |
| `0.5 * c` | Same — order shouldn't matter |
| `c[0]`, `c[1]`, `c[2]` | Access r, g, b by index |
| `c == d` | True if all three channels match |
| `c != d` | Opposite of `==` |
| `cout << c` | Print as `rgb(255, 128, 0)` |
| `cin >> c` | Read three integers into r, g, b |

### Required Static Factories

```cpp
Color Color::fromRGB(int r, int g, int b);
Color Color::fromHex(const std::string& hex);   // "#ff8000" or "ff8000"
Color Color::fromHSL(double h, double s, double l);
```

Why factories instead of constructors? Because `Color(30.0, 1.0, 0.5)` is ambiguous — is that HSL or HSV? `Color::fromHSL(30.0, 1.0, 0.5)` is not. See the HSL conversion notes below.

### Error Handling

Factories should throw `std::invalid_argument` on bad input:

```cpp
Color::fromHex("zzzzzz");   // throws — not valid hex
Color::fromHSL(400, 1, 1);  // throws — hue must be [0, 360)
```

Callers catch this in `main`:

```cpp
try {
    Color c = Color::fromHex(userInput);
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
}
```

---

## Part 2: The `PPM` Class

A `PPM` is an image. Internally it stores a 2D grid of `Color` objects. It knows how to load and save the PPM P3 format from P03.

### Required Interface

```cpp
class PPM {
public:
    static PPM load(const std::string& filename);  // factory
    void save(const std::string& filename) const;

    int width()  const;
    int height() const;

    Color&       operator[](int row, int col);        // C++23
    const Color& operator[](int row, int col) const;

    // C++20/earlier fallback — row access returns a vector
    std::vector<Color>&       operator[](int row);
    const std::vector<Color>& operator[](int row) const;

    friend std::ostream& operator<<(std::ostream& os, const PPM& img);
};
```

### Composition

`PPM` stores `Color`, not raw ints. The internal grid is:

```cpp
std::vector<std::vector<Color>> pixels;
```

This means your filters from P03 need updating — `Pixel` becomes `Color`. The arithmetic you added to `Color` (`+`, `*`) should simplify the filter implementations noticeably.

### `operator<<` for PPM

Should print a compact summary, not the entire pixel grid:

```
PPM(640 x 480, 307200 pixels)
```

---

## Part 3: Fix the Smell (Refactoring Exercise)

The file `smelly_ppm.cpp` is provided. It is a working PPM loader/saver written by a beginner — correct but unrefined. Your job is to:

1. Read it and identify the code smells (list is below)
2. Refactor it into a clean `PPM` class
3. Write a short paragraph for each smell: what it is, where it appears, and how you fixed it

### Smells to Find and Fix

| Smell | Hint |
|---|---|
| Magic numbers | `255` and `3` appear repeatedly with no explanation |
| Primitive obsession | Pixels stored as separate `r`, `g`, `b` integer arrays |
| Long method | One function does file open, parse, validate, and store |
| Dead code | A `printDebug()` function that is never called |
| God object | One struct handles file I/O, pixel math, and error reporting |
| Inconsistent naming | Mix of `camelCase`, `snake_case`, and `ALL_CAPS` in same file |

---

## HSL Conversion Notes

HSL (Hue, Saturation, Lightness) is a human-friendly color model. The conversion to RGB is well-documented — look it up, understand it, implement it. Do not copy-paste without understanding.

Inputs:
- `h` in `[0.0, 360.0)` — the color wheel position
- `s` in `[0.0, 1.0]` — 0 = gray, 1 = full color
- `l` in `[0.0, 1.0]` — 0 = black, 0.5 = normal, 1 = white

Output: a `Color` with r, g, b in [0, 255].

Some examples to test against:

| HSL | Expected RGB |
|---|---|
| (0, 1, 0.5) | (255, 0, 0) — red |
| (120, 1, 0.5) | (0, 255, 0) — green |
| (240, 1, 0.5) | (0, 0, 255) — blue |
| (0, 0, 0.5) | (128, 128, 128) — gray |
| (0, 0, 0) | (0, 0, 0) — black |

---

## Updating P03 Filters

Once `Color` is working, update your filters from P03:

- Replace `struct Pixel { int r, g, b; }` with `Color`
- `Grayscale::apply` becomes: `p = p * (1.0/3.0) * 3.0` — or just use the average
- `Brighten::apply` becomes: `p = p + Color(delta, delta, delta)` — or `p * factor` with the new double range
- `Blur` and `Rotate` stay structurally the same — the pixel arithmetic simplifies

Note: `brighten` is now a `double` in `[-1.0, 1.0]` representing a scale factor, not an additive integer.

---

## Part 4: Kernel-Based Filtering

### What Is a Kernel?

An image **kernel** (also called a convolution matrix) is a small grid of numbers — typically 3×3 or 5×5 — that defines how each output pixel is computed from its neighborhood in the original image.

The idea is simple: slide the kernel over every pixel. At each position, multiply each kernel value by the corresponding nearby pixel's channel value, then sum all those products. The result is the new pixel value at that position. Do this independently for r, g, and b.

This operation is called **convolution**, and it is the mathematical foundation of blur, sharpening, edge detection, and dozens of other effects. The same code runs for all of them — only the kernel values change.

### The Math

For a 3×3 kernel `K` applied at pixel position `(row, col)`:

```
new_channel(row, col) =
    sum over i in {-1, 0, 1}:
        sum over j in {-1, 0, 1}:
            K[i+1][j+1]  *  original_channel(row+i, col+j)
```

Clamp each channel of the result to [0, 255] after summing. Apply this formula independently to r, g, and b.

### Named Kernels

The same convolution loop produces completely different effects depending on what values are in the kernel:

| Name | Kernel (3×3) | Effect |
|---|---|---|
| Identity | `0 0 0 / 0 1 0 / 0 0 0` | No change — pixel passes through |
| Box Blur | all `1/9` | Averages each pixel with its 8 neighbors |
| Sharpen | `0 -1 0 / -1 5 -1 / 0 -1 0` | Center boosted, neighbors subtracted — enhances edges |
| Edge Detect | all `-1` except center `8` | Flat regions → black; edges → bright |
| Emboss | diagonal gradient from `-2` to `+2` | Simulates a raised 3-D surface |
| Gaussian Blur | `1 2 1 / 2 4 2 / 1 2 1` divided by 16 | Smooth, natural-looking blur |

Study these values. Notice that the box blur kernel sums to exactly 1.0 (preserves brightness). The edge-detect kernel sums to 0.0 (flat areas become black). The relationship between sum and effect is not a coincidence.

### Why Static Factories?

You used this pattern in `Color::fromHex` and `Color::fromHSL`. Use it again here:

```cpp
PPM blurred = img.apply(Kernel::boxBlur());
PPM edges   = img.apply(Kernel::edgeDetect());
```

Compare to the alternative:

```cpp
// What does this do? You have to count values.
img.apply(Kernel(3, {-1,-1,-1,-1,8,-1,-1,-1,-1}));
```

The name is the documentation. Static factories make intent unambiguous.

### Boundary Handling

At the edges of the image the kernel window extends outside the image bounds. You need a strategy for those missing pixels. Three common ones:

| Strategy | Description |
|---|---|
| **Skip** | Don't write output for border pixels — leave them unchanged |
| **Clamp** | Treat out-of-bounds coordinates as the nearest valid pixel |
| **Wrap** | Wrap around to the opposite edge (rarely useful for photos) |

Implement **skip** for this assignment. For a 3×3 kernel this means the outermost ring of pixels (row 0, last row, col 0, last col) is copied unchanged into the output. For a 5×5 kernel, the outermost two rings are skipped. In general, skip the outer `size/2` pixels on each side.

### Non-Destructive Design

`PPM::apply` must return a **new** `PPM` rather than modifying the image in place. This is the correct design because it lets you chain filters without destroying the original:

```cpp
PPM img    = PPM::load("photo.ppm");
PPM pass1  = img.apply(Kernel::gaussianBlur());
PPM pass2  = pass1.apply(Kernel::edgeDetect());
pass2.save("edges.ppm");
// img is still the unmodified original
```

If `apply` modified `img` directly you could never go back, and you could not apply the same image to two different pipelines. Immutability here is a feature, not a limitation.

### The `Kernel` Class Interface

```cpp
class Kernel {
public:
    explicit Kernel(int size);                              // size x size, all zeros
    Kernel(int size, const std::vector<double>& values);   // row-major flat init

    double&       at(int row, int col);
    const double& at(int row, int col) const;

    int size() const;

    static Kernel identity();
    static Kernel boxBlur();
    static Kernel sharpen();
    static Kernel edgeDetect();
    static Kernel emboss();
    static Kernel gaussianBlur();

    friend std::ostream& operator<<(std::ostream& os, const Kernel& k);
};
```

The `at(row, col)` accessor should throw `std::out_of_range` on invalid indices. The two constructors should throw `std::invalid_argument` if `size` is even, less than 3, or if `values.size() != size*size`.

### Connecting Kernel to PPM

Add one method to your `PPM` class:

```cpp
PPM apply(const Kernel& k) const;
```

The algorithm:
1. Create a new `PPM` of the same width and height, initialized as a copy of `*this`.
2. Determine the half-size: `int half = k.size() / 2;`
3. For every pixel `(row, col)` not within `half` of any edge:
   - For each channel `ch` in `{0, 1, 2}`:
     - Compute the convolution sum over the kernel window.
     - Clamp to [0, 255] and write into the output pixel.
4. Return the new `PPM`.

---

## What to Submit

- `Color.h / Color.cpp`
- `PPM.h / PPM.cpp`
- `Kernel.h / Kernel.cpp`
- `smelly_ppm.cpp` — original, unmodified
- `clean_ppm.cpp` — your refactored version
- `refactor_notes.md` — one paragraph per smell
- `main.cpp` — demonstrates Color factories, PPM load/save, and at least 3 kernel filters
- At least 2 test PPM images

---

## Rubric

| Category | Points |
|---|---|
| `Color` operators correct and clamped | 20 |
| `Color` static factories + error handling | 15 |
| `PPM` load/save correct | 10 |
| `PPM` composition uses `Color` correctly | 10 |
| P03 filters updated to use `Color` | 10 |
| `Kernel` factories return correct values | 15 |
| `PPM::apply` correct (convolution + boundary skip) | 10 |
| Smells identified and fixed correctly | 7 |
| Refactor notes clear and accurate | 3 |
| **Total** | **100** |

### Extra Credit

- `Color::fromHSV(h, s, v)`: +5
- `operator*` between two Colors (multiply channels, useful for lighting): +5
- `PPM::resize(int w, int h)` nearest-neighbor: +10
- `Kernel` constructor that accepts a 2-D `vector<vector<double>>`: +5
- Support 5×5 kernels (the convolution loop already generalizes — just make sure boundary skip uses `half`): +5
