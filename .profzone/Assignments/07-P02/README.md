```yaml
title: Program 2 — Args Parser
description: Command-line argument parser for imgtool
id: 07-P02
course: 2143 - Object Oriented Programming
date_assigned: 2026-03-02 12:00
date_due: 2026-03-21 11:00
points: 100
```

# Program 2 — Command-Line Args Parser

## Overview

In Program 1 you hard-coded two things: the input/output filenames came straight from `argv[1]` and `argv[2]`, and the only operation was grayscale. That works for a demo, but a real tool needs to accept options.

Your job in Program 2 is to build the `Args` component that `imgtool` will eventually use. You are not doing any image processing here — you are building the configuration layer: read raw command-line tokens, validate them, and package the result into a clean object that the rest of the program can query.

Program 3 will plug your `Args` parser directly into the image processing code from Program 1.

---

## Project Structure

```
07-P02/
├── README.md
├── src/
│   ├── main.cpp              ← do not modify (calls parse and print)
│   ├── Args.h                ← your class declaration goes here
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

`src/main.cpp` is given and should not be modified. It compiles once you implement `Args.h` and `Args.cpp`.

```cpp
#include "Args.h"

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
    args.print();
    return 0;
}
```

`src/Args.h` gives you the class skeleton with all data members defined. Fill in the implementation in `src/Args.cpp`.

---

## Build & Run

```bash
# Compile from the project root (07-P02/)
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/main.cpp src/Args.cpp -o imgtool

# Run with valid input
./imgtool in.png out.png --grayscale --brighten 20

# Run with an invalid option to test your error handling
./imgtool in.png out.png --graycale
```

---

## Program Usage Requirements

Your tool will be called like this:

```bash
./imgtool <input_image> <output_image> [options]
```

The first two positional arguments are required:

- `input_image` — must be a recognized image extension (`.png`, `.jpg`, `.jpeg`, `.bmp`, `.ppm`)
- `output_image` — same extension requirement

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

### Extra Credit: grouped short flags

`-glhv` should behave like `-g -l -h -v`. Only valid when all grouped characters are flags (no values).

---

## Error Rules

If anything is wrong, your parser must:

1. Stop parsing immediately
2. Print a helpful error message
3. Print a usage line
4. Exit with a non-zero status

### Cases you must handle

**Missing required positional args**

```bash
./imgtool in.png
# Error: output file is required
```

**Unknown option**

```bash
./imgtool in.png out.png --graycale
# Error: unknown option '--graycale'
```

**Missing option value**

```bash
./imgtool in.png out.png --brighten
# Error: '--brighten' requires an integer value
```

**Value looks like another option**

```bash
./imgtool in.png out.png --brighten --blur
# Error: '--brighten' expected a value but got option '--blur'
```

**Invalid integer format**

```bash
./imgtool in.png out.png --brighten twenty
# Error: invalid integer for '--brighten': 'twenty'
```

**Out of range**

```bash
./imgtool in.png out.png --brighten 999
# Error: '--brighten' must be in [-255, 255]
```

**Invalid rotate value**

```bash
./imgtool in.png out.png --rotate 45
# Error: '--rotate' must be one of {0, 90, 180, 270}
```

---

## Whitespace and Quoting

Your program receives arguments already split by the shell.

- `--brighten 20` → two tokens, always, regardless of spacing in the shell
- `--brighten=20` → one token; your parser splits it on `=`
- Filenames with spaces must be quoted by the user — you do not need to handle that

---

## Output Requirements

If parsing succeeds, print:

```
INPUT  : in.png
OUTPUT : out.png
FLAGS  : grayscale blur flipH
PARAMS : brighten=20 rotate=90
```

Only print flags and params that were actually set. If no flags were given, `FLAGS  :` prints with nothing after the colon.

If parsing fails, print:

```
Error: <message>
Usage: ./imgtool <input_image> <output_image> [options]
```

---

## Design Requirements

### A) An `Args` type

Your `Args` must store:

- `std::string input, output` — positional args
- `bool grayscale, blur, flipH, flipV` — flags
- `bool use_brighten; int brighten` — valued option + presence flag
- `bool use_rotate; int rotate` — valued option + presence flag

### B) A parsing method

You must provide **one** of these interfaces:

**Option 1 (recommended) — static factory method:**

```cpp
static Args parse(int argc, char* argv[]);
```

**Option 2 — parsing constructor:**

```cpp
Args(int argc, char* argv[]);
```

You choose. Be prepared to justify your choice. See [docs/factory.md](./docs/factory.md) for the full design discussion.

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
```

For converting strings to integers, use `std::stoi` — but wrap it in a try/catch. It throws `std::invalid_argument` for non-numeric input and `std::out_of_range` for overflow.

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

---

## Notes

- This is Program 2 of 4. Do not add image processing here — keep `main.cpp` as a pure parse-and-print driver.
- Program 3 will take your `Args` class and wire it into the grayscale/filter code from Program 1.
- Your code must compile with the exact command shown above, no errors, no warnings.

---

## Rubric

> _Program must compile. Or it will be considered a failure._

| Category                 | Points  | Details                                                                           |
| ------------------------ | ------- | --------------------------------------------------------------------------------- |
| **Positional args**      | 10      | Input and output parsed and validated (extension check)                           |
| **Flags**                | 15      | All four flags work, both long and short forms                                    |
| **Valued options**       | 20      | `--brighten` and `--rotate` parse correctly in both space and `=` forms           |
| **`--opt=value` format** | 10      | `--brighten=20` and `--rotate=90` work without space                              |
| **Error messages**       | 20      | All 7 error cases produce clear, specific messages + usage line                   |
| **Range checking**       | 15      | Brighten [-255,255] and rotate {0,90,180,270} enforced                            |
| **Class design**         | 10      | Clean packaging; private constructor or equivalent; `print()` output matches spec |
| **Total**                | **100** |                                                                                   |

### Extra Credit (up to +10)

| Option                                                            | Points |
| ----------------------------------------------------------------- | ------ |
| Grouped short flags: `-glhv`                                      | +5     |
| Typo suggestion for unknown options (edit distance ≤ 2)           | +5     |
| Collect all errors and print them all instead of failing on first | +5     |

### Deductions

| Issue                                                   | Penalty     |
| ------------------------------------------------------- | ----------- |
| Does not compile on grader's machine                    | up to −50   |
| Segfault or undefined behavior on any valid input       | −20         |
| Hardcoded index access (`argv[3]`) without bounds check | −10         |
| Missing usage line on error output                      | −5 per case |
