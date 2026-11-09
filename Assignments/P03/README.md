<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: P03
name: P03
title: Image Tool — Filter Pipeline
description: Inheritance, abstract classes, polymorphism; Strategy and Factory patterns; unique_ptr ownership
category: Assignments
date_due:
  month: ''
  day: ''
  year: ''
  hour: 11
```

</details>


# P03 — Image Tool, Part 2: The Filter Pipeline

## Overview

In P02, `args.order` held a list of operations, and `main` could apply exactly one of them (grayscale) with a hard-coded `if`. Now every operation becomes a **class**, and a `Pipeline` runs them in order:

```text
             ┌──────────────────────┐
             │   Filter (abstract)  │   virtual void apply(Grid&) = 0;
             └──────────┬───────────┘   virtual std::string name() const = 0;
   ┌─────────┬──────────┼──────────┬─────────┬─────────┬─────────┐
Grayscale Brighten    FlipH      FlipV    Rotate    Blur     Invert
                                                             (you, from scratch)

Pipeline ──owns──▶ vector<unique_ptr<Filter>>     FilterFactory: "rotate" ─▶ new Rotate
```

**OOP ideas in this program:** inheritance, abstract base classes, pure virtual functions, virtual destructors, run-time polymorphism, ownership with `std::unique_ptr`, lambdas and `std::function`, `std::map`.
**Patterns:** **Strategy** (each filter is an interchangeable algorithm) and **Factory** (a name→constructor registry).

---

## What Carried Over From P02

| P02 piece                    | In P03                                                                        |
| ---------------------------- | ----------------------------------------------------------------------------- |
| `Args`, `Operation`          | Provided (P02 solution). You add one flag: `--invert`. Your own P02 code is fine too. |
| `Image`                      | Provided, **minus `toGrayscale()`** (see below)                               |
| `Platform`, `Console`        | Provided, unchanged                                                           |

### Why `toGrayscale` moved

In P02, grayscale was a member function of `Image`. If every operation were an `Image` member, adding a filter would mean editing `Image` every time, and `Image` would grow forever. Instead, each operation becomes its own class, and `Image` goes back to just being an image.

That's the **Open/Closed Principle**: the program is *open* for extension (write a new `Filter` class) but *closed* for modification (`Image`, `Pipeline`, and `main` never change when you do). By the end of P03, adding a filter touches exactly three places: the new class, one line in the factory, and one flag in `Args`.

---

## Project Structure

```
P03/
├── CMakeLists.txt                 ← provided (compiles every src/*.cpp)
├── src/
│   ├── main.cpp                   ← provided, do not modify
│   ├── Args.h / Args.cpp          ← provided; YOU add --invert / -i
│   ├── Operation.h, Console.h     ← provided
│   ├── Image.h / Image.cpp        ← provided
│   ├── Platform.h / .cpp          ← provided
│   ├── stb_impl.cpp               ← provided
│   ├── Filter.h                   ← provided: the abstract base class
│   ├── Pipeline.h                 ← provided
│   ├── Pipeline.cpp               ← YOU
│   ├── Brighten.h / .cpp          ← provided: complete example, read first
│   ├── Blur.h / .cpp              ← provided: complete neighborhood example
│   ├── Grayscale.h / .cpp         ← .h provided, YOU write .cpp
│   ├── FlipH.h / .cpp             ← .h provided, YOU write .cpp
│   ├── FlipV.h / .cpp             ← .h provided, YOU write .cpp
│   ├── Rotate.h / .cpp            ← .h provided, YOU write .cpp
│   ├── Invert.h / .cpp            ← YOU write BOTH, from scratch
│   ├── FilterFactory.h            ← provided
│   └── FilterFactory.cpp          ← YOU finish the registry
├── include/, images/
```

Build and run exactly as in P02 (`cmake -S . -B build`, `cmake --build build`, `./build/imgtool ...`). The starter builds and runs; it just applies nothing yet.

---

## Part 1 — `Filter` (read `Filter.h`)

```cpp
class Filter {
public:
    virtual void apply(Grid& pixels) = 0;    // change the grid in place
    virtual std::string name() const = 0;    // "grayscale", "brighten(50)", ...
    virtual ~Filter() = default;
};
```

- `= 0` makes these **pure virtual**: `Filter` is abstract, so you can't create a plain `Filter`, only derived classes that implement both functions.
- `Grid` is `std::vector<std::vector<Pixel>>`, indexed `pixels[row][col]`.
- The **virtual destructor** matters: the pipeline deletes filters through `Filter` pointers. Without `virtual`, deleting a `Rotate` through a `Filter*` runs only `~Filter()`, which is undefined behavior.
- Write `override` on every function you implement. If you misspell `apply` or get a parameter wrong, `override` turns a silent bug into a compile error.

---

## Part 2 — `Pipeline` (implement `Pipeline.cpp`)

```cpp
void add(std::unique_ptr<Filter> f);   // take ownership; ignore nullptr
void run(Grid& pixels) const;          // apply every filter, in order
void printSteps() const;               // FILTERS : rotate(90) -> grayscale    or    FILTERS : (none)
int  size() const;
```

### Ownership (this is W08 in practice)

```cpp
std::vector<std::unique_ptr<Filter>> filters_;
```

- **Why pointers?** The vector holds *different* types. `vector<Filter>` can't: `Filter` is abstract, and a `Rotate` stored in a `Filter`-sized slot would be **sliced** down to just its `Filter` part. A pointer to the base class can point at any derived object, and the virtual call runs the right `apply()`.
- **Why `unique_ptr`?** With raw `Filter*`, `Pipeline` would need a destructor that `delete`s every filter. It would also need the rule of three, because copying a `Pipeline` would copy the pointers and both copies would delete the same filters. `unique_ptr` deletes automatically and **can't be copied**, so the compiler rules that bug out. `Pipeline` has no destructor at all.
- `unique_ptr` can only be **moved**: `filters_.push_back(std::move(f));`
- Loop with `for (const auto& f : filters_)`. Without the `&`, the loop would try to copy each `unique_ptr`, which won't compile.

---

## Part 3 — Four Filters

**Read `Brighten.cpp` first.** Every per-pixel filter has its shape. Read `Blur.cpp` to see why neighborhood filters work from a copy.

**Grayscale:** move your P02 `toGrayscale` loop here: `gray = 0.299*r + 0.587*g + 0.114*b`.

**FlipH:** in each row, swap `row[col]` with `row[width-1-col]`, for `col < width/2` only. Going past the middle swaps everything back.

**FlipV:** swap `pixels[row]` with `pixels[height-1-row]`, for `row < height/2`. `std::swap` on two whole rows is one call.

**Rotate:** clockwise. The constructor throws `std::invalid_argument` unless degrees is 0, 90, 180, or 270. `Args` already checks, but a class should protect its own rules.

| Degrees | Result size      | Mapping (`old` is `pixels`, H × W)                  |
| ------- | ---------------- | --------------------------------------------------- |
| 0       | unchanged        | nothing to do                                       |
| 90      | **W rows × H cols** | `result[col][H-1-row] = old[row][col]`           |
| 180     | unchanged        | `result[H-1-row][W-1-col] = old[row][col]`          |
| 270     | **W rows × H cols** | `result[W-1-col][row] = old[row][col]`           |

Build `Grid result(rows, std::vector<Pixel>(cols));`, fill it, then `pixels = std::move(result);`. After a 90° turn the image's width and height swap. That's why P02 made `Image::width()` computed instead of stored.

### Check yourself with identities

These must produce **byte-identical** files (`cmp a.png b.png` prints nothing):

```bash
./build/imgtool images/Hulda.png a.png
./build/imgtool images/Hulda.png b.png -r 90 -r 90 -r 90 -r 90    # same as a
./build/imgtool images/Hulda.png c.png -h -h                      # same as a
./build/imgtool images/Hulda.png d.png -r 180
./build/imgtool images/Hulda.png e.png -h -v                      # same as d
./build/imgtool images/Hulda.png f.png -r 270
./build/imgtool images/Hulda.png g.png -r 90 -r 180               # same as f
```

---

## Part 4 — `Invert`, From Scratch

Write `Invert.h` and `Invert.cpp` yourself: a photographic negative, where every channel `c` becomes `255 - c`. `name()` returns `"invert"`. Then wire it in:

1. **Args:** `--invert` / `-i` pushes `{"invert", 0}` onto `args.order` (one `else if` in `Args.cpp`).
2. **Factory:** one line in the registry (Part 5).

`main.cpp`, `Pipeline`, and `Image` don't change. If you find yourself editing them, stop: that's the Open/Closed Principle telling you something's off.

`-i -i` must give back the original image exactly.

---

## Part 5 — `FilterFactory` (finish `FilterFactory.cpp`)

`main.cpp` builds the pipeline without naming a single filter class:

```cpp
for (const Operation& op : args.order)
    pipeline.add(FilterFactory::create(op));
```

The factory is a **registry**: a `std::map` from a name to a **Creator**, a small function that builds that filter:

```cpp
using Creator = std::function<std::unique_ptr<Filter>(const Operation&)>;

static const std::map<std::string, Creator> table = {
    {"blur",     [](const Operation&)    { return std::make_unique<Blur>(); }},
    {"brighten", [](const Operation& op) { return std::make_unique<Brighten>(op.value); }},
    // TODO: grayscale, flipH, flipV, rotate, invert
};
```

- Each Creator is a **lambda**, like the ones you passed to FTXUI in P01.
- `std::function` can hold any callable with that signature.
- `make_unique<Blur>()` returns a `unique_ptr<Blur>`, which converts to `unique_ptr<Filter>` automatically. That's the derived-to-base conversion, applied to smart pointers.
- `static` inside a function means the table is built once, the first time `registry()` runs.

Implement `create`: find `op.name` in the table, throw `std::invalid_argument("no filter named '...'")` if it isn't there, otherwise call the Creator: `return it->second(op);`.

> **Note:** the factory takes an `Operation`, not all of `Args`. It doesn't need file names or `--open`, so it shouldn't see them. Depend on the smallest thing that does the job.

---

## Sample Run

```text
$ ./build/imgtool images/Hulda.png out.png -r 90 -g -b=-30 -i --open
INPUT   : images/Hulda.png
OUTPUT  : out.png
ORDER   : rotate(90) grayscale brighten(-30) invert

Loaded: Image(546 x 640)
FILTERS : rotate(90) -> grayscale -> brighten(-30) -> invert
Result: Image(640 x 546)
Saved: out.png
```

---

## What to Submit

`Pipeline.cpp`, `Grayscale.cpp`, `FlipH.cpp`, `FlipV.cpp`, `Rotate.cpp`, `Invert.h`, `Invert.cpp`, `FilterFactory.cpp`, `Args.cpp`. In your README: 5 example commands, including at least 2 that apply the same filters in different orders, and one sentence on why the two orders differ.

Don't commit `build/`.

---

## Rubric

> _The program must build. If it doesn't, it's graded as a failure._

| Category                | Points  | Details                                                                  |
| ----------------------- | ------- | ------------------------------------------------------------------------ |
| **Builds clean**        | 5       | No errors, no warnings                                                   |
| **Pipeline**            | 15      | `add` moves ownership and ignores null; `run` in order; `printSteps` format |
| **Grayscale**           | 5       | Correct formula                                                          |
| **FlipH / FlipV**       | 15      | Correct, including odd sizes; identities hold                            |
| **Rotate**              | 20      | All four angles; shape swaps on 90/270; constructor validates            |
| **Invert (from scratch)** | 15    | Own `.h`/`.cpp`, `override`s, wired through `Args` and the factory only  |
| **FilterFactory**       | 15      | All filters registered; `create` throws on an unknown name               |
| **Code quality**        | 10      | `override` everywhere, `const` where it belongs, consistent style        |
| **Total**               | **100** |                                                                          |

### Extra Credit (up to +10)

| Option                                                                                        | Points |
| --------------------------------------------------------------------------------------------- | ------ |
| `--resize W H` (nearest-neighbor) as a new `Filter` (needs a two-value `Operation`; explain your change) | +10 |
| `--list` prints every name from `FilterFactory::names()`                                       | +5     |

### Deductions

| Issue                                                         | Penalty       |
| ------------------------------------------------------------- | ------------- |
| Raw `new` / `delete` anywhere                                 | −10           |
| Modified `main.cpp`, `Filter.h`, `Pipeline.h`, or `Image`     | −10 per file  |
| An if/else chain of filter names anywhere but the factory     | −10           |
| Off-by-one at an image edge (flip or rotate)                  | −5 per filter |
| Does not build on the grader's machine                        | up to −50     |
