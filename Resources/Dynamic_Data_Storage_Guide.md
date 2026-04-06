# Storing Dynamic Heterogeneous Data in Modern C++

A progression from "I need a key-value store" to "I need a key-value store where the values can be different types."

This guide uses a command-line argument parser as the running example throughout, because it's a natural problem that pushes you through each solution in order.

---

## The Problem

You're building a parser. Every argument has a name and a value. Simple enough — until the values aren't all the same type:

| Flag          | Value type |
| ------------- | ---------- |
| `--grayscale` | `bool`     |
| `--brighten`  | `int`      |
| `--output`    | `string`   |

A `map<string, int>` won't hold all three. This is the core tension that drives everything below.

---

## Stage 1: `std::map` — Key/Value With a Fixed Type

`std::map` is an ordered key-value store backed by a balanced BST. `std::unordered_map` is the hash-table version — same API, faster lookup, no ordering.

```cpp
#include <map>
#include <unordered_map>

std::map<std::string, int> scores;
scores["alice"] = 95;
scores["bob"]   = 87;

// Access
std::cout << scores["alice"];       // 95 — creates entry if missing!
std::cout << scores.at("alice");    // 95 — throws if missing (safer)

// Check before access
if (scores.count("alice"))          // 0 or 1, reads like bool
    std::cout << scores["alice"];

if (scores.contains("alice"))       // C++20, most readable
    std::cout << scores["alice"];
```

### Iteration — three styles

```cpp
// C++11 range-for with pair
for (const auto& pair : scores)
    std::cout << pair.first << " : " << pair.second << "\n";

// C++17 structured bindings — preferred
for (const auto& [name, score] : scores)
    std::cout << name << " : " << score << "\n";
```

Structured bindings (`[name, score]`) are the modern habit. Equivalent to Python's `for k, v in d.items()`.

### The wall you hit

Works perfectly — until you need to store `bool`, `int`, and `string` in the same map. A `map<string, int>` can't hold a `string` value. You need the value type to vary.

---

## Aside: `using` — Type Aliases

Before going further, the examples below use `using` in a way you may not have seen:

```cpp
using ArgVal = std::variant<bool, int, std::string>;
```

This is a **type alias** — it gives a long or complex type a shorter, more meaningful name. Every place you write `ArgVal`, the compiler reads `std::variant<bool, int, std::string>`.

### `using` vs `typedef`

C++11 introduced `using` for aliases. Before that, `typedef` was the only option:

```cpp
// Old (typedef) — type and name are in awkward order
typedef std::variant<bool, int, std::string> ArgVal;
typedef std::vector<std::vector<Pixel>>      Grid;

// Modern (using) — reads left to right like an assignment
using ArgVal = std::variant<bool, int, std::string>;
using Grid   = std::vector<std::vector<Pixel>>;
```

`using` is strictly preferred in modern C++ — more readable, and unlike `typedef` it works cleanly with templates.

### Three distinct meanings of `using`

This is where students get confused — the word `using` does three different things depending on context:

```cpp
// 1. Namespace shortcut — "bring everything from std into scope"
using namespace std;

// 2. Specific name import — "bring just this one name into scope"
using std::string;
using std::cout;

// 3. Type alias — "give this type a new name"
using ArgVal = std::variant<bool, int, std::string>;
using Row    = std::vector<Pixel>;
using Grid   = std::vector<Row>;       // aliases can build on each other
```

`using namespace std` and `using std::string` are about _scope_. `using ArgVal = ...` is about _naming a type_. Same keyword, different jobs.

### Is it creating an ADT?

Sort of — but not in the full OOP sense. A type alias is a **rename**, not a new type. The compiler treats `ArgVal` and `std::variant<bool, int, std::string>` as identical. You get no new methods, no encapsulation, no invariants.

A `struct` or `class` creates a true new type with its own behavior:

```cpp
// Alias — just a rename, no new behavior
using ArgVal = std::variant<bool, int, std::string>;

// True new type — has its own methods and invariants
struct ArgVal {
    std::variant<bool, int, std::string> value;
    bool validate() const { ... }
};
```

That said, a well-chosen alias does make code read like a domain model. `Grid` reads better than `std::vector<std::vector<Pixel>>` everywhere it appears. That's real value even without true encapsulation.

### Practical rule

Use `using` aliases when:

- A type name is long and appears many times (`Grid`, `Row`, `ArgVal`)
- The full type name obscures intent
- You want to change the underlying type in one place later

Don't use them to hide complexity you should actually understand — `using Magic = void*` is obfuscation, not clarity.

---

## Stage 2: `std::variant` — A Type-Safe Union

### c++17

`std::variant<A, B, C>` holds exactly one value that is either type `A`, `B`, or `C`. The compiler knows all the possible types. Think of it as a union that remembers what it's storing.

```cpp
#include <variant>

using ArgVal = std::variant<bool, int, std::string>;

ArgVal v1 = true;
ArgVal v2 = 42;
ArgVal v3 = std::string("out.png");
```

### Reading the value back

```cpp
// Option 1: get by type — throws std::bad_variant_access if wrong type
int n = std::get<int>(v2);

// Option 2: check first
if (std::holds_alternative<int>(v2))
    std::cout << std::get<int>(v2);

// Option 3: std::visit — handles all types in one shot
std::visit([](const auto& val) {
    std::cout << val;   // works for bool, int, string
}, v2);
```

`std::visit` with a generic lambda is the idiomatic way to print or process a variant without caring which type is active.

### Combining with a struct

```cpp
struct ArgDef {
    ArgVal                     value;
    ArgVal                     defaultVal;
    std::optional<ArgVal>      min;       // nullopt for bool/string
    std::optional<ArgVal>      max;
    std::vector<ArgVal>        validSet;  // {0,90,180,270} for --rotate
};

std::map<std::string, ArgDef> registry;

registry["--grayscale"] = { false, false };
registry["--brighten"]  = { 0, 0, ArgVal(-255), ArgVal(255) };
registry["--rotate"]    = { 0, 0, std::nullopt, std::nullopt, {0,90,180,270} };
```

`std::optional<T>` means "there may or may not be a value of type T." More honest than a sentinel value like `-999` to mean "no minimum."

### Overloading `<<` for ArgDef

You can teach the map to print itself cleanly:

```cpp
std::ostream& operator<<(std::ostream& os, const ArgVal& v) {
    std::visit([&os](const auto& val) { os << val; }, v);
    return os;
}

std::ostream& operator<<(std::ostream& os, const ArgDef& def) {
    os << "value=" << def.value << " default=" << def.defaultVal;

    if (def.min && def.max)
        os << " range=[" << *def.min << ", " << *def.max << "]";

    if (!def.validSet.empty()) {
        os << " valid={";
        for (size_t i = 0; i < def.validSet.size(); i++) {
            if (i > 0) os << ", ";
            os << def.validSet[i];
        }
        os << "}";
    }
    return os;
}

// Now the whole registry prints itself:
for (const auto& [flag, def] : registry)
    std::cout << flag << " -> " << def << "\n";
```

Output:

```
--brighten  -> value=0 default=0 range=[-255, 255]
--grayscale -> value=false default=false
--rotate    -> value=0 default=0 valid={0, 90, 180, 270}
```

### When to use `variant`

- You know all possible types at compile time
- You want the compiler to catch type mismatches
- You want zero overhead (no heap allocation, no RTTI)

---

## Stage 3: `std::any` — Fully Dynamic, No Type Constraints

`std::any` can hold a value of literally any type. The compiler imposes no constraints. You recover the value with `any_cast`, which throws at runtime if you guess the type wrong.

```cpp
#include <any>

std::map<std::string, std::any> args;
args["--brighten"]  = 20;
args["--grayscale"] = true;
args["--output"]    = std::string("out.png");

// Extracting
int b   = std::any_cast<int>(args["--brighten"]);    // ok
bool g  = std::any_cast<bool>(args["--grayscale"]);  // ok
int bad = std::any_cast<int>(args["--output"]);      // throws std::bad_any_cast
```

### The honest assessment

`std::any` doesn't eliminate types — it defers the type error from compile time to runtime. You still owe the type system a debt; `any` just lets you pay it later, usually at the worst possible time (a crash in production).

The analogy for students: using `std::any` everywhere is the type-system equivalent of making everything a global variable. Both are real tools that exist for real reasons. Both get abused because they make hard problems _feel_ solved before they actually are.

### When `std::any` is actually justified

| Use case             | Why `any` fits                                                            |
| -------------------- | ------------------------------------------------------------------------- |
| Plugin systems       | Types are loaded from `.so` files at runtime — unknowable at compile time |
| Scripting bridges    | Python/Lua decide the type, not C++                                       |
| Generic event queues | Heterogeneous payloads registered by external handlers                    |
| Type-erased caches   | Storing computed results of unknown type by key                           |

The tell for unjustified `std::any`: **if you know the types at compile time and are using `any` to avoid writing them down, that's the shortcut.** For a parser whose values are always `bool`, `int`, or `string`, `variant` is more honest.

### `std::any` vs `std::variant` — the summary

|                             | `std::variant`         | `std::any`               |
| --------------------------- | ---------------------- | ------------------------ |
| Types known at compile time | Yes — you list them    | No — fully open          |
| Type error timing           | Compile time           | Runtime                  |
| Overhead                    | None (stack allocated) | Heap allocation possible |
| Use when                    | Closed set of types    | Genuinely unknown types  |

---

## Stage 4: nlohmann JSON — Data-Driven and Human-Readable

If `variant` is "type-safe heterogeneous storage" and `any` is "anything goes," JSON is "heterogeneous storage that also lives in a file." The argument definitions themselves become data — no recompilation needed to add a new flag.

```cpp
#include <nlohmann/json.hpp>
using json = nlohmann::json;

json registry = {
    {"--grayscale", {{"type","bool"},   {"default", false}}},
    {"--brighten",  {{"type","int"},    {"default", 0}, {"min",-255}, {"max",255}}},
    {"--rotate",    {{"type","int"},    {"default", 0}, {"valid",{0,90,180,270}}}},
    {"--output",    {{"type","string"}, {"default", "out.png"}}}
};
```

Or load it from a file:

```cpp
std::ifstream f("args.json");
json registry = json::parse(f);
```

### Iteration

```cpp
for (auto& [flag, def] : registry.items())
    std::cout << flag << " : " << def.dump() << "\n";
```

### Validation with JSON

```cpp
void validate(const std::string& flag, int val, const json& registry) {
    const json& def = registry[flag];

    if (def.contains("min") && def.contains("max")) {
        int lo = def["min"], hi = def["max"];
        if (val < lo || val > hi)
            std::cerr << "Error: " << flag << " must be in ["
                      << lo << ", " << hi << "]\n";
    }

    if (def.contains("valid")) {
        bool found = false;
        for (int v : def["valid"])
            if (v == val) { found = true; break; }
        if (!found)
            std::cerr << "Error: " << flag << " got invalid value\n";
    }
}
```

### When to use JSON

- You want to define args in a config file without recompiling
- Multiple tools share the same argument schema
- You're already using JSON elsewhere (web APIs, config files)
- You want non-programmers to be able to edit the arg definitions

### The tradeoff

External dependency (though nlohmann is header-only — just drop in one `.hpp` file). Type checking is entirely runtime. The JSON library's error messages can be cryptic. But the flexibility and readability are hard to beat for configuration-heavy programs.

---

## Choosing the Right Tool

| Situation                                           | Reach for                             |
| --------------------------------------------------- | ------------------------------------- |
| All values are the same type                        | `std::map<string, T>`                 |
| Small, fixed set of possible types                  | `std::variant`                        |
| Types truly unknown at compile time                 | `std::any`                            |
| Config lives in a file / schema shared across tools | nlohmann JSON                         |
| Teaching the concept, fewest moving parts           | struct + `std::string` for everything |

---

## A Note on C++ Then vs. Now

Pre-C++11, none of the above existed in standard form. The community cobbled together `boost::variant`, `boost::any`, and home-grown JSON parsers. Strings were `char*` and `strcmp`. Iteration over a map looked like:

```cpp
for (std::map<std::string,int>::iterator it = m.begin(); it != m.end(); ++it)
    std::cout << it->first << " : " << it->second << "\n";
```

C++11 gave us range-for and `auto`. C++17 gave us `variant`, `any`, `optional`, and structured bindings. C++20 gave us `contains`, `std::format`, and concepts. The language students learn today is substantially different from what was being written in 2003 — and substantially better.

If a textbook or course still teaches `char arrays`, `strcmp`, and manual `new`/`delete` as the primary approach, it is teaching 1998 C++ in 2026. The tools above have been stable and widely supported since 2017.

---

## Feature Version Reference

| Feature                                            | Version |
| -------------------------------------------------- | ------- |
| `std::map`, `std::set`, `std::vector`, `std::list` | C++98   |
| `std::string` (usable, `==` comparisons)           | C++98   |
| `std::ostringstream`, `std::istringstream`         | C++98   |
| `std::accumulate`                                  | C++98   |
| `std::find`                                        | C++98   |
| `auto`                                             | C++11   |
| Range-based `for` loop                             | C++11   |
| `nullptr`                                          | C++11   |
| `std::unordered_map`, `std::unordered_set`         | C++11   |
| `std::array`                                       | C++11   |
| Lambdas                                            | C++11   |
| `emplace_back`                                     | C++11   |
| Smart pointers (`unique_ptr`, `shared_ptr`)        | C++11   |
| Move semantics                                     | C++11   |
| `= delete`, `= default`                            | C++11   |
| `std::optional`                                    | C++17   |
| `std::variant`                                     | C++17   |
| `std::visit`                                       | C++17   |
| `std::any`                                         | C++17   |
| Structured bindings (`auto& [k, v]`)               | C++17   |
| `if constexpr`                                     | C++17   |
| `std::filesystem` (path, stem, extension)          | C++17   |
| `std::string::starts_with`                         | C++20   |
| `std::string::contains`                            | C++20   |
| `map::contains`                                    | C++20   |
| `std::format`                                      | C++20   |
| `std::span`                                        | C++20   |
| `std::print`                                       | C++23   |
| `std::views::join_with`                            | C++23   |

### The Eras

- **C++98/03** — the painful years. Functional but verbose and unsafe.
- **C++11** — the turning point. The language became modern.
- **C++14** — small fixes and polish on top of C++11.
- **C++17** — heterogeneous types, filesystem, structured bindings. The "use Boost? no, just use stdlib" release.
- **C++20** — concepts, ranges, `format`, `span`. The "finally caught up to other languages" release.
- **C++23** — quality of life. `std::print` alone was worth the wait.

---

## Related Topics

- [Static_Keyword_Guide.md](Static_Keyword_Guide.md) — static factory methods, utility classes, static members
- `std::optional` — "a value that may or may not exist" (pairs naturally with `variant`)
- `std::visit` — the right way to process a `variant` without if/else chains
- `std::format` (C++20) — type-safe printf, finally
