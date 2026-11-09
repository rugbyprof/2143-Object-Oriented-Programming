<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: P03
name: P03
title: Args Parser
description: Command-line argument parser for imgtool, with FTXUI error messages
category: Assignments
date_due:
  month: '11'
  day: '23'
  year: 2026
  hour: 11
```

</details>


# P03 — Command-Line Args Parser

## Overview

In P02 you hard-coded two things: the input/output filenames came straight from `argv[1]` and `argv[2]`, and the only operation was grayscale. That works for a demo, but a real tool needs to accept options.

Your job in P03 is to build the `Args` component that `imgtool` will eventually use. You are **not** doing any image processing here. You are building the configuration layer: read raw command-line tokens, validate them, and package the result into a clean object that the rest of the program can query.

The next program plugs your `Args` parser directly into your P02 image code, so build it carefully.

---

## Project Structure

```
P03/
├── README.md
├── CMakeLists.txt            ← build recipe (provided, downloads FTXUI)
├── src/
│   ├── main.cpp              ← do not modify (calls parse and print)
│   ├── Args.h                ← class declaration (data members provided)
│   └── Args.cpp              ← your implementation goes here
├── docs/
│   ├── factory.md            ← design discussion: constructor vs factory
│   └── solution.cpp          ← reference solution (look after you attempt it)
└── classroom_examples/
    ├── args_ex1.cpp          ← annotated sketch of what NOT to do
    └── args_ex2.cpp          ← annotated factory pattern skeleton
```

---

## Starter Code

`src/main.cpp` is given and should not be modified. It builds as soon as you start, and it does something useful once `Args.cpp` is filled in.

```cpp
#include "Args.h"

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
    args.print();
    return 0;
}
```

`src/Args.h` gives you the class skeleton with all data members defined. Fill in the implementation in `src/Args.cpp`. It already includes the FTXUI headers, so you can bring over your `printLine` helper from P02.

---

## Build & Run

This project builds with **CMake**, exactly like P02. If your P02 builds, this will too. If not, go back to P01's [SETUP.md](../P01/SETUP.md) and [CMake_Basics.md](../P01/CMake_Basics.md).

Run these from the `P03/` folder:

```bash
# 1) Configure (once, or after editing CMakeLists.txt)
cmake -S . -B build              # macOS / Linux
cmake -S . -B build -G Ninja     # Windows (MSYS2)

# 2) Build (every time you change a .cpp or .h)
cmake --build build

# 3) Run with valid input
./build/imgtool in.png out.png --grayscale --brighten 20

# Run with an invalid option to test your error handling
./build/imgtool in.png out.png --graycale
```

On Windows, run `.\build\imgtool.exe` instead of `./build/imgtool`.

This time there are **two** `.cpp` files. `CMakeLists.txt` compiles both and links them into one program:

```cmake
add_executable(imgtool src/main.cpp src/Args.cpp)
```

The files named on the command line (`in.png`, `out.png`) don't have to exist. P03 only checks that the names *look* like image files.

---

## Program Usage Requirements

Your tool will be called like this:

```bash
./build/imgtool <input_image> <output_image> [options]
```

The first two positional arguments are required:

- `input_image` must end in a recognized image extension: `.png`, `.jpg`, `.jpeg`, `.bmp`, `.ppm`
- `output_image` has the same extension requirement

Everything after that is optional flags and options.

---

## Required Options

### Flags (no value required)

| Long form     | Short form | Description          |
| ------------- | ---------- | -------------------- |
| `--grayscale` | `-g`       | Convert to grayscale |
| `--blur`      | `-l`       | Apply blur filter    |
| `--flipH`     | `-h`       | Flip horizontally    |
| `--flipV`     | `-v`       | Flip vertically      |

> Note: `--blur` uses `-l` (not `-b`). Yes, it's a weird letter. Life is weird.

### Options with values

| Long form      | Short form | Value   | Constraint            |
| -------------- | ---------- | ------- | --------------------- |
| `--brighten N` | `-b N`     | integer | N ∈ [-255, 255]       |
| `--rotate N`   | `-r N`     | integer | N ∈ {0, 90, 180, 270} |

---

## Accepted Token Formats

Your parser must accept both of these styles:

```bash
--brighten 20        # value as the next token
--brighten=20        # value joined with =
```

Both must work for `--brighten` and `--rotate`. Short forms take a space:

```bash
-b 20
-r 90
```

**Negative values are legal.** `--brighten -20` must work, even though `-20` starts with a dash. When you check whether the next token "looks like another option," a dash followed by a digit is a number, not an option.

### Extra Credit: grouped short flags

`-glhv` should behave like `-g -l -h -v`. Only valid when all grouped characters are flags (no values).

---

## Error Rules

If anything is wrong, your parser must:

1. Stop parsing immediately
2. Print a helpful, **colored** error message to `std::cerr` using FTXUI (see [Error Output](#error-output-ftxui))
3. Print a usage line
4. Exit with a non-zero status

### Cases you must handle

**Missing required positional args**

```bash
./build/imgtool in.png
# Error: output file is required
```

**Unknown option**

```bash
./build/imgtool in.png out.png --graycale
# Error: unknown option '--graycale'
```

**Missing option value**

```bash
./build/imgtool in.png out.png --brighten
# Error: '--brighten' requires an integer value
```

**Value looks like another option**

```bash
./build/imgtool in.png out.png --brighten --blur
# Error: '--brighten' expected a value but got option '--blur'
```

**Invalid integer format**

```bash
./build/imgtool in.png out.png --brighten twenty
# Error: invalid integer for '--brighten': 'twenty'
```

**Out of range**

```bash
./build/imgtool in.png out.png --brighten 999
# Error: '--brighten' must be in [-255, 255]
```

**Invalid rotate value**

```bash
./build/imgtool in.png out.png --rotate 45
# Error: '--rotate' must be one of {0, 90, 180, 270}
```

Your wording doesn't have to match exactly, but each message must say **what** was wrong and **which** option or file caused it.

---

## Whitespace and Quoting

Your program receives arguments already split by the shell.

- `--brighten 20` → two tokens, always, regardless of spacing in the shell
- `--brighten=20` → one token; your parser splits it on `=`
- Filenames with spaces must be quoted by the user (`"my photo.png"`). The shell hands you the whole name as one token, so you don't need to do anything special.

---

## Output Requirements

### Success output

If parsing succeeds, `print()` writes plain text to `std::cout`:

```
INPUT  : in.png
OUTPUT : out.png
FLAGS  : grayscale blur flipH
PARAMS : brighten=20 rotate=90
```

Only print flags and params that were actually set. If no flags were given, `FLAGS  :` prints with nothing after the colon. Keep this output plain (no color) so it can be checked exactly.

### Error output (FTXUI)

If parsing fails, print two lines to `std::cerr`, colored with FTXUI exactly like the P02 messages:

```
Error: <message>
Usage: ./imgtool <input_image> <output_image> [options]
```

Use the `printLine` helper from P02 (the second argument sends it to `std::cerr`). For example, with `Error:` in red and the usage text in blue:

```cpp
[[noreturn]] void error(const std::string& msg) {
    printLine(hbox({
        text("Error: ") | color(Color::Red) | bold,
        text(msg),
    }), std::cerr);
    printLine(hbox({
        text("Usage: ") | color(Color::Red),
        text("./imgtool <input_image> <output_image> [options]") | color(Color::Blue),
    }), std::cerr);
    std::exit(1);
}
```

`[[noreturn]]` tells the compiler this function never returns (it always calls `std::exit`). `std::exit` needs `#include <cstdlib>`.

---

## Design Requirements

### A) An `Args` type

Your `Args` must store:

- `std::string input, output`: positional args
- `bool grayscale, blur, flipH, flipV`: flags
- `bool use_brighten; int brighten`: valued option + presence flag
- `bool use_rotate; int rotate`: valued option + presence flag

### B) A parsing method

You must provide **one** of these interfaces:

**Option 1 (recommended): static factory method**

```cpp
static Args parse(int argc, char* argv[]);
```

**Option 2: parsing constructor**

```cpp
Args(int argc, char* argv[]);
```

You choose. Be prepared to justify your choice. See [docs/factory.md](./docs/factory.md) for the full design discussion.

> The provided `main.cpp` calls `Args::parse`. If you pick Option 2, you may change that one line of `main.cpp` to `Args args(argc, argv);`.

---

## Implementation Hints

Helper functions that will make your life easier:

```cpp
// Returns true if the filename ends in a known image extension.
bool isImageFile(const std::string& filename);

// Splits "--brighten=20" into ("--brighten", "20").
// Returns ("token", "") when there is no '='.
std::pair<std::string, std::string> splitEq(const std::string& token);

// Returns true if s begins with prefix.
bool startsWith(const std::string& s, const std::string& prefix);

// Returns true for "--blur" or "-g", false for "-20" (a negative number).
bool looksLikeOption(const std::string& s);
```

For converting strings to integers, use `std::stoi`, wrapped in a try/catch. It throws `std::invalid_argument` for non-numeric input and `std::out_of_range` for overflow.

You may **not** use external CLI parsing libraries (no `getopt`, no `cxxopts`, no Boost.ProgramOptions).

---

## Submission Requirements

Submit:

- `src/Args.h`
- `src/Args.cpp`
- `src/main.cpp` (unchanged from starter is fine)
- A short section in your `README.md` describing:
  - how to build
  - all supported options
  - 5 example commands (at least 2 that trigger errors)

Don't commit the `build/` folder or the program it makes.

---

## Notes

- Do not add image processing here. Keep `main.cpp` as a pure parse-and-print driver.
- The next program takes your `Args` class and wires it into your P02 image code.
- Your code must build with the provided `CMakeLists.txt` with **no errors and no warnings**.

---

## Rubric

> _The program must build. If it doesn't, it's graded as a failure._

| Category                 | Points  | Details                                                                                             |
| ------------------------ | ------- | --------------------------------------------------------------------------------------------------- |
| **Positional args**      | 10      | Input and output parsed and validated (extension check)                                             |
| **Flags**                | 15      | All four flags work, both long and short forms                                                      |
| **Valued options**       | 20      | `--brighten` and `--rotate` parse correctly in space form, including negative brighten values       |
| **`--opt=value` format** | 10      | `--brighten=20` and `--rotate=90` work without a space                                              |
| **Error messages**       | 20      | All 7 error cases produce clear, specific messages + usage line, colored with FTXUI, on `std::cerr` |
| **Range checking**       | 15      | Brighten [-255,255] and rotate {0,90,180,270} enforced                                              |
| **Class design**         | 10      | Clean packaging; private constructor or equivalent; `print()` output matches spec                   |
| **Total**                | **100** |                                                                                                     |

### Extra Credit (up to +10)

| Option                                                            | Points |
| ----------------------------------------------------------------- | ------ |
| Grouped short flags: `-glhv`                                      | +5     |
| Typo suggestion for unknown options (edit distance ≤ 2)           | +5     |
| Collect all errors and print them all instead of failing on first | +5     |

### Deductions

| Issue                                                              | Penalty     |
| ------------------------------------------------------------------ | ----------- |
| Does not build on the grader's machine                             | up to −50   |
| Segfault or undefined behavior on any valid input                  | −20         |
| Hardcoded index access (`argv[3]`) without bounds check            | −10         |
| Raw ANSI escape codes (`"\033[31m"`) or termcolor instead of FTXUI | −10         |
| Missing usage line on error output                                 | −5 per case |
