<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: P04
name: P04
title: Image Tool — Templates, Color, and Kernels
description: Class templates, operator overloading, convolution; Adapter and Composite patterns; unit tests
category: Assignments
date_due:
  month: ''
  day: ''
  year: ''
  hour: 11
```

</details>


# P04 — Image Tool, Part 3: Templates, `Color`, and Kernels

## Overview

P03's pipeline works, but its data types are weak:

- `Grid` is a `vector<vector<Pixel>>`. Nothing stops a row from having the wrong length, and there's no bounds checking.
- `Pixel` is a bare struct. Any code can set `p.r = 9000`.
- Blur is a hand-written loop. Sharpen, edge-detect, and emboss would each need another near-copy of it.

P04 fixes all three, and adds two design patterns on the way:

| You build              | What it is                                                                                         |
| ---------------------- | -------------------------------------------------------------------------------------------------- |
| **`Matrix<T>`**        | A **class template**: one grid type for any element. The image is a `Matrix<Color>`; a kernel's weights are a `Matrix<double>`. |
| **`Color`**            | A real class with **operator overloading** and an **invariant**: channels are always in [0, 255].  |
| **`Kernel`**           | Convolution weights with **named constructors**: `Kernel::sharpen()`, `Kernel::edgeDetect()`, …   |
| Composite **`Pipeline`** | A `Pipeline` that **is a** `Filter`, so pipelines nest. Presets like `--preset sketch` are pipelines. |
| **Unit tests**         | `./build/imgtool --test` runs them. A tiny test harness, written with function templates.          |

Provided for you to study: **`KernelFilter`**, which uses the **Adapter** pattern to make any `Kernel` usable as a `Filter`.

**OOP ideas:** class templates, member templates, function templates, operator overloading (member and friend), invariants and encapsulation, static factory methods, composition, the Adapter and Composite patterns, testing.

---

## What Carried Over From P03, and What Changed

| P03                                 | P04                                                                   |
| ----------------------------------- | --------------------------------------------------------------------- |
| `struct Pixel {int r, g, b;}`       | `class Color` (private channels, operators, always in range)          |
| `Grid = vector<vector<Pixel>>`      | `Grid = Matrix<Color>`, indexed `pixels(row, col)`                    |
| `Blur` class                        | gone: `KernelFilter(Kernel::boxBlur(), "blur")`                       |
| `Pipeline` holds filters            | `Pipeline` holds filters **and is one** (Composite)                   |
| `pipeline.run(...)`                 | `pipeline.apply(...)` (it overrides `Filter::apply`)                  |
| `Args`                              | provided, with new options: `-s -e -m -n`, `--preset NAME`, `--test`  |

**`main.cpp` barely changed**: it handles `--test`, and `run` became `apply`. Five kernel filters and every preset arrive through `FilterFactory` as plain `Filter`s. That's P03's design paying off.

---

## Project Structure

```
P04/
├── src/
│   ├── main.cpp, Console.h, Operation.h, Platform.*, stb_impl.cpp   ← provided
│   ├── Args.h / Args.cpp          ← provided (new options already added)
│   ├── Matrix.h                   ← YOU (Part 1)
│   ├── Color.h                    ← provided
│   ├── Color.cpp                  ← YOU (Part 2)
│   ├── Image.h / Image.cpp        ← provided (now uses Matrix<Color>)
│   ├── Kernel.h                   ← provided
│   ├── Kernel.cpp                 ← YOU (Part 3)
│   ├── KernelFilter.h / .cpp      ← provided: Adapter, study it
│   ├── Filter.h                   ← provided
│   ├── Pipeline.h                 ← provided (now : public Filter)
│   ├── Pipeline.cpp               ← YOU: apply() and name() (Part 5)
│   ├── Brighten.h / .cpp          ← provided, already ported: read it first
│   ├── Grayscale, FlipH, FlipV,
│   │   Rotate, Invert  (.cpp)     ← YOU port from P03 (Part 4)
│   ├── FilterFactory.h            ← provided
│   ├── FilterFactory.cpp          ← YOU: presets (Part 5)
│   ├── Test.h, Tests.h            ← provided: the test harness
│   └── Tests.cpp                  ← provided tests + YOUR tests (Part 6)
```

The starter builds. Run `./build/imgtool --test` right away: most provided tests fail. That's your checklist.

---

## Part 1 — `Matrix<T>` (finish `Matrix.h`)

```cpp
template <typename T>
class Matrix {
public:
    Matrix() = default;
    Matrix(int rows, int cols, const T& fill = T{});
    Matrix(int rows, int cols, std::initializer_list<T> values);   // row by row

    int rows() const;  int cols() const;  bool empty() const;

    T& at(int r, int c);            // bounds-checked: throws std::out_of_range
    T& operator()(int r, int c);    // unchecked, for tight loops
    // (plus const versions)

    template <typename F> void forEach(F f);    // f(element) on every element
    bool operator==(const Matrix&) const;  bool operator!=(const Matrix&) const;
    begin(), end()                              // so  for (const T& x : m)  works
private:
    int rows_ = 0, cols_ = 0;
    std::vector<T> data_;                       // element (r, c) at data_[r * cols_ + c]
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);   // one row per line
```

The constructor and `operator()` are done as examples. You write the rest.

**Why is it all in a header?** The compiler writes the real `Matrix<Color>` and `Matrix<double>` from the template wherever they're used, so it needs the complete definitions in every `.cpp` that uses a `Matrix`. Templates live in headers.

**Out-of-class syntax.** Every definition below the class repeats the template header:

```cpp
template <typename T>
T& Matrix<T>::at(int r, int c) { ... }
```

`forEach` is a template *inside* a template, so it needs two headers:

```cpp
template <typename T>
template <typename F>
void Matrix<T>::forEach(F f) { for (T& x : data_) f(x); }
```

`F` can be a lambda, a function pointer, anything callable: `m.forEach([](int& x) { x *= 2; });`

**One flat vector** instead of a vector of vectors: every row is guaranteed the same length, the data sits in one block of memory (faster), and copying is one allocation.

> **W07 connection:** `Matrix<bool>` won't compile, because `at()` returns `T&` and `std::vector<bool>` is a **specialization** that packs bits and can't hand out a `bool&`. Use `Matrix<char>` if you ever need one.

---

## Part 2 — `Color` (implement `Color.cpp`)

`Color.h` is provided. The constructor clamps every channel to [0, 255], and the channels are **private**, so **no `Color` can ever be out of range**. That's the class's invariant. Build every result with the `Color(int, int, int)` constructor and your operators get the invariant for free.

| Function                 | Behavior                                                            |
| ------------------------ | ------------------------------------------------------------------- |
| `gray(level)`            | `Color(level, level, level)`                                        |
| `fromHex("#ff8000")`     | `Color(255, 128, 0)`. `#` optional; exactly 6 hex digits or throw `std::invalid_argument` |
| `operator[](ch)`         | 0 → r, 1 → g, 2 → b; anything else throws `std::out_of_range`. Returns `int`, not `int&` (why?) |
| `luminance()`            | `0.299r + 0.587g + 0.114b`, **rounded** with `std::lround` (see `Color.h` for why) |
| `+`, `-` (Color)         | channel by channel, clamped                                         |
| `+ int`                  | add to all three, clamped                                           |
| `* double`, `double *`   | scale all three, rounded, clamped. The `double * Color` version is a `friend`; write it in one line using the member `operator*` |
| `==`, `!=`               | all three channels equal                                            |
| `<<`                     | `rgb(255, 128, 0)`                                                  |

Note the behavior change from P03: `Pixel` let channels overshoot mid-pipeline and clamped on save. `Color` clamps immediately, so `-b 100 -b -100` no longer returns to the original. That's the cost of the invariant, and in exchange `Image::save` no longer needs to clamp anything.

---

## Part 3 — `Kernel` (implement the TODOs in `Kernel.cpp`)

A kernel is a square grid of weights. **Convolution** replaces each pixel with the weighted sum of its 3×3 neighborhood. `Kernel` **has a** `Matrix<double>`: the same template as the image, with a different `T`.

- **Constructor:** throw `std::invalid_argument` unless the matrix is square with an odd size ≥ 3.
- **`sum()`:** add every weight (a range-for over the matrix works, thanks to `begin`/`end`).
- **`operator<<`:** one line, reusing `Matrix`'s `operator<<`.
- **Named kernels** (`identity` is done as the example):

| Kernel         | Weights (row by row)               | Sum | Effect                        |
| -------------- | ---------------------------------- | --- | ----------------------------- |
| `identity`     | `0 0 0 / 0 1 0 / 0 0 0`            | 1   | no change                     |
| `boxBlur`      | all `1/9`                          | 1   | blur                          |
| `gaussianBlur` | `1 2 1 / 2 4 2 / 1 2 1`, ÷ 16      | 1   | smoother blur                 |
| `sharpen`      | `0 -1 0 / -1 5 -1 / 0 -1 0`        | 1   | sharpen                       |
| `edgeDetect`   | all `-1`, center `8`               | 0   | edges bright, flat areas black |
| `emboss`       | `-2 -1 0 / -1 1 1 / 0 1 2`         | 1   | raised-relief look            |

A sum of 1 keeps overall brightness. A sum of 0 turns flat regions black. For `gaussianBlur`, build the integer grid, then `forEach` to divide by 16.

### Study: `KernelFilter`, the Adapter (provided)

`Kernel` is just numbers. It knows nothing about filters or pipelines. `KernelFilter` **adapts** it to the `Filter` interface, so every kernel plugs into the pipeline without changing `Kernel` or `Pipeline`:

```cpp
pipeline.add(std::make_unique<KernelFilter>(Kernel::sharpen(), "sharpen"));
```

Read `KernelFilter::apply`. Notice that it adds up the weighted sums in `double` and builds a `Color` **once** at the end. Using `Color`'s clamping `+` and `*` step by step would be wrong: sharpen's `-1` weights would be clamped to 0 halfway through the sum.

---

## Part 4 — Port Your Filters

Port `Grayscale`, `FlipH`, `FlipV`, `Rotate`, and `Invert` from P03 to `Matrix<Color>`. **Read `Brighten.cpp` first.** It shows the new style:

```cpp
void Brighten::apply(Grid& pixels) {
    pixels.forEach([this](Color& c) { c = c + amount_; });
}
```

- Index with `pixels(row, col)`; sizes are `pixels.rows()` and `pixels.cols()`.
- `Grayscale` and `Invert` become one `forEach` each. Use `Color::gray(c.luminance())` and `Color(255, 255, 255) - c`.
- `FlipV` can't swap whole rows anymore (a `Matrix` has no row objects). Swap element by element.
- `Rotate`: `Grid result(newRows, newCols);` then `result(r, c) = ...`. The mapping table is the same as P03's.

The P03 identities (`-r 90` ×4, `-h -h`, `-i -i`, …) must still produce byte-identical files.

---

## Part 5 — Composite: Pipelines Inside Pipelines

`Pipeline` now **inherits from `Filter`**:

```cpp
class Pipeline : public Filter {
public:
    explicit Pipeline(std::string label = "pipeline");
    void add(std::unique_ptr<Filter> f);
    void apply(Grid& pixels) override;    // YOU: P03's run(), renamed
    std::string name() const override;    // YOU: label[child -> child -> child]
    ...
```

Because a `Pipeline` **is a** `Filter`, it can be added to another `Pipeline`. Code that runs filters can't tell one filter from a whole group, and doesn't need to. That's the **Composite** pattern.

`name()` returns the label and its children's names in brackets. Nested pipelines nest naturally, because each child's `name()` is a virtual call:

```text
FILTERS : brighten(20) -> sketch[grayscale -> edgeDetect -> invert] -> rotate(90)
```

### Presets

In `FilterFactory.cpp`, write the `preset(label, steps)` helper. It returns a **Creator** that builds a `Pipeline` named `label` and adds `FilterFactory::create(step)` for each step. The lambda must capture `label` and `steps` **by value**, because it runs long after `preset()` has returned. Then register at least:

| Preset    | Steps                                    |
| --------- | ---------------------------------------- |
| `sketch`  | grayscale → edgeDetect → invert          |
| `soft`    | gaussian → gaussian → brighten(15)       |
| *yours*   | at least 3 steps, your design; describe it in your README |

```bash
./build/imgtool images/Hulda.png out.png -b 20 --preset sketch -r 90
```

An unknown preset (`--preset nope`) must produce `Error: no filter named 'nope'`. Your P03 `create()` already handles that.

---

## Part 6 — Tests

`./build/imgtool --test` runs everything in `Tests.cpp`:

```text
PASS Matrix rows
PASS Color fromHex
FAIL Color * 0.5: expected rgb(100, 50, 26), got rgb(0, 0, 0)
...
SOME FAIL: 15 passed, 2 failed
```

Read `Test.h`: it's a short, real example of **function templates**. One `check(what, actual, expected)` works for `int`, `Color`, `Matrix<int>`, `std::string`… any types that support `==` and `<<`. The compiler writes a separate version for each combination you use. And if `Color` had no `operator<<`, calls to `check` with Colors **wouldn't compile**: templates are checked when they're used.

```cpp
t.check("2 + 2", 2 + 2, 4);
t.checkNear("sharpen sums to 1", Kernel::sharpen().sum(), 1.0);       // doubles
t.checkThrows<std::out_of_range>("at(9, 9)", [&] { m.at(9, 9); });   // exception type in < >
```

All provided tests must pass. Then add **at least 12 of your own** in `yours()`, including:

- `Matrix<double>` and `Matrix<Color>` (it's one template, but test more than one type), plus an empty matrix and a negative index
- every `Color` operator you wrote, including clamping at both ends and a bad `fromHex`
- `boxBlur` and `gaussianBlur` sums (use `checkNear`), and one filter applied to a tiny hand-built `Grid` with a known result

---

## Sample Runs

```text
$ ./build/imgtool images/my_82_jeep.png out.jpg --sharpen --emboss
ORDER   : sharpen emboss

Loaded: Image(1600 x 902)
FILTERS : sharpen -> emboss
Result: Image(1600 x 902)
Saved: out.jpg

$ ./build/imgtool --test
...
ALL PASS: 31 passed, 0 failed      (your count will differ)
```

---

## What to Submit

`Matrix.h`, `Color.cpp`, `Kernel.cpp`, `Pipeline.cpp`, the five ported filter `.cpp` files, `FilterFactory.cpp`, `Tests.cpp`. In your README: 5 example commands (at least 2 with kernels and 1 with your preset), and the output of `--test`.

Don't commit `build/`.

---

## Rubric

> _The program must build. If it doesn't, it's graded as a failure._

| Category                 | Points  | Details                                                                          |
| ------------------------ | ------- | -------------------------------------------------------------------------------- |
| **Builds clean**         | 5       | No errors, no warnings                                                           |
| **`Matrix<T>`**          | 20      | All members; out-of-class template syntax; `forEach` member template; `operator<<` |
| **`Color`**              | 15      | Every operator and factory; invariant never broken; throws where specified       |
| **`Kernel`**             | 10      | Validation, `sum`, all named kernels, `operator<<`                               |
| **Ported filters**       | 15      | All five on `Matrix<Color>`; P03 identities still hold                           |
| **Composite + presets**  | 15      | `Pipeline` `apply`/`name`; nesting works; `sketch`, `soft`, and your own preset  |
| **Tests**                | 15      | All provided tests pass; ≥ 12 of your own covering the list above                |
| **Code quality**         | 5       | `const`-correct, no raw `new`/`delete`, consistent style                         |
| **Total**                | **100** |                                                                                  |

### Extra Credit (up to +15)

| Option                                                                                         | Points |
| ---------------------------------------------------------------------------------------------- | ------ |
| `Color::fromHSL(h, s, l)` with tests (`(0,1,0.5)` → red, `(120,1,0.5)` → green, `(0,0,0.5)` → `rgb(128,128,128)`) | +5 |
| `Matrix<T>::map(f)`: returns a new `Matrix<U>`, where `U` is whatever `f` returns (`decltype`/`std::invoke_result_t`) | +5 |
| A 5×5 kernel (e.g., a bigger Gaussian). `KernelFilter` already handles any odd size; prove it with a test | +5 |

### Deductions

| Issue                                                                       | Penalty   |
| --------------------------------------------------------------------------- | --------- |
| `Color` channels made public, or `operator[]` returning `int&`              | −10       |
| Kernel filters added with an if/else in `main` instead of the factory       | −10       |
| Raw `new` / `delete` anywhere                                               | −10       |
| Does not build on the grader's machine                                      | up to −50 |
