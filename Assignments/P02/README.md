<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: P02
name: P02
title: Image Tool — Args and Image
description: Command-line parser and an RAII Image class (static factories, exceptions)
category: Assignments
date_due:
  month: ''
  day: ''
  year: ''
  hour: 11
```

</details>


# P02 — Image Tool, Part 1: `Args` and `Image`

## Overview

This is the first of three programs that build one command-line image editor, `imgtool`:

| Program | You build                                        | The tool can…                                  |
| ------- | ------------------------------------------------ | ---------------------------------------------- |
| **P02** | `Args` (the parser) and `Image` (load/save)      | read options, load an image, grayscale, save   |
| P03     | a filter pipeline (inheritance, polymorphism)    | grayscale, brighten, flip, rotate, invert, blur |
| P04     | `Matrix<T>`, `Color`, kernels (templates)        | sharpen, edge detect, emboss, presets          |

In P02 you write two classes:

- **`Args`** reads the command line, validates every option, and hands back one clean object. If anything is wrong, it explains exactly what, and the program stops.
- **`Image`** wraps the C library `stb_image`. Its static factory `Image::load` makes sure a C buffer is always freed, and it reports problems by **throwing exceptions** instead of printing.

You also write one small function, `openInDefaultViewer`, that opens the result the way double-clicking would.

**OOP ideas in this program:** encapsulation and invariants, static factory methods with a private constructor, RAII with `std::unique_ptr` and a custom deleter, exceptions, `const`-correctness, operator overloading (`operator<<`), and separate compilation.

---

## Project Structure

```
P02/
├── README.md
├── CMakeLists.txt        ← provided (downloads FTXUI, compiles every src/*.cpp)
├── src/
│   ├── main.cpp          ← provided, do not modify
│   ├── Console.h         ← provided: colored output (printError, printStatus, ...)
│   ├── Operation.h       ← provided: one image operation {name, value}
│   ├── Args.h            ← provided
│   ├── Args.cpp          ← YOU: Args::parse and Args::print
│   ├── Pixel.h           ← provided
│   ├── Image.h           ← provided
│   ├── Image.cpp         ← YOU: every Image member function
│   ├── Platform.h        ← provided
│   ├── Platform.cpp      ← YOU: openInDefaultViewer
│   └── stb_impl.cpp      ← provided, do not modify (see "One Definition Rule")
├── include/              ← stb_image.h, stb_image_write.h (third-party)
├── images/               ← Hulda.png/.jpg, HuldaBW.png (grayscale of Hulda.jpg), extras
└── docs/
    └── factory.md        ← constructor vs. static factory, explained
```

---

## Build & Run

Same CMake commands as P01. Run them from the `P02/` folder:

```bash
cmake -S . -B build              # configure (Windows MSYS2: add -G Ninja)
cmake --build build              # build, every time you change code
./build/imgtool images/Hulda.png out.png --grayscale
```

On Windows, run `.\build\imgtool.exe`.

`CMakeLists.txt` compiles **every** `.cpp` in `src/`. If you add a file, re-run the configure step.

The starter builds and runs as-is. It just doesn't do much yet.

---

## Part 1 — `Args`

### Usage

```bash
./build/imgtool <input_image> <output_image> [options]
```

Both positional arguments are required and must end in `.png`, `.jpg`, `.jpeg`, or `.bmp` (any capitalization).

| Option         | Short   | Value                 | Becomes                    |
| -------------- | ------- | --------------------- | -------------------------- |
| `--grayscale`  | `-g`    |                       | `{"grayscale", 0}`         |
| `--blur`       | `-l`    |                       | `{"blur", 0}`              |
| `--flipH`      | `-h`    |                       | `{"flipH", 0}`             |
| `--flipV`      | `-v`    |                       | `{"flipV", 0}`             |
| `--brighten N` | `-b N`  | integer in [-255, 255] | `{"brighten", N}`         |
| `--rotate N`   | `-r N`  | 0, 90, 180, or 270    | `{"rotate", N}`            |
| `--open`       |         |                       | sets `args.open = true`    |

> `--blur` is `-l`, not `-b` (that's brighten). Yes, it's a weird letter.

Valued options accept `--brighten 20`, `--brighten=20`, `-b 20`, and `-b=20`. **Negative values are legal**: `--brighten -20` must work, even though `-20` starts with a dash.

### `Operation` and `args.order`

Every image option is stored, in the order typed, as an `Operation` (see `Operation.h`):

```bash
./build/imgtool a.png b.png -b 20 -g -r 90 -b -5
# args.order = { {"brighten",20}, {"grayscale",0}, {"rotate",90}, {"brighten",-5} }
```

Why not just `bool grayscale` and `int brighten` members? Because options can repeat with different values (`-b 20 ... -b -5`), and **order matters** (brighten-then-grayscale is a different image from grayscale-then-brighten). One `int brighten` could only remember the last value. A list of Operations remembers everything, in order. P03 runs this list as a pipeline.

### Errors

On any error, call `fail(message)` (the starter has it). It prints a red `Error:` line and the usage line to `std::cerr`, then exits with status 1. Your messages don't have to match these word for word, but each must say **what** went wrong and **which** argument caused it:

| Situation                                | Example message                                          |
| ---------------------------------------- | -------------------------------------------------------- |
| no arguments                             | `input and output files are required`                    |
| only one argument                        | `output file is required`                                |
| not an image name                        | `output must be an image file (...): 'out.txt'`          |
| unknown option                           | `unknown option '--graycale'`                            |
| value missing                            | `'--brighten' requires an integer value`                 |
| next token is an option, not a value     | `'--brighten' expected a value but got option '--blur'`  |
| not an integer (`twenty`, `20abc`)       | `invalid integer for '--brighten': 'twenty'`             |
| out of range                             | `'--brighten' must be in [-255, 255]`                    |
| bad rotation                             | `'--rotate' must be one of {0, 90, 180, 270}`            |

### `Args::print`

```
INPUT   : images/Hulda.png
OUTPUT  : out.png
ORDER   : brighten(20) grayscale rotate(90)
```

`Operation::label()` gives you `grayscale` or `brighten(20)`. With no operations, `ORDER   :` has nothing after the colon.

### Why is the constructor private?

`Args()` is private, so the only way to get an `Args` is `Args::parse()`, which validates everything first. That means **every `Args` object in the program is valid**. No other code ever has to re-check it. A constructor couldn't do this as cleanly, because a constructor can't decline to make an object (see [docs/factory.md](./docs/factory.md)).

### Hints

Put helpers in an unnamed namespace at the top of `Args.cpp` (only that file can see them):

```cpp
bool isImageFile(const std::string& filename);                  // extension check
std::pair<std::string, std::string> splitEq(const std::string&); // "--b=20" -> ("--b","20")
bool looksLikeOption(const std::string& s);   // "-g" yes, "-20" no (dash + digit = number)
std::string takeValue(flag, inlineValue, tokens);   // after '=' or the next token
int toInt(const std::string& flag, const std::string& text);    // fail() if not a whole int
```

For `toInt`, use `std::stoi(text, &used)`. It throws on `"twenty"`. It does **not** throw on `"20abc"` (it reads 20 and stops), so also check that `used == text.size()`.

No CLI libraries (`getopt`, `cxxopts`, Boost). The point is to write it.

---

## Part 2 — `Image`

`Image.h` is provided. Implement every function in `Image.cpp`, roughly in this order:

| Function                 | What it does                                                                                 |
| ------------------------ | -------------------------------------------------------------------------------------------- |
| `width()` / `height()`   | columns / rows, **computed from `pixels_`** (be careful with an empty grid)                  |
| `Image(w, h)`            | `h` rows of `w` black pixels; throw `std::invalid_argument` if either is < 1                 |
| `at(row, col)`           | the pixel, or throw `std::out_of_range` with a useful message                                |
| `operator<<`             | prints `Image(546 x 640)`                                                                    |
| `load(filename)`         | see below                                                                                    |
| `save(filename, q)`      | see below                                                                                    |
| `toGrayscale()`          | `gray = 0.299*r + 0.587*g + 0.114*b` for every pixel                                         |

**Why aren't width and height stored?** If they were separate members, any code that changed the grid's shape would also have to remember to update them, and one day someone wouldn't. In P03, a rotate filter changes the shape. Computing them from the grid means there is **one source of truth**, and it can't go stale.

### `Image::load` and RAII

`stbi_load` is a C function. It `malloc`s a buffer of bytes (r, g, b, r, g, b, …) that **must** be released with `stbi_image_free`, on every path, including when you throw. Don't do it by hand. Let an object do it:

```cpp
int w = 0, h = 0, channelsInFile = 0;

std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(
    stbi_load(filename.c_str(), &w, &h, &channelsInFile, 3),   // 3 = force RGB
    &stbi_image_free);                                         // the "deleter"

if (!data)
    throw std::runtime_error("cannot read image '" + filename + "'");

// ... copy data.get()[i], [i+1], [i+2] into each Pixel ...
// When 'data' goes out of scope, stbi_image_free runs automatically.
```

That's **RAII** (Resource Acquisition Is Initialization): tie a resource to an object's lifetime, and the destructor cleans up. `unique_ptr` usually calls `delete`, but you can give it any cleanup function. Here it's `stbi_image_free`.

Pixel `(row, col)` starts at byte `(row * w + col) * 3`.

### `Image::save`

1. Flatten the grid into a `std::vector<unsigned char>` of size `w * h * 3`, clamping each channel to [0, 255] (`std::clamp`). Channels are `int` so filters can overshoot. Save is where they get pulled back.
2. Choose the writer by lowercase extension: `.jpg`/`.jpeg` → `stbi_write_jpg(name, w, h, 3, data, quality)`, `.bmp` → `stbi_write_bmp(name, w, h, 3, data)`, anything else → `stbi_write_png(name, w, h, 3, data, w * 3)`.
3. Each returns 0 on failure. Throw `std::runtime_error` if it did.

### Why throw instead of print?

`Image` doesn't know whether it's running in a terminal, a unit test, or a GUI. It just reports the problem. `main.cpp` catches the exception and decides what to do (print it, exit with status 1). Keeping "detect the problem" separate from "tell the user" is what lets `Image` be reused unchanged in P03 and P04.

### The One Definition Rule (`stb_impl.cpp`)

stb is a "single-header" library: the `.h` holds the function **bodies** too, compiled only when `STB_IMAGE_IMPLEMENTATION` is defined first. A function may be defined only **once** in a whole program, so those `#define`s live in exactly one file (`stb_impl.cpp`). Your `Image.cpp` includes the headers **without** them. If you see `duplicate symbol stbi_load`, some other file defined the macros too.

---

## Part 3 — `openInDefaultViewer`

```cpp
bool openInDefaultViewer(const std::string& path) {
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\" >/dev/null 2>&1";
#endif
    return std::system(cmd.c_str()) == 0;
}
```

The `#if` lines run in the **preprocessor**, before compiling, so only your OS's branch is in the program. In Codespaces or over SSH there's no display. The function returns `false`, `main` prints a warning, and that's fine.

---

## Sample Run

```text
$ ./build/imgtool images/Hulda.png out.png -b 20 --grayscale --open
INPUT   : images/Hulda.png
OUTPUT  : out.png
ORDER   : brighten(20) grayscale

Loaded: Image(546 x 640)
Warning: 'brighten(20)' is parsed but not applied yet (that's P03)
Applied: grayscale
Saved: out.png
```

`./build/imgtool images/Hulda.jpg out.png -g` should match `images/HuldaBW.png` **exactly**, pixel for pixel. (It was made from the `.jpg`. Starting from `Hulda.png` looks the same but differs slightly, because JPEG compression changed the source pixels.)

Error runs to try: `images/nope.png out.png` (load throws), `images/Hulda.png /no/such/dir/out.png -g` (save throws), plus every row of the error table.

---

## What to Submit

`src/Args.cpp`, `src/Image.cpp`, `src/Platform.cpp`, and a short section in your README with 5 example commands (at least 2 that produce errors). Don't commit `build/`.

---

## Rubric

> _The program must build. If it doesn't, it's graded as a failure._

| Category                     | Points  | Details                                                                        |
| ---------------------------- | ------- | ------------------------------------------------------------------------------ |
| **Builds clean**             | 10      | No errors, no warnings                                                         |
| **Args: options**            | 15      | All options, long and short, space and `=` forms, negative values, repeats     |
| **Args: errors**             | 15      | Every case in the table: specific message + usage, exit 1                      |
| **Args: print**              | 5       | Matches the format                                                             |
| **Image: basics**            | 10      | Constructor validation, computed width/height, `at` bounds check, `operator<<` |
| **Image: load (RAII)**       | 15      | `unique_ptr` with `stbi_image_free`; throws on failure; pixels correct         |
| **Image: save**              | 10      | Clamps; PNG/JPG/BMP by extension; throws on failure                            |
| **Image: grayscale**         | 5       | `Hulda.jpg -g` matches `HuldaBW.png` exactly                                   |
| **openInDefaultViewer**      | 5       | All three platforms via `#if defined(...)`                                     |
| **Code quality**             | 10      | Helpers in an unnamed namespace, no dead code, consistent style                |
| **Total**                    | **100** |                                                                                |

### Deductions

| Issue                                                             | Penalty   |
| ----------------------------------------------------------------- | --------- |
| `Image` prints errors or calls `exit` instead of throwing         | −10       |
| Manual `stbi_image_free` instead of RAII                          | −10       |
| `argv[3]`-style indexing without a bounds check                   | −10       |
| CLI library used                                                  | −20       |
| Does not build on the grader's machine                            | up to −50 |
